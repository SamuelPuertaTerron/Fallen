#pragma once
#include <random>

namespace FEngine
{
    class Random
    {
    public:
        // Initialize with a random seed
        static void Init()
        {
            std::random_device rd;
            s_Generator.seed(rd());
        }

        // Random integer in [min, max]
        static int Range(int min, int max)
        {
            std::uniform_int_distribution<int> dist(min, max);
            return dist(s_Generator);
        }

        // Random float in [min, max]
        static float Range(float min, float max)
        {
            std::uniform_real_distribution<float> dist(min, max);
            return dist(s_Generator);
        }

        // Random float in [0, 1]
        static float Value()
        {
            std::uniform_real_distribution<float> dist(0.0f, 1.0f);
            return dist(s_Generator);
        }

        // Random boolean (50/50)
        static bool Bool()
        {
            std::bernoulli_distribution dist(0.5);
            return dist(s_Generator);
        }

        // Random sign (-1 or +1)
        static int Sign()
        {
            return Bool() ? 1 : -1;
        }

    private:
        inline static std::mt19937 s_Generator{ std::random_device{}() };
    };
}//namespace FEngine