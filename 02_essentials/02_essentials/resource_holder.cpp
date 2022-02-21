#include "resource_holder.h"


template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename) {
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename)) {
		throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);
	}

	auto inserted = res_map_.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template<typename Resource, typename Identifier>
template<typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& second_param) {
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, second_param)) {
		throw std::runtime_error("ResourceHolder::Load - Failed to load " + filename);
	}

	auto inserted = res_map_.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)const {
	auto found = res_map_.find(id);
	assert(found != res_map_.end());
	return *found->second;
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
	auto found = res_map_.find(id);
	assert(found != res_map_.end());
	return *found->second;
}