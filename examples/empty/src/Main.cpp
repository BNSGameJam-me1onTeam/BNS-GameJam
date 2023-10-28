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
    Window::SetTitle(U"鍋パニック！逆襲の具材たち（適）");
    //仮
    FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);
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
    //manager.init(State::Game);

    while (System::Update())
    {
        if (not manager.update())
        {
            break;
        }
    }
}

