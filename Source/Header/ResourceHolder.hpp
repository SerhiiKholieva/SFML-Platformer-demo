#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP

#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <cassert>


template <typename Identifier, typename Resource>
class ResourceHolder
{
	public:
		void				load(Identifier id, const std::string& filename);

		Resource&			get(Identifier id);
		const Resource&		get(Identifier id) const;

	private:
		void				insertResource(Identifier id, std::unique_ptr<Resource> resource);

	private:
		std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "resourceHolder.inl"
#endif