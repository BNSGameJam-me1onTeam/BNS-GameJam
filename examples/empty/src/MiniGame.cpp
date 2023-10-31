#include "MiniGame.hpp"
#include "math.h"

int32 count = 10;
double d_time = 0.0;

int8 game_renda(InputGroup p1_in, InputGroup p2_in, Texture p1_img, Texture p2_img)
{
    Rect{Arg::center(Scene::Center()), 1280, 720}.draw(ColorF{Palette::Black, 0.5});
    
    if(d_time < 1.0)
    {
        FontAsset(U"CountFont")(3).drawAt(Scene::Center(), ColorF{1.0, 1.0, 1.0});
    }
    else if(d_time >= 1.0 and d_time < 2.0)
    {
        p1_img.resized(1024).drawAt(Scene::Center()-Point(300, 0));
        FontAsset(U"CountFont")(2).drawAt(Scene::Center()+Point(200, 0), ColorF{1.0, 1.0, 1.0});
    }
    else if(d_time >= 2.0 and d_time < 3.0)
    {
        p2_img.resized(1024).drawAt(Scene::Center()+Point(300, 0));
        FontAsset(U"CountFont")(1).drawAt(Scene::Center()-Point(200, 0), ColorF{1.0, 1.0, 1.0});
    }
    else{
        // バー
        Rect::FromPoints(Scene::Center()-Point(500, 300), Scene::Center()-Point((count-10)*50, 250)).draw(ColorF{Palette::Blue});
        Rect::FromPoints(Scene::Center()-Point((count-10)*50, 300), Scene::Center()-Point(-500, 250)).draw(ColorF{Palette::Red});
        // キャラ画像
        p1_img.resized(256).drawAt(Scene::Center()+Point(-400, 100));
        p2_img.resized(256).drawAt(Scene::Center()+Point(400, 100));
        // 値の増減
        if(p1_in.down()){ count--;}
        if(p2_in.down()){ count++;}
        count = Clamp(count, 0, 20);
    }

    
    // 勝利判定
    if(count <= 0)
    {
        count = 10;
        d_time = 0.0;
        return 1;
    }
    if(count >= 20)
    {
        count = 10;
        d_time = 0.0;
        return 2;
    }
    d_time += Scene::DeltaTime();
    return 0;
}
