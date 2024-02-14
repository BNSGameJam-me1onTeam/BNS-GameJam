#pragma once
#include <Siv3D.hpp>

// シーンの名前
enum class State
{
	HowToPlay,
	Title,
	SelectStage,
	Story,
	SelectEquipment,
	Game,
	Result,
};

// プレイヤーデータ role:役割(0:攻め, 1:逃げ), eqid:装備id, conindex:コントローラーindex
struct PlayerData
{
	int8 role;
	int8 eqid;
	int8 conindex;
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
	bool use_controller;

	// プレイヤーデータ
	PlayerData p1_data;
	PlayerData p2_data;

	// キーコンフィグ
	InputData p1_input;
	InputData p2_input;

	// ステージid 0:鍋, 1:パフェ
	int8 stage_id;

	// 勝者 0:P1 1:P2
	int8 winner;
};

using App = SceneManager<State, GameData>;
