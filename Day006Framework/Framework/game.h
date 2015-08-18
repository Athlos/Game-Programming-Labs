// 717310 C++ SDL Framework
#ifndef __GAME_H__
#define __GAME_H__



// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;

#include "PlayerShip.h";
#include "enemy.h";
#include "bullet.h";
#include "explosion.h";
#include "fmod.hpp";
#include <vector>;

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool DoGameLoop();
	void Quit();

	void MoveSpaceShipLeft();
	void FireSpaceShipBullet();
	void MoveSpaceShipRight();

	void SpawnEnemy(int x, int y);
	void SpawnExplosion(int x, int y);
	
protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

	// Game Entities:
	// Ex006.2: Add a PlayerShip field.    
	PlayerShip m_player;
	// Ex006.3: Add an alien enemy container field.
	std::vector<Enemy*> m_enemies;
	// Ex006.4: Add a bullet container field.
	std::vector<Bullet*> m_bullets;

	std::vector<Explosion*> m_explosions;

	FMOD::System *system;
	FMOD::Sound* m_bulletFiredSound;
	FMOD::Sound* m_enemyExplodedSound;
	FMOD_RESULT result;
	FMOD::Channel* channel;

private:

};

#endif // __GAME_H__
