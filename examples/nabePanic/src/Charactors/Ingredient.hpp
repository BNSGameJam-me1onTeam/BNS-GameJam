#pragma once
#include "Common.hpp"

struct IngredientConfig
{
	int ingredient_id;

	int ingredient_direction;

	int ingredient_speed;

	double ingredient_size;

	int ingredient_Xborder_left;
	int ingredient_Xborder_right;

	int ingredient_hitRangeX_right;
	int ingredient_hitRangeX_left;
	int ingredient_hitRangeY_high;
	int ingredient_hitRangeY_low;

	int skill_timer;
	int skill_interval;
	int skill_view_height;

	Vec2 ingredient_position;
};

class Ingredient : public App::Scene
{
public:
	Ingredient(const InitData& init, InputData ingredient_input, IngredientConfig ingredient_config);

	~Ingredient();

	void update() override;

	void draw() const override;

	IngredientConfig getIngredientConfig() const {
		return ingredient_config;
	}

	Stopwatch getStopwatchSkill()
	{
		return ingredient_stopwatch_interval;
	}

	void stopwatchSkillSwitching(int flag)
	{
		if (flag == 0)
		{
			ingredient_stopwatch_skill.pause();
		}
		else
		{
			ingredient_stopwatch_skill.resume();
		}
	}

	Stopwatch getStopwatchhInterval()
	{
		return ingredient_stopwatch_skill;
	}

	void stopwatchIntervalSwitching(int flag)
	{
		if (flag == 0)
		{
			ingredient_stopwatch_interval.pause();
		}
		else
		{
			ingredient_stopwatch_interval.resume();
		}
	}

	bool getSkillEnable() {
		return skillEnable;
	}

	double getSkillIntervalLen()
	{
		return skill_interval_len;
	}

private:
	InputData ingredient_input;

	Stopwatch ingredient_stopwatch_skill;
	Stopwatch ingredient_stopwatch_interval;

	IngredientConfig ingredient_config;

	int skill_interval_prev = 0;

	double skill_interval_len = 0;

	bool skillActive = false;

	bool skillEnable = true;

	const Array<Audio> skill_se = {
		Audio{ Resource(U"nabePanic/sounds/skill_1.mp3")},
		Audio{ Resource(U"nabePanic/sounds/skill_2.mp3")},
		Audio{ Resource(U"nabePanic/sounds/skill_3.mp3")}
	};
};
