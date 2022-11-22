#include <Enemy.hpp>




Enemy::Enemy(AnimationManager& anim, Level& lvl, float x, float y, float w, float h)
: Entity(anim, lvl, x, y, w, h)
, mTimer(sf::Time::Zero)
{

	mName = "Enemy";
	mSpeedX = 0.1;

	mAnimations.set("run");
}


void Enemy::update(sf::Time time)
{
	mPositionX += mSpeedX * time.asMilliseconds();

	mTimer += time;
	if (mTimer > sf::seconds(3.0f))
	{
		mSpeedX *= -1;
		mTimer = sf::Time::Zero;
	}


	if (mHitpoints <= 0)
	{
		mAnimations.set("explosion");
		mSpeedX = 0;

		if (mAnimations.isPlaying() == false)
			mIsAlive = false;
	}

	mAnimations.tick(time);
}