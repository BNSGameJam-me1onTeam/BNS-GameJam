// SelectStage.cpp
#include "SelectStage.hpp"
#include "Controller.hpp"

SelectStage::SelectStage(const InitData& init) : IScene{ init }, textureStageOden(U"example/StageOden.png")
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
    if (getData().p1_input.Confirm.down() || getData().p2_input.Confirm.down())
    {
        changeScene(State::Title);
    }
    if (KeySpace.down())
    {
        changeScene(State::Story);
    }
}

void SelectStage::draw() const
{
    Rect{ 490, 210, 300 }.draw(Palette::Skyblue);
    Rect{ 840, 210, 300 }.draw(Palette::Black);
    
    Rect{Arg::center(Scene::Center()+Point{cursor+350*getData().stage_id-350, 0}), 300}.drawFrame(0, 5, Palette::Orange);
    textureStageOden.resized(300).draw(140,210);
    Scene::SetBackground(ColorF(1, 1, 1));
}


