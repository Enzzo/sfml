#include <assert.h>

template<class resource, class identifier>
void ResourceHolder<resource, identifier>::load(const identifier id, const std::string& filename) {
	std::unique_ptr<resource> src(new resource());
	if (!src->loadFromFile(filename)) {
		throw std::runtime_error("TextureHolder::load(): Failed to load from file "+ filename);
	}
	auto inserted = _src_map.insert(std::make_pair(id, std::move(src)));
	assert(inserted.second);
}

template<class resource, class identifier>
template<class parameter>
void ResourceHolder<resource, identifier>::load(	const identifier id,
												const std::string& filename, 
												const parameter& param) {
	std::unique_ptr<resource> src(new resource());
	if (!src->loadFromFile(filename, param)) {
		throw std::runtime_error("TextureHolder::load(): Failed to load from file " + filename);
	}

	auto inserted = _src_map.insert(std::make_pair(id, std::move(src)));
	assert(inserted.second);
}

template<typename resource, typename identifier>
resource& ResourceHolder<resource, identifier>::get(identifier id) const {
	auto found = _src_map.find(id);
	assert(found != _src_map.end());
	return *found->second;
}