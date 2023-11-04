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
    const VideoTexture titleAnimation{U"bns-gamejam/backgrounds/title.mp4", Loop::Yes};
    const Audio bgm{ U"bns-gamejam/sounds/title.mp3", Loop::Yes};
    const Audio confirm{U"bns-gamejam/sounds/confirm.mp3"};
};

