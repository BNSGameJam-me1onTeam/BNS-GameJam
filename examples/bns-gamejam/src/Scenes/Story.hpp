// Story.hpp
#pragma once
#include "Common.hpp"

class Story : public App::Scene
{
public:
    Story(const InitData& init);
    ~Story();

    void update() override;
    void draw() const override;

private:
    VideoTexture storyAnimation{U"bns-gamejam/backgrounds/story.mp4", Loop::No};
    const Audio bgm{U"bns-gamejam/sounds/story.mp3", Loop::Yes};
};
