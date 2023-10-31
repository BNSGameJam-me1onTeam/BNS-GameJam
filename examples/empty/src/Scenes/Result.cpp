// Result.cpp
#include "Result.hpp"

Result::Result(const InitData& init) : IScene{ init }
{
    if (getData().winner == 0 or getData().winner == 1)
    {
        int8 winner_id = getData().winner ^ getData().p1_data.role;
        winnerAnimation = VideoTexture{U"example/video/{}win.mp4"_fmt(winner_id ? U"guzai" : U"otama"), Loop::Yes};
    }
}

Result::~Result() {}

void Result::update()
{
    if(winnerAnimation.isEmpty())
    {
        changeScene(State::Title);
        Print << U"ERROR";
    }
    if (MouseL.down())
    {
        changeScene(State::Title);
    }
}

void Result::draw() const
{
    Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });
    winnerAnimation.advance();
    winnerAnimation.scaled(0.5).drawAt(Scene::Center());
}

