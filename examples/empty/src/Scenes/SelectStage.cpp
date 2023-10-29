// SelectStage.cpp
#include "SelectStage.hpp"
#include "Controller.hpp"

SelectStage::SelectStage(const InitData& init) : IScene{ init }, textureStageOden(U"example/StageOden.png"), textureComingSoon(U"example/ComingSoon.png")
{
    Print << U"SelectStage::SelectStage()";
}

SelectStage::~SelectStage()
{
    Print << U"SelectStage::~SelectStage()";
}

void SelectStage::update()
{
    if ((getData().p1_input.Left.down() || getData().p2_input.Left.down()) && getData().stage_id != 0)
    {
        getData().stage_id -= 1;
        // Print << getData().stage_id;
    }
    if ((getData().p1_input.Right.down() || getData().p2_input.Right.down()) && getData().stage_id != 2)
    {
        getData().stage_id += 1;
        // Print << getData().stage_id;
    }
    // 後々カーソル操作にするので、後でなくす。ステージをクリックすることで次のシーンに移動する
    if (getData().p1_input.Confirm.down() || getData().p2_input.Confirm.down())
    {
        changeScene(State::Title);
    }
    // 後々カーソル操作にするので、後でなくす
    if (KeySpace.down())
    {
        changeScene(State::Story);
    }
}

void SelectStage::draw() const
{
    textureStageOden.resized(300).draw(140,210);
    textureComingSoon.resized(300).draw(490,210);
    textureComingSoon.resized(300).draw(840,210);
    
    Rect{Arg::center(Scene::Center()+Point{cursor+350*getData().stage_id-350, 0}), 300}.drawFrame(0, 5, Palette::Orange);
    Scene::SetBackground(ColorF(1, 1, 1));
}


