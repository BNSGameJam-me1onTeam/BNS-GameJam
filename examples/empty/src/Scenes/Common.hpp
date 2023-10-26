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

// プレイヤーデータ role:役割, eqid:装備id, conindex:コントローラーindex
struct PlayerData
{
    int32 role;
    int32 eqid;
    int32 conindex;
};

// キーコンフィグ
struct InputData
{
    InputGroup Left;
    InputGroup Right;
    InputGroup Up;
    InputGroup Down;
    InputGroup Confirm;
};

// 共有するデータ
struct GameData
{
    // コントローラーを使用する
    bool use_controller = false;
    // プレイヤーデータ
    PlayerData p1_data{-1, -1, -1};
    PlayerData p2_data{-1, -1, -1};
    // キーコンフィグ
    InputData p1_input{KeyA, KeyD, KeyW, KeyS, KeyQ};
    InputData p2_input{KeyLeft, KeyRight, KeyUp, KeyDown, KeySlash};
    // ステージid 0:鍋, 1:パフェ
    int32 stage_id = 0;
};

using App = SceneManager<State, GameData>;
