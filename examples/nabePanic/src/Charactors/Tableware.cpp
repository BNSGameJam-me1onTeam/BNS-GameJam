#include "Tableware.hpp"

Tableware::Tableware(const InitData& init, InputData tableware_input, TablewareConfig config) : IScene{ init }
{
	// GIFの大きさ
	tableware_config.tableware_size = config.tableware_size;

	// 画像の回転
	tableware_config.tableware_angle = config.tableware_angle;

	// 画像の向き（0：左、1：右）
	tableware_config.tableware_direction = config.tableware_direction;

	// 移動速度
	tableware_config.tableware_speed = config.tableware_speed;

	// すくう速さ
	tableware_config.scoop_speed = config.scoop_speed;

	// すくった判定をする際の高さ（これより大きくないといけない）
	tableware_config.scoop_JudgeHeight = config.scoop_JudgeHeight;

	// 当たり判定（これを現在の位置にプラスして判定する）
	tableware_config.tableware_catchRangeX_right = config.tableware_catchRangeX_right;
	tableware_config.tableware_catchRangeX_left = config.tableware_catchRangeX_left;
	tableware_config.tableware_catchRangeY_high = config.tableware_catchRangeY_high;
	tableware_config.tableware_catchRangeY_low = config.tableware_catchRangeY_low;

	// 移動制限
	tableware_config.tableware_top_height = config.tableware_top_height;
	tableware_config.tableware_under_height = config.tableware_under_height;
	tableware_config.tableware_Xborder_right = config.tableware_Xborder_right;
	tableware_config.tableware_Xborder_left = config.tableware_Xborder_left;

	// 画像の初期位置
	tableware_config.tableware_position = Vec2(900, Scene::Height() - (Scene::Height() - config.tableware_top_height));

	// 入力
	this->tableware_input = tableware_input;

	// ミニゲームの敗北判定
	this->tableware_miniGameLoser = false;
}

Tableware::~Tableware() {}

void Tableware::update()
{
	if (!tableware_miniGameLoser) {
		if (tableware_input.Confirm.pressed() && tableware_config.tableware_position.y < Scene::Height() - tableware_config.tableware_under_height) {
			tableware_config.tableware_position.y += (Scene::DeltaTime() * tableware_config.scoop_speed);
		}
		if (!tableware_input.Confirm.pressed() && tableware_config.tableware_position.y > tableware_config.tableware_top_height) {
			tableware_config.tableware_position.y -= (Scene::DeltaTime() * tableware_config.scoop_speed);
		}
		if (tableware_input.Left.pressed() && tableware_config.tableware_position.x > tableware_config.tableware_Xborder_left && tableware_config.tableware_position.y < Scene::Height() - tableware_config.tableware_under_height - 5) {
			tableware_config.tableware_position.x -= (Scene::DeltaTime() * tableware_config.tableware_speed);
		}
		if (tableware_input.Right.pressed() && tableware_config.tableware_position.x < tableware_config.tableware_Xborder_right && tableware_config.tableware_position.y < Scene::Height() - tableware_config.tableware_under_height - 5) {
			tableware_config.tableware_position.x += (Scene::DeltaTime() * tableware_config.tableware_speed);
		}
	}
}

void Tableware::draw() const
{

}
