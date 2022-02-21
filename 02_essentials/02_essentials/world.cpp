#include "world.h"
#include "sprite_node.h"

World::World(sf::RenderWindow& window)
	:mWindow(window)
	, mWorldView(window.getDefaultView())
	, mWorldBounds(
		0.f, //left X position
		0.f, //top Y position
		mWorldView.getSize().x, //width
		2000.f)	//height
	, mSpawnPosition(
		mWorldView.getSize().x / 2.f, //X
		mWorldBounds.height - mWorldView.getSize().y) //Y
	, mPlayerAircraft(nullptr) {

	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures() {
	mTextures.Load(Textures::ID::Eagle, "Media/Textures/Eagle.png");
	mTextures.Load(Textures::ID::Raptor, "Media/Textures/Raptor.png");
	mTextures.Load(Textures::ID::Desert, "Media/Textures/Desert.png");
}

void World::buildScene() {
	for (std::size_t i = 0; i < LayerCount; ++i) {
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.AttachChild(std::move(layer));
	}

	sf::Texture& texture = mTextures.Get(Textures::ID::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->AttachChild(std::move(backgroundSprite));

	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Type::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->SetVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->AttachChild(std::move(leader));

	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Type::Raptor, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->AttachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Type::Raptor, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->AttachChild(std::move(rightEscort));
}

void World::draw() {
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

void World::update(sf::Time dt) {
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	if (position.x <= mWorldBounds.left + 150 || position.x >= mWorldBounds.left + mWorldBounds.width - 150) {
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}
	mSceneGraph.update(dt);
}