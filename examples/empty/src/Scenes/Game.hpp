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
        MiniGame,
        Finished
    };
    
    Texture m_texture_background;
    Texture m_texture_guzai;
    Texture m_texture_otama;
    Texture m_texture_nabeTop;
    Texture m_texture_nabeUnder;
    
    Array<Image> images;
    Array<int32> delays;
    Array<Texture> guzai_textures;
    
    GameState m_state;
    
    Stopwatch m_stopwatch;
    
    int m_countdownSeconds;
    
    int speed_otama = 450;
    int speed_guzai = 360;
    
    int guzai_direction;
    
    int max_timeCount;
    
    int top_height_otama;
    
    int Xborder_left_guzai;
    int Xborder_right_guzai;
    int Xborder_left_otama;
    int Xborder_right_otama;
    
    Vec2 m_position_guzai;
    Vec2 m_position_otama;
    Vec2 m_position_nabeTop;
    Vec2 m_position_nabeUnder;

    Texture m_texture;
    bool miniGame = false;
    Texture p1_img;
    Texture p2_img;
};

