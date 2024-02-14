// SelectStage.hpp
#pragma once
#include "Common.hpp"
#include "VideoLoader.hpp"

class SelectStage : public App::Scene
{
public:
	SelectStage(const InitData& init);

	~SelectStage();

	void update() override;

	void draw() const override;

private:
	Texture textureStageOden;
	Texture textureStageParfait;
	Texture textureStageRandom;

	Array<Texture> textures;
	Array<int32> delays;

	const AnimatedGIFReader bg{ Resource(U"nabePanic/backgrounds/selectstage.gif") };
	
	const Texture loading{ Resource(U"nabePanic/backgrounds/loading.png") };

	const Audio bgm{ Resource(U"nabePanic/sounds/selectstage.mp3"), Loop::Yes };
	const Audio cursor{ Resource(U"nabePanic/sounds/cursor.mp3") };
	const Audio confirm{ Resource(U"nabePanic/sounds/confirm.mp3") };

	double flag = 2.0;
};
