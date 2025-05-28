#pragma once

#include <application.hpp>

class GameApp : public Mnemos::Application
{
protected:
    void OnStart() override;
    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnShutdown() override;
};
