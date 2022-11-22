#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <Utility.hpp>


class Button
{
	public:
					Button();

		void		activate();
		void		deactivate();

		bool		isActive() const;

		void		setFont(const sf::Font& font);
		void		setText(const sf::String& text);
		void		setPosition(sf::Vector2f position);
		void		setPosition(float x, float y);
		void		setColor(sf::Color color);

		sf::Text	getText() const;

	private:
		sf::Text	mText;
		
		bool		mIsActive;
};

#endif