#include "game_app.hpp"

void GameApp::OnStart()
{
    Mnemos::Log(Mnemos::TRACE, "Game started");
}

void GameApp::OnUpdate(float deltaTime)
{
    Mnemos::Log(Mnemos::TRACE, "Updating");
    //std::cout << "Updating, Delta time: " << deltaTime * 1e3 << "ms\n";
}

void GameApp::OnRender()
{
    Mnemos::Log(Mnemos::TRACE, "Rendering");
}

void GameApp::OnShutdown()
{
    Mnemos::Log(Mnemos::TRACE, "Game stopped");
}