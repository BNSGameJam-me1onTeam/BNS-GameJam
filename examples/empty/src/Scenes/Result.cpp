// Result.cpp
#include "Result.hpp"

Result::Result(const InitData& init) : IScene{ init }, winner{0}
{
    if(winner){winnerAnimation = VideoTexture{U"example/video/winseme.mp4", Loop::Yes};}
    else{winnerAnimation = VideoTexture{U"example/video/guzaiwin.mp4", Loop::Yes};}
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
    winnerAnimation.advance();
    winnerAnimation.drawAt(Scene::Center());
}

