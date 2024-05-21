#ifndef PLAYPOWER_H_INCLUDED
#define PLAYPOWER_H_INCLUDED

#include "CommonFunction.h"
#include "BaseObject.h"

class PlayPower : public BaseObject
{
public:
    PlayPower();
    ~PlayPower();

    void SetNum(const int& num) {number_ = num;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);

    void InitCrease();
    void Decrease();
    int getNum() {return number_;}
private:
    int number_;
    vector<int> pos_list;
};

#endif // PLAYPOWER_H_INCLUDED
