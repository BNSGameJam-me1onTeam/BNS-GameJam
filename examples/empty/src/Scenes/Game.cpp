// Game.cpp
#include "Game.hpp"

Game::Game(const InitData& init) : IScene{ init }, m_texture{ U"🐈"_emoji }, m_state{ GameState::Countdown }, m_countdownSeconds{ 3 }
{
    // フォントの設定
    FontAsset::Register(U"CountDownFont", 160, Typeface::Heavy);
    FontAsset::Register(U"StopwatchFont", 30, Typeface::Heavy);
    
    // 画像の読み込み
    // TextureAsset::Register(U"guzai", U"example/windmill.png");
    // TextureAsset::Register(U"otama", U"example/siv3d-kun.png", TextureDesc::Mipped);
    
    m_texture_guzai = Texture(U"images/food_toufu_pack.png");
    m_texture_otama = Texture(U"images/cooking_otama.png");

    // 画像の初期位置
    m_position_guzai = Vec2(300, 300);
    m_position_otama = Vec2(500, 300);
    
    m_stopwatch.start();
    
    Print << U"Game::Game(aaaaa)";
}

Game::~Game()
{
    Print << U"Game::~Game()";
}

void Game::update()
{
    if (m_state == GameState::Countdown)
    {
        if (m_stopwatch.ms() >= 1000)
        {
            m_countdownSeconds--;
            m_stopwatch.restart();
        }
        if (m_countdownSeconds <= 0)
        {
            m_state = GameState::StartPlaying;
            m_stopwatch.restart();
        }
    }
    else if (m_state == GameState::StartPlaying)
    {
        if (m_stopwatch.ms() >= 1000)
        {
            m_state = GameState::Playing;
            m_stopwatch.restart();
        }
    }
    else if (m_state == GameState::Playing)
    {
        if (MouseL.down())
        {
            changeScene(State::Result);
        }

        if (m_stopwatch.s() >= 90)  // とりあえず1分30秒
        {
            m_state = GameState::Finished;
            m_stopwatch.restart();
        }
        
            // 1つ目の画像の位置更新 (ADキーで操作)
            if (KeyA.pressed() && m_position_guzai.x > 0)
            {
                m_position_guzai.x -= 5;
            }
            if (KeyD.pressed() && m_position_guzai.x < Scene::Width() - m_texture_guzai.width())
            {
                m_position_guzai.x += 5;
            }

            // 2つ目の画像の位置更新 (矢印キーで操作)
            if (KeyUp.pressed() && m_position_otama.y > 0)
            {
                m_position_otama.y -= 5;
            }
            if (KeyDown.pressed() && m_position_otama.y < Scene::Height() - m_texture_otama.height())
            {
                m_position_otama.y += 5;
            }
            if (KeyLeft.pressed() && m_position_otama.x > 0)
            {
                m_position_otama.x -= 5;
            }
            if (KeyRight.pressed() && m_position_otama.x < Scene::Width() - m_texture_otama.width())
            {
                m_position_otama.x += 5;
                    }
    }
    else if (m_state == GameState::Finished)
    {
        if (m_stopwatch.ms() >= 1000)
        {
            changeScene(State::Result);
            m_stopwatch.restart();
        }
    }
}

void Game::draw() const
{
    Scene::SetBackground(ColorF(0.2, 0.8, 0.6));
    m_texture.drawAt(Cursor::Pos());
    
    // 画像の描画
    m_texture_guzai.scaled(0.5).drawAt(m_position_guzai);
    m_texture_otama.scaled(1.5).drawAt(m_position_otama);

    if (m_state == GameState::Countdown)
    {
        FontAsset(U"CountDownFont")(m_countdownSeconds).drawAt(Scene::Center(), Palette::Red);
    }
    else if (m_state == GameState::StartPlaying)
    {
        FontAsset(U"CountDownFont")(U"GO").drawAt(Scene::Center(), Palette::Red);
    }
    else if (m_state == GameState::Playing)
    {
        FontAsset(U"StopwatchFont")(U"Time: {}"_fmt(90 - m_stopwatch.s())).draw(Vec2(Scene::Width() - 150, 20), Palette::Black);
    }
    else if (m_state == GameState::Finished)
    {
        FontAsset(U"CountDownFont")(U"Finish !!!").drawAt(Scene::Center(), Palette::Red);
    }
}


