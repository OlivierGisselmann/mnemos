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
        virtual void OnShutdown() {}

    private:
        bool mRunning {true};
    };
}