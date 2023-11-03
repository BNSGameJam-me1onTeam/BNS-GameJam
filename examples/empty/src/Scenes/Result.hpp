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
    AnimatedGIFReader winnerAnimation;
    Array<Texture> textures;
    Array<int32> delays;
    int32 cursor = 0;
    Audio bgm;
    const Audio cursor_s{U"example/sounds/cursor.mp3"};
    const Audio confirm{U"example/sounds/confirm.mp3"};
};
