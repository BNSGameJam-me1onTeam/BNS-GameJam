#include <Siv3D.hpp>
#include "Game.hpp"

Game::Game(const InitData& init) : IScene{ init }, m_state{ GameState::Countdown }, m_countdownSeconds{ 3 }{
    // 各種値の設定
    max_timeCount = 60;
    
    top_height_otama = 50;
    
    Xborder_left_guzai = 240;
    Xborder_right_guzai = 1050;
    Xborder_left_otama = 240;
    Xborder_right_otama = 1050;
    
    miniGame_counter = 10;
    miniGame_timeCounter = 0.0;
    
    // フォントの設定
    FontAsset::Register(U"CountDownFont", 160, Typeface::Heavy);
    FontAsset::Register(U"StopwatchFont", 30, Typeface::Heavy);
    
    // 画像の読み込み
    m_texture_background = Texture(U"bns-gamejam/images/IMG_0543.png");
    m_texture_otama = Texture(U"bns-gamejam/images/IMG_0542.png");
    m_texture_nabeTop = Texture(U"bns-gamejam/images/nabe_top.png");
    m_texture_nabeUnder = Texture(U"bns-gamejam/images/TestOden.png");
    
    for (auto i : step(3))
    {
        p1_texture << Texture{U"bns-gamejam/images/nabe/{}_{}_{}.png"_fmt(getData().p1_data.role ? U"nige" : U"seme", getData().p1_data.eqid+1, i+1)};
        p2_texture << Texture{U"bns-gamejam/images/nabe/{}_{}_{}.png"_fmt(getData().p2_data.role ? U"nige" : U"seme", getData().p1_data.eqid+1, i+1)};
    }

    // 画像の初期位置
    m_position_guzai = Vec2(400, Scene::Height()-250);
    m_position_otama = Vec2(900, top_height_otama);
    m_position_nabeTop = Vec2(Scene::Width()/2, Scene::Height()-650);
    m_position_nabeUnder = Vec2(Scene::Width()/2, Scene::Height());
    
    // GIF アニメーション画像を開く
    // const AnimatedGIFReader gif{ U"images/IMG_0536.gif" };
    const AnimatedGIFReader gif{ U"bns-gamejam/images/Moti.gif" };

    // 各フレームの画像と、次のフレームへのディレイ（ミリ秒）をロード
    gif.read(images, delays);

    // 画像の向き（0：左、1：右）
    guzai_direction = 0;

    // 各フレームの Image から Texure を作成
    for (const auto& image : images){
        guzai_textures << Texture{ image };
    }
    images.clear();
    
    m_stopwatch.start();
}

Game::~Game(){}

void Game::update(){
    if (m_state == GameState::Countdown){
        if (m_stopwatch.ms() >= 1000){
            m_countdownSeconds--;
            m_stopwatch.restart();
        }
        if (m_countdownSeconds <= 0){
            m_state = GameState::StartPlaying;
            m_stopwatch.restart();
        }
    }
    else if (m_state == GameState::StartPlaying){
        if (m_stopwatch.ms() >= 1000){
            m_state = GameState::Playing;
            m_stopwatch.restart();
            main_bgm.play(1s);
        }
    }
    else if (m_state == GameState::Playing)
    {
        // デバック用
//        m_state = GameState::MiniGame;
        if (MouseL.down()){
            changeScene(State::Result);
        }

        if (m_stopwatch.s() >= max_timeCount){
            m_state = GameState::Finished;
            m_stopwatch.restart();
        }
        
        // 具材の画像の位置更新 (ADキーで操作)
        if (KeyA.pressed() && m_position_guzai.x > Xborder_left_guzai){
            m_position_guzai.x -= (Scene::DeltaTime() * speed_guzai);
            guzai_direction = 0;
        }
        if(KeyD.pressed() && m_position_guzai.x < Xborder_right_guzai){
            m_position_guzai.x += (Scene::DeltaTime() * speed_guzai);
            guzai_direction = 1;
        }

        // おたまの画像の位置更新 (矢印キーで操作)
        if (KeyEnter.pressed() && m_position_otama.y < Scene::Height()-200){
            m_position_otama.y += (Scene::DeltaTime() * speed_otama);
        }
        if(!KeyEnter.pressed() && m_position_otama.y > top_height_otama) {
            m_position_otama.y -= (Scene::DeltaTime() * speed_otama);
        }
        if (KeyLeft.pressed() && m_position_otama.x > Xborder_left_otama){
            m_position_otama.x -= (Scene::DeltaTime() * speed_otama);
        }
        if (KeyRight.pressed() && m_position_otama.x < Xborder_right_otama){
            m_position_otama.x += (Scene::DeltaTime() * speed_otama);
        }
        
        // ミニゲームに移行
        if (m_position_otama.x - m_position_guzai.x >= 55 && m_position_otama.x - m_position_guzai.x <= 65 &&
            m_position_otama.y - m_position_guzai.y >= -100 && m_position_otama.y - m_position_guzai.y <= -90){
            m_state = GameState::MiniGame;
            main_bgm.stop(1s);
            mini_bgm.play(1s);
        }
    }
    else if (m_state == GameState::MiniGame){
        miniGame_timeCounter += Scene::DeltaTime();
        if(miniGame_timeCounter > 3.0){
            if(getData().p1_input.Confirm.down()){
                miniGame_counter--;
                if (p1_state % 2) {p1_state = 2;}
                else {p1_state = 1;}
            }
            if(getData().p2_input.Confirm.down()){
                miniGame_counter++;
                if (p2_state % 2) {p2_state = 2;}
                else {p2_state = 1;}
            }
            miniGame_counter = Clamp(miniGame_counter, 0, 20);
        }else{
            p1_state = 0;
            p2_state = 0;
        }
        
        if(miniGame_counter <= 0)
        {
            if (getData().p1_data.role){
                m_state = GameState::Playing;
                mini_bgm.stop(1s);
                main_bgm.play(1s);
            }
            else {
                m_state = GameState::Finished;
                getData().winner = 0;
            }
            miniGame_counter = 10;
            miniGame_timeCounter = 0.0;
        }
        if(miniGame_counter >= 20)
        {
            if (getData().p2_data.role){
                m_state = GameState::Playing;
                mini_bgm.stop(1s);
                main_bgm.play(1s);
            }
            else {
                m_state = GameState::Finished;
                getData().winner = 1;
            }
            miniGame_counter = 10;
            miniGame_timeCounter = 0.0;
        }
    }
    else if (m_state == GameState::Finished){
        if (m_stopwatch.ms() >= 1000){
            changeScene(State::Result);
            getData().winner = !(getData().p1_data.role);
            m_stopwatch.restart();
            main_bgm.stop(1s);
            mini_bgm.stop(1s);
        }
    }
}

