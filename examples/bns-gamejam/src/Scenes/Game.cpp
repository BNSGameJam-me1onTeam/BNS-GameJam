#include <Siv3D.hpp>
#include "Game.hpp"
#include "Mob.hpp"

Game::Game(const InitData& init) : IScene{ init }, m_state{ GameState::Countdown }, m_countdownSeconds{ 3 }{
    
    // --------------------------------------------------------------------------------------------
    // デバック用の背邸
    // --------------------------------------------------------------------------------------------
    
    m_position_debug = Vec2(Scene::Width()/2, Scene::Height()/2);
    
    
    // --------------------------------------------------------------------------------------------
    // 共有データの取得
    // --------------------------------------------------------------------------------------------
    
    auto data = getData();
    
    
    // --------------------------------------------------------------------------------------------
    // ステージに関する設定
    // --------------------------------------------------------------------------------------------
    
    miniGame_counter = 10;
    miniGame_timeCounter = 0.0;
    
    // フォントの設定
    FontAsset::Register(U"CountDownFont", 200, Typeface::Heavy);
    FontAsset::Register(U"StopwatchFont", 45, Typeface::Heavy);
    
    // 制限時間
    max_timeCount = 6000;
    
    // 画像の読み込み
    m_texture_background = Texture(U"bns-gamejam/images/nabe/background.png");
    m_texture_nabeTop = Texture(U"bns-gamejam/images/nabe/nabe_top.png");
    m_texture_nabeUnder = Texture(U"bns-gamejam/images/nabe/nabe_under.png");
    
    // 画像の位置
    m_position_nabeTop = Vec2(Scene::Width()/2, Scene::Height()-665);
    m_position_nabeUnder = Vec2(Scene::Width()/2, Scene::Height());

    for (auto i : step(3))
    {
        p1_texture << Texture{U"bns-gamejam/images/nabe/{}_{}_{}.png"_fmt(getData().p1_data.role ? U"nige" : U"seme", getData().p1_data.eqid+1, i+1)};
        p2_texture << Texture{U"bns-gamejam/images/nabe/{}_{}_{}.png"_fmt(getData().p2_data.role ? U"nige" : U"seme", getData().p2_data.eqid+1, i+1)};
    }
    for (auto i : step(4))
    {
        punch << Audio{U"bns-gamejam/sounds/punch_{}.mp3"_fmt(i+1)};
    }

    // 画像の初期位置
    m_position_guzai = Vec2(400, Scene::Height()-250);
    m_position_otama = Vec2(900, top_height_otama);
    m_position_nabeTop = Vec2(Scene::Width()/2, Scene::Height()-650);
    m_position_nabeUnder = Vec2(Scene::Width()/2, Scene::Height());
    
    
    // --------------------------------------------------------------------------------------------
    // プレイヤー1に関する設定
    // --------------------------------------------------------------------------------------------
    
    String gifPath_p1 = U"";

    // 条件に基づいてgifPathに適切な文字列を代入
    if (!data.stage_id){
        // stage_idが0の場合
        gifPath_p1 = U"bns-gamejam/images/nabe_gif/";
    }
    else{
        // stage_idが0でない場合
        gifPath_p1 = U"bns-gamejam/images/pafe_gif/";
    }

    // プレイヤーの役割に応じてパスの続きを追加
    gifPath_p1 += data.p1_data.role ? U"nige_soubi_" : U"seme_soubi_";

    // 装備IDに1を足した値をパスの最後に追加
    gifPath_p1 += Format(data.p1_data.eqid + 1);
    gifPath_p1 += U".gif";

    // 生成したパスを元にGIFオブジェクトを作成
    AnimatedGIFReader gif_p1{gifPath_p1};

    // 各フレームの画像と、次のフレームへのディレイ（ミリ秒）をロード
    gif_p1.read(images_p1, delays_p1);

    // 各フレームの Image から Texure を作成
    for (const auto& image : images_p1){
        p1_textures << Texture{ image };
    }
    images_p1.clear();
    
    if (data.p1_data.role){
        
        guzai_input = getData().p1_input;
        
        getData().winner = 0;
        
        switch (data.p1_data.eqid) {
            case 0:
                guzai_id = 0;
                
                // 画像の向き（0：左、1：右）
                direction_guzai = 1;
                
                // GIFの大きさ
                size_guzai = 0.25;
                
                // スキルの制限時間（ms）
                skill_timer = 3000;
                
                // スキルのインターバル（ms）
                skill_interval = 10000;
                
                // スキルゲージの描画位置
                skill_gauge_height = 100;
                
                // 移動速度
                speed_guzai = 360;
                
                // 移動制限
                Xborder_left_guzai = 290;
                Xborder_right_guzai = 985;
                
                // 当たり判定（これを現在の位置にプラスして判定する）
                hitRangeX_right = 46;
                hitRangeX_left = -47;
                hitRangeY_high = -101;
                hitRangeY_low = 42;
                
                // 画像の初期位置
                m_position_guzai = Vec2(400, Scene::Height()-250);
                
                // 残りのモブを生成
                mob_1 = new Mob(init, 1);
                mob_2 = new Mob(init, 2);
                
                break;
            case 1:
                guzai_id = 1;
                
                // 画像の向き（0：左、1：右）
                direction_guzai = 1;
                
                // GIFの大きさ
                size_guzai = 0.32;
                
                // スキルの制限時間（ms）
                skill_timer = 2000;
                
                // スキルのインターバル（ms）
                skill_interval = 15000;
                
                // スキルゲージの描画位置
                skill_gauge_height = 100;
                
                // 移動速度
                speed_guzai = 360;
                
                // 当たり判定（これを現在の位置にプラスして判定する）
                hitRangeX_right = 66;
                hitRangeX_left = -48;
                hitRangeY_high = -99;
                hitRangeY_low = 53;
                
                // 移動制限
                Xborder_left_guzai = 295;
                Xborder_right_guzai = 985;
                
                // 画像の初期位置
                m_position_guzai = Vec2(400, Scene::Height()-250);
                
                // 残りのモブを生成
                mob_1 = new Mob(init, 0);
                mob_2 = new Mob(init, 2);
                
                break;
            case 2:
                guzai_id = 2;
                
                // 画像の向き（0：左、1：右）
                direction_guzai = 1;
                
                // GIFの大きさ
                size_guzai = 0.30;
                
                // スキルの制限時間（ms）
                skill_timer = 2000;
                
                // スキルのインターバル（ms）
                skill_interval = 10000;
                
                // スキルゲージの描画位置
                skill_gauge_height = 100;
                
                // 移動速度
                speed_guzai = 360;
                
                // 当たり判定（これを現在の位置にプラスして判定する）
                hitRangeX_right = 62;
                hitRangeX_left = -71;
                hitRangeY_high = -110;
                hitRangeY_low = 66;
                
                // 移動制限
                Xborder_left_guzai = 325;
                Xborder_right_guzai = 965;
                
                // 画像の初期位置
                m_position_guzai = Vec2(400, Scene::Height()-270);
                
                // 残りのモブを生成
                mob_1 = new Mob(init, 0);
                mob_2 = new Mob(init, 1);
                
                break;
            default:
                break;
        }
    }
    else{
        
        otama_input = getData().p1_input;
        
        switch (data.p1_data.eqid) {
            case 0:
                // 画像の向き（0：左、1：右）
                direction_otama = 1;
                
                // 画像の回転
                angle_otama = -10;
                
                // GIFの大きさ
                size_otama = 0.4;
                
                // 移動速度
                speed_otama = 450;
                
                // すくう速さ
                scoop_speed = 900;
                
                // すくった判定をする際の高さ（これより大きくないといけない）
                scoop_JudgeHeight = 490;
                
                // 当たり判定（これを現在の位置にプラスして判定する）
                catchRangeX_right = -48;
                catchRangeX_left = -135;
                catchRangeY_high = 8;
                catchRangeY_low = 140;
                
                // 移動制限
                top_height_otama = 50;
                under_height_otama = 220;
                Xborder_left_otama = 357;
                Xborder_right_otama = 1075;
                
                // 画像の初期位置
                m_position_otama = Vec2(900, Scene::Height()-(Scene::Height()-top_height_otama));
                break;
            case 1:
                // 画像の向き（0：左、1：右）
                direction_otama = 1;
                
                // 画像の回転
                angle_otama = -20;
                
                // GIFの大きさ
                size_otama = 0.5;
            
                // 移動速度
                speed_otama = 850;
                
                // すくう速さ
                scoop_speed = 450;
                
                // すくった判定をする際の高さ（これより大きくないといけない）
                scoop_JudgeHeight = 490;
                
                // 当たり判定（これを現在の位置にプラスして判定する）
                catchRangeX_right = -32;
                catchRangeX_left = -139;
                catchRangeY_high = 27;
                catchRangeY_low = 173;
                
                // 移動制限
                top_height_otama = 50;
                under_height_otama = 230;
                Xborder_left_otama = 333;
                Xborder_right_otama = 1060;
                
                // 画像の初期位置
                m_position_otama = Vec2(900, Scene::Height()-(Scene::Height()-top_height_otama));
                break;
            case 2:
                // 画像の向き（0：左、1：右）
                direction_otama = 1;
                
                // 画像の回転
                angle_otama = 0;
                
                // GIFの大きさ
                size_otama = 0.6;
                
                // 移動速度
                speed_otama = 350;
                
                // すくう速さ
                scoop_speed = 350;
                
                // すくった判定をする際の高さ（これより大きくないといけない）
                scoop_JudgeHeight = 650;
                
                // 当たり判定（これを現在の位置にプラスして判定する）
                catchRangeX_right = 50;
                catchRangeX_left = -170;
                catchRangeY_high = 119;
                catchRangeY_low = 269;
                
                // 移動制限
                top_height_otama = 50;
                under_height_otama = 200;
                Xborder_left_otama = 350;
                Xborder_right_otama = 1025;
                
                // 画像の初期位置
                m_position_otama = Vec2(900, Scene::Height()-(Scene::Height()-top_height_otama));
                break;
            default:
                break;
        }
    }
    
    
    // --------------------------------------------------------------------------------------------
    // プレイヤー2に関する設定
    // --------------------------------------------------------------------------------------------
    
    String gifPath_p2 = U"";

    // 条件に基づいてgifPathに適切な文字列を代入
    if (!data.stage_id){
        // stage_idが0の場合
        gifPath_p2 = U"bns-gamejam/images/nabe_gif/";
    }
    else{
        // stage_idが0でない場合
        gifPath_p2 = U"bns-gamejam/images/pafe_gif/";
    }

    // プレイヤーの役割に応じてパスの続きを追加
    gifPath_p2 += data.p2_data.role ? U"nige_soubi_" : U"seme_soubi_";

    // 装備IDに1を足した値をパスの最後に追加
    gifPath_p2 += Format(data.p2_data.eqid + 1);
    gifPath_p2 += U".gif";

    // 生成したパスを元にGIFオブジェクトを作成
    AnimatedGIFReader gif_p2{gifPath_p2};

    // 各フレームの画像と、次のフレームへのディレイ（ミリ秒）をロード
    gif_p2.read(images_p2, delays_p2);

    // 各フレームの Image から Texure を作成
    for (const auto& image : images_p2){
        p2_textures << Texture{ image };
    }
    images_p2.clear();
    
    if (data.p2_data.role){
        
        guzai_input = getData().p2_input;
        
        getData().winner = 1;
        
        switch (data.p2_data.eqid) {
            case 0:
                guzai_id = 0;
                
                // 画像の向き（0：左、1：右）
                direction_guzai = 1;
                
                // GIFの大きさ
                size_guzai = 0.25;
                
                // スキルの制限時間（ms）
                skill_timer = 3000;
                
                // スキルのインターバル（ms）
                skill_interval = 10000;
                
                // スキルゲージの描画位置
                skill_gauge_height = 100;
                
                // 移動速度
                speed_guzai = 360;
                
                // 移動制限
                Xborder_left_guzai = 290;
                Xborder_right_guzai = 985;
                
                // 当たり判定（これを現在の位置にプラスして判定する）
                hitRangeX_right = 46;
                hitRangeX_left = -47;
                hitRangeY_high = -101;
                hitRangeY_low = 42;
                
                // 画像の初期位置
                m_position_guzai = Vec2(400, Scene::Height()-250);
                
                // 残りのモブを生成
                mob_1 = new Mob(init, 1);
                mob_2 = new Mob(init, 2);
                
                break;
            case 1:
                guzai_id = 1;
                
                // 画像の向き（0：左、1：右）
                direction_guzai = 1;
                
                // GIFの大きさ
                size_guzai = 0.32;
                
                // スキルの制限時間（ms）
                skill_timer = 2000;
                
                // スキルのインターバル（ms）
                skill_interval = 15000;
                
                // スキルゲージの描画位置
                skill_gauge_height = 100;
                
                // 移動速度
                speed_guzai = 360;
                
                // 当たり判定（これを現在の位置にプラスして判定する）
                hitRangeX_right = 66;
                hitRangeX_left = -48;
                hitRangeY_high = -99;
                hitRangeY_low = 53;
                
                // 移動制限
                Xborder_left_guzai = 295;
                Xborder_right_guzai = 985;
                
                // 画像の初期位置
                m_position_guzai = Vec2(400, Scene::Height()-250);
                
                // 残りのモブを生成
                mob_1 = new Mob(init, 0);
                mob_2 = new Mob(init, 2);
                
                break;
            case 2:
                guzai_id = 2;
                
                // 画像の向き（0：左、1：右）
                direction_guzai = 1;
                
                // GIFの大きさ
                size_guzai = 0.30;
                
                // スキルの制限時間（ms）
                skill_timer = 2000;
                
                // スキルのインターバル（ms）
                skill_interval = 10000;
                
                // スキルゲージの描画位置
                skill_gauge_height = 100;
                
                // 移動速度
                speed_guzai = 360;
                
                // 当たり判定（これを現在の位置にプラスして判定する）
                hitRangeX_right = 62;
                hitRangeX_left = -71;
                hitRangeY_high = -110;
                hitRangeY_low = 66;
                
                // 移動制限
                Xborder_left_guzai = 325;
                Xborder_right_guzai = 965;
                
                // 画像の初期位置
                m_position_guzai = Vec2(400, Scene::Height()-270);
                
                // 残りのモブを生成
                mob_1 = new Mob(init, 0);
                mob_2 = new Mob(init, 1);
                
                break;
            default:
                break;
        }
    }
    else{
        
        otama_input = getData().p2_input;
        
        switch (data.p2_data.eqid) {
            case 0:
                // 画像の向き（0：左、1：右）
                direction_otama = 1;
                
                // 画像の回転
                angle_otama = -10;
                
                // GIFの大きさ
                size_otama = 0.4;
                
                // 移動速度
                speed_otama = 450;
                
                // すくう速さ
                scoop_speed = 900;
                
                // すくった判定をする際の高さ（これより大きくないといけない）
                scoop_JudgeHeight = 490;
                
                // 当たり判定（これを現在の位置にプラスして判定する）
                catchRangeX_right = -48;
                catchRangeX_left = -135;
                catchRangeY_high = 8;
                catchRangeY_low = 140;
                
                // 移動制限
                top_height_otama = 50;
                under_height_otama = 220;
                Xborder_left_otama = 357;
                Xborder_right_otama = 1075;
                
                // 画像の初期位置
                m_position_otama = Vec2(900, Scene::Height()-(Scene::Height()-top_height_otama));
                break;
            case 1:
                // 画像の向き（0：左、1：右）
                direction_otama = 1;
                
                // 画像の回転
                angle_otama = -20;
                
                // GIFの大きさ
                size_otama = 0.5;
            
                // 移動速度
                speed_otama = 850;
                
                // すくう速さ
                scoop_speed = 450;
                
                // すくった判定をする際の高さ（これより大きくないといけない）
                scoop_JudgeHeight = 490;
                
                // 当たり判定（これを現在の位置にプラスして判定する）
                catchRangeX_right = -32;
                catchRangeX_left = -139;
                catchRangeY_high = 37;
                catchRangeY_low = 173;
                
                // 移動制限
                top_height_otama = 50;
                under_height_otama = 230;
                Xborder_left_otama = 333;
                Xborder_right_otama = 1060;
                
                // 画像の初期位置
                m_position_otama = Vec2(900, Scene::Height()-(Scene::Height()-top_height_otama));
                break;
            case 2:
                // 画像の向き（0：左、1：右）
                direction_otama = 1;
                
                // 画像の回転
                angle_otama = 0;
                
                // GIFの大きさ
                size_otama = 0.6;
                
                // 移動速度
                speed_otama = 350;
                
                // すくう速さ
                scoop_speed = 350;
                
                // すくった判定をする際の高さ（これより大きくないといけない）
                scoop_JudgeHeight = 650;
                
                // 当たり判定（これを現在の位置にプラスして判定する）
                catchRangeX_right = 50;
                catchRangeX_left = -170;
                catchRangeY_high = 119;
                catchRangeY_low = 269;
                
                // 移動制限
                top_height_otama = 50;
                under_height_otama = 200;
                Xborder_left_otama = 350;
                Xborder_right_otama = 1025;
                
                // 画像の初期位置
                m_position_otama = Vec2(900, Scene::Height()-(Scene::Height()-top_height_otama));
                break;
            default:
                break;
        }
    }
    
    
    // --------------------------------------------------------------------------------------------
    // ミニゲーム結果用のGIF設定
    // --------------------------------------------------------------------------------------------
    
    String gifPath_miniGame = U"";

    // 条件に基づいてgifPathに適切な文字列を代入
    if (!data.stage_id){
        // stage_idが0の場合
        gifPath_miniGame = U"bns-gamejam/images/nabe_gif/notMove_";
    }
    else{
        // stage_idが0でない場合
        gifPath_miniGame = U"bns-gamejam/images/pafe_gif/notMove_";
    }
    
    if (data.p1_data.role){
        // プレイヤーの役割に応じてパスの続きを追加
        gifPath_miniGame += data.p2_data.role ? U"nige_soubi_" : U"seme_soubi_";

        // 装備IDに1を足した値をパスの最後に追加
        gifPath_miniGame += Format(data.p2_data.eqid + 1);
        gifPath_miniGame += U".gif";

        // 生成したパスを元にGIFオブジェクトを作成
        AnimatedGIFReader gif_miniGame{gifPath_miniGame};

        // 各フレームの画像と、次のフレームへのディレイ（ミリ秒）をロード
        gif_miniGame.read(images_miniGame, delays_miniGame);

        // 各フレームの Image から Texure を作成
        for (const auto& image : images_miniGame){
            miniGame_textures << Texture{ image };
        }
        images_miniGame.clear();
    }
    else{
        // プレイヤーの役割に応じてパスの続きを追加
        gifPath_miniGame += data.p1_data.role ? U"nige_soubi_" : U"seme_soubi_";

        // 装備IDに1を足した値をパスの最後に追加
        gifPath_miniGame += Format(data.p1_data.eqid + 1);
        gifPath_miniGame += U".gif";

        // 生成したパスを元にGIFオブジェクトを作成
        AnimatedGIFReader gif_miniGame{gifPath_miniGame};

        // 各フレームの画像と、次のフレームへのディレイ（ミリ秒）をロード
        gif_miniGame.read(images_miniGame, delays_miniGame);

        // 各フレームの Image から Texure を作成
        for (const auto& image : images_miniGame){
            miniGame_textures << Texture{ image };
        }
        images_miniGame.clear();
    }
    
    
    
    // --------------------------------------------------------------------------------------------
    // そのほかの設定
    // --------------------------------------------------------------------------------------------
    
    m_stopwatch.start();
    
    countdown_se.playOneShot();
}

