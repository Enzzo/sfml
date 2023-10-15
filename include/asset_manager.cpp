#include "asset_manager.h"

#include <cassert>

//	+-----------------------------------------------+
//	|	class asset_manager							|
//	+-----------------------------------------------+
//	|	constructor									|
//	+-----------------------------------------------+
//asset_manager::asset_manager() {
//	assert(_instance == nullptr);
//	_instance = this;
//}

//	+-----------------------------------------------+
//	|	class asset_manager							|
//	+-----------------------------------------------+
//	|	get_texture									|
//	+-----------------------------------------------+
sf::Texture& asset_manager::get_texture(const std::string& filename) {
	
	std::map<std::string, sf::Texture>& textures = _instance->_textures;

	std::map<std::string, sf::Texture>::iterator found = textures.find(filename);

	//	Если текстура имеется в словаре, то возвращаем её
	if (found != textures.end()) {
		return found->second;
	}
	//	Иначе - добавляем в словарь и возвращаем её
	else {
		sf::Texture& new_texture = textures[filename];
		
		assert(new_texture.loadFromFile(filename));
			
		return textures.at(filename);
	}
}

//	+-----------------------------------------------+
//	|	class asset_manager							|
//	+-----------------------------------------------+
//	|	instance									|
//	+-----------------------------------------------+
asset_manager* asset_manager::instance() {
	if (!_instance) {
		_instance = new asset_manager;
	}
	return _instance;
}

//	+-----------------------------------------------+
//	|	class asset_manager							|
//	+-----------------------------------------------+
//	|	_instance									|
//	+-----------------------------------------------+
asset_manager* asset_manager::_instance = nullptr;