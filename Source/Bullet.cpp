#include <Bullet.hpp>

#include <iostream>

Bullet::Bullet(AnimationManager anim, Level& lvl, Entity& character, float x, float y, float w, float h) 
: Entity(anim, lvl, x, y, w, h) 
{
	mObjects = lvl.GetAllObjects();
	mAnimations.set("move");

	mName = "Bullet";

	if (character.moveDirection == RIGHT)
	{
		moveDirection = RIGHT;
		mSpeedX = 0.3;
	}	
	else
	{
		moveDirection = LEFT;
		mSpeedX = -0.3;
	}		
}


void Bullet::update(sf::Time dt)
{
	mPositionX += mSpeedX * dt.asMilliseconds();

	for (int i = 0; i < mObjects.size(); i++)
		if (getEntityRectangle().intersects(mObjects[i].rect))
		{
			mAnimations.set("explosion");
			mSpeedX = 0;
			if (mAnimations.isPlaying() == false)
				mIsAlive = false;
		}

	mAnimations.tick(dt);
}