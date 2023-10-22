#include <Siv3D.hpp>
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
    FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);

    // シーンマネージャーを作成
    App manager;
    // シーンの登録
    manager.add<Title>(State::Title);
    manager.add<SelectStage>(State::SelectStage);
    manager.add<Story>(State::Story);
    manager.add<SelectEquipment>(State::SelectEquipment);
    manager.add<Game>(State::Game);
    manager.add<Result>(State::Result);

    while (System::Update())
    {
        if (not manager.update())
        {
            break;
        }
    }
}

