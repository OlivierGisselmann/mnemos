#pragma once

namespace mnm
{
    class Application
    {
    public:
        virtual ~Application() = default;

        void Run();

    protected:
        virtual void OnStart() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}

    private:
        bool m_running = true;
    };
}