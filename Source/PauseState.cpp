#include <PauseState.hpp>

#include <MenuState.hpp>
#include <GameState.hpp>
#include <Application.hpp>


#include <iostream>

PauseState::PauseState(Application& application, sf::Texture& tex)
: State(application)
, mButtons()
, mTexture(tex)
, mView()
, mWindowWidth(mApplication->mWindow.getSize().x)
, mWindowHeight(mApplication->mWindow.getSize().y)
, mActiveButton(0)
{
	for (int i = 0; i < NUMBER_OF_MENU_ELEMENTS; i++)
		mButtons[i].setFont(mApplication->mFonts.get(Fonts::Main));

	for (int i = 0; i < NUMBER_OF_MENU_ELEMENTS; i++)
		mButtons[i].setPosition(mWindowWidth / 2,
		mWindowHeight / (NUMBER_OF_MENU_ELEMENTS + 1) + i * (mWindowHeight / (NUMBER_OF_MENU_ELEMENTS + 1)));

	mButtons[0].setText("Resume");
	mButtons[1].setText("Exit");

	mButtons[mActiveButton].activate();

	mBGSprite.setTexture(mTexture);
	mBGSprite.setPosition(0, 0);

	mView.reset(sf::FloatRect(0, 0, mWindowWidth, mWindowHeight));
}


void PauseState::processInput(const sf::Event event)
{
	if (event.KeyReleased && mButtons[0].isActive())
	if (event.key.code == sf::Keyboard::Return)
	{
		mApplication->popState(); return;
	}
		

	if (event.KeyReleased && mButtons[1].isActive())
	{
		if (event.key.code == sf::Keyboard::Return)
			mApplication->mWindow.close();
	}

	if (event.KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Up)
			moveUp();
		else
		if (event.key.code == sf::Keyboard::Down)
			moveDown();
	}
}


void PauseState::update(sf::Time dt)
{
}


void PauseState::draw(sf::RenderWindow& window)
{
	window.draw(mBGSprite);

	for (int i = 0; i < NUMBER_OF_MENU_ELEMENTS; i++)
	{
		if (mButtons[i].isActive())
			mButtons[i].setColor(sf::Color::Red);
		else
			mButtons[i].setColor(sf::Color::White);

		window.draw(mButtons[i].getText());
	}

	window.setView(mView);
}


void PauseState::moveUp()
{
	if (mActiveButton > 0)
	{
		mButtons[mActiveButton].deactivate();
		mActiveButton--;
		mButtons[mActiveButton].activate();
	}
}


void PauseState::moveDown()
{
	if (mActiveButton < NUMBER_OF_MENU_ELEMENTS - 1)
	{
		mButtons[mActiveButton].deactivate();
		mActiveButton++;
		mButtons[mActiveButton].activate();
	}
}