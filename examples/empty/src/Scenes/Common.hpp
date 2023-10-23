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

// プレイヤーデータ role:役割, eqid:装備id, conid:コントローラid
struct PlayerData
{
    int32 role;
    int32 eqid;
    String conid;
};

// 共有するデータ
struct GameData
{
    // コントローラーを使用する
    bool use_controller = false;
    // プレイヤーデータ
    PlayerData p1_data{-1, -1, U""};
    PlayerData p2_data{-1, -1, U""};
    // ステージid 0:鍋, 1:パフェ
    int32 stage_id = 0;
};

using App = SceneManager<State, GameData>;
