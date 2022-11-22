#ifndef TITLE_STATE_HPP
#define TITLE_STATE_HPP

#include <State.hpp>


class TitleState : public State
{
	public:
					TitleState(Application& application, sf::Texture& tex);

		void		processInput(const sf::Event event) override;
		void		update(sf::Time dt) override;
		void		draw(sf::RenderWindow& window) override;

	private:
		sf::Sprite  mBGSprite;
		sf::Texture mTexture;
		sf::Text	mText;

		sf::Time	mTextAppearanceTime;
		bool		mShowText;
};

#endif