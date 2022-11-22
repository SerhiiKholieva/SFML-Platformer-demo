#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <Animation.hpp>
#include <Level.hpp>



class Entity
{
public:
							Entity(AnimationManager& anim, Level& lvl, float x, float y, float w, float h);

	void					draw(sf::RenderWindow& window);

	virtual void			update(sf::Time time) = 0;


	sf::FloatRect			getEntityRectangle() const;

public:

	enum
	{
		RIGHT,
		LEFT
	}					    moveDirection;


	AnimationManager		mAnimations;
	std::vector<Object>		mObjects;

	float					mPositionX, mPositionY;
	float					mSpeedX, mSpeedY;
	float					mWidth, mHeight;
	float					mHitpoints;

	std::string				mName;

	bool					mIsAlive;
};

#endif