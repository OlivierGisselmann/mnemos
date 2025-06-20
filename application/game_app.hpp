#pragma once

#include <application.hpp>

class GameApp : public Mnemos::Application
{
protected:
    void OnStart() override;
    void OnUpdate(f64 deltaTime) override;
    void OnShutdown() override;
};
