#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <State.hpp>
#include <Player.hpp>
#include <level.hpp>
#include <HitpointsBar.hpp>

#include <SFML\Graphics\View.hpp>

#include <stack>
#include <memory>
#include <list>

class GameState : public State
{
	public:
											GameState(Application& application, sf::Texture& tex);

		void								processInput(sf::Event event) override;
		void								update(sf::Time dt) override;
		void								draw(sf::RenderWindow& window) override;

	private:
		void								restartGame();

	public:
		std::stack<std::unique_ptr<Level>>	mLevels;
		std::list<std::unique_ptr<Entity>>  mEntities;

		std::unique_ptr<Player>			    mPlayer;
		HitpointsBar						mHitpointsBar;
		float								mSpawnX;
		float								mSpawnY;

		sf::Sprite							mBGSprite;

		sf::View							mCamera;

		sf::Time							mShootTimer;

		sf::FloatRect						mWonBar;
};

#endif