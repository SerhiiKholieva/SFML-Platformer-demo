#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace sf
{
	class Texture;
	class Font;
}

class AnimationManager;

namespace Textures
{
	enum ID
	{
		Player,
		Bullet,
		Enemy,
		Explosion,
		HitpointsBar,
		MainBG,
		Space
	};
}


namespace Animations
{
	enum ID
	{
		Player,
		Bullet,
		Enemy,
		Explosion
	};
}

namespace Fonts
{
	enum ID
	{
		Main
	};
}

template <typename Identifier, typename Resource>
class ResourceHolder;

typedef ResourceHolder<Textures::ID, sf::Texture> TextureHolder;
typedef ResourceHolder<Fonts::ID, sf::Font> FontHolder;
typedef ResourceHolder<Animations::ID, AnimationManager> AnimationHolder;

#endif