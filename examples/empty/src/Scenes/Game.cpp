// Game.cpp
#include "Game.hpp"

Game::Game(const InitData& init) : IScene{ init }, m_texture{ U"🐈"_emoji }
{
    Print << U"Game::Game()";
}

Game::~Game()
{
    Print << U"Game::~Game()";
}

void Game::update()
{
    if (MouseL.down())
    {
        changeScene(State::Result);
    }
}

void Game::draw() const
{
    Scene::SetBackground(ColorF(0.2, 0.8, 0.6));
    m_texture.drawAt(Cursor::Pos());
}

