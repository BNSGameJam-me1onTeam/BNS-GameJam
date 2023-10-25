// SelectStage.cpp
#include "SelectStage.hpp"

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
    if (KeyA.down() && select != 0)
    {
        select -= 1;
    }
    if (KeyD.down() && select != 2)
    {
        select += 1;
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
    
    RoundRect{Arg::center(Scene::Center()+Point{cursor+350*select-350, 0}), 300, 300, 10}.drawFrame(0, 5, Palette::Orange);
    Scene::SetBackground(ColorF(1, 1, 1));
    m_texture.drawAt(Cursor::Pos());
}


