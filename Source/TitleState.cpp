#include <TitleState.hpp>
#include <MenuState.hpp>

#include <Application.hpp>

TitleState::TitleState(Application& application, sf::Texture& tex)
: State(application)
, mTexture(tex)
, mBGSprite()
, mText()
, mTextAppearanceTime(sf::Time::Zero)
, mShowText(true)
{
	mBGSprite.setTexture(mTexture);
	mBGSprite.setPosition(0, 0);
	mText.setFont(mApplication->mFonts.get(Fonts::Main));
	mText.setString("Press any key");
	centerOrigin(mText);
	mText.setPosition(sf::Vector2f(mApplication->mWindow.getSize() / 2u));
	mText.setColor(sf::Color::Cyan);
}


void TitleState::processInput(const sf::Event event)
{
	//change the state when a key is pressed
	if (event.type == sf::Event::KeyReleased)
		mApplication->changeState(std::make_unique<MenuState>(*mApplication, mApplication->mTextures.get(Textures::MainBG)));
}


void TitleState::update(sf::Time dt)
{
	mTextAppearanceTime += dt;

	if (mTextAppearanceTime >= sf::seconds(0.5f))
	{
		mShowText = !mShowText;
		mTextAppearanceTime = sf::Time::Zero;
	}
}


void TitleState::draw(sf::RenderWindow& window)
{
	window.draw(mBGSprite);

	if (mShowText)
		window.draw(mText);
}