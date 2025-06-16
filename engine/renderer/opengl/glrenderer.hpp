#pragma once

#include <renderer/irenderer.hpp>

#include <glad/glad.h>

namespace Mnemos
{
    class GLRenderer : public IRenderer
    {
    public:
        bool Init(const SubsystemInitInfo& info) override;
        void Shutdown() override;

        void BeginFrame() override;
        void DrawFrame() override;
        void EndFrame() override;

    private:
        IWindow* mWindow = nullptr;
        InputSystem* mInput = nullptr;
        ILogger* mLogger = nullptr;

        bool mPolygonMode = false;
    };
}
