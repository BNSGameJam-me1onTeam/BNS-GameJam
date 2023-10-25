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
    enum class GameState
    {
        Countdown,
        StartPlaying,
        Playing,
        Finished
    };
    
    Texture m_texture;
    Texture m_texture_guzai;
    Texture m_texture_otama;
    
    GameState m_state;
    
    Stopwatch m_stopwatch;
    
    int m_countdownSeconds;
    
    Vec2 m_position_guzai;
    Vec2 m_position_otama;
};

