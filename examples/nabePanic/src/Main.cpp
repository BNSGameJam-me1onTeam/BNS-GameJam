// シーン関連
#include "Title.hpp"
#include "SelectStage.hpp"
#include "Story.hpp"
#include "SelectEquipment.hpp"
#include "Game.hpp"
#include "Result.hpp"
#include "Common.hpp"

void Main()
{
    Window::Resize(1280, 720);
    Window::SetTitle(U"鍋パニック！逆襲の具材たち");
    //仮
    FontAsset::Register(U"CountFont", 300, Typeface::Heavy);
    FontAsset::Register(U"TitleFont", 60, Typeface::Bold);
    FontAsset::Register(U"LargeFont", 40, Typeface::Bold);
    FontAsset::Register(U"NormalFont", 28, Typeface::Bold);

    // シーンマネージャーを作成
    App manager;
    // シーンの登録
    manager.add<Title>(State::Title);
    manager.add<SelectStage>(State::SelectStage);
    manager.add<Story>(State::Story);
    manager.add<SelectEquipment>(State::SelectEquipment);
    manager.add<Game>(State::Game);
    manager.add<Result>(State::Result);
    
    // テスト用
//    manager.init(State::SelectEquipment);
    
    int FPS = 60; // 1秒間に1画面を書き換える回数
    Stopwatch sw;   //FPS60
    sw.start(); //FPS60

    while (System::Update())
    {
        if (not manager.update())
        {
            break;
        }
        while (sw.msF() < 1000.0 / FPS);    //1/60秒経過するまでループ
        sw.restart();
    }
}
