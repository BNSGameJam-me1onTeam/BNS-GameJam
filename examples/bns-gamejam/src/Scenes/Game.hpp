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
    
    // ----------------------------------------
    // ステージ関係
    // ----------------------------------------
    
    Texture m_texture_background;
    Texture m_texture_nabeTop;
    Texture m_texture_nabeUnder;
    
    Vec2 m_position_nabeTop;
    Vec2 m_position_nabeUnder;
    
    GameState m_state;
    
    Stopwatch m_stopwatch;
    
    int m_countdownSeconds;
    int max_timeCount;
    
    
    // ----------------------------------------
    // 具材関係
    // ----------------------------------------

    Texture m_texture_guzai;
    
    Vec2 m_position_guzai;
    
    InputData guzai_input;
    
    Stopwatch m_stopwatch_skil;
    
    Stopwatch m_stopwatch_interval;
    
    double size_guzai;
    
    int direction_guzai;
    
    int Xborder_left_guzai;
    int Xborder_right_guzai;
    
    int hitRangeX_right;
    int hitRangeX_left;
    int hitRangeY_high;
    int hitRangeY_low;
    
    int guzai_id;
    
    int speed_guzai;
    
    int skil_timer;
    
    int skil_interval;
    
    bool skilActive = false;
    
    bool skilEnable = true;
    
    
    // ----------------------------------------
    // 器具関係
    // ----------------------------------------
    
    Texture m_texture_otama;
    
    Vec2 m_position_otama;
    
    InputData otama_input;
    
    double size_otama;
    
    double angle_otama;
    
    int direction_otama;
    
    int top_height_otama;
    int under_height_otama;
    int Xborder_left_otama;
    int Xborder_right_otama;
    
    int catchRangeX_right;
    int catchRangeX_left;
    int catchRangeY_high;
    int catchRangeY_low;
    
    int speed_otama;
    
    int scoop_JudgeHeight;
    
    int scoop_speed;
    
    
    // ----------------------------------------
    // プレイヤー関係
    // ----------------------------------------
    
    Array<Image> images_p1;
    Array<int32> delays_p1;
    Array<Texture> p1_textures;
    
    Array<Image> images_p2;
    Array<int32> delays_p2;
    Array<Texture> p2_textures;
    
    
    // ----------------------------------------
    // ミニゲーム関係
    // ----------------------------------------
    
    Texture m_texture;
    Texture p1_img;
    Texture p2_img;
    
    //bool miniGame = false;
    
    // ----------------------------------------
    // デバック関係
    // ----------------------------------------
    
    Vec2 m_position_debug;
    int speed_debug = 200;
};
