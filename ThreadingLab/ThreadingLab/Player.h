#pragma once
#include "sdl.h"
#include "Sprite.h"

class Player
{
public:
	Player();
	~Player()
	{
		delete m_Texture;
	}
	
	void Update(int dir);
	void Draw();
	float getX() { return m_x; }
	float getY() { return m_y; }
	

private:
	float m_x;
	float m_y;
	int m_dir;
	float m_speed;

	Sprite m_sprite;
	SDL_Texture* m_Texture;

	void Move(int dir);
};

