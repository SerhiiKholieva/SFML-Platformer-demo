#include <WonState.hpp>
#include <MenuState.hpp>

#include <Application.hpp>

#include <iostream>

WonState::WonState(Application& application, sf::Texture& tex)
: State(application)
, mText()
, mView()
, mTextAppearanceTime(sf::Time::Zero)
, mShowText(true)
, mTimer(sf::Time::Zero)
{
	mText.setFont(mApplication->mFonts.get(Fonts::Main));
	mText.setString("You Won!");
	centerOrigin(mText);
	mText.setPosition(sf::Vector2f(mApplication->mWindow.getSize() / 2u));
	mText.setColor(sf::Color::Cyan);

	mBGSprite.setTexture(tex);
	mBGSprite.setPosition(0, 0);

	mView.reset(sf::FloatRect(0, 0, application.mWindow.getSize().x, application.mWindow.getSize().y));
}


void WonState::processInput(const sf::Event event)
{
	
	//change the state when a key is pressed
	//if (event.type == sf::Event::KeyReleased)
		//mApplication->pushState(std::make_unique<MenuState>(*mApplication, mApplication->mTextures.get(Textures::MainBG)));
	
}


void WonState::update(sf::Time dt)
{
	mTextAppearanceTime += dt;
	mTimer += dt;

	if (mTimer > sf::seconds(5.f)) mApplication->pushState(std::make_unique<MenuState>(*mApplication, mApplication->mTextures.get(Textures::MainBG)));

	if (mTextAppearanceTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextAppearanceTime = sf::Time::Zero;
	}
}


void WonState::draw(sf::RenderWindow& window)
{
	mApplication->mWindow.setView(mView);
	mApplication->mWindow.draw(mBGSprite);

	if (mShowText)
		window.draw(mText);

}
