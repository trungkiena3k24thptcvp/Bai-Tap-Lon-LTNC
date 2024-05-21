#include "BulletObject.h"
#include "CommonFunction.h"
#include "BaseObject.h"
BulletObject::BulletObject()
{
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    is_move = false;
    bullet_type = SPHERE_SIMPLE_BULLET;
}
BulletObject::~BulletObject()
{

}
bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    bool ret = false;
    if (bullet_type == LASER_BULLET) {
        ret = LoadImg("IMG//laser_bullet.png", des);
    }
    else if (bullet_type == SPHERE_BULLET) {
        ret = LoadImg("IMG//sphere_bullet.png", des);
    }
    else if (bullet_type == THREAT_BULLET) {
        ret = LoadImg("IMG//bullet_threat1.png", des);
    }
    else if (bullet_type == SPHERE_MAX_BULLET) {
        ret = LoadImg("IMG//2.png", des);
    }
    else if (bullet_type == SPHERE_SIMPLE_BULLET) {
        ret = LoadImg("IMG//1.png", des);
    }
    else {
        ret = LoadImg("IMG//bullet_threat2.png", des);
    }
    return ret;
}
void BulletObject::HandleMovePlayer(Map& map_data, const int& x_border, const int& y_border)
{
	if (bullet_dir == DIR_RIGHT) {
		rect_.x += x_val;
		x_pos += x_val;
		if (rect_.x > x_border) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_LEFT) {
		rect_.x -= x_val;
		x_pos -= x_val;
		if (rect_.x < 0) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_UP)
	{
		rect_.y -= y_val;
		if (rect_.y < 0) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_UP_LEFT) {
		rect_.x -= x_val;
		if (rect_.x < 0) {
			is_move = false;
		}
		rect_.y -= y_val;
		if (rect_.y < 0) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_UP_RIGHT) {
		rect_.x += x_val;
		if (rect_.x > x_border) {
			is_move = false;
		}
		rect_.y -= y_val;
		if (rect_.y < 0) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_DOWN)
	{
		rect_.y += y_val;
		if (rect_.y < 0) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_DOWN_LEFT)
	{
		rect_.x -= x_val;
		if (rect_.x < 0) {
			is_move = false;
		}
		rect_.y += y_val;
		if (rect_.y > y_border) {
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_DOWN_RIGHT)
	{
		rect_.x += x_val;
		if (rect_.x < 0) {
			is_move = false;
		}
		rect_.y += y_val;
		if (rect_.y > y_border) {
			is_move = false;
		}
	}
}
void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    if (bullet_dir == DIR_RIGHT) {
        rect_.x += x_val;
        if (rect_.x > x_border) {
          is_move = false;
        }
    }
    else if (bullet_dir == DIR_LEFT) {
        rect_.x -= x_val;
        if (rect_.x < 0) {
            is_move = false;
        }
    }
    else if (bullet_dir == DIR_UP) {
        rect_.y -= y_val;
        if (rect_.y < 0) {
            is_move = false;
        }
    }
    else if (bullet_dir == DIR_UP_LEFT) {
        rect_.x -= x_val;
        if (rect_.x < 0) {
            is_move = false;
        }
        rect_.y -= y_val;
        if (rect_.y < 0) {
            is_move = false;
        }
    }
    else if (bullet_dir == DIR_UP_RIGHT) {
        rect_.x += x_val;
        if (rect_.x > x_border) {
            is_move = false;
        }
        rect_.y -= y_val;
        if (rect_.y < 0) {
            is_move = false;
        }
    }
    else if (bullet_dir == DIR_DOWN_LEFT) {
        rect_.x -= x_val;
        if (rect_.x < 0) {
            is_move = false;
        }
        rect_.y += y_val;
        if (rect_.y > y_border) {
            is_move = false;
        }
    }
    else if (bullet_dir == DIR_DOWN_RIGHT) {
        rect_.x += x_val;
        if (rect_.x > x_border) {
            is_move = false;
        }
        rect_.y += y_val;
        if (rect_.y > y_val) {
            is_move = false;
        }
    }
}
void BulletObject::CheckToMap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	int height_min = rect_.h < TILE_SIZE ? rect_.h : TILE_SIZE;
	if (get_bullet_dir() == DIR_RIGHT) {
		x1 = (x_pos + x_val) / TILE_SIZE;
		x2 = (x_pos + x_val + rect_.w - 1) / TILE_SIZE;
	}
	else if (get_bullet_dir() == DIR_LEFT) {
		x1 = (x_pos - x_val) / TILE_SIZE;
		x2 = (x_pos - x_val + rect_.w - 1) / TILE_SIZE;
	}
	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (get_bullet_dir() == DIR_RIGHT) {
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
			if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
				is_move = false;
				x_val = 0;
			}
		}
		else if (get_bullet_dir() == DIR_LEFT) { // Lùi
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
				is_move = false;
				x_val = 0;
			}
		}
	}

	if (x_pos < 0) {
		x_pos = 0;
	}
	if (x_pos + rect_.w > map_data.Max_x)
	{
		x_pos = map_data.Max_x - rect_.w - 1;
	}
}
