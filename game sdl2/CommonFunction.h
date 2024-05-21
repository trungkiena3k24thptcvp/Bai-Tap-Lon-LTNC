#ifndef COMMONFUNCTION_H_INCLUDED
#define COMMONFUNCTION_H_INCLUDED
#include <windows.h>
#include <string.h>
#include <SDL_image.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include<iostream>
#include<bits/stdc++.h>
#include<cstdio>
#include<vector>
#include<fstream>
using namespace std;
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];
static Mix_Chunk* g_sound_effect[2];
static Mix_Chunk* g_sound_result[2];
static Mix_Music* g_music;
static char g_name_map[] = {"map//map01.dat"};
static char g_type_map[] = {"map/%d.png"};
//Screen
const int FRAME_PER_SECOND = 35;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;

#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define MAX_TILE 20
#define STATE_MONEY 4
#define IMMORTAL_TIME 6
#define MAX_PLAYER_TIME 1000
#define MAX_BULLET 18
#define HEART 19
#define FIGUREHEAD 15
#define ABYSS_TILE 10
typedef struct Input
{
    int left;
    int right;
    int up;
    int down;
    int jump;
    int stop;
    int change_bullet;
};
typedef struct Map
{
    int start_x;
    int start_y;
    int Max_x;
    int Max_y;
    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};
namespace SDLCommonFunction
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    int ShowMenu(SDL_Renderer* g_screen, TTF_Font* font,
		const string& menu1,
		const string& menu2,
		const string& img_name);
	int ShowMenuHelp(SDL_Renderer* g_screen, TTF_Font* font,
		const string& menuHelp,
		const string& img_name);
	int ShowMenuFinal(SDL_Renderer* g_screen, TTF_Font* font,
		const string& menu1,
		const string& menu2,
		const string& menu3,
		const string& img_name);
}
#endif // COMMONFUNCTION_H_INCLUDED
