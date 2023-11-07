#pragma once
#include <map>
#include <iostream>

#include "SFML/graphics.hpp"
#include "SFML/Audio.hpp"

//	+-----------------------------------------------+
//	|				class asset_manager				|
//	+-----------------------------------------------+
//	| singleton										|
//	+-----------------------------------------------+
class asset_manager {
public:	
	~asset_manager();
	
	static asset_manager* instance();

	sf::Texture& get_texture(const std::string& filename);
	sf::SoundBuffer& get_sound_buffer(const std::string& filename);
	sf::Font& get_font(const std::string& filename);
	sf::Shader* get_shader(const std::string& vs_file, const std::string& fs_file);

protected:
	asset_manager() {};

private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::SoundBuffer> _sound_buffers;
	std::map<std::string, sf::Font> _fonts;
	std::map<std::string, std::unique_ptr<sf::Shader>> _shaders;

	static asset_manager* _instance;
};