#pragma once
#include "Common.hpp"

class Mob : public App::Scene
{
public:
	Mob(const InitData& init, int guzai_id);

	~Mob();

	void update() override;

	void draw() const override;

private:

	// ----------------------------------------
	// 具材
	// ----------------------------------------

	Texture m_texture_mob;

	Vec2 m_position_mob;

	Array<Image> images_mob;
	Array<int32> delays_mob;
	Array<Texture> mob_textures;

	double size_mob;

	int direction_mob;

	int Xborder_left_mob;
	int Xborder_right_mob;

	int speed_mob;
};
