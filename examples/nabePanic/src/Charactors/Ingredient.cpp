#include "Ingredient.hpp"

Ingredient::Ingredient(const InitData& init, InputData ingredient_input, IngredientConfig config) : IScene{ init }
{
	// 具材のID
	ingredient_config.ingredient_id = config.ingredient_id;

	// 画像の向き（0：左、1：右）
	ingredient_config.ingredient_direction = config.ingredient_direction;

	// 移動速度
	ingredient_config.ingredient_speed = config.ingredient_speed;

	// GIFの大きさ
	ingredient_config.ingredient_size = config.ingredient_size;

	// 移動制限
	ingredient_config.ingredient_Xborder_left = config.ingredient_Xborder_left;
	ingredient_config.ingredient_Xborder_right = config.ingredient_Xborder_right;

	// 当たり判定（これを現在の位置にプラスして判定する）
	ingredient_config.ingredient_hitRangeX_right = config.ingredient_hitRangeX_right;
	ingredient_config.ingredient_hitRangeX_left = config.ingredient_hitRangeX_left;
	ingredient_config.ingredient_hitRangeY_high = config.ingredient_hitRangeY_high;
	ingredient_config.ingredient_hitRangeY_low = config.ingredient_hitRangeY_low;

	// スキルの制限時間（ms）
	ingredient_config.skill_timer = config.skill_timer;

	// スキルのインターバル（ms）
	ingredient_config.skill_interval = config.skill_interval;

	// スキルゲージの描画位置
	ingredient_config.skill_view_height = config.skill_view_height;

	// 画像の初期位置
	ingredient_config.ingredient_position = config.ingredient_position;

	// 入力
	this->ingredient_input = ingredient_input;
}

Ingredient::~Ingredient() {}

void Ingredient::update()
{
	// --------------------------------------------------------------------------------------------
	// 具材の画像の位置更新 (ADキーで操作)
	// --------------------------------------------------------------------------------------------

	if (ingredient_input.Left.pressed() && ingredient_config.ingredient_position.x > ingredient_config.ingredient_Xborder_left)
	{
		ingredient_config.ingredient_position.x -= (Scene::DeltaTime() * ingredient_config.ingredient_speed);
		ingredient_config.ingredient_direction = 0;
	}
	if (ingredient_input.Right.pressed() && ingredient_config.ingredient_position.x < ingredient_config.ingredient_Xborder_right)
	{
		ingredient_config.ingredient_position.x += (Scene::DeltaTime() * ingredient_config.ingredient_speed);
		ingredient_config.ingredient_direction = 1;
	}


	// --------------------------------------------------------------------------------------------
	// 具材のスキル発動
	// --------------------------------------------------------------------------------------------

	if (skillActive)
	{
		if (ingredient_stopwatch_skill.ms() < 1000 && ingredient_config.ingredient_id == 2)
		{
			ingredient_config.ingredient_position.y -= (Scene::DeltaTime() * 400);
		}

		if (ingredient_stopwatch_skill.ms() >= 1000 && ingredient_config.ingredient_id == 2)
		{
			if ((ingredient_config.ingredient_position.y + (Scene::DeltaTime() * 400)) < Scene::Height() - 270)
			{
				ingredient_config.ingredient_position.y += (Scene::DeltaTime() * 400);
			}
			else
			{
				ingredient_config.ingredient_position.y = Scene::Height() - 270;
			}
		}

		if (ingredient_stopwatch_skill.ms() > ingredient_config.skill_timer)
		{
			skillActive = false;
			skillEnable = false;

			switch (ingredient_config.ingredient_id) {
			case 0:
				ingredient_config.ingredient_speed /= 4;
				ingredient_stopwatch_skill.reset();
				ingredient_stopwatch_interval.reset();
				ingredient_stopwatch_interval.start();
				break;
			case 1:
				ingredient_config.ingredient_position.y -= 160;

				ingredient_stopwatch_skill.reset();
				ingredient_stopwatch_interval.reset();
				ingredient_stopwatch_interval.start();
				break;
			case 2:
				ingredient_stopwatch_skill.reset();
				ingredient_stopwatch_interval.reset();
				ingredient_stopwatch_interval.start();
				break;
			default:
				break;
			}
		}
	}
	else
	{
		if (skillEnable == false)
		{
			if (ingredient_stopwatch_interval.ms() - skill_interval_prev >= 1000)
			{
				skill_interval_len += ingredient_config.skill_interval / (ingredient_config.skill_interval / 10);
				skill_interval_prev = ingredient_stopwatch_interval.ms();
			}
		}
		if (ingredient_input.Confirm.down() && skillEnable == true && skillActive == false)
		{
			skillActive = true;

			skill_se[ingredient_config.ingredient_id].playOneShot();

			switch (ingredient_config.ingredient_id) {
			case 0:
				ingredient_config.ingredient_speed *= 4;

				ingredient_stopwatch_skill.start();
				break;
			case 1:
				ingredient_config.ingredient_position.y += 160;

				ingredient_stopwatch_skill.start();
				break;
			case 2:
				ingredient_stopwatch_skill.start();
				break;
			default:
				break;
			}
		}

		if (skillEnable == false && ingredient_stopwatch_interval.ms() > ingredient_config.skill_interval)
		{
			skillEnable = true;

			skill_interval_len = 0;
			skill_interval_prev = 0;

			switch (ingredient_config.ingredient_id) {
			case 0:
				ingredient_stopwatch_interval.reset();
				break;
			case 1:
				ingredient_stopwatch_interval.reset();
				break;
			case 2:
				ingredient_stopwatch_interval.reset();
				break;
			default:
				break;
			}
		}
	}
}

void Ingredient::draw() const
{

}
