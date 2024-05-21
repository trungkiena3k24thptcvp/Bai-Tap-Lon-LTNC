#ifndef BULLETOBJECT_H_INCLUDED
#define BULLETOBJECT_H_INCLUDED
#include "BaseObject.h"
#include "CommonFunction.h"

class BulletObject : public BaseObject
{
public:
    BulletObject();
    ~BulletObject();
    enum BulletDir
    {
       DIR_RIGHT = 20,
       DIR_LEFT = 21,
       DIR_UP = 22,
       DIR_UP_LEFT = 23,
       DIR_UP_RIGHT = 24,
       DIR_DOWN_LEFT = 25,
       DIR_DOWN_RIGHT = 26,
       DIR_DOWN = 27,
    };
    enum BulletType
    {
        SPHERE_BULLET = 50,
        LASER_BULLET = 51,
        THREAT_BULLET = 52,
        STATIC_THREAT_BULLET = 53,
        SPHERE_SIMPLE_BULLET = 54,
        SPHERE_MAX_BULLET = 55,
    };
    void set_x_val(const int &xVal) {x_val = xVal;}
    void set_y_val(const int &yVal) {y_val = yVal;}
    int get_x_val() const {return x_val;}
    int get_y_val() const {return y_val;}
    void HandleMovePlayer(Map& map_data, const int& x_border, const int& y_border);
    void set_xy_pos_(const int& xpos, const int& ypos) {x_pos = xpos; y_pos = ypos;}
    void set_is_move(const bool& isMove) {is_move = isMove;}
    bool get_is_move() const {return is_move;}


    void set_bullet_dir(const unsigned int& bulletDir) {bullet_dir = bulletDir;}
    unsigned int get_bullet_dir() const {return bullet_dir;}

    void set_bullet_type(const unsigned int& bulletType) {bullet_type = bulletType;}
    unsigned int get_bullet_type() const {return bullet_type;}
    void HandleMove(const int& x_border, const int& y_border);
    bool LoadImgBullet(SDL_Renderer* des);
    void CheckToMap(Map& map_data);
private:
    int x_val;
    int y_val;
    bool is_move;
    unsigned int bullet_dir;
    unsigned int bullet_type;
    float x_pos;
    float y_pos;
} ;


#endif // BULLETOBJECT_H_INCLUDED
