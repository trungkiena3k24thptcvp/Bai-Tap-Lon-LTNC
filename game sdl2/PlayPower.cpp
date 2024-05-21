#include "PlayPower.h"

PlayPower::PlayPower()
{
    number_ = 0;
}
PlayPower::~PlayPower()
{

}
void PlayPower::AddPos(const int& xp)
{
    pos_list.push_back(xp);
}
void PlayPower::Show(SDL_Renderer* screen)
{
    for (int i = 0; i < pos_list.size(); i++) {
        rect_.x = pos_list.at(i);
        rect_.y = 0;
        Render(screen);
    }
}
void PlayPower::Init(SDL_Renderer* screen)
{
    LoadImg("IMG//player_pw.png", screen);
    number_ = 3;
    if (pos_list.size() > 0) {
        pos_list.clear();
    }
    AddPos(20);
    AddPos(80);
    AddPos(140);
}
void PlayPower::Decrease()
{
    number_--;
    pos_list.pop_back();
}
void PlayPower::InitCrease()
{
    number_++;
    int last_pos = pos_list.back();
    last_pos += 40;
    pos_list.push_back(last_pos);
}
