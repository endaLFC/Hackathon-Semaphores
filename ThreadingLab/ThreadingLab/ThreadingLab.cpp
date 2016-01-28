// ThreadingLab.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <SDL.h>
#include "Renderer.h"
#include "Player.h"
#include "KeyBoardInput.h"
#include "Enemy.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1248;			//SDL
const int SCREEN_HEIGHT = 704;			//SDL


int PhysicsThread(void * data);
int AIThread(void * data);
Enemy* e1;
SDL_Thread *AI_Thread = NULL;
SDL_Thread *Physics_Thread = NULL;
bool quit = false;


int _tmain(int argc, _TCHAR* argv[])
{
	SDL_Window* window = NULL;
	Player* p1;
	
	// Timing variables
	Uint32 old_time, current_time;
	float ftime;

	// Need to initialize this here for event loop to work
	current_time = SDL_GetTicks();

	//SDL
#pragma region SDL STUFF
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create Renderer for the Window
			if (!Renderer::GetInstance()->Init(window, SCREEN_WIDTH, SCREEN_HEIGHT))
			{
				return 0;
			}
			p1 = new Player();
			e1 = new Enemy();
			
			AI_Thread = SDL_CreateThread(AIThread,"AI Thread",(void*)p1);
			Physics_Thread = SDL_CreateThread(PhysicsThread, "Physics Thread", NULL);
			SDL_Event e;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0){
					KeyBoardInput::GetInstance()->updateKeyboard(e);
					switch (e.type)
					{
					case SDL_QUIT:
						quit = true;
						break;

					}
				}

				old_time = current_time;
				current_time = SDL_GetTicks();
				ftime = (current_time - old_time) / 1000.0f;

				if (ftime > 0)
					cout << ftime << endl;


				//update stuff
				if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_UP))
				{
					p1->Update(1);
				}
				if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_RIGHT))
				{
					p1->Update(2);
				}
				if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_DOWN))
				{
					p1->Update(3);
				}
				if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_LEFT))
				{
					p1->Update(4);
				}
				
				//e1->Update(p1->getX(),p1->getY());

				Renderer::GetInstance()->ClearRenderer();
				//draw stuff
				p1->Draw();
				e1->Draw();
				Renderer::GetInstance()->RenderScreen();
			}//end while wuit
		}//end else
	//	delete p1;
		return 0;
	}
}

int PhysicsThread(void *data)
{
	Uint32 oldTime, currentTime;
	float ticks;
	currentTime = SDL_GetTicks();


	while (!quit)
	{
		oldTime = currentTime;
		currentTime = SDL_GetTicks();
		ticks = (currentTime - oldTime)/1000.0f;

		e1->Physics(ticks);
	}

	return 0;
}
int AIThread(void *data)
{
	Player *p = (Player*)data;

	while (!quit)
	{
		e1->AI(p->getX(), p->getY());
	}

	return 0;
}
