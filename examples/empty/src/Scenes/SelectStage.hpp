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
    int cursor = 0;
};
