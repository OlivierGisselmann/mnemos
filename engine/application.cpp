#include "application.hpp"

#include <iostream>
#include <chrono>

namespace mnm
{
    void Application::Run()
    {
        OnStart();

        auto last = std::chrono::high_resolution_clock::now();

        while(m_running)
        {
            auto now = std::chrono::high_resolution_clock::now();
            float delta = std::chrono::duration<float>(now - last).count();
            last = now;

            OnUpdate(delta);
            OnRender();
        }
    }
}
