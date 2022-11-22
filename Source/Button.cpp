#include <Button.hpp>

Button::Button()
: mText()
, mIsActive(false)
{
	centerOrigin(mText);
}


void Button::activate()
{
	mIsActive = true;
}


void Button::deactivate()
{
	mIsActive = false;
}


bool Button::isActive() const
{
	return mIsActive;
}

void Button::setFont(const sf::Font& font)
{
	mText.setFont(font);
}


void Button::setText(const sf::String& text)
{
	mText.setString(text);
}


void Button::setPosition(sf::Vector2f position)
{
	mText.setPosition(position);
}


void Button::setPosition(float x, float y)
{
	mText.setPosition(x, y);
}


void Button::setColor(sf::Color color)
{
	mText.setColor(color);
}

sf::Text Button::getText() const
{
	return mText;
}