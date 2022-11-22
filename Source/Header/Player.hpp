#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <Entity.hpp>

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Player : public Entity
{
	public:
										Player(AnimationManager& anim, Level& lvl, float x, float y, float w, float h);

		void							keyCheck();

		void							collisionDetectionX();
		void							collisionDetectionY();

		void							animate(sf::Time time);
		void							update(sf::Time time) override;

	public:

		enum
		{
			STAY,
			RUN,
			JUMP,
			CLIMB,	
			ATTACK
		}								STATE;


		std::map<sf::String, bool>		key;

		sf::Time						mHitTimer;

		bool							onLadder;
		bool							isShooting;
		bool							isHit;
};

#endif