#include "MiniGame.hpp"

int32 count = 10;
double d_time = 0.0;

int32 game_renda(InputGroup p1_in, InputGroup p2_in, Texture p1_img, Texture p2_img)
{
    Rect{Arg::center(Scene::Center()), 1280, 720}.draw(ColorF{Palette::Black, 0.5});
    
    // バー
    Rect::FromPoints(Scene::Center()-Point(500, 300), Scene::Center()-Point((count-10)*50, 250)).draw(ColorF{Palette::Blue});
    Rect::FromPoints(Scene::Center()-Point((count-10)*50, 300), Scene::Center()-Point(-500, 250)).draw(ColorF{Palette::Red});
    
    // キャラ画像
    p1_img.resized(256).drawAt(Scene::Center()+Point(-450, 100));
    p2_img.resized(256).drawAt(Scene::Center()+Point(450, 100));
    
    // 値の増減
    if(p1_in.down()){ count--;}
    if(p2_in.down()){ count++;}
    count = Clamp(count, 0, 20);
    
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
