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
    Texture textureComingSoon;
    const Audio bgm{U"bns-gamejam/sounds/selectstage.mp3", Loop::Yes};
    const Audio cursor{U"bns-gamejam/sounds/cursor.mp3"};
    const Audio confirm{U"bns-gamejam/sounds/confirm.mp3"};
};
