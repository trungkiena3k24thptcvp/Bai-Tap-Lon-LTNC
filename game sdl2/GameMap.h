#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED
#include "CommonFunction.h"
#include "BaseObject.h"
class TileMat : public BaseObject
{
public:
    TileMat() {;}
    ~TileMat() {;}
};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map;}
    void SetMap(const Map& map_data) {game_map = map_data;}
private:
    Map game_map;
    TileMat tile_mat[MAX_TILE];
};

#endif // GAMEMAP_H_INCLUDED
