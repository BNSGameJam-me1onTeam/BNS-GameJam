#include <Siv3D.hpp>
#include "Title.hpp"
#include "Game.hpp"

void Main()
{
    FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);

    // シーンマネージャーを作成
    SceneManager<String> manager;

    // タイトルシーン（名前は "Title"）を登録
    manager.add<Title>(U"Title");

    // ゲームシーン（名前は "Game"）を登録
    manager.add<Game>(U"Game");

    while (System::Update())
    {
        if (not manager.update())
        {
            break;
        }
    }
}

