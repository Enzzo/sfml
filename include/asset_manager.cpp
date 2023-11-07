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
//	|	get_sound_buffer							|
//	+-----------------------------------------------+
sf::SoundBuffer& asset_manager::get_sound_buffer(const std::string& filename) {
	std::map<std::string, sf::SoundBuffer>& buffers = _instance->_sound_buffers;

	std::map<std::string, sf::SoundBuffer>::iterator found = buffers.find(filename);

	// Если такой буфер имеется в словаре, то возвращаем его
	if (found != buffers.end()) {
		return found->second;
	}

	// Иначе - добавляем в словарь и возвращаем его
	else {
		sf::SoundBuffer& new_buffer = buffers[filename];

		assert(new_buffer.loadFromFile(filename));

		return buffers.at(filename);
	}
}

//	+-----------------------------------------------+
//	|	class asset_manager							|
//	+-----------------------------------------------+
//	|	get_font									|
//	+-----------------------------------------------+
sf::Font& asset_manager::get_font(const std::string& filename) {
	std::map<std::string, sf::Font>& fonts = _instance->_fonts;

	std::map<std::string, sf::Font>::iterator found = fonts.find(filename);

	// Если такой буфер имеется в словаре, то возвращаем его
	if (found != fonts.end()) {
		return found->second;
	}

	// Иначе - добавляем в словарь и возвращаем его
	else {
		sf::Font& new_font = fonts[filename];

		assert(new_font.loadFromFile(filename));

		return fonts.at(filename);
	}
}

//	+-----------------------------------------------+
//	|	class asset_manager							|
//	+-----------------------------------------------+
//	|	get_shader									|
//	+-----------------------------------------------+
sf::Shader* asset_manager::get_shader(const std::string& vs_file, const std::string& fs_file) {
	std::map<std::string, std::unique_ptr<sf::Shader>>& shader_map = _shaders;

	// The key to be stored ni the map
	const std::string& combine_key = vs_file + ";" + fs_file;
	std::map<std::string, std::unique_ptr<sf::Shader>>::iterator found = shader_map.find(combine_key);

	if (found != shader_map.end()) {
		return found->second.get();
	}
	else {
		// create an element in the shader map
		std::unique_ptr<sf::Shader>& shader = (shader_map[combine_key] = std::unique_ptr<sf::Shader>(new sf::Shader()));
		shader->loadFromFile(vs_file, fs_file);
		return shader.get();
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