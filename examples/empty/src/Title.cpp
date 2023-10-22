// Title.cpp
#include "Title.hpp"

Title::Title(const InitData& init) : IScene{ init }
{
    Print << U"Title::Title()";
}

Title::~Title()
{
    Print << U"Title::~Title()";
}

void Title::update()
{
    if (MouseL.down())
    {
        changeScene(U"Game");
    }
}

void Title::draw() const
{
    Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });
    FontAsset(U"TitleFont")(U"My Game").drawAt(400, 100);
    Circle{ Cursor::Pos(), 50 }.draw(Palette::Orange);
}

