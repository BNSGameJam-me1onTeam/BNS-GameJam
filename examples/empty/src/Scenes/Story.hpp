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
    Texture m_texture;
};
