#include <Animation.hpp>
#include <tinyxml.h>

#include <iostream>

Animation::Animation()
{
}

//Animation constructor receives a texture and the parameters of frames
// scaleX and scaleY are the parameters to normalize a texture to the needed size
Animation::Animation(sf::Texture& tex, int x, int y, int width, int height, int step, 
					 int framesQuantity, float speed, bool isLooped, float scaleX, float scaleY)
: mSprite(tex)
, mAnimationSpeed(speed)
, mCurrentFrame(0)
, mIsPlaying(true)
, mIsFliped(false)
, mIsLooped(isLooped)
{
	mSprite.setScale(scaleX, scaleY);

	for (int i = 0; i < framesQuantity; i++)
	{
		mFrames.push_back(sf::IntRect(x + i * step, y, width, height));
		mFlipedFrames.push_back(sf::IntRect(x + i * step + width, y, -width, height));
	}
}


void Animation::tick(sf::Time time)
{
	if (!mIsPlaying) return;

	mCurrentFrame += mAnimationSpeed * time.asSeconds() * 1500;

	if (mCurrentFrame > mFrames.size())
	{
		mCurrentFrame -= mFrames.size();

		if (!mIsLooped) { mIsPlaying = false; return; }
	}
		


	if (mIsFliped)
		mSprite.setTextureRect(mFlipedFrames[int(mCurrentFrame)]);
	else
		mSprite.setTextureRect(mFrames[int(mCurrentFrame)]);
}



AnimationManager::AnimationManager()
{
}


void AnimationManager::addAnimation(sf::String name, sf::Texture& tex, int x, int y, int width, int height, int framesQuantity,
									float speed, int step, bool isLooped, float scaleX, float scaleY)
{
	mAnimationMap[name] = Animation(tex, x, y, width, height, step, framesQuantity, speed, isLooped, scaleX, scaleY);
	mCurrentAnimation = name;
}


void AnimationManager::loadFromXML(std::string fileName, sf::Texture &t, float scaleX, float scaleY)
{
	TiXmlDocument animFile(fileName.c_str());

	animFile.LoadFile();

	TiXmlElement *head;
	head = animFile.FirstChildElement("sprites");

	TiXmlElement *animElement;
	animElement = head->FirstChildElement("animation");
	while (animElement)
	{
		Animation anim;
		mCurrentAnimation = animElement->Attribute("title");
		int delay = atoi(animElement->Attribute("delay"));
		anim.mAnimationSpeed = 1.0 / delay; anim.mSprite.setTexture(t);
		anim.mCurrentFrame = 0;

		TiXmlElement *cut;
		cut = animElement->FirstChildElement("cut");
		while (cut)
		{
			int x = atoi(cut->Attribute("x"));
			int y = atoi(cut->Attribute("y"));
			int w = atoi(cut->Attribute("w"));
			int h = atoi(cut->Attribute("h"));

			anim.mFrames.push_back(sf::IntRect(x, y, w, h));
			anim.mFlipedFrames.push_back(sf::IntRect(x + w, y, -w, h));
			cut = cut->NextSiblingElement("cut");
		}

		//anim.sprite.setOrigin(0, anim.frames[0].height);
		anim.mSprite.setScale(scaleX, scaleY);

		mAnimationMap[mCurrentAnimation] = anim;
		animElement = animElement->NextSiblingElement("animation");
	}
}

void AnimationManager::draw(sf::RenderWindow& window, int x, int y)
{
	mAnimationMap[mCurrentAnimation].mSprite.setPosition(x, y);
	window.draw(mAnimationMap[mCurrentAnimation].mSprite);
}


void AnimationManager::set(sf::String name)
{
	mCurrentAnimation = name;
}


void AnimationManager::flip(bool b)
{
	mAnimationMap[mCurrentAnimation].mIsFliped = b;
}


void AnimationManager::tick(sf::Time time)
{
	mAnimationMap[mCurrentAnimation].tick(time);
}


void AnimationManager::play()
{
	mAnimationMap[mCurrentAnimation].mIsPlaying = true;
}


void AnimationManager::play(sf::String name)
{
	mAnimationMap[name].mIsPlaying = true;
}


void AnimationManager::pause()
{
	mAnimationMap[mCurrentAnimation].mIsPlaying = false;
}


bool AnimationManager::isPlaying()
{
	return mAnimationMap[mCurrentAnimation].mIsPlaying;
}


sf::String AnimationManager::getCurrentAnimation() const
{
	return mCurrentAnimation;
}

