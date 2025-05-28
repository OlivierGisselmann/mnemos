#include "game_app.hpp"

#include <iostream>

void GameApp::OnStart()
{
    std::cout << "Game started\n";
}

void GameApp::OnUpdate(float deltaTime)
{
    std::cout << "Updating, Delta time: " << deltaTime * 1e6 << '\n';
}

void GameApp::OnRender()
{
    std::cout << "Rendering\n";
}

void GameApp::OnShutdown()
{
    std::cout << "Shutdown\n";
}