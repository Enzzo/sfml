#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <cassert>

namespace Textures {
	enum class ID {
		Landscape,
		Airplane,
		Missile
	};
}

template<typename Resource, typename Identifier>
class ResourceHolder {
	std::map<Identifier, std::unique_ptr<Resource>> res_map_;

public:
	void Load(Identifier, const std::string&);

	template<typename Parameter>
	void Load(Identifier, const std::string&, const Parameter&);

	const Resource& Get(Identifier)const;
	Resource& Get(Identifier);
};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& filename) {
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename)) {
		throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);
	}

	auto inserted = res_map_.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template<typename Resource, typename Identifier>
template<typename Parameter>
void ResourceHolder<Resource, Identifier>::Load<Parameter>(Identifier id, const std::string& filename, const Parameter& second_param) {
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, second_param)) {
		throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);
	}

	auto inserted = res_map_.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id)const {
	auto found = res_map_.find(id);
	assert(found != res_map_.end());
	return *found->second;
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id) {
	auto found = res_map_.find(id);
	assert(found != res_map_.end());
	return *found->second;
}