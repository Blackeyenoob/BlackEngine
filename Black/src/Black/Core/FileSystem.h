#pragma once

#include "Black/Core/Buffer.h"

namespace Black {

	class FileSystem
	{
	public:
		// TODO: move to FileSystem class
		static Buffer ReadFileBinary(const std::filesystem::path& filepath);
	};

}
