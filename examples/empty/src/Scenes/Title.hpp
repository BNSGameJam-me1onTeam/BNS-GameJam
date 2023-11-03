// Title.hpp
#pragma once
#include "Common.hpp"

class Title : public App::Scene
{
public:
    Title(const InitData& init);
    ~Title();

    void update() override;
    void draw() const override;

private:
    VideoTexture titleAnimation{U"example/backgrounds/title.mp4", Loop::Yes};
    const Audio bgm{ U"example/sounds/title.mp3", Loop::Yes};
    const Audio confirm{U"example/sounds/confirm.mp3"};
};

