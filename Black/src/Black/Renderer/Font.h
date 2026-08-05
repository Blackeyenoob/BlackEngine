#pragma once

#ifndef BK_NO_FONT

#include <filesystem>

#include "Black/Core/Base.h"
#include "Black/Renderer/Texture.h"

namespace Black {

	struct MSDFData;

	class Font
	{
	public:
		Font(const std::filesystem::path& font);
		~Font();

		const MSDFData* GetMSDFData() const { return m_Data; }
		Ref<Texture2D> GetAtlasTexture() const { return m_AtlasTexture; }

		static Ref<Font> GetDefault();
	private:
		MSDFData* m_Data;
		Ref<Texture2D> m_AtlasTexture;
	};

}

#endif // BK_NO_FONT
