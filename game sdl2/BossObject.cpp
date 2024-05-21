#include "BossObject.h"

BossObject::BossObject()
{
    frame = 0;
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    width_frame = 0;
    height_frame = 0;
    think_time = 0;
    map_x = 0;
    on_ground = false;
    map_y = 0;
}
BossObject::~BossObject()
{

}
bool BossObject::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    if (ret == true) {
        width_frame = rect_.w / FRAME_NUM;
        height_frame = rect_.h;
    }
    return ret;
}
void BossObject::set_clips()
{
    if (width_frame > 0 && height_frame > 0) {
        for (int i = 0; i < FRAME_NUM; i++) {
            frame_clip[i].x = width_frame * i;
            frame_clip[i].y = 0;
            frame_clip[i].h = height_frame;
            frame_clip[i].w = width_frame;
        }
    }
}
SDL_Rect BossObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = rect_.w / FRAME_NUM;
    rect.h = rect_.h;
    return rect;
}
void BossObject::Show(SDL_Renderer* des)
{
    if (think_time == 0)
    {
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;
        frame++;
        if (frame >= 32)
        {
            frame = 0;
        }

        SDL_Rect* currentClip = &frame_clip[frame];
        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame, height_frame};
        if (currentClip != NULL)
        {
            renderQuad.w = currentClip->w;
            renderQuad.h = currentClip->h;
        }

        SDL_RenderCopy(des, p_object_, currentClip, &renderQuad);
    }
}

void BossObject::DoPlayer(Map& g_map)
{
    if (think_time == 0)
    {
        x_val = 0;
        y_val += GRAVITY;

        if (y_val >= MAX_FALL_SPEED)
        {
            y_val = MAX_FALL_SPEED;
        }

        if (input_type.left == 1)
        {
            x_val -= PLAYER_SPEED;
        }

        else if (input_type.right == 1)
        {
            x_val += PLAYER_SPEED;
        }

        if (input_type.jump == 1)
        {
            if (on_ground == true)
            {
                y_val = -PLAYER_HIGHT_VAL;
            }

            input_type.jump = 0;
        }
        CheckToMap(g_map);
    }

    if (think_time > 0)
    {
        think_time--;

        if (think_time == 0)
        {
            InitBoss();
        }
    }
}
void BossObject::InitBoss()
{
    x_val = 0;
    y_val = 0;

    if (x_pos > 256)
    {
        x_pos -= 256;
    }
    else x_pos = 0;
    y_pos = 0;
    think_time = 0;
    input_type.left = 1;
}

void BossObject::CenterEntityOnMap(Map& g_map)
{
    g_map.start_x = x_pos - (SCREEN_WIDTH / 2);

    if (g_map.start_x < 0)
    {
        g_map.start_x = 0;
    }

    else if (g_map.start_x + SCREEN_WIDTH >= g_map.Max_x)
    {
        g_map.start_x = g_map.Max_x - SCREEN_WIDTH;
    }

    g_map.start_y = y_pos - (SCREEN_HEIGHT / 2);

    if (g_map.start_y < 0)
    {
        g_map.start_y = 0;
    }

    else if (g_map.start_y + SCREEN_HEIGHT >= g_map.Max_y)
    {
        g_map.start_y = g_map.Max_y - SCREEN_HEIGHT;
    }
}

void BossObject::CheckToMap(Map& g_map)
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;
    on_ground = 0;
    int height_min = height_frame;
    x1 = (x_pos + x_val) / TILE_SIZE;
    x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;
    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + height_min - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val > 0)
        {
            if ((g_map.tile[y1][x2] != BLANK_TILE) || (g_map.tile[y2][x2] != BLANK_TILE))
            {
                x_pos = x2 * TILE_SIZE;
                x_pos -= width_frame + 1;
                x_val = 0;
            }
        }
        else if (x_val < 0)
        {
            if ((g_map.tile[y1][x1] != BLANK_TILE) || (g_map.tile[y2][x1] != BLANK_TILE))
            {
                x_pos = (x1 + 1) * TILE_SIZE;
                x_val = 0;
            }
        }
    }
    int width_min = width_frame;

    x1 = (x_pos) / TILE_SIZE;
    x2 = (x_pos + width_min) / TILE_SIZE;

    y1 = (y_pos + y_val) / TILE_SIZE;
    y2 = (y_pos + y_val + height_frame) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val > 0)
        {
            if ((g_map.tile[y2][x1] != BLANK_TILE) || (g_map.tile[y2][x2] != BLANK_TILE))
            {
                y_pos = y2 * TILE_SIZE;
                y_pos -= height_frame;
                y_val = 0;
                on_ground = true;
            }
        }
        else if (y_val < 0)
        {
            if ((g_map.tile[y1][x1] != BLANK_TILE) || (g_map.tile[y1][x2] != BLANK_TILE))
            {
                y_pos = (y1 + 1) * TILE_SIZE;

                y_val = 0;
            }
        }
    }

    x_pos += x_val;
    y_pos += y_val;

    if (x_pos < 0)
    {
        x_pos = 0;
    }
    else if (x_pos + width_frame >= g_map.Max_x)
    {
        x_pos = g_map.Max_x - width_frame - 1;
    }

    if (y_pos > g_map.Max_y)
    {
        think_time = 60;
    }
}

void BossObject::InitBullet(SDL_Renderer* screen)
{
    BulletObject* p_bullet = new BulletObject();
    bool ret = p_bullet->LoadImg("IMG\\boss_bullet.png", screen);
    if (ret)
    {
        p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
        p_bullet->set_is_move(true);
        p_bullet->SetRect(rect_.x - 50, rect_.y + height_frame - 30);
        p_bullet->set_x_val(15);
        bullet_list.push_back(p_bullet);
    }
}


void BossObject::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
    if (frame == 18)
    {
        InitBullet(des);
    }

    for (int i = 0; i < bullet_list.size(); i++)
    {
        BulletObject* p_bullet = bullet_list.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move())
            {
                p_bullet->HandleMove(x_limit, y_limit);
                p_bullet->Render(des);
            }
            else
            {
                p_bullet->Free();
                bullet_list.erase(bullet_list.begin() + i);
            }
        }
    }
}

void BossObject::RemoveBullet(const int& idx)
{
    int sz = bullet_list.size();
    if (sz > 0 && idx < sz) {
        BulletObject* p_bullet = bullet_list.at(idx);
        bullet_list.erase(bullet_list.begin() + idx);

        if (p_bullet) {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

void BossObject::ResetBullet(BulletObject* p_bullet)
{
    p_bullet->SetRect(rect_.x - 50, rect_.y + height_frame - 30);
    p_bullet->set_x_val(15);
}
