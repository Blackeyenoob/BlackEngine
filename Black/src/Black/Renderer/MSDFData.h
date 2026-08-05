#pragma once

#ifndef BK_NO_FONT

#include <vector>

#undef INFINITE
#include "msdf-atlas-gen.h"

namespace Black {

	struct MSDFData
	{
		std::vector<msdf_atlas::GlyphGeometry> Glyphs;
		msdf_atlas::FontGeometry FontGeometry;
	};


}

#endif // BK_NO_FONT
