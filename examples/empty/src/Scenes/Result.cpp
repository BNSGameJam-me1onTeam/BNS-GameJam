// Result.cpp
#include "Result.hpp"

Result::Result(const InitData& init) : IScene{ init }
{
    if (getData().winner == 0 or getData().winner == 1)
    {
        int8 winner_id = getData().winner ^ getData().p1_data.role;
        winnerAnimation = AnimatedGIFReader{U"example/background/{}-win.gif"_fmt(winner_id ? U"oden" : U"otama")};
        
        // 各フレームの画像と、次のフレームへのディレイ（ミリ秒）をロード
        Array<Image> images;
        winnerAnimation.read(images, delays);

        for (const auto& image : images)
        {
            textures << Texture{ image };
        }
        images.clear();
    }
}

Result::~Result() {}

void Result::update()
{
    if (MouseL.down())
    {
        changeScene(State::Title);
    }
}

void Result::draw() const
{
    const double t = Scene::Time();
    const size_t frameIndex = AnimatedGIFReader::GetFrameIndex(t, delays);
    textures[frameIndex].scaled(0.7).drawAt(Scene::Center());
}

