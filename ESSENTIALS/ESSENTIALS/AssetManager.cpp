#include "AssetManager.h"
#include <cassert>

static AssetManager* instance = nullptr;

AssetManager::AssetManager() {
	assert(instance, nullptr);
}