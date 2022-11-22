#include <GameState.hpp>
#include <WonState.hpp>
#include <TitleState.hpp>
#include <PauseState.hpp>
#include <MenuState.hpp>
#include <Application.hpp>
#include <Bullet.hpp>
#include <Enemy.hpp>



GameState::GameState(Application& application, sf::Texture& tex)
: State(application)
, mLevels()
, mEntities()
, mCamera()
, mShootTimer(sf::seconds(0.5))
, mHitpointsBar(mApplication->mTextures.get(Textures::HitpointsBar))
{
	mLevels.push(std::make_unique<Level>());
	mLevels.top()->LoadFromFile("Resources/Levels/Level1.tmx");

	Object plr = mLevels.top()->GetObject("player");
	mSpawnX = plr.rect.left;
	mSpawnY = plr.rect.top;
	mPlayer = std::make_unique<Player>(mApplication->mAnimations[Animations::Player], *mLevels.top(), mSpawnX, mSpawnY, 70, 85);

	Object bar = mLevels.top()->GetObject("wonBar");
	mWonBar = sf::FloatRect(bar.rect.left, bar.rect.top, bar.rect.width, bar.rect.height);

	std::vector<Object> e = (*mLevels.top()).GetObjects("enemy");
	for (int i = 0; i < e.size(); i++)
		mEntities.push_back(std::make_unique<Enemy>(mApplication->mAnimations[Animations::Enemy], * mLevels.top(), e[i].rect.left, e[i].rect.top, 70, 80));

	
	mCamera.reset(sf::FloatRect(0, 0, mApplication->mWindow.getSize().x, mApplication->mWindow.getSize().y));

	mBGSprite.setTexture(tex);
	mBGSprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
	mBGSprite.setPosition(mCamera.getCenter());
}

void GameState::restartGame()
{
	Object plr = mLevels.top()->GetObject("player");
	mPlayer->mPositionX = mSpawnX;
	mPlayer->mPositionY = mSpawnY;
	mPlayer->mHitpoints = 100;

	mEntities.clear();
	std::vector<Object> e = (*mLevels.top()).GetObjects("enemy");
	for (int i = 0; i < e.size(); i++)
		mEntities.push_back(std::make_unique<Enemy>(mApplication->mAnimations[Animations::Enemy], *mLevels.top(), e[i].rect.left, e[i].rect.top, 70, 80));
}


void GameState::processInput(sf::Event event)
{

	if (event.KeyReleased)
	if (event.key.code == sf::Keyboard::Escape)
		mApplication->pushState(std::make_unique<PauseState>(*mApplication, mApplication->mTextures.get(Textures::MainBG)));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) mPlayer->key["Right"] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) mPlayer->key["Left"] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) mPlayer->key["Space"] = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) mPlayer->key["Ctrl"] = true;
}


void GameState::update(sf::Time dt)
{
	if (mPlayer->getEntityRectangle().intersects(mWonBar))
		mApplication->pushState(std::make_unique<WonState>(*mApplication, mApplication->mTextures.get(Textures::Space)));

	if (mShootTimer < sf::seconds(0.5))
		mShootTimer += dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	if (mShootTimer >= sf::seconds(0.5))
	{

		 mShootTimer = sf::Time::Zero;

		 AnimationManager anim = mApplication->mAnimations[Animations::Bullet];

		 mEntities.push_back(std::make_unique<Bullet>(mApplication->mAnimations[Animations::Bullet], *mLevels.top(), *mPlayer,
							 mPlayer->mPositionX + 18, mPlayer->mPositionY + 33, 5, 5));
		
	}

	std::list<std::unique_ptr<Entity>>::iterator it;
	std::list<std::unique_ptr<Entity>>::iterator it2;

	for (it = mEntities.begin(); it != mEntities.end();)
	{
		(*it)->update(dt);

		if ((*it)->mIsAlive == false)
			it = mEntities.erase(it);
		else
			it++;
	}

	for (it = mEntities.begin(); it != mEntities.end(); it++)
	{

		if ((*it)->mName == "Enemy")
		{
			if (mPlayer->getEntityRectangle().intersects((*it)->getEntityRectangle()))
			if (mPlayer->mSpeedY>0)  mPlayer->mSpeedY = -0.2; 
			else if (!mPlayer->isHit) {
				mPlayer->mHitpoints -= 20; mPlayer->isHit = true;
				if (mPlayer->moveDirection) mPlayer->mPositionX += 10; else mPlayer->mPositionX -= 10;
			}


			for (it2 = mEntities.begin(); it2 != mEntities.end(); it2++)
			{
				if ((*it2)->mName == "Bullet")
					if ((*it2)->getEntityRectangle().intersects((*it)->getEntityRectangle()))
					{
						(*it2)->mIsAlive = false;

						(*it)->mHitpoints -= 30;
					}
			}
		}
	}

	mHitpointsBar.update(mPlayer->mHitpoints);
	mPlayer->update(dt);

	if (mPlayer->mHitpoints <= 0)
		restartGame();

	mCamera.setCenter(mPlayer->mPositionX + 100, mPlayer->mPositionY);
	mApplication->mWindow.setView(mCamera);

	mBGSprite.setPosition(mCamera.getCenter());
}


void GameState::draw(sf::RenderWindow& window)
{
	std::list<std::unique_ptr<Entity>>::iterator it;

	window.draw(mBGSprite);

	mLevels.top()->Draw(window);

	for (it = mEntities.begin(); it != mEntities.end(); it++)
		(*it)->draw(window);

	mHitpointsBar.draw(window);
	mPlayer->draw(window);
}