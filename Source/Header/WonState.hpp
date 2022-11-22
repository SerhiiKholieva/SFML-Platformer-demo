#ifndef WON_STATE_HPP
#define WON_STATE_HPP

#include <State.hpp>


class WonState : public State
{
public:
	WonState(Application& application, sf::Texture& tex);

	void		processInput(const sf::Event event) override;
	void		update(sf::Time dt) override;
	void		draw(sf::RenderWindow& window) override;

private:
	sf::Text	mText;

	sf::Sprite  mBGSprite;

	sf::View	mView;

	sf::Time	mTextAppearanceTime;
	bool		mShowText;

	sf::Time    mTimer;
};

#endif