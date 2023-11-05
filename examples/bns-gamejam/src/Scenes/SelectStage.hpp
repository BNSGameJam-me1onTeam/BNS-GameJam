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
    
    const AnimatedGIFReader bg{ Resource(U"bns-gamejam/backgrounds/selectstage.gif")};
    Array<Texture> textures;
    Array<int32> delays;
    const Texture loading{ Resource(U"bns-gamejam/backgrounds/loading.png")};

    const Audio bgm{ Resource(U"bns-gamejam/sounds/selectstage.mp3"), Loop::Yes};
    const Audio cursor{ Resource(U"bns-gamejam/sounds/cursor.mp3")};
    const Audio confirm{ Resource(U"bns-gamejam/sounds/confirm.mp3")};
    
    double flag = 2.0;
};
