// 717310 C++ SDL Framework

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "PlayerShip.h"
#include "animatedsprite.h"
#include "fmod.hpp"


// Library includes:
#include <cassert>
#include <SDL.h>
#include <stdio.h>

// Static Members:
Game* Game::sm_pInstance = 0;


Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{ 
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void 
Game::DestroyInstance()
{
	delete sm_pInstance; 
	sm_pInstance = 0;
}

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
{
	
}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	for (int i = 0; i < m_bullets.size(); i++)
	{
		delete m_bullets[i];
		m_bullets[i] = 0;
	}
	for (int i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies[i];
		m_enemies[i] = 0;
	}

	system->release();
}

bool 
Game::Initialise()
{
	const int width = 800;
	const int height = 600;

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	// Ex006.2: Load the player ship sprite.
	// For example: 
	Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");

	// Ex006.2: Create the player ship instance.
	m_player.Initialise(pPlayerSprite);
	
	// Ex006.3: Spawn four rows of 14 alien enemies.
	
	
	for (int i = 0; i < 4; i++) {
		for (int a = 0; a < 14; a++ ) {
			SpawnEnemy(i, a);
		}
	}
	//SpawnEnemy(0, 0);
	// Ex006.3: Fill the container with these new enemies.

	system = NULL;

	result = FMOD::System_Create(&system);      // Create the main system object.
	result = system->init(32, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.

	//system->createSound();

	channel = 0;

	result = system->createSound("assets\\bulletFired.wav", FMOD_DEFAULT, 0, &m_bulletFiredSound);
	result = system->createSound("assets\\Explosion.wav", FMOD_DEFAULT, 0, &m_enemyExplodedSound);


	result = m_enemyExplodedSound->setMode(FMOD_LOOP_OFF);

	//ERRCHECK(result);

	result = m_bulletFiredSound->setMode(FMOD_LOOP_OFF);    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
	//ERRCHECK(result);                           /* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */

	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;




	return (true);
}

bool 
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);
	
	if (m_looping)
	{
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
		}
		
		Draw(*m_pBackBuffer);
	}

	SDL_Delay(1);

	return (m_looping);
}

void 
Game::Process(float deltaTime)
{


	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}



	// Update the game world simulation:

	// Ex003.5: Process each alien enemy in the container.

	for each (Enemy* e in m_enemies) {
		if (!e->IsDead()) {
			e->Process(deltaTime);
		}
	}



	// Ex006.4: Process each bullet in the container.
	for each (Bullet* b in m_bullets) {
		if (!b->IsDead()) {
			b->Process(deltaTime);
		}
	}
	// Ex006.2: Update player...
	m_player.Process(deltaTime);


	// Ex006.4: Check for bullet vs alien enemy collisions...
	// Ex006.4: For each bullet
	for (int i = 0; i < m_bullets.size(); i++) {
		// Ex006.4: For each alien enemy
		for (int a = 0; a < m_enemies.size(); a++) {
			// Ex006.4: Check collision between two entities.
			if (!m_enemies.at(a)->IsDead() && m_enemies.at(a)->IsCollidingWith(*m_bullets.at(i))){
				SpawnExplosion(m_enemies.at(a)->GetPositionX(), m_enemies.at(a)->GetPositionY());
				// Ex006.4: If collided, destory both and spawn explosion.
				m_enemies.at(a)->SetDead(true);
				m_bullets.at(i)->SetDead(true);
				result = system->playSound(m_enemyExplodedSound, 0, false, &channel);
								
			}
			if (m_bullets.at(i)->IsOutOfBounds()) {
				m_bullets.at(i)->SetDead(true);
			}
		}
	}

	// Ex006.4: Remove any dead bullets from the container...
	for (int i = 0; i < m_bullets.size(); i++) {
		if (m_bullets.at(i)->IsDead()) {
			m_bullets.erase(m_bullets.begin() + i);
		}
	}

	// Ex006.4: Remove any dead enemy aliens from the container...
	for (int i = 0; i < m_enemies.size(); i++) {
		if (m_enemies.at(i)->IsDead()) {
			m_enemies.erase(m_enemies.begin() + i);
		}
	}

	

	
	for each (Explosion* b in m_explosions) {
			b->Process(deltaTime);
	}

	for (int i = 0; i < m_explosions.size(); i++) {
		if (m_explosions.at(i)->IsDead()) {
			m_explosions.erase(m_explosions.begin() + i);
		}
	}

	

	//FMOD::System::Update();

	system->update();

	// Ex006.4: Remove any dead explosions from the container...
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	// Ex006.3: Draw all enemy aliens in container...



	for each (Enemy* e in m_enemies) {
		if (!e->IsDead()) {
			e->Draw(*m_pBackBuffer);
		}
			
	}

	// Ex006.4: Draw all bullets in container...
	for each (Bullet* b in m_bullets) {
		if (!b->IsDead()) {
			b->Draw(*m_pBackBuffer);
		}
	}

	for each (Explosion* e in m_explosions) {
		if (!e->IsDead()) {
			e->Draw(*m_pBackBuffer);
		}
	}



	// Ex006.2: Draw the player ship...
	m_player.Draw(*m_pBackBuffer);
	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

void 
Game::MoveSpaceShipLeft()
{
	// Ex006.2: Tell the player ship to move left.
	m_player.setHorizontalVelocity(-100);        
}

// Ex006.2: Add the method to tell the player ship to move right...

void
Game::MoveSpaceShipRight()
{
	m_player.setHorizontalVelocity(100);
}

// Ex006.4: Space a Bullet in game.
void 
Game::FireSpaceShipBullet()
{
	Bullet* b = new Bullet;
	b->SetPosition(m_player.GetPositionX() + 8, m_player.GetPositionY());
	// Ex006.4: Load the player bullet sprite.      
	Sprite* bulletSprite = m_pBackBuffer->CreateSprite("assets\\playerbullet.png");

	// Ex006.4: Create a new bullet object.
	
	// Ex006.4: Set the bullets vertical velocity.
	
	b->Initialise(bulletSprite);
	
	b->SetVerticalVelocity(-500);
	// Ex006.4: Add the new bullet to the bullet container.

	m_bullets.push_back(b);


	
	result = system->playSound(m_bulletFiredSound, 0, false, &channel);
	
	

}


void Game::SpawnExplosion(int x, int y){
	Explosion* e = new Explosion();
	//AnimatedSprite* enemySprite = reinterpret_cast<AnimatedSprite*>(m_pBackBuffer->CreateSprite("assets\\explosion.png"));
	AnimatedSprite* explosionSprite = m_pBackBuffer->CreateAnimatedSprite("assets\\explosion.png");
	e->Initialise(explosionSprite);
	e->SetPosition(x-24, y-24);
	m_explosions.push_back(e);
}



// Ex006.3: Spawn a Enemy in game.
void 
Game::SpawnEnemy(int x, int y)
{
	Enemy* e = new Enemy();
	Sprite* enemySprite = m_pBackBuffer->CreateSprite("assets\\alienenemy.png");
	e->Initialise(enemySprite);
	e->SetPosition(y*(832 / 14), x * 40);

	m_enemies.push_back(e);

	// Ex006.3: Load the alien enemy sprite file.

	// Ex006.3: Create a new Enemy object. 

	// Ex006.3: Add the new Enemy to the enemy container.
}
