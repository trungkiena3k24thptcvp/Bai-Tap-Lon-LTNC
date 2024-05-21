#ifndef RENDERWINDOW_HPP_INCLUDED
#define RENDERWINDOW_HPP_INCLUDED
#include "CommonFunction.h"
class RenderWindow
{
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    void cleanUp();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

};


#endif // RENDERWINDOW_HPP_INCLUDED
