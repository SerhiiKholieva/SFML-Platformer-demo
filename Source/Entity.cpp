#include <Entity.hpp>


Entity::Entity(AnimationManager& anim, Level& lvl, float x, float y, float w, float h)
: mAnimations(anim)
, mObjects()
, mPositionX(x)
, mPositionY(y)
, mSpeedX(0)
, mSpeedY(0)
, mWidth(w)
, mHeight(h)
, mHitpoints(100)
, mIsAlive(true)
{
}

sf::FloatRect Entity::getEntityRectangle() const
{
	return sf::FloatRect(mPositionX, mPositionY, mWidth, mHeight);
}

void Entity::draw(sf::RenderWindow& window)
{
	mAnimations.draw(window, mPositionX, mPositionY);
}