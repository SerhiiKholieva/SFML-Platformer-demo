#ifndef STATE_HPP
#define STATE_HPP

#include <ResourceIdentifiers.hpp>
#include <Utility.hpp>

#include <SFML\System\Time.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Text.hpp>

class Application;

class State
{
	public:
						State(Application& application);

		virtual void	processInput(sf::Event event) = 0;
		virtual void	update(sf::Time dt) = 0;
		virtual void	draw(sf::RenderWindow& window) = 0;

	public:
		Application*	mApplication;
};

#endif