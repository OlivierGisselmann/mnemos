#include "game_app.hpp"

void GameApp::OnStart()
{
    Mnemos::Log(Mnemos::TRACE, "Game started");
}

void GameApp::OnUpdate(float deltaTime)
{
    //Mnemos::Log(Mnemos::TRACE, "Updating");
}

void GameApp::OnRender()
{
    //Mnemos::Log(Mnemos::TRACE, "Rendering");
}

void GameApp::OnShutdown()
{
    Mnemos::Log(Mnemos::TRACE, "Game stopped");
}