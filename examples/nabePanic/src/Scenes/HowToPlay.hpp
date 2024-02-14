# pragma once
# include "Common.hpp"

class HowToPlay : public App::Scene
{
public:
	HowToPlay(const InitData& init);

	~HowToPlay();

	void update() override;

	void draw() const override;

private:
	Array<Texture> textures;
	Array<int32> delays;

	const AnimatedGIFReader bg{ Resource(U"nabePanic/backgrounds/selectstage.gif") };

	const Texture loading{ Resource(U"nabePanic/backgrounds/loading.png") };
	const Texture howto{ Resource(U"nabePanic/images/howto.png") };

	const Audio bgm{ Resource(U"nabePanic/sounds/selectstage.mp3"), Loop::Yes };
	const Audio confirm{ Resource(U"nabePanic/sounds/confirm.mp3") };

	double flag = 2.0;
};

