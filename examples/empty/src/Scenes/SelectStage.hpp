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
    const Audio bgm{U"example/sounds/selectstage.mp3", Loop::Yes};
    const Audio cursor{U"example/sounds/cursor.mp3"};
    const Audio confirm{U"example/sounds/confirm.mp3"};
};
