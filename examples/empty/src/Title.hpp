// Title.hpp
#pragma once
#include <Siv3D.hpp>
//#include "SceneManager.hpp"

using App = SceneManager<String>;

class Title : public App::Scene
{
public:
    Title(const InitData& init);
    ~Title();

    void update() override;
    void draw() const override;
};

