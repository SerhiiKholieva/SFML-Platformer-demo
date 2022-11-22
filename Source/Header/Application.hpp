#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <State.hpp>
#include <ResourceHolder.hpp>
#include <Animation.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>
#include <stack>


class Application
{
	public:
														Application();

		void											run();
		
		void											pushState(std::unique_ptr<State> state);
		void											popState();
		void											changeState(std::unique_ptr<State> state);

	private:
		void											checkWindowEvents(sf::Event& event);

	public:
		sf::RenderWindow								mWindow;

		FontHolder										mFonts;
		TextureHolder									mTextures;
		std::map<Animations::ID, AnimationManager>		mAnimations;

	private:
		std::stack<std::unique_ptr<State>>				mStates;

		static const sf::Time							mTimePerFrame;
};

#endif