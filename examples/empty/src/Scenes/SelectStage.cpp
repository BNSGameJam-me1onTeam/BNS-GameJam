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
    Scene::SetBackground(ColorF(0.2, 0.8, 0.6));
    m_texture.drawAt(Cursor::Pos());
}


