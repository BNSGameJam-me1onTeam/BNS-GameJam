# pragma once
# include <Siv3D.hpp>

// シーンの名前
enum class State
{
    Title,
    SelectStage,
    Story,
    SelectEquipment,
    Game,
    Result,
};

// 共有するデータ
struct GameData
{
    String test = U"共有データ";
};

using App = SceneManager<State, GameData>;
