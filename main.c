#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "data.h"

#include <stdio.h>
#include <stdlib.h>

#define RESOLUTION_WIDTH 1280
#define RESOLUTION_HEIGHT 720

void renderTex(int, float, float, float, SDL_Renderer*, SDL_Texture*[]);



int main(int argc, char *argv[]) 
{
	printf("argc = %d, name of exe: %s\n\n", argc, argv[0]);
	FILE* print;
	print = fopen("output.txt", "w");
	
	data game;
    game.column = 16;
	game.row = 9;
	float PpB = RESOLUTION_HEIGHT / game.row;
	
	// Init Map 1
	FILE* map1;
	map1 = fopen("map2.txt", "r");
	level level1;
	for (int i = 0; i < game.row; i++)
	{
		fgets(level1.map[i], (game.column*2)+1, map1);
		fprintf(print, "level1.map[%d]: %s", i, level1.map[i]);
	}
	fclose(map1);
	// Init Map 1 End
	

	
	
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
	#define NumberOfTextures 4
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
	
/*	// testing
	SDL_RenderClear(rend);
	SDL_Surface* BackgroundImage = IMG_Load("textures/Background.jpg");
	SDL_Texture* texBackgroundImage = SDL_CreateTextureFromSurface(rend, BackgroundImage);
	SDL_FreeSurface(BackgroundImage);
	SDL_RenderCopy(rend, texBackgroundImage, NULL, NULL);
*/	// testing end
	
	// Rendering
//  SDL_RenderClear(rend);
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
	
	
	SDL_Delay(10000);
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
	case 0:
		SDL_RenderCopy(rend, texNum[0], NULL, &RrenderTex);
		break;
	case 48:
		SDL_RenderCopy(rend, texNum[1], NULL, &RrenderTex);
		break;
/*	case 2:
		SDL_RenderCopy(rend, texNum[2], NULL, &RrenderTex);
		break;
	case 3:
		SDL_RenderCopy(rend, texNum[3], NULL, &RrenderTex);
		break;
	case 4:
		SDL_RenderCopy(rend, texNum[4], NULL, &RrenderTex);
		break;
	case 5:
		SDL_RenderCopy(rend, texNum[5], NULL, &RrenderTex);
		break;
	case 6:
		SDL_RenderCopy(rend, texNum[6], NULL, &RrenderTex);
		break;
	case 7:
		SDL_RenderCopy(rend, texNum[7], NULL, &RrenderTex);
		break;
	case 8:
		SDL_RenderCopy(rend, texNum[8], NULL, &RrenderTex);
		break;
	case 9:
		SDL_RenderCopy(rend, texNum[9], NULL, &RrenderTex);
		break;
*/	default: 
		break;
	}
}