#include "SelectStage.hpp"
#include "Controller.hpp"

// 定数の定義
constexpr int RECT_X = 90;
constexpr int RECT_Y = 150;
constexpr int RECT_WIDTH = 250;
constexpr int RECT_HEIGHT = 60;
constexpr int TEXTURE_SIZE = 300;
constexpr int TEXTURE_GAP = 350;
constexpr int TEXTURE_Y = 300;
constexpr Point TITLE_FONT_OFFSET = {0, 260};
constexpr Point NORMAL_FONT_OFFSET = {430, 180};

SelectStage::SelectStage(const InitData& init)
    : IScene{ init },
      textureStageOden(U"example/StageOden.png"),
      textureComingSoon(U"example/ComingSoon.png")
{
    Print << U"SelectStage::SelectStage()";
}

SelectStage::~SelectStage()
{
    Print << U"SelectStage::~SelectStage()";
}

void SelectStage::update()
{
    if (getData().p1_input.Left.down() && getData().stage_id != -1)
    {
        --getData().stage_id;
    }
    if (getData().p1_input.Right.down() && getData().stage_id != 2)
    {
        ++getData().stage_id;
    }

    if (getData().p1_input.Confirm.down())
    {
        if (getData().stage_id == -1)
        {
            changeScene(State::Title);
        }
        else if (getData().stage_id == 0)
        {
            changeScene(State::Story);
        }
    }
}

void SelectStage::draw() const
{
    Scene::SetBackground(ColorF(0.2, 0.2, 0.2));
    
    RoundRect{ RECT_X, RECT_Y, RECT_WIDTH, RECT_HEIGHT, 10}.draw(ColorF{ 0.6 });

    textureStageOden.resized(TEXTURE_SIZE).draw(RECT_X + 50, TEXTURE_Y);
    textureComingSoon.resized(TEXTURE_SIZE).draw(RECT_X + 50 + TEXTURE_GAP, TEXTURE_Y);
    textureComingSoon.resized(TEXTURE_SIZE).draw(RECT_X + 50 + TEXTURE_GAP * 2, TEXTURE_Y);
    
    FontAsset(U"TitleFont")(U"ステージを選んでね！（仮）").drawAt(Scene::Center() - TITLE_FONT_OFFSET, ColorF{1.0, 1.0, 1.0});
    FontAsset(U"NormalFont")(U"タイトルに戻る").drawAt(Scene::Center() - NORMAL_FONT_OFFSET, ColorF{1.0, 1.0, 1.0});

    if (getData().stage_id == -1)
    {
        Rect{ RECT_X, RECT_Y, RECT_WIDTH, RECT_HEIGHT }.drawFrame(0, 5, Palette::Orange);
    }
    
    if (getData().stage_id != -1)
    {
        int xOffset = TEXTURE_GAP * (getData().stage_id - 1);
        Rect{Arg::center(Scene::Center() + Point{xOffset, 90}), TEXTURE_SIZE}.drawFrame(0, 5, Palette::Orange);
    }
}

