#pragma once
#include <Siv3D.hpp>

class VideoLoader
{
public:
	static VideoTexture LoadVideoFromResource(const FilePathView resourcePath, const FilePathView temporaryFilePath, const Loop loop);
};
