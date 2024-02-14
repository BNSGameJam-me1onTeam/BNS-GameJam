#include "stdafx.h"
#include "VideoLoader.hpp"

VideoTexture VideoLoader::LoadVideoFromResource(const FilePathView resourcePath, const FilePathView temporaryFilePath, const Loop loop)
{
# if SIV3D_PLATFORM(WINDOWS)

	if (not FileSystem::Exists(temporaryFilePath))
	{
		BinaryReader reader{ resourcePath };

		if (not reader)
		{
			return{};
		}

		BinaryWriter writer{ temporaryFilePath };
		int64 copySize = reader.size();
		constexpr int64 BlockSize = (1024 * 64);
		Array<Byte> buffer(BlockSize);

		while (copySize)
		{
			const int64 readSize = Min(copySize, BlockSize);
			reader.read(buffer.data(), readSize);
			writer.write(buffer.data(), readSize);
			copySize -= readSize;
		}
	}

	return VideoTexture{ temporaryFilePath, loop };

# else

	return VideoTexture{ resourcePath, loop };

# endif
}
