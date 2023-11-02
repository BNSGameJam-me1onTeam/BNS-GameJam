#include "SelectStage.hpp"
#include "Controller.hpp"

// ステージセレクトの定数
constexpr int RECT_X = 90;                 // 戻るボタンのX座標
constexpr int RECT_Y = 150;                // 戻るボタンのY座標
constexpr int RECT_WIDTH = 250;            // 戻るボタンの幅
constexpr int RECT_HEIGHT = 60;            // 戻るボタンの高さ
constexpr int TEXTURE_SIZE = 300;          // ステージ画像のサイズ
constexpr int TEXTURE_GAP = 350;           // ステージ画像の間隔
constexpr int TEXTURE_Y = 300;             // ステージ画像のY座標
constexpr Point TITLE_FONT_OFFSET = {0, 260};      // タイトルフォントのオフセット
constexpr Point NORMAL_FONT_OFFSET = {430, 180};   // 通常フォントのオフセット

// コンストラクタ: ステージセレクトの開始時に呼び出される
SelectStage::SelectStage(const InitData& init)
    : IScene{ init },
      textureStageOden(U"example/StageOden.png"),        // おでんステージのテクスチャ
      textureComingSoon(U"example/ComingSoon.png")       // 未実装ステージのテクスチャ
{
    bgm.setVolume(0.3);
    bgm.play(1s);
}

// デストラクタ: ステージセレクトの終了時に呼び出される
SelectStage::~SelectStage(){}

// アップデート処理: ステージセレクトの更新
void SelectStage::update()
{
    // 左入力時、かつ現在選択中の項目が左端でなければ、項目枠を左に移動
    if (getData().p1_input.Left.down() && getData().stage_id != -1)
    {
        --getData().stage_id;
        cursor.playOneShot();
    }
    // 右入力時、かつ現在選択中の項目が右端でなければ、項目枠を右に移動
    if (getData().p1_input.Right.down() && getData().stage_id != 2)
    {
        ++getData().stage_id;
        cursor.playOneShot();
    }
    // 確認ボタンを押下時の処理
    if (getData().p1_input.Confirm.down())
    {
        // 戻るボタンが選択中の場合、タイトルシーンに戻る
        if (getData().stage_id == -1)
        {
            bgm.stop(1s);
            confirm.playOneShot();
            changeScene(State::Title);
        }
        // おでんステージが選択中の場合、ストーリーシーンに移動
        else if (getData().stage_id == 0)
        {
            bgm.stop(1s);
            confirm.playOneShot();
            changeScene(State::Story);
        }
    }
}

// 描画処理: ステージセレクトの表示内容を描画
void SelectStage::draw() const
{
    // 背景色の設定
    Scene::SetBackground(ColorF(0.2, 0.2, 0.2));
    
    // 戻るボタンの描画
    RoundRect{ RECT_X, RECT_Y, RECT_WIDTH, RECT_HEIGHT, 10}.draw(ColorF{ 0.6 });

    // ステージの画像を描画
    textureStageOden.resized(TEXTURE_SIZE).draw(RECT_X + 50, TEXTURE_Y);
    textureComingSoon.resized(TEXTURE_SIZE).draw(RECT_X + 50 + TEXTURE_GAP, TEXTURE_Y);
    textureComingSoon.resized(TEXTURE_SIZE).draw(RECT_X + 50 + TEXTURE_GAP * 2, TEXTURE_Y);
    
    // タイトルと戻るテキストの描画
    FontAsset(U"TitleFont")(U"ステージを選んでね！（仮）").drawAt(Scene::Center() - TITLE_FONT_OFFSET, ColorF{1.0, 1.0, 1.0});
    FontAsset(U"NormalFont")(U"タイトルに戻る").drawAt(Scene::Center() - NORMAL_FONT_OFFSET, ColorF{1.0, 1.0, 1.0});

    // 現在選択中の項目を可視化する枠表示
    if (getData().stage_id == -1)
    {
        RoundRect{ RECT_X, RECT_Y, RECT_WIDTH, RECT_HEIGHT, 10}.drawFrame(0, 5, Palette::Orange);
    }
    if (getData().stage_id != -1)
    {
        int xOffset = TEXTURE_GAP * (getData().stage_id - 1);
        RoundRect{Arg::center(Scene::Center() + Point{xOffset, 90}), Size(TEXTURE_SIZE, TEXTURE_SIZE), 10}.drawFrame(0, 5, Palette::Orange);
    }
}

