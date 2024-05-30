#ifndef THREATOBJECT_H_INCLUDED
#define THREATOBJECT_H_INCLUDED
#include "CommonFunction.h"
#include "BaseObject.h"
#include "BulletObject.h"
#define THREAT_FRAME_NUM 8
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_SPEED 3
class ThreatObject : public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();
    enum type_move
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1,
        MOVE_IN_SKY_THREAT = 2
    };
    void set_x_val(const float& xVal) {x_val = xVal;}
    void set_y_val(const float& yVal) {y_val = yVal;}
    void set_x_pos(const float& xPos) {x_pos = xPos;}
    void set_y_pos(const float& yPos) {y_pos = yPos;}
    float get_x_pos() const {return x_pos;}
    float get_y_pos() const {return y_pos;}
    void SetMapXY(const int& mp_x, const int& mp_y) {map_x = mp_x; map_y = mp_y;}
    void set_clips();
    void set_clips4();
    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}
    void DoPlayer(Map& gMap);
    void CheckToMap(Map& gMap);
    void ResetBullet(BulletObject* p_bullet);
    void InitThreat();
    void set_type_move(const int& typeMove) {type_move = typeMove;}
    void SetAnimation(const int& pos_a, const int& pos_b) {animation_a = pos_a, animation_b = pos_b;}
    void set_input_left(const int& ipLeft) {input_type.left = ipLeft;}
    void ImpMoveType(SDL_Renderer* screen);
    vector<BulletObject*> get_bullet_list() const {return bullet_list;}
    void set_bullet_list(const vector<BulletObject*>& bulletList) {bullet_list = bulletList;}
    void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);
    void InitBullet1(BulletObject* p_bullet, SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
    void RemoveBullet(const int& idx);
    SDL_Rect GetRectFrame();
private:
    int map_x, map_y;
    float x_pos, y_pos;
    float x_val, y_val;
    bool on_ground;
    int come_back_time;
    SDL_Rect frame_clip[THREAT_FRAME_NUM];
    int frame_;
    int width_frame;
    int height_frame;
    int type_move;
    int animation_a, animation_b;
    Input input_type;
    vector<BulletObject*> bullet_list;
    bool on_sky;
    int status;

};


#endif // THREATOBJECT_H_INCLUDED
