# include "HowToPlay.hpp"

HowToPlay::HowToPlay(const InitData& init) : IScene{ init }
{
	bgm.play(1.0s);


}

HowToPlay::~HowToPlay() {}

void HowToPlay::update()
{
	if (flag == 2.0)
	{
		Array<Image> images;
		bg.read(images, delays);
		for (const auto& image : images)
		{
			textures << Texture{ image };
		}
		ClearPrint();
		flag = 1.0;
	}

	if (flag > 0)
	{
		flag -= Scene::DeltaTime();
	}

	if (Keyboard::GetAllInputs().size() > 0) {
		bgm.stop(1s);
		confirm.playOneShot();
		changeScene(State::Title);
	}
}

void HowToPlay::draw() const
{
	if (flag == 2.0)
	{
		loading.drawAt(Scene::Center());
		return;
	}

	// アニメーションの経過時間
	const double t = Scene::Time() / 2;

	// 経過時間と各フレームのディレイに基づいて、何番目のフレームを描けばよいかを計算
	const size_t frameIndex = AnimatedGIFReader::GetFrameIndex(t, delays);
	
	textures[frameIndex].drawAt(Scene::Center());

	howto.drawAt(Scene::Center());

	if (flag > 0)
	{
		loading.drawAt(Scene::Center(), ColorF{ 1.0, 1.0, 1.0, flag });
	}
}

