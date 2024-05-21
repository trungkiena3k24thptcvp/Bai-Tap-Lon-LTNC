#include "Explosion.h"

Explosion::Explosion()
{
    frame_height = 0;
    frame_width = 0;
    frame_ = 0;
}
Explosion::~Explosion()
{

}
bool Explosion::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret) {
        frame_width = rect_.w / NUM_FRAME_EXP;
        frame_height = rect_.h;
    }
    return ret;
}
void Explosion::set_clip()
{
    if (frame_width > 0 && frame_height > 0) {
        for (int i = 0; i < 8; i++) {
            frame_clip[i].x = i * frame_width;
            frame_clip[i].y = 0;
            frame_clip[i].w = frame_width;
            frame_clip[i].h = frame_height;
        }
    }
}
void Explosion::Show(SDL_Renderer* screen)
{
    SDL_Rect* curr_clip = &frame_clip[frame_];
    SDL_Rect render_quad = {rect_.x, rect_.y, frame_width, frame_height};
    if (curr_clip != NULL) {
        render_quad.w = curr_clip->w;
        render_quad.h = curr_clip->h;
    }
    SDL_RenderCopy(screen, p_object_, curr_clip, &render_quad);
}
