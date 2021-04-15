#include "AssetManager.h"
#include <cassert>

AssetManager* AssetManager::instance = nullptr;

AssetManager::AssetManager() {
	assert(instance, nullptr);
	instance = this;
}