#ifndef HITPOINTSBAR_HPP
#define HITPOINTSBAR_HPP

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\RectangleShape.hpp>


class HitpointsBar
{
	public:
							HitpointsBar(sf::Texture& tex);


		void				update(int hitpoints);
	

		void				draw(sf::RenderWindow &window);
	

	public:
		sf::Texture			mTexture;
		sf::Sprite			mSptite;
		sf::RectangleShape	mBar;

		int					max;
};

#endif HITPOINTSBAR_HPP
