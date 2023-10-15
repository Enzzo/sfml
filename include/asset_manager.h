#pragma once
#include <map>
#include <iostream>

#include "SFML/graphics.hpp"

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

protected:
	asset_manager() {};

private:
	std::map<std::string, sf::Texture> _textures;

	static asset_manager* _instance;
};