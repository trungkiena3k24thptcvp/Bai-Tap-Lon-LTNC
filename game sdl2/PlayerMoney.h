#ifndef PLAYERMONEY_H_INCLUDED
#define PLAYERMONEY_H_INCLUDED
#include "CommonFunction.h"
#include "BaseObject.h"

class PlayerMoney : public BaseObject
{
public:
    PlayerMoney();
    ~PlayerMoney();
    void Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetPos(const int& xp, const int& yp) {x_pos = xp; y_pos = yp;}
private:
    int x_pos;
    int y_pos;
};


#endif // PLAYERMONEY_H_INCLUDED
