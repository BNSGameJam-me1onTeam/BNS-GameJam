// Game.hpp
#pragma once
#include "Common.hpp"

class Game : public App::Scene
{
public:
    Game(const InitData& init);
    ~Game();

    void update() override;
    void draw() const override;

private:
    Texture m_texture;
    bool miniGame = false;
    Texture p1_img;
    Texture p2_img;
};

