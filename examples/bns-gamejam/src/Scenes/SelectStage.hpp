// SelectStage.hpp
#pragma once
#include "Common.hpp"

class SelectStage : public App::Scene
{
public:
    SelectStage(const InitData& init);
    ~SelectStage();

    void update() override;
    void draw() const override;

private:
    Texture textureStageOden;
    Texture textureStageParfait;
    Texture textureStageRandom;
    const VideoTexture Animation{U"bns-gamejam/backgrounds/selectstage.mp4", Loop::Yes};
    const Audio bgm{U"bns-gamejam/sounds/selectstage.mp3", Loop::Yes};
    const Audio cursor{U"bns-gamejam/sounds/cursor.mp3"};
    const Audio confirm{U"bns-gamejam/sounds/confirm.mp3"};
};