Game::~Game(){
    delete mob_1;
    delete mob_2;
}

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
        // --------------------------------------------------------------------------------------------
        // デバック用
        // --------------------------------------------------------------------------------------------
        
        if (debug_on){
            if (MouseL.down()){
                changeScene(State::Result);
            }
            
            if (KeyK.pressed()){
                m_position_debug.y += (Scene::DeltaTime() * speed_debug);
                
                Print << U"out";
                Print << m_position_debug.x << U", " << m_position_debug.y;
                Print << m_position_otama.x << U", " << m_position_otama.y;
                Print << m_position_guzai.x << U", " << m_position_guzai.y;
            }
            
            if (KeyI.pressed()){
                m_position_debug.y -= (Scene::DeltaTime() * speed_debug);
                
                Print << U"out";
                Print << m_position_debug.x << U", " << m_position_debug.y;
                Print << m_position_otama.x << U", " << m_position_otama.y;
                Print << m_position_guzai.x << U", " << m_position_guzai.y;
            }
            
            if (KeyJ.pressed()){
                m_position_debug.x -= (Scene::DeltaTime() * speed_debug);
                
                Print << U"out";
                Print << m_position_debug.x << U", " << m_position_debug.y;
                Print << m_position_otama.x << U", " << m_position_otama.y;
                Print << m_position_guzai.x << U", " << m_position_guzai.y;
            }
            
            if (KeyL.pressed()){
                m_position_debug.x += (Scene::DeltaTime() * speed_debug);
                
                Print << U"out";
                Print << m_position_debug.x << U", " << m_position_debug.y;
                Print << m_position_otama.x << U", " << m_position_otama.y;
                Print << m_position_guzai.x << U", " << m_position_guzai.y;
            }
        }
        
        
        
        // --------------------------------------------------------------------------------------------
        //タイマー
        // --------------------------------------------------------------------------------------------
        
        if (m_stopwatch.s() >= max_timeCount){
            m_state = GameState::Finished;
            m_stopwatch.restart();
        }
        
        
        // --------------------------------------------------------------------------------------------
        // 具材の画像の位置更新 (ADキーで操作)
        // --------------------------------------------------------------------------------------------
        
        if (guzai_input.Left.pressed() && m_position_guzai.x > Xborder_left_guzai){
            m_position_guzai.x -= (Scene::DeltaTime() * speed_guzai);
            direction_guzai = 0;
        }
        if (guzai_input.Right.pressed() && m_position_guzai.x < Xborder_right_guzai){
            m_position_guzai.x += (Scene::DeltaTime() * speed_guzai);
            direction_guzai = 1;
        }
        
        
        // --------------------------------------------------------------------------------------------
        // 具材のスキル発動
        // --------------------------------------------------------------------------------------------
        
        if (skillActive){
            if (m_stopwatch_skill.ms() < 1000 && guzai_id == 2){
                m_position_guzai.y -= (Scene::DeltaTime() * 400);
            }
            if (m_stopwatch_skill.ms() >= 1000 && guzai_id == 2){
                
                if ((m_position_guzai.y + (Scene::DeltaTime() * 400)) < Scene::Height() - 270){
                    m_position_guzai.y += (Scene::DeltaTime() * 400);
                }
                else{
                    m_position_guzai.y = Scene::Height() - 270;
                }
            }
            
            if (m_stopwatch_skill.ms() > skill_timer){
                skillActive = false;
                skillEnable = false;
                switch (guzai_id) {
                    case 0:
                        speed_guzai /= 4;
                        m_stopwatch_skill.reset();
                        m_stopwatch_interval.reset();
                        m_stopwatch_interval.start();
                        break;
                    case 1:
                        m_position_guzai.y -= 160;
                        
                        m_stopwatch_skill.reset();
                        m_stopwatch_interval.reset();
                        m_stopwatch_interval.start();
                        break;
                    case 2:
                        m_stopwatch_skill.reset();
                        m_stopwatch_interval.reset();
                        m_stopwatch_interval.start();
                        break;
                    default:
                        break;
                }
            }
        }
        else{
            if (skillEnable == false){
                if (m_stopwatch_interval.ms() - skill_interval_prev >= 1000){
                    skill_interval_len += skill_interval / (skill_interval / 10);
                    skill_interval_prev = m_stopwatch_interval.ms();
                }
            }
            if (guzai_input.Confirm.down() && skillEnable == true && skillActive == false){
                skillActive = true;
                skill_se[guzai_id].playOneShot();
                switch (guzai_id) {
                    case 0:
                        speed_guzai *= 4;
                        
                        m_stopwatch_skill.start();
                        break;
                    case 1:
                        m_position_guzai.y += 160;
                        
                        m_stopwatch_skill.start();
                        break;
                    case 2:
                        m_stopwatch_skill.start();
                        break;
                    default:
                        break;
                }
            }
            
            if (skillEnable == false && m_stopwatch_interval.ms() > skill_interval){
                skillEnable = true;
                skill_interval_len = 0;
                skill_interval_prev = 0;
                switch (guzai_id) {
                    case 0:
                        m_stopwatch_interval.reset();
                        break;
                    case 1:
                        m_stopwatch_interval.reset();
                        break;
                    case 2:
                        m_stopwatch_interval.reset();
                        break;
                    default:
                        break;
                }
            }
        }
        
        
        // --------------------------------------------------------------------------------------------
        // おたまの画像の位置更新 (矢印キーで操作)
        // --------------------------------------------------------------------------------------------
        
        if (!miniGameLoser_otama){
            if (otama_input.Confirm.pressed() && m_position_otama.y < Scene::Height()-under_height_otama){
                m_position_otama.y += (Scene::DeltaTime() * scoop_speed);
            }
            if (!otama_input.Confirm.pressed() && m_position_otama.y > top_height_otama) {
                m_position_otama.y -= (Scene::DeltaTime() * scoop_speed);
            }
            if (otama_input.Left.pressed() && m_position_otama.x > Xborder_left_otama && m_position_otama.y < Scene::Height()-under_height_otama-5){
                m_position_otama.x -= (Scene::DeltaTime() * speed_otama);
            }
            if (otama_input.Right.pressed() && m_position_otama.x < Xborder_right_otama && m_position_otama.y < Scene::Height()-under_height_otama-5){
                m_position_otama.x += (Scene::DeltaTime() * speed_otama);
            }
        }
        

        
        // --------------------------------------------------------------------------------------------
        // ミニゲームに移行するか判定
        // --------------------------------------------------------------------------------------------
        
        if (!miniGameLoser_otama){
            bool judge = false;
            for (int i = m_position_otama.x + catchRangeX_left; i <= m_position_otama.x + catchRangeX_right; i++){
                for (int j = m_position_otama.y + catchRangeY_high; j <= m_position_otama.y + catchRangeY_low; j++){
                    // 当たり判定
                    if (m_position_guzai.x + hitRangeX_left <= i && m_position_guzai.x + hitRangeX_right >= i && m_position_guzai.y + hitRangeY_high <= j && m_position_guzai.y + hitRangeY_low >= j){
                        if (debug_on){
                            Print << U"i,j = " << i << U", " << j;
                            Print << U"height";
                        }
                        if (m_position_otama.y + catchRangeY_low > scoop_JudgeHeight){
                            judge = true;
                            break;
                        }
                    }
                }
                if (judge){
                    // タイマーを一時停止
                    m_stopwatch.pause();
                    if (m_stopwatch_skill.ms() != 0){
                        m_stopwatch_skill.pause();
                    }
                    if (m_stopwatch_interval.ms() != 0){
                        m_stopwatch_interval.pause();
                    }
                    
                    // GameStateをミニゲームに移行
                     m_state = GameState::MiniGame;
                     main_bgm.stop(1s);
                     mini_bgm.play(1s);
                    
                    break;
                }
            }
        }
        else{
            if (m_position_otama.y > top_height_otama) {
                m_position_otama.y -= (Scene::DeltaTime() * 200);
            }
            else{
                miniGameLoser_otama = false;
            }
        }
        
        
        // --------------------------------------------------------------------------------------------
        // モブの移動処理
        // --------------------------------------------------------------------------------------------
        
        mob_1->update();
        mob_2->update();
    }
    else if (m_state == GameState::MiniGame){
        
        miniGame_timeCounter += Scene::DeltaTime();
        if(miniGame_timeCounter > 3.0){
            if(getData().p1_input.Confirm.down()){
                miniGame_counter--;
                punch[Random(3)].playOneShot();
                if (p1_state % 2) {p1_state = 2;}
                else {p1_state = 1;}
            }
            if(getData().p2_input.Confirm.down()){
                miniGame_counter++;
                punch[Random(3)].playOneShot();
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
            if (getData().p1_data.role)
            {
                m_state = GameState::Playing;
                miniGameLoser_otama = true;
                mini_bgm.stop(1s);
                main_bgm.play(1s);
            }
            else {
                m_state = GameState::Finished;
            }
            getData().winner = 0;
            miniGame_counter = 10;
            miniGame_timeCounter = 0.0;
        }
        else if(miniGame_counter >= 20)
        {
            if (getData().p2_data.role)
            {
                m_state = GameState::Playing;
                miniGameLoser_otama = true;
                mini_bgm.stop(1s);
                main_bgm.play(1s);
            }
            else {
                m_state = GameState::Finished;
            }
            getData().winner = 1;
            miniGame_counter = 10;
            miniGame_timeCounter = 0.0;
        }

        // タイマーを再開
        m_stopwatch.resume();
        if (m_stopwatch_skill.ms() != 0){
            m_stopwatch_skill.resume();
        }
        if (m_stopwatch_interval.ms() != 0){
            m_stopwatch_interval.resume();
        }
    }
    else if (m_state == GameState::Finished){
        changeScene(State::Result);
        m_stopwatch.reset();
        main_bgm.stop(1s);
        mini_bgm.stop(1s);
    }
}

