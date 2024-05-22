#include "CommonFunction.h"
#include "BaseObject.h"
#include "CharacterObject.h"

CharacterObject::CharacterObject()
{
    frame_ = 0;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    status = WALK_NONE;
    input_type.left = 0;
    input_type.right = 0;
    input_type.jump = 0;
    input_type.down = 0;
    input_type.up = 0;
    on_ground = false;
    map_x_ = 0;
    map_y_ = 0;
    come_back_time = 0;
    money_count = 0;
    num_die_ = 0;
    come_back_die_ = false;
    change_bullet_ = false;
    player_left_ = false;
    inHeart_ = false;
    sit_on_ground = false;
}
CharacterObject::~CharacterObject()
{

}
bool CharacterObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret == true)
    {
        width_frame = rect_.w / 8;
        height_frame = rect_.h;
    }
    return ret;
}
void CharacterObject::SetClip()
{
    if (width_frame > 0 && height_frame > 0) {
        for (int i = 0; i < 8; i++) {
            frame_clip[i].x = i * width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}
void CharacterObject::Show(SDL_Renderer* des)
{
    UpdateImagePlayer(des);
    if (input_type.left == 1 || input_type.right == 1) {
        frame_++;
    }
    else {
        frame_ = 0;
    }
    if (frame_ >= 8) {
        frame_ = 0;
    }

    rect_.x = x_pos - map_x_;
    rect_.y = y_pos - map_y_;

    SDL_Rect* curr_clip = &frame_clip[frame_];
    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame, height_frame};
    SDL_RenderCopy(des, p_object_, curr_clip, &renderQuad);
}
void CharacterObject::HandleInputAction(SDL_Event p_events, SDL_Renderer* screen, Mix_Chunk* bullet_sound[2])
{
    if (p_events.type == SDL_KEYDOWN) {
        switch (p_events.key.keysym.sym) {
        case SDLK_RIGHT:
            {
                status = WALK_RIGHT;
                input_type.right = 1;
                input_type.left = 0;
                UpdateImagePlayer(screen);

            }break;
        case SDLK_LEFT:
            {
                status = WALK_LEFT;
                input_type.left = 1;
                input_type.right = 0;
                player_left_ = true;
                sit_on_ground = false;
                UpdateImagePlayer(screen);

            }break;
        case SDLK_DOWN:
            {
                input_type.down = 1;
                input_type.jump = 0;
                sit_on_ground = true;
                UpdateImagePlayer(screen);

            }break;
        case SDLK_UP:
            {
                input_type.jump = 1;
                input_type.down = 0;
                sit_on_ground = false;
                UpdateImagePlayer(screen);
            }break;
        case SDLK_f:
            {
                if (input_type.change_bullet == 1) {
                    status = CHANGE_BULLET;
                    input_type.change_bullet = 0;
                    if (input_type.jump == 1) {
                        sit_on_ground = false;
                    }
                    UpdateImagePlayer(screen);
                }
            }break;
        case SDLK_g:
            {
                if (change_bullet_ == true) {
				status = CHANGE_BULLET;
				input_type.change_bullet = 1;
				if (input_type.jump == 1) {
					sit_on_ground = false;
				}
				UpdateImagePlayer(screen);
			  }
            }break;

        case SDLK_1:
            {
			BulletObject* p_bullet = new BulletObject();
            if (input_type.change_bullet == 0) {
				p_bullet->set_bullet_type(BulletObject::SPHERE_SIMPLE_BULLET);
				Mix_PlayChannel(-1, bullet_sound[0], 0);
			}
			else if (input_type.change_bullet == 1) {
				p_bullet->set_bullet_type(BulletObject::SPHERE_MAX_BULLET);
				Mix_PlayChannel(-1, bullet_sound[1], 0);
			}
			p_bullet->LoadImgBullet(screen);

			if (status == WALK_LEFT && sit_on_ground == false) {
				p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
				p_bullet->SetRect(this->rect_.x, rect_.y + height_frame * 0.25);
				p_bullet->set_xy_pos_(x_pos, rect_.y + height_frame * 0.25);
			}
			else if (status == WALK_RIGHT && sit_on_ground == false) {
				p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
				p_bullet->SetRect(this->rect_.x + width_frame - 20, rect_.y + height_frame * 0.25);
				p_bullet->set_xy_pos_(x_pos + width_frame - 20, rect_.y + height_frame * 0.25);
			}

			else if (status == WALK_LEFT && sit_on_ground == true) {
				p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
				p_bullet->SetRect(this->rect_.x, rect_.y + height_frame * 0.55);
				p_bullet->set_xy_pos_(x_pos, rect_.y + height_frame * 0.55);
			}

			else if (status == WALK_RIGHT && sit_on_ground == true) {
				p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
				p_bullet->SetRect(this->rect_.x + width_frame - 20, rect_.y + height_frame * 0.55);
				p_bullet->set_xy_pos_(x_pos + width_frame - 20, rect_.y + height_frame * 0.55);
			}

			else {
				p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
				p_bullet->set_xy_pos_(x_pos + width_frame - 20, rect_.y + height_frame * 0.25);
			}

			p_bullet->set_x_val(20);
			p_bullet->set_y_val(20);
			p_bullet->set_is_move(true);
			p_bullet_list.push_back(p_bullet);
            }
        }
    }
    else if (p_events.type == SDL_KEYUP) {
       switch (p_events.key.keysym.sym) {
        case SDLK_RIGHT:
            input_type.right = 0;
            break;
        case SDLK_LEFT:
            input_type.left = 0;
            break;
        case SDLK_DOWN:
            {
                input_type.down = 0;
                sit_on_ground = false;
            }break;
        case SDLK_UP:
            {
                input_type.jump = 0;
            }break;
        }
    }
}
void CharacterObject::HandleBullet(Map& map_data, SDL_Renderer* des)
{
    for (int i = 0; i < p_bullet_list.size(); i++) {
        BulletObject* p_bullet = p_bullet_list.at(i);
        if (p_bullet != NULL) {
            if (p_bullet->get_is_move() == true) {
                p_bullet->HandleMovePlayer(map_data, SCREEN_WIDTH, SCREEN_HEIGHT);
                if (input_type.change_bullet != 1) {
                    p_bullet->CheckToMap(map_data);
                }
                p_bullet->Render(des);
            }
            else {
                p_bullet_list.erase(p_bullet_list.begin() + i);
                if (p_bullet != NULL) {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}
void CharacterObject::Doplayer(Map& map_data, Mix_Chunk* g_sound_effect[2])
{
    if (come_back_time  == 0) {
    x_val = 0;
    y_val += GRAVITY;

    if (y_val >= MAX_FALL_SPEED) {
        y_val = MAX_FALL_SPEED;
    }
    if (input_type.left == 1) {
        x_val -= PLAYER_SPEED;
    }
    else if (input_type.right == 1) {
        x_val += PLAYER_SPEED;
    }

    if (input_type.jump == 1) {
        if (on_ground == true) {
           y_val = - PLAYER_JUMP_SPEED;
        }
        on_ground = false;
        input_type.jump = 0;
       }
    CheckMap(map_data, g_sound_effect);
    CenterEntityOnMap(map_data);
    }
    if (come_back_time > 0) {
        come_back_time--;
        if (come_back_time == 0) {
            if (x_pos > 256) {
            x_pos -= 256;
        }
        else {
            x_pos = 0;
        }
            y_pos = 0;
            x_val = 0;
            y_val = 0;
        }
    }
}
void CharacterObject::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x = x_pos - (SCREEN_WIDTH / 2);
    if (map_data.start_x < 0) {
        map_data.start_x = 0;
    }
    else if (map_data.start_x + SCREEN_WIDTH >= map_data.Max_x) {
        map_data.start_x = map_data.Max_x - SCREEN_WIDTH;

    }
    map_data.start_y = y_pos - (SCREEN_HEIGHT / 2);
    if (map_data.start_y < 0) {
        map_data.start_y = 0;
    }
    else if (map_data.start_y + SCREEN_HEIGHT >= map_data.Max_y) {
        map_data.start_y = map_data.Max_y - SCREEN_HEIGHT;
    }
}
void CharacterObject::CheckMap(Map& map_data, Mix_Chunk* g_sound_effect[2])
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;

	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val > 0) {
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

			if (val1 == STATE_MONEY || val2 == STATE_MONEY || val1 == MAX_BULLET || val2 == MAX_BULLET || val1 == HEART || val2 == HEART) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
				if (val1 == STATE_MONEY || val2 == STATE_MONEY) {
					IncreaseMoney(g_sound_effect);
				}
				if(val1 == MAX_BULLET || val2 == MAX_BULLET)
				{
					input_type.change_bullet = 1;
					change_bullet_ = true;
					Mix_PlayChannel(-1, g_sound_effect[0], 0);
				}
				if (val1 == HEART || val2 == HEART) {
					Mix_PlayChannel(-1, g_sound_effect[0], 0);
					inHeart_ = true;
				}
			}
			else if (val1 == FIGUREHEAD || val2 == FIGUREHEAD) {
				x_pos = -500;
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					x_pos = x2 * TILE_SIZE;
					x_pos -= width_frame + 1;
					x_val = 0;
				}
			}
		}
		else if (x_val < 0) {
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			if (val1 == STATE_MONEY || val2 == STATE_MONEY || val1 == MAX_BULLET || val2 == MAX_BULLET || val1 == HEART || val2 == HEART) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;
				if (val1 == STATE_MONEY || val2 == STATE_MONEY)
				{
					IncreaseMoney(g_sound_effect);
				}
				if (val1 == MAX_BULLET || val2 == MAX_BULLET)
				{
					input_type.change_bullet = 1;
					change_bullet_ = true;
					Mix_PlayChannel(-1, g_sound_effect[0], 0);
				}
				if (val1 == HEART || val2 == HEART)
				{
					Mix_PlayChannel(-1, g_sound_effect[0], 0);
					inHeart_ = true;
				}
			}
			else if (val1 == FIGUREHEAD || val2 == FIGUREHEAD) {
				x_pos = -500;
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					x_pos = (x1 + 1) * TILE_SIZE;
					x_val = 0;
				}
			}

		}
	}
	int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
	x1 = (x_pos) / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + height_frame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val > 0) {
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			if (val1 == STATE_MONEY || val2 == STATE_MONEY || val1 == MAX_BULLET || val2 == MAX_BULLET || val1 == HEART || val2 == HEART) {

				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				if (val1 == STATE_MONEY || val2 == STATE_MONEY)
				{
					IncreaseMoney(g_sound_effect);
				}
				if (val1 == MAX_BULLET || val2 == MAX_BULLET)
				{
					input_type.change_bullet = 1;
					change_bullet_ = true;
					Mix_PlayChannel(-1, g_sound_effect[0], 0);
				}
				if (val1 == HEART || val2 == HEART)
				{
					Mix_PlayChannel(-1, g_sound_effect[0], 0);
					inHeart_ = true;
				}
			}
			else if (val1 == FIGUREHEAD || val2 == FIGUREHEAD) {
				x_pos = -500;
			}
			else if (val1 == ABYSS_TILE || val2 == ABYSS_TILE) on_ground = false;
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					y_pos = y2 * TILE_SIZE;
					y_pos -= height_frame + 1;
					y_val = 0;

					on_ground = true;

					if (status == WALK_NONE) {
						status = WALK_RIGHT;
					}
				}

			}

		}
		else if (y_val < 0) {
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if (val1 == STATE_MONEY || val2 == STATE_MONEY || val1 == MAX_BULLET || val2 == MAX_BULLET || val1 == HEART || val2 == HEART) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				if (val1 == STATE_MONEY || val2 == STATE_MONEY)
				{
					IncreaseMoney(g_sound_effect);
				}
				if (val1 == MAX_BULLET || val2 == MAX_BULLET)
				{
					input_type.change_bullet = 1;
					change_bullet_ = true;
					Mix_PlayChannel(-1, g_sound_effect[0], 0);
				}
				if (val1 == HEART || val2 == HEART)
				{
					Mix_PlayChannel(-1, g_sound_effect[0], 0);
					inHeart_ = true;
				}
			}
			else if (val1 == FIGUREHEAD || val2 == FIGUREHEAD) {
				x_pos = -500;
			}
			else if (val1 == ABYSS_TILE || val2 == ABYSS_TILE) on_ground = false;
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					y_pos = (y1 + 1) * TILE_SIZE;
					y_val = 0;

					on_ground = true;
				}
			}

		}
	}

	x_pos += x_val;
	y_pos += y_val;

	if (x_pos < 0) {
		x_pos = 0;
	}
	else if (x_pos + width_frame > map_data.Max_x)
	{
		x_pos = map_data.Max_x - width_frame - 1;
	}
	if (y_pos > map_data.Max_y) {
		come_back_time = 60;
		come_back_die_ = true;
	}
}
void CharacterObject::RemoveBullet(const int& idx)
{
    int Size = p_bullet_list.size();
    if (Size > 0 && idx < Size) {
        BulletObject* p_bullet = p_bullet_list.at(idx);
        p_bullet_list.erase(p_bullet_list.begin() + idx);
        if (p_bullet) {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}
void CharacterObject::IncreaseMoney(Mix_Chunk* money_sound[2])
{
    money_count++;
    Mix_PlayChannel(-1, g_sound_effect[0], 0);
}

void CharacterObject::UpdateImagePlayer(SDL_Renderer* des)
{
    if (on_ground == true && sit_on_ground == false)
    {
        if (status == WALK_LEFT)
        {
            LoadImg("IMG//player_left.png", des);
        }
        else
        {
            LoadImg("IMG//player_right.png", des);
        }
    }
    else if (on_ground == true && sit_on_ground == true)
    {
        if (status == WALK_LEFT)
        {
            LoadImg("IMG//SitL.png", des);
        }
        else
        {
            LoadImg("IMG//SitR.png", des);
        }
    }
    else if (on_ground == false && sit_on_ground == false) {
        if (status == WALK_LEFT) {
            LoadImg("IMG//jum_left.png", des);
        }
        else {
            LoadImg("IMG//jum_right.png", des);
        }
    }
}
SDL_Rect CharacterObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame;
    rect.h = height_frame;
    return rect;
}
void CharacterObject::CountDie()
{
    num_die_++;
}
