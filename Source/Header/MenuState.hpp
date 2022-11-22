#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP


#define NUMBER_OF_MENU_ELEMENTS 2


#include <State.hpp>
#include <Button.hpp>	

class MenuState : public State
{
	public:
							MenuState(Application& application, sf::Texture& tex);

		void				processInput(const sf::Event event) override;
		void				update(sf::Time dt) override;
		void				draw(sf::RenderWindow& window) override;

	private:
		void				moveUp();
		void				moveDown();

	private:
		Button				mButtons[NUMBER_OF_MENU_ELEMENTS];

		sf::Sprite			mBGSprite;
		sf::Texture			mTexture;

		int					mWindowWidth;
		int					mWindowHeight;

		int					mActiveButton;
};	

#endif
