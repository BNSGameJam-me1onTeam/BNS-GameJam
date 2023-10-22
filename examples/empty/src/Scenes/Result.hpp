// Result.hpp
#pragma once
#include "Common.hpp"

class Result : public App::Scene
{
public:
    Result(const InitData& init);
    ~Result();

    void update() override;
    void draw() const override;

private:
    Texture m_texture;
};