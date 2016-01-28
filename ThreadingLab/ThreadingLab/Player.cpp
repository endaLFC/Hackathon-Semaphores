#include "Player.h"


Player::Player()
{
	m_x = 100;
	m_y = 100;
	m_speed = 0.1f;

	m_Texture = Sprite::loadTexture("sprite.png", Renderer::GetInstance()->Get_SDL_RENDERER());

	m_sprite.Init(m_Texture, SDL_Rect{ m_x, m_y, 210, 210 }, SDL_Rect{ 0, 0, 32, 32 });
	m_sprite.SetOffset(SDL_Point{ 10, 10 });
}


void Player::Update(int dir)
{
	Move(dir);
}

void Player::Move(int dir)
{
	if (dir == 1) //UP
	{
		m_y -= m_speed;
	}
	else if (dir == 2) //RIGHT
	{
		m_x += m_speed;
	}
	else if (dir == 3) //DOWN
	{
		m_y += m_speed;
	}
	else if (dir == 4) //LEFT
	{
		m_x -= m_speed;
	}

	m_sprite.SetPosition(m_x, m_y);
}

void Player::Draw()
{
	m_sprite.DrawNoCamOffset();
}


