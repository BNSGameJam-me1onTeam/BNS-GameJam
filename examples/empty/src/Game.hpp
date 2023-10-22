// Game.hpp
#pragma once
#include <Siv3D.hpp>
//#include "SceneManager.hpp"

using App = SceneManager<String>;

class Game : public App::Scene
{
public:
    Game(const InitData& init);
    ~Game();

    void update() override;
    void draw() const override;

private:
    Texture m_texture;
};

