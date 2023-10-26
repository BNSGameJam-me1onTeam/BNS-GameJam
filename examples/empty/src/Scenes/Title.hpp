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
};

