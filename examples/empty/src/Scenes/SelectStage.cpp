// SelectStage.cpp
#include "SelectStage.hpp"
#include "Controller.hpp"

SelectStage::SelectStage(const InitData& init) : IScene{ init }, m_texture{ U"🐈"_emoji }
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
    if (KeyQ.down())
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
    RoundRect{ 140, 210, 300, 300, 10 }.draw(Palette::Seagreen);
    RoundRect{ 490, 210, 300, 300, 10 }.draw(Palette::Skyblue);
    RoundRect{ 840, 210, 300, 300, 10 }.draw(Palette::Black);
    
    RoundRect{Arg::center(Scene::Center()+Point{cursor+350*getData().stage_id-350, 0}), 300, 300, 10}.drawFrame(0, 5, Palette::Orange);
    Scene::SetBackground(ColorF(1, 1, 1));
    m_texture.drawAt(Cursor::Pos());
}