void Game::draw() const{
    Scene::SetBackground(ColorF(0.2, 0.8, 0.6));
    
    m_texture_background.scaled(0.47).drawAt(Scene::Width()/2,Scene::Height()/2);
    
    // 鍋上半分
    m_texture_nabeTop.scaled(1.3).drawAt(m_position_nabeTop);
    
    if(m_state != GameState::MiniGame){
        // おたま
        m_texture_otama.scaled(0.5).drawAt(m_position_otama);
        
        // 具材
        // アニメーションの経過時間
        const double t = Scene::Time();
        
        // 経過時間と各フレームのディレイに基づいて、何番目のフレームを描けばよいかを計算
        const size_t frameIndex = AnimatedGIFReader::GetFrameIndex(t, delays);
        
        if (guzai_direction == 0){
            guzai_textures[frameIndex].scaled(0.25).drawAt(m_position_guzai);
        }
        else{
            guzai_textures[frameIndex].mirrored().scaled(0.25).drawAt(m_position_guzai);
            
        }
    }
    // 鍋下半分
    m_texture_nabeUnder.scaled(1.3).drawAt(m_position_nabeUnder);
    
    if (m_state == GameState::Countdown){
        FontAsset(U"CountDownFont")(m_countdownSeconds).drawAt(Scene::Center(), Palette::Red);
    }
    else if (m_state == GameState::StartPlaying){
        FontAsset(U"CountDownFont")(U"GO").drawAt(Scene::Center(), Palette::Red);
    }
    else if (m_state == GameState::Playing){
        FontAsset(U"StopwatchFont")(U"Time: {}"_fmt(max_timeCount - m_stopwatch.s())).draw(Vec2(Scene::Width() - 150, 20), Palette::Black);
    }
    else if (m_state == GameState::Finished){
        FontAsset(U"CountDownFont")(U"Finish !!!").drawAt(Scene::Center(), Palette::Red);
    }
    // ミニゲーム用draw
    if(m_state == GameState::MiniGame)
    {
        Rect{Arg::center(Scene::Center()), 1280, 720}.draw(ColorF{Palette::Black, 0.5});
        
        if(miniGame_timeCounter < 1.0)
        {
            FontAsset(U"CountFont")(3).drawAt(Scene::Center(), ColorF{1.0, 1.0, 1.0});
        }
        else if(miniGame_timeCounter < 2.0)
        {
            p1_texture[0].resized(1024).mirrored().drawAt(Scene::Center()-Point(200, 100));
            FontAsset(U"CountFont")(2).drawAt(Scene::Center()+Point(200, 0), ColorF{1.0, 1.0, 1.0});
        }
        else if(miniGame_timeCounter < 3.0)
        {
            p2_texture[0].resized(1024).drawAt(Scene::Center()+Point(200, -100));
            FontAsset(U"CountFont")(1).drawAt(Scene::Center()-Point(200, 0), ColorF{1.0, 1.0, 1.0});
        }
        else
        {
            // バー
            Rect::FromPoints(Scene::Center()-Point(500, 300), Scene::Center()-Point((miniGame_counter-10)*50, 250)).draw(ColorF{Palette::Blue});
            Rect::FromPoints(Scene::Center()-Point((miniGame_counter-10)*50, 300), Scene::Center()-Point(-500, 250)).draw(ColorF{Palette::Red});
            // キャラ画像
            p1_texture[p1_state].resized(512).mirrored().drawAt(Scene::Center()+Point(-100, 100));
            p2_texture[p2_state].resized(512).drawAt(Scene::Center()+Point(100, 100));
        }
    }
}
