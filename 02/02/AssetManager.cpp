#include "AssetManager.h"


class cant_load_image {
public: const std::string& what = "can't load image or texture\n";
};

AssetManager* AssetManager::instance = nullptr;

AssetManager::AssetManager() {
	assert(instance == nullptr);
	instance = this;
}

sf::Texture& AssetManager::GetTexture(const std::string& filename) {
	//Проверить, загружена ли текстура с указанным filename
	std::map<std::string, sf::Texture>& mt = instance->mapTex;
	const std::map<std::string, sf::Texture>::iterator tex = mt.find(filename);
		//Если не загружена, то загрузить
	if (tex == mt.end()) try{
		if (!mt[filename].loadFromFile(filename)) {
			throw cant_load_image();
		}
	}
	catch (cant_load_image c) {
		std::cerr << c.what;
	}
	//Вернуть ссылку на текстуру
	return mt.at(filename);
}
