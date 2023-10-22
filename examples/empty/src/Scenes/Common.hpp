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
    // コントローラーを使用する
    use_controller = false;
    // プレイヤーデータ [役割:0-おたま 1-具材, 装備id:0~3]
    Array<int32>　p1_data = [0, 0];
    Array<int32>　p2_data = [0, 0];
    // ステージid 0:鍋, 1:パフェ
    int32 stage_id = 0;
};

using App = SceneManager<State, GameData>;
