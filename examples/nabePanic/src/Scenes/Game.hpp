#pragma once
#include "Common.hpp"
#include "Mob.hpp"
#include "Ingredient.hpp"
#include "Tableware.hpp"

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
        
    Ingredient* ingredient;


    // ----------------------------------------
    // 食器関係
    // ----------------------------------------

	Tableware* tableware;
        
        
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
        
    const Audio main_bgm{ Resource(U"nabePanic/sounds/game.mp3"), Loop::Yes};
    const Audio mini_bgm{ Resource(U"nabePanic/sounds/minigame.mp3"), Loop::Yes};
    const Audio countdown_se{ Resource(U"nabePanic/sounds/countdown.mp3")};
        
    // ----------------------------------------
    // デバック関係
    // ----------------------------------------
        
    Vec2 m_position_debug;
        
    int speed_debug = 200;
        
    bool debug_on = false;
};
