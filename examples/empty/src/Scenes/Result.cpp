// Result.cpp
#include "Result.hpp"

Result::Result(const InitData& init) : IScene{ init }
{
    if (getData().winner == 0 or getData().winner == 1)
    {
        int8 winner_id = getData().winner ^ getData().p1_data.role;
        winnerAnimation = AnimatedGIFReader{U"example/background/{}-win.gif"_fmt(winner_id ? U"oden" : U"otama")};
        
        Array<Image> images;
        winnerAnimation.read(images, delays);

        for (const auto& image : images)
        {
            textures << Texture{ image };
        }
        images.clear();
        
        bgm = Audio{U"example/sound/{}-win.mp3"_fmt(winner_id ? U"oden" : U"otama"), Loop::Yes};
        bgm.play(1s);
    }
}

Result::~Result() {}

void Result::update()
{
    if (getData().p1_input.Left.down() or getData().p2_input.Left.down())
    {
        cursor -= 1;
    }
    if (getData().p1_input.Right.down() or getData().p2_input.Right.down())
    {
        cursor += 1;
    }
    cursor = Clamp(cursor, 0, 1);
    
    if (getData().p1_input.Confirm.down() or getData().p2_input.Confirm.down())
    {
        bgm.stop(1s);
        if(cursor){System::Exit();}
        else{changeScene(State::Title);}
    }
}

void Result::draw() const
{
    // GIF表示
    const double t = Scene::Time();
    const size_t frameIndex = AnimatedGIFReader::GetFrameIndex(t, delays);
    textures[frameIndex].scaled(0.7).drawAt(Scene::Center());
    
    // ボタン
    Rect{Arg::center(Scene::Center()+Point{-400, 300}), 210, 50}.rounded(1).drawFrame(0, 10, ColorF{cursor ? Palette::Gray : Palette::White});
    FontAsset(U"NormalFont")(U"タイトルに戻る").drawAt(Scene::Center()+Point{-400, 300}, ColorF{cursor ? Palette::Gray : Palette::White});
    Rect{Arg::center(Scene::Center()+Point{400, 300}), 210, 50}.rounded(1).drawFrame(0, 10, ColorF{cursor ? Palette::White : Palette::Gray});
    FontAsset(U"NormalFont")(U"終了する").drawAt(Scene::Center()+Point{400, 300}, ColorF{cursor ? Palette::White : Palette::Gray});
}

