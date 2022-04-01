#include "aircraft.h"
#include "resource_holder.h"

Textures::ID toTextureID(Aircraft::Type type) {
	/*switch (type) {
	case Aircraft::Eagle: return Textures::Eagle;
	case Aircraft::Raptor: return Textures::Raptor;
	}
	return Textures::Eagle;*/
	return (type == Aircraft::Raptor) ? Textures::Raptor : Textures::Eagle;
}

//--------------------AIRCRAFT-----------------------
Aircraft::Aircraft(Type type, const TextureHolder& textureholder)
	: mType(type)
	, mSprite(textureholder.get(toTextureID(type))) {
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(mSprite, states);
}