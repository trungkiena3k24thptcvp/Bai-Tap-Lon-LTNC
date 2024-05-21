
#ifndef BOSS_OBJECT_H_
#define BOSS_OBJECT_H_


#include "BaseObject.h"
#include "CommonFunction.h"
#include "BulletObject.h"
#define GRAVITY 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 2
#define PLAYER_HIGHT_VAL 18;
#define FRAME_NUM 32

class BossObject : public BaseObject
{
public:
    BossObject();
    ~BossObject();

    void set_x_val(int xp) {x_val = xp;}
    void set_y_val(int yp) {y_val = yp;}
    void set_xpos(const int& xps) {x_pos = xps;}
    void set_ypos(const int& yps) {y_pos = yps;}
    int get_x_pos() const {return x_pos;}
    int get_y_pos() const {return y_pos;}
    void Show(SDL_Renderer* des);
    bool LoadImg(string path, SDL_Renderer* screen);
    void set_clips();
    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}
    SDL_Rect GetRectFrame();
    void SetMapXY(const int mpx, const int mpy) {map_x = mpx, map_y = mpy;};
    void CheckToMap(Map& g_map);
    void CenterEntityOnMap(Map& g_map);
    void DoPlayer(Map& g_map);
    void InitBoss();
    std::vector<BulletObject*> get_bullet_list() const {return bullet_list;}
    void set_bullet_list(const vector<BulletObject*>& bl_list) {bullet_list = bl_list;}
    void InitBullet(SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit);
    void RemoveBullet(const int& idx);
    void ResetBullet(BulletObject* p_bullet);
private:

    int map_x;
    int map_y;
    bool on_ground;
    int think_time;
    Input input_type;
    int frame;
    SDL_Rect frame_clip[FRAME_NUM];
    int x_pos;
    int y_pos;
    float x_val;
    float y_val;
    int width_frame;
    int height_frame;
    std::vector<BulletObject*> bullet_list;
};
#endif
