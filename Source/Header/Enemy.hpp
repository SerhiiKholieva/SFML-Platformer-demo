#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <Entity.hpp>

#include <SFML\System\Time.hpp>


class Enemy : public Entity
{
	public:
		Enemy(AnimationManager& anim, Level& lvl, float x, float y, float w, float h);

		void		update(sf::Time time) override;

	public:
		sf::Time	mTimer;
};

#endif