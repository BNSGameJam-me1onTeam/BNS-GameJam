// SelectEquipment.cpp
#include "SelectEquipment.hpp"

SelectEquipment::SelectEquipment(const InitData& init) : IScene{ init }
{
    Print << U"SelectEquipment::SelectEquipment()";
}

SelectEquipment::~SelectEquipment()
{
    Print << U"SelectEquipment::~SelectEquipment()";
}

void SelectEquipment::update()
{
    if (MouseL.down())
    {
        changeScene(State::Game);
    }
}

void SelectEquipment::draw() const
{
    Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });
    FontAsset(U"TitleFont")(U"My Game").drawAt(400, 100);
    Circle{ Cursor::Pos(), 50 }.draw(Palette::Orange);
}

