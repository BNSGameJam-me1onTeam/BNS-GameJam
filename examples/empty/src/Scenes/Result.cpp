// Result.cpp
#include "Result.hpp"

Result::Result(const InitData& init) : IScene{ init }
{
    Print << U"Result::Result()";
}

Result::~Result()
{
    Print << U"Result::~Result()";
}

void Result::update()
{
    if (MouseL.down())
    {
        changeScene(State::Title);
    }
}

void Result::draw() const
{
    Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });
    FontAsset(U"TitleFont")(U"My Game").drawAt(400, 100);
    Circle{ Cursor::Pos(), 50 }.draw(Palette::Orange);
}

