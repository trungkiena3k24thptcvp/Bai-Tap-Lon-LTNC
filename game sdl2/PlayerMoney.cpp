#include "PlayerMoney.h"
PlayerMoney::PlayerMoney()
{
	x_pos = 0;
	y_pos = 0;
}

PlayerMoney::~PlayerMoney()
{
}

void PlayerMoney::Init(SDL_Renderer* screen)
{
	bool ret = LoadImg("IMG//money.png", screen);
	SetPos(SCREEN_WIDTH * 0.5 - 300, 8);
}

void PlayerMoney::Show(SDL_Renderer* screen)
{
	rect_.x = x_pos;
	rect_.y = y_pos;
	Render(screen);
}
