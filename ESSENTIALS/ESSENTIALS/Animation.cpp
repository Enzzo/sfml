#include "Animation.h"

Animator::Animator(sf::Sprite& sprite)
	:m_Sprite(sprite)
	,m_CurrentTime()
	,m_CurrentAnimation(nullptr){}

Animator::Animation& Animator::CreateAnimation(const std::string& name, const std::string& textureName, const sf::Time& duration, bool loop) {
	m_Animations.push_back(Animator::Animation(name, textureName, duration, loop));
	
	//If we don't have any other animations, use that as current animation
	if (m_CurrentAnimation == nullptr) {
		SwitchAnimation(&m_Animations.back());
	}

	return m_Animations.back();
}

void Animator::SwitchAnimation(Animator::Animation* animation) {
	//Change the sprite texture
	if (animation != nullptr) {
		m_Sprite.setTexture(AssetManager::GetTexture(animation->m_TextureName));
	}

	m_CurrentAnimation = animation;
	m_CurrentTime = sf::Time::Zero; //Reset the time
}

bool Animator::SwitchAnimation(const std::string& name) {
	auto animation = FindAnimation(name);
	if (animation != nullptr) {
		SwitchAnimation(animation);
		return true;
	}
	return false;
}

Animator::Animation* Animator::FindAnimation(const std::string& name) {
	for (auto it = m_Animations.begin(); it != m_Animations.end(); ++it) {
		if (it->m_Name == name) {
			return &*it;
		}
	}
	return nullptr;
}

std::string Animator::GetCurrentAnimationName() const {
	if (m_CurrentAnimation != nullptr) {
		return m_CurrentAnimation->m_Name;
	}

	//If no animation is playing, return empty string
	return "";
}

void Animator::Update(const sf::Time& dt) {
	//If we don't have any animations yet return
	if (m_CurrentAnimation == nullptr) {
		return;
	}

	m_CurrentTime += dt;

	//Get the current animation frame
	float scaledTime = (m_CurrentTime.asSeconds() / m_CurrentAnimation->m_Duration.asSeconds());
	int numFrames = m_CurrentAnimation->m_Frames.size();
	int currentFrame = static_cast<int>(scaledTime * numFrames);

	//If the animation is looping, calculate the correct frame
	if (m_CurrentAnimation->m_Looping) {
		currentFrame %= numFrames;
	}
	else if (currentFrame >= numFrames) { //If the current frame is greater than the number of frames
		currentFrame = numFrames - 1; //Show last frame
	}
	//Set the texture rectangle, depending on the frame
	m_Sprite.setTextureRect(m_CurrentAnimation->m_Frames[currentFrame]);
}