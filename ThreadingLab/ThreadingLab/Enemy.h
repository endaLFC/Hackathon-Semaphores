#pragma once
#include "Sprite.h"

class Enemy
{
public:
	Enemy();
	~Enemy()
	{
		delete m_Texture;
	}
	void Update(float x, float y);
	void Draw();
	float getX() { return m_x; }
	float getY() { return m_y; }	
	void AI(float x, float y);
	void Physics(float);
	void isColliding(float x, float y);
private:
	float m_x;
	float m_y;
	float m_dirX;
	float m_dirY;
	float m_speed;

	SDL_mutex* mutex;

	Sprite m_sprite;
	SDL_Texture* m_Texture;

	//The protective semaphore
	SDL_sem *moveLock = NULL;
};

