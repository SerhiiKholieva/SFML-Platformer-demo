#ifndef BULLET_HPP
#define BULLET_HPP

#include <Entity.hpp>
#include <Player.hpp>


class Bullet :public Entity
{
	public:
				Bullet(AnimationManager anim, Level& lvl, Entity& character, float x, float y, float w, float h);

		void	update(sf::Time dt) override;
};

#endif BULLET_HPP
