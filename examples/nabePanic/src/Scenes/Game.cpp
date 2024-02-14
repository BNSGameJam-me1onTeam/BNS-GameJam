#include <Siv3D.hpp>
#include "Game.hpp"
#include "Mob.hpp"
#include "Ingredient.hpp"
#include "Tableware.hpp"

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
	// 具材生成関数
	// --------------------------------------------------------------------------------------------
	auto createIngredient = [this, &init](int eqid, InputData input) {
		switch (eqid) {
			case 0:
				// 具材を生成
				ingredient = new Ingredient(init, input, IngredientConfig{ 0, 1, 360, 0.25, 290, 985, 46, -47, -101, 42, 3000, 10000, 100, Vec2(400, Scene::Height() - 250) });

				// 残りのモブを生成
				mob_1 = new Mob(init, 1);
				mob_2 = new Mob(init, 2);

				break;
			case 1:
				// 具材を生成
				ingredient = new Ingredient(init, input, IngredientConfig{ 1, 1, 360, 0.32, 295, 985, 66, -48, -99, 53, 2000, 10000, 100, Vec2(400, Scene::Height() - 250) });

				// 残りのモブを生成
				mob_1 = new Mob(init, 0);
				mob_2 = new Mob(init, 2);

				break;
			case 2:
				// 具材を生成
				ingredient = new Ingredient(init, input, IngredientConfig{ 2, 1, 360, 0.30, 325, 965, 62, -71, -110, 66, 2000, 10000, 100, Vec2(400, Scene::Height() - 270) });

				// 残りのモブを生成
				mob_1 = new Mob(init, 0);
				mob_2 = new Mob(init, 1);

				break;
			default:
				break;
		}
	};


	// --------------------------------------------------------------------------------------------
	// 食器生成関数
	// --------------------------------------------------------------------------------------------

	auto createTableware = [this, &init](int eqid, InputData input) {
		switch (eqid) {
			case 0: {
				// 食器を生成
				int tableware_top_height = 50;
				Vec2 tableware_position = Vec2(900, Scene::Height() - (Scene::Height() - tableware_top_height));
				tableware = new Tableware(init, input, TablewareConfig{ 0.4, -10, 1, 450, 900, 510, -48, -135, 8, 140, tableware_top_height, 220, 1075, 357, tableware_position });

				break;
			}
			case 1: {
				// 食器を生成
				int tableware_top_height = 50;
				Vec2 tableware_position = Vec2(900, Scene::Height() - (Scene::Height() - tableware_top_height));
				tableware = new Tableware(init, input, TablewareConfig{ 0.5, -20, 1, 850, 450, 510, -32, -139, 27, 173, tableware_top_height, 230, 1060, 333, tableware_position });
				break;
			}
			case 2: {
				// 食器を生成
				int tableware_top_height = 50;
				Vec2 tableware_position = Vec2(900, Scene::Height() - (Scene::Height() - tableware_top_height));
				tableware = new Tableware(init, input, TablewareConfig{ 0.6, 0, 1, 350, 350, 650, 50, -170, 119, 269, tableware_top_height, 200, 1025, 350, tableware_position });
				break;
			}
			default:
				break;
			}
	};
    
    
    // --------------------------------------------------------------------------------------------
    // ステージに関する設定
    // --------------------------------------------------------------------------------------------
    
    miniGame_counter = 10;
    miniGame_timeCounter = 0.0;
    
    // フォントの設定
    FontAsset::Register(U"CountDownFont", 200, Typeface::Heavy);
    FontAsset::Register(U"StopwatchFont", 45, Typeface::Heavy);
    
    // 制限時間
    max_timeCount = 90;
    
    // 画像の読み込み
    m_texture_background = Texture( Resource(U"nabePanic/images/nabe/background.png"));
    m_texture_nabeTop = Texture( Resource(U"nabePanic/images/nabe/nabe_top.png"));
    m_texture_nabeUnder = Texture( Resource(U"nabePanic/images/nabe/nabe_under.png"));

    for (auto i : step(3))
    {
        p1_texture << Texture{ Resource(U"nabePanic/images/nabe/{}_{}_{}.png"_fmt(getData().p1_data.role ? U"nige" : U"seme", getData().p1_data.eqid+1, i+1))};
        p2_texture << Texture{ Resource(U"nabePanic/images/nabe/{}_{}_{}.png"_fmt(getData().p2_data.role ? U"nige" : U"seme", getData().p2_data.eqid+1, i+1))};
    }
    for (auto i : step(4))
    {
        punch << Audio{ Resource(U"nabePanic/sounds/punch_{}.mp3"_fmt(i+1))};
    }

    // 画像の初期位置
    m_position_nabeTop = Vec2(Scene::Width()/2, Scene::Height()-664);
    m_position_nabeUnder = Vec2(Scene::Width()/2, Scene::Height());
    
    
    // --------------------------------------------------------------------------------------------
    // プレイヤー1に関する設定
    // --------------------------------------------------------------------------------------------
    
    String gifPath_p1 = U"";

    // 条件に基づいてgifPathに適切な文字列を代入
    if (!data.stage_id){
        // stage_idが0の場合
        gifPath_p1 = U"nabePanic/images/nabe_gif/";
    }
    else{
        // stage_idが0でない場合
        gifPath_p1 = U"nabePanic/images/pafe_gif/";
    }

    // プレイヤーの役割に応じてパスの続きを追加
    gifPath_p1 += data.p1_data.role ? U"nige_soubi_" : U"seme_soubi_";

    // 装備IDに1を足した値をパスの最後に追加
    gifPath_p1 += Format(data.p1_data.eqid + 1);
    gifPath_p1 += U".gif";

    // 生成したパスを元にGIFオブジェクトを作成
    AnimatedGIFReader gif_p1{ Resource(gifPath_p1)};

    // 各フレームの画像と、次のフレームへのディレイ（ミリ秒）をロード
    gif_p1.read(images_p1, delays_p1);

    // 各フレームの Image から Texure を作成
    for (const auto& image : images_p1){
        p1_textures << Texture{ image };
    }
    images_p1.clear();
    
    if (data.p1_data.role){
        getData().winner = 0;

		// 具材を生成
		createIngredient(data.p1_data.eqid, getData().p1_input);
    }
    else{
		// 食器を生成
		createTableware(data.p1_data.eqid, getData().p1_input);
    }
    
    
    // --------------------------------------------------------------------------------------------
    // プレイヤー2に関する設定
    // --------------------------------------------------------------------------------------------
    
    String gifPath_p2 = U"";

    // 条件に基づいてgifPathに適切な文字列を代入
    if (!data.stage_id){
        // stage_idが0の場合
        gifPath_p2 = U"nabePanic/images/nabe_gif/";
    }
    else{
        // stage_idが0でない場合
        gifPath_p2 = U"nabePanic/images/pafe_gif/";
    }

    // プレイヤーの役割に応じてパスの続きを追加
    gifPath_p2 += data.p2_data.role ? U"nige_soubi_" : U"seme_soubi_";

    // 装備IDに1を足した値をパスの最後に追加
    gifPath_p2 += Format(data.p2_data.eqid + 1);
    gifPath_p2 += U".gif";

    // 生成したパスを元にGIFオブジェクトを作成
    AnimatedGIFReader gif_p2{ Resource(gifPath_p2)};

    // 各フレームの画像と、次のフレームへのディレイ（ミリ秒）をロード
    gif_p2.read(images_p2, delays_p2);

    // 各フレームの Image から Texure を作成
    for (const auto& image : images_p2){
        p2_textures << Texture{ image };
    }
    images_p2.clear();
    
    if (data.p2_data.role){
        getData().winner = 1;

		// 具材を生成
		createIngredient(data.p2_data.eqid, getData().p2_input);
    }
    else{
		// 食器を生成
		createTableware(data.p2_data.eqid, getData().p2_input);
    }
    
    
    // --------------------------------------------------------------------------------------------
    // ミニゲーム結果用のGIF設定
    // --------------------------------------------------------------------------------------------
    
    String gifPath_miniGame = U"";

    // 条件に基づいてgifPathに適切な文字列を代入
    if (!data.stage_id){
        // stage_idが0の場合
        gifPath_miniGame = U"nabePanic/images/nabe_gif/notMove_";
    }
    else{
        // stage_idが0でない場合
        gifPath_miniGame = U"nabePanic/images/pafe_gif/notMove_";
    }
    
    if (data.p1_data.role){
        // プレイヤーの役割に応じてパスの続きを追加
        gifPath_miniGame += data.p2_data.role ? U"nige_soubi_" : U"seme_soubi_";

        // 装備IDに1を足した値をパスの最後に追加
        gifPath_miniGame += Format(data.p2_data.eqid + 1);
        gifPath_miniGame += U".gif";

        // 生成したパスを元にGIFオブジェクトを作成
        AnimatedGIFReader gif_miniGame{ Resource(gifPath_miniGame)};

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
        AnimatedGIFReader gif_miniGame{ Resource(gifPath_miniGame)};

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
                Print << tableware->getTablewareConfig().tableware_position.x << U", " << tableware->getTablewareConfig().tableware_position.y;
                Print << ingredient->getIngredientConfig().ingredient_position.x << U", " << ingredient->getIngredientConfig().ingredient_position.y;
            }
            
            if (KeyI.pressed()){
                m_position_debug.y -= (Scene::DeltaTime() * speed_debug);
                
                Print << U"out";
                Print << m_position_debug.x << U", " << m_position_debug.y;
				Print << tableware->getTablewareConfig().tableware_position.x << U", " << tableware->getTablewareConfig().tableware_position.y;
                Print << ingredient->getIngredientConfig().ingredient_position.x << U", " << ingredient->getIngredientConfig().ingredient_position.y;
            }
            
            if (KeyJ.pressed()){
                m_position_debug.x -= (Scene::DeltaTime() * speed_debug);
                
                Print << U"out";
                Print << m_position_debug.x << U", " << m_position_debug.y;
				Print << tableware->getTablewareConfig().tableware_position.x << U", " << tableware->getTablewareConfig().tableware_position.y;
                Print << ingredient->getIngredientConfig().ingredient_position.x << U", " << ingredient->getIngredientConfig().ingredient_position.y;
            }
            
            if (KeyL.pressed()){
                m_position_debug.x += (Scene::DeltaTime() * speed_debug);
                
                Print << U"out";
                Print << m_position_debug.x << U", " << m_position_debug.y;
				Print << tableware->getTablewareConfig().tableware_position.x << U", " << tableware->getTablewareConfig().tableware_position.y;
                Print << ingredient->getIngredientConfig().ingredient_position.x << U", " << ingredient->getIngredientConfig().ingredient_position.y;
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
        // 具材の処理
        // --------------------------------------------------------------------------------------------

        ingredient->update();
        
        
        // --------------------------------------------------------------------------------------------
        // 食器の画像の位置更新 (矢印キーで操作)
        // --------------------------------------------------------------------------------------------

		tableware->update();

        
        // --------------------------------------------------------------------------------------------
        // ミニゲームに移行するか判定
        // --------------------------------------------------------------------------------------------
        
        if (!tableware->getTablewareMiniGameLoser()){
            bool judge = false;
			Vec2 tableware_position = tableware->getTablewareConfig().tableware_position;
			int catchRangeX_left = tableware->getTablewareConfig().tableware_catchRangeX_left;
			int catchRangeX_right = tableware->getTablewareConfig().tableware_catchRangeX_right;
			int catchRangeY_high = tableware->getTablewareConfig().tableware_catchRangeY_high;
			int catchRangeY_low = tableware->getTablewareConfig().tableware_catchRangeY_low;

            for (int i = tableware_position.x + catchRangeX_left; i <= tableware_position.x + catchRangeX_right; i++){
                for (int j = tableware_position.y + catchRangeY_high; j <= tableware_position.y + catchRangeY_low; j++){
                    // 当たり判定
                    Vec2 ingredient_position = ingredient->getIngredientConfig().ingredient_position;
                    int hitRangeX_left = ingredient->getIngredientConfig().ingredient_hitRangeX_left;
                    int hitRangeX_right = ingredient->getIngredientConfig().ingredient_hitRangeX_right;
                    int hitRangeY_high = ingredient->getIngredientConfig().ingredient_hitRangeY_high;
                    int hitRangeY_low = ingredient->getIngredientConfig().ingredient_hitRangeY_low;
                    
                    if (ingredient_position.x + hitRangeX_left <= i && ingredient_position.x + hitRangeX_right >= i && ingredient_position.y + hitRangeY_high <= j && ingredient_position.y + hitRangeY_low >= j){
                        if (debug_on){
                            Print << U"i,j = " << i << U", " << j;
                            Print << U"height";
                        }
                        if (tableware_position.y + catchRangeY_low > tableware->getTablewareConfig().scoop_JudgeHeight){
                            judge = true;
                            break;
                        }
                    }
                }
                if (judge){
                    // タイマーを一時停止
                    m_stopwatch.pause();
                    if (ingredient->getStopwatchSkill().isRunning()) {
						ingredient->stopwatchSkillSwitching(0);
                    }
                    if (ingredient->getStopwatchhInterval().isRunning()) {
						ingredient->stopwatchIntervalSwitching(0);
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
            if (tableware->getTablewareConfig().tableware_position.y > tableware->getTablewareConfig().tableware_top_height) {
				Vec2 newPosition(tableware->getTablewareConfig().tableware_position.x, tableware->getTablewareConfig().tableware_position.y - (Scene::DeltaTime() * 200));
				tableware->setTablewarePosition(newPosition);
            }
            else{
				tableware->tablewareMiniGameLoserSwitching(0);
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
				tableware->tablewareMiniGameLoserSwitching(1);
                mini_bgm.stop(1s);
                main_bgm.play(1s);
            }
            else {
                m_state = GameState::Finished;
            }
            getData().winner = 0;
            miniGame_counter = 10;
            miniGame_timeCounter = 0.0;
            
            // タイマーを再開
            m_stopwatch.resume();
			ingredient->stopwatchSkillSwitching(1);
			ingredient->stopwatchIntervalSwitching(1);

        }
        else if(miniGame_counter >= 20)
        {
            if (getData().p2_data.role)
            {
                m_state = GameState::Playing;
				tableware->tablewareMiniGameLoserSwitching(1);
                mini_bgm.stop(1s);
                main_bgm.play(1s);
            }
            else {
                m_state = GameState::Finished;
            }
            getData().winner = 1;
            miniGame_counter = 10;
            miniGame_timeCounter = 0.0;
            
            // タイマーを再開
            m_stopwatch.resume();
			ingredient->stopwatchSkillSwitching(1);
			ingredient->stopwatchIntervalSwitching(1);
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

	double tableware_size = tableware->getTablewareConfig().tableware_size;
	double tableware_angle = tableware->getTablewareConfig().tableware_angle;
	Vec2 tableware_position = tableware->getTablewareConfig().tableware_position;

	int ingredient_direction = ingredient->getIngredientConfig().ingredient_direction;
	double ingredient_size = ingredient->getIngredientConfig().ingredient_size;
	Vec2 ingredient_position = ingredient->getIngredientConfig().ingredient_position;

    
    if (getData().p1_data.role){
        // 経過時間と各フレームのディレイに基づいて、何番目のフレームを描けばよいかを計算
        const size_t frameIndex_tableware = AnimatedGIFReader::GetFrameIndex(t2, delays_p2);
        
        if (tableware->getTablewareMiniGameLoser()){
            // おたまの描画
            miniGame_textures[frameIndex_tableware].scaled(tableware_size).rotated(Math::ToRadians(tableware_angle)).drawAt(tableware_position);
        }
        else{
            // おたまの描画
            p2_textures[frameIndex_tableware].scaled(tableware_size).rotated(Math::ToRadians(tableware_angle)).drawAt(tableware_position);
        }
        
        // 経過時間と各フレームのディレイに基づいて、何番目のフレームを描けばよいかを計算
        const size_t frameIndex_ingredient = AnimatedGIFReader::GetFrameIndex(t1, delays_p1);
        
        // 具材の描画
        if (ingredient_direction == 0){
            p1_textures[frameIndex_ingredient].scaled(ingredient_size).drawAt(ingredient_position);
        }
        else{
            p1_textures[frameIndex_ingredient].mirrored().scaled(ingredient_size).drawAt(ingredient_position);
        }
    }
    else{
        // 経過時間と各フレームのディレイに基づいて、何番目のフレームを描けばよいかを計算
        const size_t frameIndex_tableware = AnimatedGIFReader::GetFrameIndex(t1, delays_p1);
        
        if (tableware->getTablewareMiniGameLoser()){
            // おたまの描画
            miniGame_textures[frameIndex_tableware].scaled(tableware_size).rotated(Math::ToRadians(tableware_angle)).drawAt(tableware_position);
        }
        else{
            // おたまの描画
            p1_textures[frameIndex_tableware].scaled(tableware_size).rotated(Math::ToRadians(tableware_angle)).drawAt(tableware_position);
        }
        
        // 経過時間と各フレームのディレイに基づいて、何番目のフレームを描けばよいかを計算
        const size_t frameIndex_ingredient = AnimatedGIFReader::GetFrameIndex(t2, delays_p2);
        
        // 具材の描画
        if (ingredient_direction == 0){
            p2_textures[frameIndex_ingredient].scaled(ingredient_size).drawAt(ingredient_position);
        }
        else{
            p2_textures[frameIndex_ingredient].mirrored().scaled(ingredient_size).drawAt(ingredient_position);
        }
    }
    
    
    // --------------------------------------------------------------------------------------------
    // 鍋下半分の描画
    // --------------------------------------------------------------------------------------------
    
    m_texture_nabeUnder.scaled(1.3).drawAt(m_position_nabeUnder);
    
    
    // --------------------------------------------------------------------------------------------
    // スキルのクールダウンを描画
    // --------------------------------------------------------------------------------------------
    
    if (ingredient->getSkillEnable() == false) {
		Vec2 ingredient_position = ingredient->getIngredientConfig().ingredient_position;
		int skill_interval = ingredient->getIngredientConfig().skill_interval;
		int skill_view_height = ingredient->getIngredientConfig().skill_view_height;

		RectF(Arg::center(ingredient_position.x, ingredient_position.y - skill_view_height), skill_interval/100+4, 14).draw(ColorF(0, 0, 0));
        Rect(ingredient_position.x - skill_interval/100/2 + 1, ingredient_position.y - skill_view_height - 5, ingredient->getSkillIntervalLen(), 10).draw(ColorF{1, 0, 0});
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

		Vec2 tableware_position = tableware->getTablewareConfig().tableware_position;
		int catchRangeX_left = tableware->getTablewareConfig().tableware_catchRangeX_left;
		int catchRangeX_right = tableware->getTablewareConfig().tableware_catchRangeX_right;
		int catchRangeY_high = tableware->getTablewareConfig().tableware_catchRangeY_high;
		int catchRangeY_low = tableware->getTablewareConfig().tableware_catchRangeY_low;
        Rect(tableware_position.x + catchRangeX_left, tableware_position.y + catchRangeY_high, catchRangeX_right-catchRangeX_left, catchRangeY_low-catchRangeY_high).rounded(10).draw(ColorF{0, 0, 0});

		Vec2 ingredient_position = ingredient->getIngredientConfig().ingredient_position;
		int hitRangeX_left = ingredient->getIngredientConfig().ingredient_hitRangeX_left;
		int hitRangeX_right = ingredient->getIngredientConfig().ingredient_hitRangeX_right;
		int hitRangeY_high = ingredient->getIngredientConfig().ingredient_hitRangeY_high;
		int hitRangeY_low = ingredient->getIngredientConfig().ingredient_hitRangeY_low;
        Rect(ingredient_position.x + hitRangeX_left, ingredient_position.y + hitRangeY_high, hitRangeX_right-hitRangeX_left, hitRangeY_low-hitRangeY_high).rounded(10).draw(ColorF{0, 0, 0});
    }
}
