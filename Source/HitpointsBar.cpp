#include <HitpointsBar.hpp>


	

HitpointsBar::HitpointsBar(sf::Texture& tex)
{
	mTexture = tex;
	mSptite.setTexture(mTexture);

	mBar.setFillColor(sf::Color(0, 0, 0));
	max = 100;
	mSptite.setScale(2, 2);
}

void HitpointsBar::update(int hitpoints)
{
	if (hitpoints == 100)
		mBar.setSize(sf::Vector2f(0, 0));
	else
		mBar.setSize(sf::Vector2f(20, (max - hitpoints) * 150 / max));
}

void HitpointsBar::draw(sf::RenderWindow &window)
{
	sf::Vector2f center = window.getView().getCenter();
	sf::Vector2f size = window.getView().getSize();

	mSptite.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);
	mBar.setPosition(center.x - size.x / 2 + 11, center.y - size.y / 2 + 13);

	window.draw(mSptite);
	window.draw(mBar);
}



