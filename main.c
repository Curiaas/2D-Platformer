#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "data.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RESOLUTION_WIDTH 1280
#define RESOLUTION_HEIGHT 720
#define FPS 60

void renderTex(int, float, float, float, SDL_Renderer*, SDL_Texture*[]);



int main(int argc, char *argv[]) 
{
	printf("argc = %d, name of exe: %s\n\n", argc, argv[0]);
	FILE* print;
	print = fopen("output.txt", "w");
	
	data game;
    game.column = 32;
	game.row = 18;
	game.open = true;
	game.end = false;
	float PpB = RESOLUTION_HEIGHT / game.row;

	// Basic Framework
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
	{
		fprintf(print, "SDL_Init failed: %s\n", SDL_GetError());
		return 1;
	}
	
	
	SDL_Window* win = SDL_CreateWindow("2D Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0);
	if (!win)
	{
		fprintf(print, "SDL_Window failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	
	
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
	if (!rend)
	{
		fprintf(print, "SDL_Renderer failed: %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	// Basic Framework End

	// Texture Initialization
	#define NumberOfTextures 7
	SDL_Texture* texNum[NumberOfTextures];
	for (int i = 0; i < NumberOfTextures; i++)
	{
		char buf[100];
		sprintf(buf, "textures/tex%d.png", i);
		SDL_Surface* temp = IMG_Load(buf);
		texNum[i] = SDL_CreateTextureFromSurface(rend, temp);
		SDL_FreeSurface(temp);
	}
	// Texture Initialization End
	
/*	// Background
	SDL_RenderClear(rend);
	SDL_Surface* BackgroundImage = IMG_Load("textures/texBackground.jpg");
	SDL_Texture* texBackgroundImage = SDL_CreateTextureFromSurface(rend, BackgroundImage);
	SDL_FreeSurface(BackgroundImage);
	SDL_RenderCopy(rend, texBackgroundImage, NULL, NULL);
*/	// Background End

	// Level 1
	// Init Map 1
	FILE* map1;
	map1 = fopen("map1.txt", "r");
	level level1;
	for (int i = 0; i < game.row; i++)
	{
		fgets(level1.map[i], (game.column*2)+1, map1);
		fprintf(print, "level1.map[%d]: %s", i, level1.map[i]);
	}
	fclose(map1);
	// Init Map 1 End
	// Rendering
    SDL_RenderClear(rend);
	FILE* rendertests;
	rendertests = fopen("rendertests.txt", "w");
	int TexFromMap;
	for (int m = 0; m < game.row; m++)
	{
		for (int n = 0, i = 0; n < game.column*2; n+=2, i++)
		{
			TexFromMap = level1.map[m][n];
			fprintf(rendertests, "TexFromMap[%d][%d]: %d\n", m , n, TexFromMap);
			renderTex(TexFromMap, i, m, PpB, rend, texNum);
		}
	}
	fclose(rendertests);
	SDL_RenderPresent(rend);
	// Rendering End
	
	while (game.open && !(game.end))
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
				if (event.type == SDL_QUIT)
				{
					game.open = false;
					game.end = true;
				}
				else if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.scancode)
					{
						case SDL_SCANCODE_ESCAPE:
							game.open = false;
							game.end = true;
							break;
						default:
							break;
					}
				}
		}
		SDL_Delay(1000/FPS);
	}
	// Level 1 End
	
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);									
	SDL_Quit();
	fclose(print);
	return 0;
}

// renderTex(int texNumber, float x_offset, float y_offset, PpB, rend, texNum);
void renderTex(int texNumber, float x_offset, float y_offset, float PpB, SDL_Renderer* rend, SDL_Texture* texNum[])
{
	
	SDL_Rect RrenderTex;
	RrenderTex.x = x_offset*PpB;
	RrenderTex.y = y_offset*PpB;
	RrenderTex.w = PpB;
	RrenderTex.h = PpB;
	
	switch(texNumber)
	{
	case 48:
		SDL_RenderCopy(rend, texNum[0], NULL, &RrenderTex);
		break;
	case 49:
		SDL_RenderCopy(rend, texNum[4], NULL, &RrenderTex);
		break;
	case 50:
		SDL_RenderCopy(rend, texNum[2], NULL, &RrenderTex);
		break;
	case 51:
		SDL_RenderCopy(rend, texNum[3], NULL, &RrenderTex);
		break;
	case 52:
		SDL_RenderCopy(rend, texNum[4], NULL, &RrenderTex);
		break;
	case 53:
		SDL_RenderCopy(rend, texNum[5], NULL, &RrenderTex);
		break;
	case 54:
		SDL_RenderCopy(rend, texNum[6], NULL, &RrenderTex);
		break;
	case 55:
		SDL_RenderCopy(rend, texNum[7], NULL, &RrenderTex);
		break;
/*	case 8:
		SDL_RenderCopy(rend, texNum[8], NULL, &RrenderTex);
		break;
	case 9:
		SDL_RenderCopy(rend, texNum[9], NULL, &RrenderTex);
		break;
*/	default: 
		break;
	}
}