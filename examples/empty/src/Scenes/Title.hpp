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
    double alpha = 0.0;
    VideoTexture titleAnimation{U"example/video/title.mp4", Loop::Yes};
    const Audio bgm{ U"example/sound/title.mp3", Loop::Yes};
};

