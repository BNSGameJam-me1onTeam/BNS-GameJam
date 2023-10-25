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
    RoundRect{ 140, 210, 300, 300, 10 }.draw(Palette::Orange);
    RoundRect{ 490, 210, 300, 300, 10 }.draw(Palette::Skyblue);
    RoundRect{ 840, 210, 300, 300, 10 }.draw(Palette::Black);
    Scene::SetBackground(ColorF(1, 1, 1));
    m_texture.drawAt(Cursor::Pos());
}


