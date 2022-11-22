#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <map>



class Animation
{

public:
								 Animation();
								 Animation(sf::Texture& tex, int x, int y, int width, int height, 
									       int step, int framesQuantity, float speed, bool loop, float scaleX, float scaleY);

	void						 tick(sf::Time time);

public:
	sf::Sprite					 mSprite;

	std::vector<sf::IntRect>	 mFrames;
	std::vector<sf::IntRect>	 mFlipedFrames;

	float						 mAnimationSpeed;
	float						 mCurrentFrame;

	bool						 mIsFliped;
	bool						 mIsPlaying;
	bool						 mIsLooped;
};




class AnimationManager
{

public:
										AnimationManager();

	void								addAnimation(sf::String name, sf::Texture& tex, int x, int y, 
													 int width, int height, int framesQuantity, float speed, int step, bool isLooped, float scaleX, float scaleY);
	void								loadFromXML(std::string fileName, sf::Texture &tex, float scaleX, float scaleY);

	void								draw(sf::RenderWindow& window, int x, int y);

	void								set(sf::String name);
	void								flip(bool b);								
	void								tick(sf::Time time);
	void								play();
	void								play(sf::String name);
	void								pause();


	bool								isPlaying();

	sf::String							getCurrentAnimation() const;

public:
	std::map<sf::String, Animation>		mAnimationMap;
	sf::String							mCurrentAnimation;
};

#endif