#pragma once
#include "Common.hpp"
#include "VideoLoader.hpp"

class Story : public App::Scene
{
public:
	Story(const InitData& init);

	~Story();

	void update() override;

	void draw() const override;

private:
	VideoTexture storyAnimation{ VideoLoader::LoadVideoFromResource(Resource(U"nabePanic/backgrounds/story.mp4"), FileSystem::TemporaryDirectoryPath() + U"MyApp/story.mp4", Loop::No) };
	const Audio bgm{ Resource(U"nabePanic/sounds/story.mp3"), Loop::Yes };
};
