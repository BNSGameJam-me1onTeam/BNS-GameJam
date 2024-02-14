#pragma once
#include "Common.hpp"

struct TablewareConfig
{
	double tableware_size;

	double tableware_angle;

	int tableware_direction;

	int tableware_speed;

	int scoop_speed;

	int scoop_JudgeHeight;

	int tableware_catchRangeX_right;
	int tableware_catchRangeX_left;
	int tableware_catchRangeY_high;
	int tableware_catchRangeY_low;

	int tableware_top_height;
	int tableware_under_height;

	int tableware_Xborder_right;
	int tableware_Xborder_left;

	Vec2 tableware_position;
};

class Tableware : public App::Scene
{
public:
	Tableware(const InitData& init, InputData tableware_input, TablewareConfig tableware_config);

	~Tableware();

	void update() override;

	void draw() const override;

	TablewareConfig getTablewareConfig() const {
		return tableware_config;
	}

	bool getTablewareMiniGameLoser() {
		return tableware_miniGameLoser;
	}

	void tablewareMiniGameLoserSwitching(int flag) {
		if (flag == 0)
		{
			tableware_miniGameLoser = false;
		}
		else
		{
			tableware_miniGameLoser = true;
		}
	}

	void setTablewarePosition(const Vec2& newPosition) {
		tableware_config.tableware_position = newPosition;
	}

private:
	InputData tableware_input;

	TablewareConfig tableware_config;

	bool tableware_miniGameLoser;
};

