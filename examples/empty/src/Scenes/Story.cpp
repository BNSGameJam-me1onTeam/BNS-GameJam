// Story.cpp
#include "Story.hpp"

Story::Story(const InitData& init) : IScene{ init }
{
    Print << U"Story::Story()";
}

Story::~Story()
{
    Print << U"Story::~Story()";
}

void Story::update()
{
    if (MouseL.down())
    {
        changeScene(State::SelectEquipment);
    }
}

void Story::draw() const
{
    Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });
    FontAsset(U"TitleFont")(U"My Game").drawAt(400, 100);
    Circle{ Cursor::Pos(), 50 }.draw(Palette::Orange);
}

