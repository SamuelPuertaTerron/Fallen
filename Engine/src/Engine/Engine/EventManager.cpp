#include "Globals.h"
#include "EventManager.h"

#include <ranges>

#include <raylib/raylib.h>

#include "Window.h"

namespace FEngine
{
    void EventManager::RemoveListener(ListenerID id)
    {
        m_ListenersToRemove.insert(id);
    }

    void EventManager::ProcessRemovals()
    {
        for (auto id : m_ListenersToRemove)
        {
            m_Listeners.erase(id);
        }
        m_ListenersToRemove.clear();
    }

    void EventManager::PollEvents()
    {
        PollWindowEvents();
        PollInputEvents();
        DispatchEvents();
        ProcessRemovals();
    }

    void EventManager::DispatchEvents()
    {
        while (!m_EventQueue.empty())
        {
            std::unique_ptr<Event> ev = std::move(m_EventQueue.front());
            m_EventQueue.pop();

            for (auto& [id, listener] : m_Listeners)
            {
                if (m_ListenersToRemove.contains(id))
                    continue;

                if (listener.first == ev->Type)
                    listener.second(*ev);
            }
        }
    }

    void EventManager::PollWindowEvents()
    {
        Engine::GetInstance().GetWindow().WindowResize();
    }

    void EventManager::PollInputEvents()
    {
        // Keyboard
        for (int key = MIN_RAYLIB_KEYS; key < MAX_RAYLIB_KEYS; key++)
        {
            if (::IsKeyPressed(key))
                PushEvent<KeyEvent>(EEventType::KeyPressed, static_cast<EKeyCode>(key));

            if (::IsKeyReleased(key))
                PushEvent<KeyEvent>(EEventType::KeyReleased, static_cast<EKeyCode>(key));
        }

        // Mouse buttons
        for (int btn = MIN_RAYLIB_MOUSE; btn <= MAX_RAYLIB_MOUSE; btn++)
        {
            if (::IsMouseButtonPressed(btn))
                PushEvent<MouseButtonEvent>(EEventType::MouseButtonPressed, static_cast<EMouseButton>(btn));

            if (::IsMouseButtonReleased(btn))
                PushEvent<MouseButtonEvent>(EEventType::MouseButtonReleased, static_cast<EMouseButton>(btn));
        }

        auto mouse = ::GetMousePosition();
        PushEvent<MouseMoveEvent>(mouse.x, mouse.y);

        auto scroll = ::GetMouseWheelMoveV();
        if (scroll.x != 0 || scroll.y != 0)
            PushEvent<MouseScrollEvent>(scroll.x, scroll.y);
    }
}//namespace FEngine