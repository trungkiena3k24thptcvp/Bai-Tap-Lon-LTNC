#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED
#include "CommonFunction.h"
#include "BaseObject.h"
#define NUM_FRAME_EXP 8

class Explosion : public BaseObject
{

public:
    Explosion();
    ~Explosion();
public:
    void set_clip();
    void set_frame(const int &f) {frame_ = f;}
    virtual bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int get_width_frame() const {return frame_width;}
    int get_height_frame() const {return frame_height;}
private:
    int frame_width;
    int frame_height;
    unsigned int frame_;
    SDL_Rect frame_clip[8];
};


#endif // EXPLOSION_H_INCLUDED
