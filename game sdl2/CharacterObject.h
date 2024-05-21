#ifndef CHARACTEROBJECT_H_INCLUDED
#define CHARACTEROBJECT_H_INCLUDED

#include "CommonFunction.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>
#define GRAVITY 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_SPEED 18
class CharacterObject : public BaseObject
{
public:
    CharacterObject();
    ~CharacterObject();

    enum WalkType
    {
        WALK_NONE = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
        WALK_JUMP = 3,
        CHANGE_BULLET = 4,
    };
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleInputAction (SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound[2]);
    void SetClip();
    void updateImagePlayer(SDL_Renderer * des);
    void Doplayer(Map& map_data, Mix_Chunk* g_sound_effect[2]);
    void CheckMap(Map& map_data, Mix_Chunk* g_sound_effect[2]);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x, map_y_ = map_y;};
    void CenterEntityOnMap(Map& map_data);
    void UpdateImagePlayer(SDL_Renderer* des);
    SDL_Rect GetRectFrame();
    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}
    void set_bullet_list(vector<BulletObject*> bullet_list) {
        p_bullet_list = bullet_list;
    }
    vector<BulletObject*> get_bullet_list() const {return p_bullet_list;}
    void HandleBullet(Map& map_data, SDL_Renderer* des);
    void RemoveBullet(const int& idx);
    void IncreaseMoney(Mix_Chunk* money_sound[2]);
    int GetMoneyCount() const {return money_count;}
    void set_comeback_time(const int& cb_time) {come_back_time = cb_time;}
    void CountDie();
    void setDie(const int& ndie) {num_die_ = ndie;}
    int getDie() const {return num_die_;}
    int getComeBack() const {return come_back_die_;}
    int setComeBack(const bool& cbd) {come_back_die_ = cbd;}
    bool player_left() const {return player_left_;}
    void setHeart(const bool& heart) {inHeart_ = heart;}
	bool getHeart() const {return inHeart_;}

private:
    int money_count;
    vector<BulletObject*> p_bullet_list;
    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[8];
    Input input_type;
    int frame_;
    int status;
    bool on_ground;

    int map_x_;
    int map_y_;
    bool sit_on_ground;
    int come_back_time;
    bool come_back_die_;
	int num_die_;
	bool change_bullet_;
	bool player_left_;
	bool inHeart_;
};

#endif // CHARACTEROBJECT_H_INCLUDED
