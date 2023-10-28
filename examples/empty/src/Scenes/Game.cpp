// Game.cpp
#include "Game.hpp"
#include "MiniGame.hpp"

Game::Game(const InitData& init) : IScene{ init }, m_texture{ U"🐈"_emoji }
{
    p1_img = Texture{U"example/texture/{}/{}_soubi_{}.png"_fmt(!(getData().stage_id) ? U"nabe" : U"pafe", getData().p1_data.role ? U"nige" : U"seme", getData().p1_data.eqid+1)};
    p2_img = Texture{U"example/texture/{}/{}_soubi_{}.png"_fmt(!(getData().stage_id) ? U"nabe" : U"pafe", getData().p2_data.role ? U"nige" : U"seme", getData().p2_data.eqid+1)};
}

Game::~Game()
{
    Print << U"Game::~Game()";
}

void Game::update()
{
    if (MouseL.down())
    {
        //changeScene(State::Result);
    }
    if (KeyBackslash_US.down())
    {
        miniGame = true;
    }
    if(miniGame)
    {
        int32 result = game_renda(getData().p1_input.Confirm, getData().p2_input.Confirm, p1_img, p2_img);
        if(result) {
            miniGame = false;
            Print << U"Player{} Win!!"_fmt(result);
        }
        return;
    }
}

void Game::draw() const
{
    Scene::SetBackground(ColorF(0.2, 0.8, 0.6));
    if(miniGame)
    {
        return;
    }
    m_texture.drawAt(Cursor::Pos());
    
}

