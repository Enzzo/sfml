#include "aricraft.h"

Textures::ID ToTextureID(Aircraft::Type type) {
	switch (type) {
	case Aircraft::Type::Eagle: return Textures::ID::Eagle;
	case Aircraft::Type::Raptor: return Textures::ID::Raptor;
	}
}

//--------------------AIRCRAFT-----------------------
Aircraft::Aircraft(Type type, const TextureHolder& textureholder) 
	: type_(type)
	, sprite_(textureholder.Get(ToTextureID(type))) {}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(sprite_, states);
}