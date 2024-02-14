#pragma once
#include "Common.hpp"
#include "VideoLoader.hpp"

class Title : public App::Scene
{
public:
	Title(const InitData& init);

	~Title();

	void update() override;

	void draw() const override;

	const VideoTexture titleAnimation{ VideoLoader::LoadVideoFromResource(Resource(U"nabePanic/backgrounds/title.mp4"), FileSystem::TemporaryDirectoryPath() + U"MyApp/title.mp4", Loop::Yes) };

	const Audio bgm{ Resource(U"nabePanic/sounds/title.mp3"), Loop::Yes };
	const Audio confirm{ Resource(U"nabePanic/sounds/confirm.mp3") };
};