void Game::draw() const{
    // --------------------------------------------------------------------------------------------
    // 背景の描画
    // --------------------------------------------------------------------------------------------
    
    m_texture_background.scaled(0.47).drawAt(Scene::Width()/2,Scene::Height()/2);
    
    
    // --------------------------------------------------------------------------------------------
    // 鍋上半分の描画
    // --------------------------------------------------------------------------------------------
    
    m_texture_nabeTop.scaled(1.3).drawAt(m_position_nabeTop);
    
    
    // --------------------------------------------------------------------------------------------
    // モブの描画
    // --------------------------------------------------------------------------------------------
    
    mob_1 -> draw();
    mob_2 -> draw();
    
    
    // --------------------------------------------------------------------------------------------
    // 具材とおたまの描画
    // --------------------------------------------------------------------------------------------
    
    // アニメーションの経過時間
    const double t1 = Scene::Time();
    const double t2 = Scene::Time();
    
    if (getData().p1_data.role){
        // 経過時間と各フレームのディレイに基づいて、何番目のフレームを描けばよいかを計算
        const size_t frameIndex_otama = AnimatedGIFReader::GetFrameIndex(t2, delays_p2);
        
        if (miniGameLoser_otama){
            // おたまの描画
            miniGame_textures[frameIndex_otama].scaled(size_otama).rotated(Math::ToRadians(angle_otama)).drawAt(m_position_otama);
        }
        else{
            // おたまの描画
            p2_textures[frameIndex_otama].scaled(size_otama).rotated(Math::ToRadians(angle_otama)).drawAt(m_position_otama);
        }
        
        // 経過時間と各フレームのディレイに基づいて、何番目のフレームを描けばよいかを計算
        const size_t frameIndex_guzai = AnimatedGIFReader::GetFrameIndex(t1, delays_p1);
        
        // 具材の描画
        if (direction_guzai == 0){
            p1_textures[frameIndex_guzai].scaled(size_guzai).drawAt(m_position_guzai);
        }
        else{
            p1_textures[frameIndex_guzai].mirrored().scaled(size_guzai).drawAt(m_position_guzai);
        }
    }
    else{
        // 経過時間と各フレームのディレイに基づいて、何番目のフレームを描けばよいかを計算
        const size_t frameIndex_otama = AnimatedGIFReader::GetFrameIndex(t1, delays_p1);
        
        if (miniGameLoser_otama){
            // おたまの描画
            miniGame_textures[frameIndex_otama].scaled(size_otama).rotated(Math::ToRadians(angle_otama)).drawAt(m_position_otama);
        }
        else{
            // おたまの描画
            p1_textures[frameIndex_otama].scaled(size_otama).rotated(Math::ToRadians(angle_otama)).drawAt(m_position_otama);
        }
        
        // 経過時間と各フレームのディレイに基づいて、何番目のフレームを描けばよいかを計算
        const size_t frameIndex_guzai = AnimatedGIFReader::GetFrameIndex(t2, delays_p2);
        
        // 具材の描画
        if (direction_guzai == 0){
            p2_textures[frameIndex_guzai].scaled(size_guzai).drawAt(m_position_guzai);
        }
        else{
            p2_textures[frameIndex_guzai].mirrored().scaled(size_guzai).drawAt(m_position_guzai);
        }
    }
    
    
    // --------------------------------------------------------------------------------------------
    // 鍋下半分の描画
    // --------------------------------------------------------------------------------------------
    
    m_texture_nabeUnder.scaled(1.3).drawAt(m_position_nabeUnder);
    
    
    // --------------------------------------------------------------------------------------------
    // スキルのクールダウンを描画
    // --------------------------------------------------------------------------------------------
    
    if (skillEnable == false){
        RectF(Arg::center(m_position_guzai.x, m_position_guzai.y - skill_gauge_height), skill_interval/100 + 4, 14).draw(ColorF(0, 0, 0));
        Rect(m_position_guzai.x - skill_interval/100/2 + 1, m_position_guzai.y - skill_gauge_height - 5, skill_interval_len, 10).draw(ColorF{1, 0, 0});
    }
    
    
    // --------------------------------------------------------------------------------------------
    // GameStateに応じた描画
    // --------------------------------------------------------------------------------------------
    
    if (m_state == GameState::Countdown){
        FontAsset(U"CountDownFont")(m_countdownSeconds).drawAt(Scene::Center(), Palette::Red);
    }
    else if (m_state == GameState::StartPlaying){
        FontAsset(U"CountDownFont")(U"GO").drawAt(Scene::Center(), Palette::Red);
    }
    else if (m_state == GameState::Playing){
        // 制限時間の枠
        Rect{Arg::center(Scene::Width() - 130, 70), 188, 68}.rounded(10).draw(ColorF{0, 0, 0});
        Rect{Arg::center(Scene::Width() - 130, 70), 180, 60}.rounded(10).draw(ColorF{1, 1, 1});
        
        // 制限時間の描画
        int totalSeconds = max_timeCount - m_stopwatch.s();
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;
        s3d::String timeText = U"{:0>2}:{:0>2}"_fmt(minutes, seconds);
        FontAsset(U"StopwatchFont")(timeText).draw(Vec2(Scene::Width() - 200, 38), Palette::Black);
    }
    else if(m_state == GameState::MiniGame)
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
    else if (m_state == GameState::Finished){
        FontAsset(U"CountDownFont")(U"Finish !!!").drawAt(Scene::Center(), Palette::Red);
    }
    

    // --------------------------------------------------------------------------------------------
    // デバック用の描画
    // --------------------------------------------------------------------------------------------
    
    if (debug_on){
        Circle(m_position_debug, 10).draw(Palette::Red);
        
        Rect(m_position_otama.x + catchRangeX_left, m_position_otama.y + catchRangeY_high, catchRangeX_right-catchRangeX_left, catchRangeY_low-catchRangeY_high).rounded(10).draw(ColorF{0, 0, 0});
        Rect(m_position_guzai.x + hitRangeX_left, m_position_guzai.y + hitRangeY_high, hitRangeX_right-hitRangeX_left, hitRangeY_low-hitRangeY_high).rounded(10).draw(ColorF{0, 0, 0});
    }
}
