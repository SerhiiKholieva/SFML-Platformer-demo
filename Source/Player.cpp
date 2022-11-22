#include <Player.hpp>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <iostream>


Player::Player(AnimationManager& anim, Level& lvl, float x, float y, float w, float h) : Entity(anim, lvl, x, y, w, h)
{
	mObjects = lvl.GetAllObjects();

	STATE = STAY;

	isHit = false;

	key["Ctrl"] = false;
	key["Left"] = false;
	key["Right"] = false;
	key["Space"] = false;
}

void Player::keyCheck()
{
	if (key["Left"])
	{
		moveDirection = LEFT;
		mSpeedX = -0.3;
		if (STATE == STAY) STATE = RUN;
	}

	if (key["Right"])
	{
		moveDirection = RIGHT;
		mSpeedX = 0.3;
		if (STATE == STAY) STATE = RUN;
	}

	if (key["Space"])
	{
		if (onLadder) STATE = CLIMB;
		if (STATE == STAY || STATE == RUN) { mSpeedY = -0.6; STATE = JUMP; mAnimations.play("jump"); }
		if (STATE == CLIMB) mSpeedY = -0.05;
		if (STATE == CLIMB) if (key["Left"] || key["Right"]) STATE = STAY;
	}


	if (key["Ctrl"])
	{
		isShooting = true;
	}

	//Process key release
	if (!(key["Right"] || key["Left"]))
	{
		mSpeedX = 0;
		if (STATE == RUN) STATE = STAY;
	}

	if (!key["Space"])
	{
		if (STATE == CLIMB) mSpeedY = 0;
	}


	if (!key["Ctrl"])
	{
		isShooting = false;
	}

	key["Right"] = key["Left"] = key["Space"] = key["Ctrl"] = false;
}


void Player::animate(sf::Time time)
{
	if (STATE == STAY) mAnimations.set("stay");
	if (STATE == RUN)  mAnimations.set("run");
	if (STATE == JUMP) mAnimations.set("jump");
	if (STATE == CLIMB) { mAnimations.set("climb"); mAnimations.pause(); if (mSpeedY != 0) mAnimations.play(); }

	if (isShooting) {
		mAnimations.set("shoot");
		if (STATE == RUN) mAnimations.set("shootAndWalk");
	}

	if (isHit) {
		mHitTimer += time;
		if (mHitTimer > sf::seconds(1.f)) { isHit = false; mHitTimer = sf::Time::Zero; }
		mAnimations.set("hit");
	}

	if (moveDirection == LEFT) mAnimations.flip(true);
	else
		mAnimations.flip(false);

	mAnimations.tick(time);
}


void Player::collisionDetectionX()
{
	for (int i = 0; i < mObjects.size(); i++)
	if (getEntityRectangle().intersects(mObjects[i].rect))
	if (mObjects[i].name == "solid")
	{
		if (mSpeedX > 0) mPositionX = mObjects[i].rect.left - mWidth;
		if (mSpeedX < 0) mPositionX = mObjects[i].rect.left + mObjects[i].rect.width;
	}
}


void Player::collisionDetectionY()
{
	for (int i = 0; i < mObjects.size(); i++)
	if (getEntityRectangle().intersects(mObjects[i].rect))
	if (mObjects[i].name == "solid")
	{
		if (mSpeedY > 0) { mPositionY = mObjects[i].rect.top - mHeight; mSpeedY = 0; STATE = STAY; }
		if (mSpeedY < 0) { mPositionY = mObjects[i].rect.top; mSpeedY = 0; }
	}
}


void Player::update(sf::Time time)
{
	keyCheck();

	animate(time);

	if (STATE == CLIMB) if (!onLadder) STATE = STAY;
	if (STATE != CLIMB) mSpeedY += 0.0007 * time.asMilliseconds();
	onLadder = false;

	mPositionX += mSpeedX * time.asMilliseconds();
	collisionDetectionX();

	mPositionY += mSpeedY * time.asMilliseconds();
	collisionDetectionY();
}