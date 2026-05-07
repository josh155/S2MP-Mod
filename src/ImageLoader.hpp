#pragma once

#include "structs.h"

class ImageLoader {
public:
	static bool dumpImage(GfxImage* image);
	static void reloadImages();
	static bool loadFromDisk(GfxImage* image);
	static void init();
};
