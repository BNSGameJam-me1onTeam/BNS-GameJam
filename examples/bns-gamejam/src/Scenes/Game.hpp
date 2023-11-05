// Game.hpp
#pragma once
#include "Common.hpp"
#include "Mob.hpp"

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
    Array<Texture> p1_texture;
    Array<Texture> p2_texture;
    
    Vec2 m_position_nabeTop;
    Vec2 m_position_nabeUnder;
    
    GameState m_state;
    
    Stopwatch m_stopwatch;
    
    int m_countdownSeconds;
    int max_timeCount;
    
    Mob* mob_1;
    Mob* mob_2;
    
    
    // ----------------------------------------
    // 具材関係
    // ----------------------------------------

    Texture m_texture_guzai;
    
    Vec2 m_position_guzai;
    
    InputData guzai_input;
    
    Stopwatch m_stopwatch_skill;
    
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
    
    int skill_timer;
    
    int skill_interval;
    
    int skill_interval_prev = 0;
    
    double skill_interval_len = 0;
    
    int skill_gauge_height;
    
    bool skillActive = false;
    
    bool skillEnable = true;
    
    
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
    
    Array<Image> images_miniGame;
    Array<int32> delays_miniGame;
    Array<Texture> miniGame_textures;
    
    int32 miniGame_counter;
    int32 p1_state;
    int32 p2_state;

    Texture m_texture;
    Texture p1_img;
    Texture p2_img;
    
    // パンチ音
    Array<Audio> punch;
    
    double miniGame_timeCounter;
    
    bool miniGameLoser_otama = false;
    
    
    // ----------------------------------------
    // サウンド関係
    // ----------------------------------------
    
    const Audio main_bgm{ U"bns-gamejam/sounds/game.mp3", Loop::Yes};
    const Audio mini_bgm{ U"bns-gamejam/sounds/minigame.mp3", Loop::Yes};
    const Audio countdown_se{ U"bns-gamejam/sounds/countdown.mp3"};
    const Array<Audio> skill_se = {
        Audio{U"bns-gamejam/sounds/skill_1.mp3"},
        Audio{U"bns-gamejam/sounds/skill_2.mp3"},
        Audio{U"bns-gamejam/sounds/skill_3.mp3"}
    };
    bool countdown_flag = true;
    
    // ----------------------------------------
    // デバック関係
    // ----------------------------------------
    
    Vec2 m_position_debug;
    
    int speed_debug = 200;
    
    bool debug_on = false;
};
