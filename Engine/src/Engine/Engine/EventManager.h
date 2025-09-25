#pragma once
#include <queue>
#include <unordered_map>
#include <functional>
#include <set>
#include "Events.h"

namespace FEngine
{
    using EventCallback = std::function<void(const Event&)>;
    using ListenerID = size_t;

    class ListenerHandle;

    class EventManager
    {
    public:
        EventManager() = default;
        ~EventManager() = default;

        template<typename TEvent, typename... Args>
        void PushEvent(Args&&... args)
        {
            m_EventQueue.emplace(std::make_unique<TEvent>(std::forward<Args>(args)...));
        }

        template<typename TEvent>
        ListenerHandle AddListener(EEventType type, std::function<void(const TEvent&)> callback);

        void RemoveListener(ListenerID id);
        void ProcessRemovals(); // New method to process deferred removals

        void PollEvents();
        void DispatchEvents();

    private:
        void PollWindowEvents();
        void PollInputEvents();

        std::queue<std::unique_ptr<Event>> m_EventQueue;
        std::unordered_map<ListenerID, std::pair<EEventType, EventCallback>> m_Listeners;
        std::set<ListenerID> m_ListenersToRemove; // New set to track listeners to remove
        ListenerID m_NextID = 0;

        const int MIN_RAYLIB_KEYS = 32;
        const int MAX_RAYLIB_KEYS = 349;
        const int MIN_RAYLIB_MOUSE = 0;
        const int MAX_RAYLIB_MOUSE = 6;
    };

    class ListenerHandle
    {
    public:
        ListenerHandle() = default;
        ListenerHandle(EventManager* manager, ListenerID id) : m_Manager(manager), m_ID(id) {}
        ~ListenerHandle() { if (m_Manager) m_Manager->RemoveListener(m_ID); }

        // Prevent copying
        ListenerHandle(const ListenerHandle&) = delete;
        ListenerHandle& operator=(const ListenerHandle&) = delete;

        // Allow moving
        ListenerHandle(ListenerHandle&& other) noexcept : m_Manager(other.m_Manager), m_ID(other.m_ID)
        {
            other.m_Manager = nullptr;
        }

        ListenerHandle& operator=(ListenerHandle&& other) noexcept
        {
            if (this != &other)
            {
                if (m_Manager)
                    m_Manager->RemoveListener(m_ID);
                m_Manager = other.m_Manager;
                m_ID = other.m_ID;
                other.m_Manager = nullptr;
            }
            return *this;
        }

    private:
        EventManager* m_Manager = nullptr;
        ListenerID m_ID;
    };

    template<typename TEvent>
    ListenerHandle EventManager::AddListener(EEventType type, std::function<void(const TEvent&)> callback)
    {
        ListenerID id = m_NextID++;
        m_Listeners[id] = std::make_pair(type, [callback](const Event& e) {
            callback(static_cast<const TEvent&>(e));
            });
        return ListenerHandle(this, id);
    }
}//namespace FEngine