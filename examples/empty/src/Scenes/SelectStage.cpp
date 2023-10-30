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
    if (getData().p1_input.Left.down() && getData().stage_id != -1)
    {
        getData().stage_id -= 1;
        // Print << getData().stage_id;
    }
    if (getData().p1_input.Right.down() && getData().stage_id != 2)
    {
        getData().stage_id += 1;
        // Print << getData().stage_id;
    }
    // 「戻る」が押されたときの処理
    if (getData().p1_input.Confirm.down() && getData().stage_id == -1)
    {
        changeScene(State::Title);
    // stage_idは0のみ実装。1,2は処理なし
    }else if(getData().p1_input.Confirm.down() && getData().stage_id == 0){
        changeScene(State::Story);
    }
}

void SelectStage::draw() const
{
    
    
    RoundRect{ 90, 150, 250, 60 ,10}.draw(ColorF{ 0.6 });
    textureStageOden.resized(300).draw(140,300);
    textureStageOden.resized(300).draw(140,300);
    textureComingSoon.resized(300).draw(490,300);
    textureComingSoon.resized(300).draw(840,300);
    
    FontAsset(U"TitleFont")(U"ステージを選んでね！（仮）").drawAt(Scene::Center()-Point{0, 260}, ColorF{1.0, 1.0, 1.0});
    
    FontAsset(U"NormalFont")(U"タイトルに戻る").drawAt(Scene::Center()-Point{430, 180}, ColorF{1.0, 1.0, 1.0});
    
    if (getData().stage_id == -1)
    {
        Rect{ 90, 150, 250, 60 }.drawFrame(0, 5, Palette::Orange);
    }
    
    if (getData().stage_id != -1)
    {
        Rect{Arg::center(Scene::Center()+Point{cursor+350*getData().stage_id-350, 90}), 300}.drawFrame(0, 5, Palette::Orange);
    }
    Scene::SetBackground(ColorF(0.2, 0.2, 0.2));
}


