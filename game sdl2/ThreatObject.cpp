#include "ThreatObject.h"

ThreatObject::ThreatObject() {
	width_frame = 0;
	height_frame = 0;
	x_val = 0.0;
	y_val = 0.0;
	x_pos = 0.0;
	y_pos = 0.0;
	on_ground = false;
	come_back_time = 0;
	frame_ = 0;
	animation_a = 0;
	animation_b = 0;
	input_type.left = 0;
	type_move = STATIC_THREAT;
	input_type.right = 0;
	input_type.stop = 0;
	on_sky = false;
	status = 0;
}
ThreatObject::~ThreatObject() {

}
bool ThreatObject::LoadImg (string path, SDL_Renderer* screen) {
	bool ret = BaseObject::LoadImg (path, screen);

	if (ret) {
		width_frame = rect_.w / THREAT_FRAME_NUM;
		height_frame = rect_.h;
	}

	return ret;
}
void ThreatObject::set_clips() {
	if (width_frame > 0 && height_frame > 0) {
		for (int i = 0; i < 8; i++) {
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}
}
void ThreatObject::set_clips4() {
	if (width_frame > 0 && height_frame > 0) {
		for (int i = 0; i < 4; i++) {
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}
}
void ThreatObject::Show (SDL_Renderer* des) {
	if (come_back_time == 0) {
		rect_.x = x_pos - map_x;
		rect_.y = y_pos - map_y;
		frame_++;

		if (frame_ >= 8) {
			frame_ = 0;
		}

		SDL_Rect* currClips = &frame_clip[frame_];
		SDL_Rect renQuad = {rect_.x, rect_.y, width_frame, height_frame};
		SDL_RenderCopy (des, p_object_, currClips, &renQuad);
	}
}
void ThreatObject::CheckToMap (Map& gMap) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;
	int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;

	y1 = y_pos / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val > 0) {
			int val1 = gMap.tile[y1][x2];
			int val2 = gMap.tile[y2][x2];

			if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY) ) {
				x_pos = x2 * TILE_SIZE;
				x_pos -= width_frame + 1;
				x_val = 0;
			}
		} else if (x_val < 0) {
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y2][x1];

			if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY)) {
                input_type.stop = 1;
				x_pos = (x1 + 1) * TILE_SIZE;
				x_val = 0;
			}

		}
	}

	int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
	x1 = x_pos / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + height_frame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val > 0) {
			int val1 = gMap.tile[y2][x1];
			int val2 = gMap.tile[y2][x2];

			if ( (val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY) ) {
				y_pos = y2 * TILE_SIZE;
				y_pos -= (height_frame + 1);
				y_val = 0;
				on_ground = true;
			}
		}
	} else if (y_val < 0) {
		int val1 = gMap.tile[y1][x1];
		int val2 = gMap.tile[y1][x2];

		if ( (val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY) ) {
			y_pos = (y1 + 1) * TILE_SIZE;
			y_val = 0;
		}

	}
    on_sky = true;

	x_pos += x_val;
	y_pos += y_val;

	if (x_pos < 0) {
		x_pos = 0;
	} else if (x_pos + width_frame > gMap.Max_x) {
		x_pos = gMap.Max_x - width_frame - 1;

	}

	if (y_pos > gMap.Max_y) {
		come_back_time = 60;
	}
}
void ThreatObject::InitThreat() {
	x_val = 0;
	y_val = 0;

	if (x_pos > 256) {
		x_pos -= 256;
		animation_a -= 256;
		animation_b -= 256;
	}

	else {
		x_pos = 0;
	}

	y_pos = 0;
	come_back_time = 0;
	input_type.left = 1;
}
void ThreatObject::ImpMoveType (SDL_Renderer* screen) {
	if (type_move == STATIC_THREAT) {

	}
	else if (type_move == MOVE_IN_SKY_THREAT) {
        if (on_sky == true) {
            if (x_pos > animation_b || (input_type.stop == 1 && input_type.right == 1)) {
                input_type.left = 1;
                input_type.right = 0;
                input_type.stop = 0;
                status = 0;
                LoadImg("IMG//threat2_left.png", screen);
            }
            else if (x_pos < animation_a || (input_type.stop == 1 && input_type.right == 1)) {
                input_type.left = 0;
                input_type.right = 1;
                input_type.stop = 0;
                status = 1;
                LoadImg("IMG//threat2_right.png", screen);
            }
        }
        else {
            if (input_type.left == 1) {
                LoadImg("IMG//threat2_left.png", screen);
            }
        }
	}
	else if (type_move == MOVE_IN_SPACE_THREAT) {
        if (on_ground == true) {
			if (x_pos > animation_b || (input_type.stop == 1 && input_type.right == 1)) {
				input_type.left = 1;
				input_type.right = 0;
				input_type.stop = 0;
				status = 0; // left
				LoadImg("IMG//goku_left.png", screen);
			}
			else if (x_pos < animation_a || (input_type.stop == 1 && input_type.left == 1)) {
				input_type.left = 0;
				input_type.right = 1;
				input_type.stop = 0;
				status = 1; // right
				LoadImg("IMG//goku_right.png", screen);
			}
		}
		else
		{
			if (input_type.left == 1) {
				LoadImg("IMG//goku_left.png", screen);
			}
		}
	}
}
void ThreatObject::DoPlayer (Map& gMap) {
	if (come_back_time == 0)
	{
		x_val = 0;
		y_val += THREAT_GRAVITY_SPEED;
		if (y_val >= THREAT_MAX_FALL_SPEED)
		{
			y_val = THREAT_MAX_FALL_SPEED;
		}

		if (type_move == MOVE_IN_SKY_THREAT)
		{
			y_val = 0;
		}

		if (input_type.left == 1) {
			x_val -= THREAT_SPEED;
			status = 0;
		}
		else if (input_type.right == 1) {
			x_val += THREAT_SPEED;
			status = 1;
		}

		CheckToMap(gMap);
	}
	else if (come_back_time > 0)
	{
		come_back_time--;
		if (come_back_time == 0) {
			InitThreat();
		}
	}
}
void ThreatObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
    if (p_bullet != NULL) {
        p_bullet->set_bullet_type(BulletObject::LASER_BULLET);
        p_bullet->LoadImgBullet(screen);
        p_bullet->set_is_move(true);
        p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
        p_bullet->SetRect(rect_.x + 10, rect_.y + 25);
        p_bullet->set_x_val(15);
        bullet_list.push_back(p_bullet);
    }
}
void ThreatObject::InitBullet1(BulletObject* p_bullet, SDL_Renderer* screen)
{
    if (p_bullet != NULL) {
        p_bullet->set_bullet_type(BulletObject::STATIC_THREAT_BULLET);
        p_bullet->LoadImgBullet(screen);
        p_bullet->set_is_move(true);
        p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
        p_bullet->SetRect(rect_.x + 10, rect_.y + 20);
        p_bullet->set_x_val(10);
        bullet_list.push_back(p_bullet);
    }
}
void ThreatObject::ResetBullet(BulletObject* p_bullet)
{
	if (p_bullet->get_bullet_type() == MOVE_IN_SPACE_THREAT) {
		p_bullet->SetRect(rect_.x + 20, y_pos + 20);
	}
	else if (p_bullet->get_bullet_type() == STATIC_THREAT) {
		p_bullet->SetRect(rect_.x + 20, y_pos + 20);
	}
	p_bullet->set_x_val(15);
}
void ThreatObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
    for (int i = 0; i < bullet_list.size(); i++) {
        BulletObject* p_bullet = bullet_list.at(i);
        if (p_bullet != NULL) {
            if (p_bullet->get_is_move()) {
                int bullet_distance = rect_.x + width_frame - p_bullet->GetRect().x;
                if (bullet_distance < 300 && bullet_distance > 0) {
                p_bullet->HandleMove(x_limit, y_limit);
                p_bullet->Render(screen);
              }
                else {
                 p_bullet->set_is_move(false);
              }
            }
            else {
                p_bullet->set_is_move(true);
                p_bullet->SetRect(rect_.x + 5, rect_.y + 20);
            }
        }
    }
}
void ThreatObject::RemoveBullet(const int& idx)
{
    int Size = bullet_list.size();
    if (Size > 0 && idx < Size) {
        BulletObject* p_bullet = bullet_list.at(idx);
        bullet_list.erase(bullet_list.begin() + idx);
        if (p_bullet) {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}
SDL_Rect ThreatObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame;
    rect.h = height_frame;
    return rect;
}
