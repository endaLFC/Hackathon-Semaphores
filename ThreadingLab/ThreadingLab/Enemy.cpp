#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	m_x = 100;
	m_y = 100;
	m_speed =  100;

	m_Texture = Sprite::loadTexture("sprite2.png", Renderer::GetInstance()->Get_SDL_RENDERER());

	m_sprite.Init(m_Texture, SDL_Rect{ m_x, m_y, 210, 210 }, SDL_Rect{ 0, 0, 32, 32 });
	m_sprite.SetOffset(SDL_Point{ 10, 10 });
	
	moveLock = SDL_CreateSemaphore(1);
}


void Enemy::Update(float x, float y)
{
	//AI(x,y);
	//Physics();
}

void Enemy::AI(float x, float y)
{
	//SDL_LockMutex(mutex);
	//Sem Lock
	SDL_SemWait(moveLock);
	//std::cout << "AI Lock" << std::endl;

	m_dirX = 0;
	m_dirY = 0;

	if (m_x < x)
	{
		m_dirX = 1;
	}
	else if (m_x > x)
	{
		m_dirX = -1;
	}

	if (m_y < y)
	{
		m_dirY = 1;
	}
	else if (m_y > y)
	{
		m_dirY = -1;
	}

	isColliding(x,y);

	//SDL_UnlockMutex(mutex);
	SDL_SemPost(moveLock);
	//std::cout << "AI Unlock" << std::endl;
}
void Enemy::Physics(float time)
{
	//SDL_LockMutex(mutex);
	//Sem Lock
	SDL_SemWait(moveLock);
	//std::cout << "Physics Lock" << std::endl;

	m_x += m_dirX * m_speed * time;
	m_y += m_dirY * m_speed * time;
	
	m_sprite.SetPosition(m_x, m_y);

	//SDL_UnlockMutex(mutex);
	SDL_SemPost(moveLock);
	//std::cout << "Physics Unlock" << std::endl;
}

void Enemy::Draw()
{
	m_sprite.DrawNoCamOffset();
}

void Enemy::isColliding(float x, float y)
{
	float len = sqrt((m_x - x)*(m_x - x) + (m_y - y)*(m_y - y));
	if (len <= 50)
	{
		m_x = 0;
		m_y = 0;
		m_sprite.SetPosition(m_x,m_y);
	}
}