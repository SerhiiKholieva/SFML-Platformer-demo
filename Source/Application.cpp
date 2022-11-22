#include <Application.hpp>
#include <TitleState.hpp>


#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>

const sf::Time Application::mTimePerFrame = sf::seconds(1.f / 60.f);

//Loadining all the resources of the game, such as textures, fonts, maps etc...
Application::Application()
: mWindow(sf::VideoMode(1280, 720), "HeavyR combat")
, mStates()
, mFonts()
, mTextures()
{
	mFonts.load(Fonts::Main, "Resources/Sansation.ttf");

	mTextures.load(Textures::Player, "Resources/Textures/Megaman.png");
	mTextures.load(Textures::Bullet, "Resources/Textures/Bullet.png");
	mTextures.load(Textures::Enemy, "Resources/Textures/Enemy.png");
	mTextures.load(Textures::Explosion, "Resources/Textures/Explosion.png");
	mTextures.load(Textures::HitpointsBar, "Resources/Textures/HealthBar.png");
	mTextures.load(Textures::MainBG, "Resources/Textures/MainBG.png");
	mTextures.load(Textures::Space, "Resources/Textures/Space.png");
	
	mAnimations[Animations::Player] = AnimationManager();
	mAnimations[Animations::Player].loadFromXML("Resources/Animations/MegamanAnim.xml", mTextures.get(Textures::Player), 2.2, 2.2);
	mAnimations[Animations::Player].mAnimationMap["jump"].mIsLooped = false;

	mAnimations[Animations::Bullet] = AnimationManager();
	mAnimations[Animations::Bullet].addAnimation("move", mTextures.get(Textures::Bullet), 7, 10, 8, 8, 1, 0, 0, true, 3, 3);
	mAnimations[Animations::Bullet].addAnimation("explosion", mTextures.get(Textures::Bullet), 27, 7, 18, 18, 4, 0.01, 29, false, 3, 3);

	mAnimations[Animations::Enemy] = AnimationManager();
	mAnimations[Animations::Enemy].loadFromXML("Resources/Animations/EnemyAnim.xml", mTextures.get(Textures::Enemy), 0.5, 0.5);
	mAnimations[Animations::Enemy].loadFromXML("Resources/Animations/ExplosionAnim.xml", mTextures.get(Textures::Explosion), 0.5, 0.5);
	mAnimations[Animations::Enemy].mAnimationMap["explosion"].mIsLooped = false;

	//Pushing on the top of the stack Title state when the game are started
	mStates.push(std::make_unique<TitleState>(*this, mTextures.get(Textures::MainBG)));
}


//Main game sicle. The mechanism whithin the sicle are constructed to give 60 fps game perfomence
void Application::run()
{
	sf::Clock clock;
	sf::Time  timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Event event;

		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		

		if (timeSinceLastUpdate > mTimePerFrame)
		{
			timeSinceLastUpdate -= mTimePerFrame;

			mWindow.clear(sf::Color::Green);
			
			checkWindowEvents(event);
		
			mStates.top()->processInput(event);
			mStates.top()->update(mTimePerFrame);
			mStates.top()->draw(mWindow);

			mWindow.display();
		}	
	}
}


void Application::pushState(std::unique_ptr<State> state)
{
	mStates.push(std::move(state));
}


void Application::popState()
{
	mStates.pop();
}


void Application::changeState(std::unique_ptr<State> state)
{
	mStates.pop();
	mStates.push(std::move(state));
}


void Application::checkWindowEvents(sf::Event& event)
{
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}