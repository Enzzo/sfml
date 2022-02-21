#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include <cassert>

template<typename Resource, typename Identifier>
class ResourceHolder {
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;

public:
	void load(Identifier, const std::string&);

	template<typename Parameter>
	void load(Identifier, const std::string&, const Parameter&);

	const Resource& get(Identifier)const;
	Resource& get(Identifier);

private:
	void insertResource(Identifier, std::unique_ptr<Resource>);
};

#include "resource_holder.inl"