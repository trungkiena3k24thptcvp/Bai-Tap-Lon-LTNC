#include "CommonFunction.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "CharacterObject.h"
#include "Time.h"
#include "BulletObject.h"
#include "ThreatObject.h"
#include "Explosion.h"
#include "Text.h"
#include "PlayPower.h"
#include "PlayerMoney.h"
#include "Geometric.h"
#include "ResultObject.h"
#include "BossObject.h"
BaseObject g_background;
int checkvictory = -1;
int checkdefeat = -1;
bool come_back_ = false;
int check_come_back_ = -1;
int time_val_temp = 0;
int playtime;
TTF_Font* font_time = NULL;
TTF_Font* font_menu = NULL;
TTF_Font* font_load = NULL;
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (ret < 0) return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("BRAVE SOLDIER", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL) success = false;
    else {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (g_screen == NULL) {
            cout << "SDL Error: \n" << SDL_GetError();
			success = false;
        }
        else {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags)) {
				cout << "SDL_image Error: \n" << IMG_GetError();
				success = false;
			}
        }
        if (TTF_Init() == -1) {
            cout << "SDL_ttf Error: \n" << TTF_GetError();
            success = false;
        }
        font_time = TTF_OpenFont("font//dlxfont.ttf", 15);
        if (font_time == NULL) {
            cout << "Khong load duoc dlxfont! SDL_ttf Error: \n" << TTF_GetError();
			success = false;
        }
        font_menu = TTF_OpenFont("font//ARCADE.ttf", 80/*Kích thước*/);
		if (font_menu == NULL) {
			cout << "Khong load duoc ARCADE! SDL_ttf Error: \n" << TTF_GetError();
			success = false;
		}

		font_load = TTF_OpenFont("font//COOPBL.ttf", 60/*Kích thước*/);
		if (font_load == NULL) {
			cout << "Khong load duoc dlxfont! SDL_ttf Error: \n" << TTF_GetError();
			success = false;
		}
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		return false;
	}
	g_sound_bullet[0] = Mix_LoadWAV("sound//Fire1.wav");
	g_sound_bullet[1] = Mix_LoadWAV("sound//Fire.wav");
	g_sound_exp[0] = Mix_LoadWAV("sound//explosion.wav");
	g_sound_exp[1] = Mix_LoadWAV("sound//Bomb1.wav");
	g_sound_effect[0] = Mix_LoadWAV("sound//beep_.wav");
	g_sound_effect[1] = Mix_LoadWAV("sound//fall.wav");

	g_sound_result[0] = Mix_LoadWAV("sound//Victory.wav");
	g_sound_result[1] = Mix_LoadWAV("sound//Defeat.wav");

	if (g_sound_exp[0] == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL) {
		return false;
	}
    return success;
}
bool Loadbackground()
{
    bool ret = g_background.LoadImg("IMG//background1.png", g_screen);
    if (ret == false) return false;
    return true;

}
void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    TTF_CloseFont(font_time);
	font_time = NULL;
	TTF_CloseFont(font_menu);
	font_menu = NULL;
	TTF_CloseFont(font_load);
	font_load = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
int LoadGame()
{
    int x = 0;
    Text text_object[3];
    text_object[0].SetText("Game Loading...");
	text_object[0].SetColor(0, 255, 0);
	text_object[0].LoadFromRenderText(font_load, g_screen);

	text_object[2].SetText("%");
	text_object[2].SetColor(255, 0, 0);
	text_object[2].LoadFromRenderText(font_load, g_screen);

	SDL_Rect pos[3];
	pos[0].x = SCREEN_WIDTH / 4.5f;
	pos[0].y = SCREEN_HEIGHT / 3;

	pos[1].x = SCREEN_WIDTH / 1.6f;
	pos[1].y = SCREEN_HEIGHT / 3;

	pos[2].x = SCREEN_WIDTH / 1.4f;
	pos[2].y = SCREEN_HEIGHT / 3;

	while (x <= 100) {
		text_object[1].SetText(std::to_string(x));
		text_object[1].SetColor(255, 0, 0);
		text_object[1].LoadFromRenderText(font_load, g_screen);

		SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 0);
		SDL_RenderClear(g_screen);

		for (int i = 0; i < 3; ++i)
		{
			text_object[i].RenderText(g_screen, pos[i].x, pos[i].y);
			pos[i].w = text_object[i].GetWidth();
			pos[i].h = text_object[i].GetHeight();
		}

		SDL_RenderPresent(g_screen);
		if (x == 75) SDL_Delay(1000);
		if (x == 100) SDL_Delay(500);
		SDL_Delay(20);
		x++;
	}
	return x;
}
void Graphic(CharacterObject& p_player, Text& mark_game, Text& money_game, Text& time_game, PlayPower& player_power, PlayerMoney& player_money, unsigned int& mark_value) {

	GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
	ColorData color_data(36, 36, 36);
	Geometric::RenderRectangle(rectangle_size, color_data, g_screen);

	GeometricFormat outLineSize(1, 1, SCREEN_WIDTH - 1, 38);
	ColorData color_data2(255, 255, 255);
	Geometric::RenderOutLine(outLineSize, color_data2, g_screen);

	string val_str_mark = to_string(mark_value);
	string strMark("Mark: ");
	strMark += val_str_mark;

	mark_game.SetText(strMark);
	mark_game.LoadFromRenderText(font_time, g_screen);
	mark_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 50, 15);

	int money_count = p_player.GetMoneyCount();
	string money_str = to_string(money_count);
	string strMoney("Money: ");
	strMoney += money_str;

	money_game.SetText(strMoney);
	money_game.LoadFromRenderText(font_time, g_screen);
	money_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 250, 15);

	string str_time = "Time: ";
	unsigned int time_val = SDL_GetTicks() / 1000;
	int val_time = MAX_PLAYER_TIME - (playtime / 1000);
	if (val_time <= 0) {
		checkdefeat = 0;
	}
	else
	{
		string str_val = to_string(val_time);
		str_time += str_val;

		time_game.SetText(str_time);
		time_game.LoadFromRenderText(font_time, g_screen);
		time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
	}
	player_power.Show(g_screen);
	player_money.Show(g_screen);
}
int comeback(CharacterObject& player, bool& is_quit, const LPCTSTR& message, const LPCTSTR& title, UINT information) {
	if (MessageBox(NULL, message, title, information) == IDOK)
	{
		Sleep(500);
		int ret_menu = SDLCommonFunction::ShowMenuFinal(g_screen, font_menu, "Play Again", "Help", "Exit", "IMG//menu_background.png");
		if (ret_menu == 2)
		{
			is_quit = true;
			return 2;
		}
		else if (ret_menu == 1) {
			is_quit = false;
			return 1;
		}
		else
		{
			is_quit = false;
			return 0;
		}
	}
}
int result(ResultObject& re, CharacterObject& player, bool& is_quit, const LPCTSTR& message, const LPCTSTR& title, UINT information) {
	for (int e = 0; e < 32; e++) {
		re.set_frame(e);
		re.SetRect(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 150);
		re.Show(g_screen);
		SDL_RenderPresent(g_screen);
		Sleep(200);
	}
	return comeback(player, is_quit, message, title, information);
}
vector<ThreatObject*> MakeThreatList()
{
    vector<ThreatObject*> list_threat;

    ThreatObject* dynamic_threat = new ThreatObject[10];
    for (int i = 0; i < 10; i++) {
        ThreatObject* p_threat = (dynamic_threat + i);
        if (p_threat != NULL) {
            p_threat->LoadImg("IMG//goku_left.png", g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 + i * 500);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - 100;
            int pos2 = p_threat->get_x_pos() + 100;
            p_threat->SetAnimation(pos1, pos2);
            p_threat->set_input_left(1);
            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);
            list_threat.push_back(p_threat);
        }
    }

    ThreatObject* dynamic_fly_threats = new ThreatObject[20];
	for (int i = 0; i < 20; i++)
	{
		ThreatObject* p_threat = (dynamic_fly_threats + i);
		if (p_threat != NULL) {
			p_threat->LoadImg("IMG//threat2_left.png", g_screen);
			p_threat->set_clips();
			p_threat->set_type_move(ThreatObject::MOVE_IN_SKY_THREAT);
			p_threat->set_x_pos(550 + i * 650);
			p_threat->set_y_pos(150);

			int pos1 = p_threat->get_x_pos() - 200;
			int pos2 = p_threat->get_x_pos() + 200;
			p_threat->SetAnimation(pos1, pos2);
			p_threat->set_input_left(1);

			list_threat.push_back(p_threat);
		}
	}



    ThreatObject* threat_objs = new ThreatObject[20];

    for (int i = 0; i < 20; i++) {
        ThreatObject* p_threat = (threat_objs + i);
        if (p_threat != NULL) {
            p_threat->LoadImg("IMG//goku_static.png", g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(600 + i * 1200);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatObject::STATIC_THREAT);
            p_threat->set_input_left(0);
            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet1(p_bullet, g_screen);

            list_threat.push_back(p_threat);
        }
    }
    return list_threat;
}
int main(int argc, char* argv[])
{
    Time fps_time;
    if (InitData() == false) return -1;
    bool is_quit = false;
    if (LoadGame() >= 100) {
      menu:
        int ret_menu = SDLCommonFunction::ShowMenuFinal(g_screen, font_menu, "Play game", "Help", "Exit", "IMG//Menu.png");
        if (ret_menu == 2) {
            is_quit = true;
        }
        else if (ret_menu == 1) {
            int ret_menuHelp = SDLCommonFunction::ShowMenuHelp(g_screen, font_time, "<-- Go Back", "IMG//HelpMenu.png");
            if (ret_menuHelp == 0) {
                goto menu;
            }
        }
    }

    if (Loadbackground() == false) return -1;
again_label:
    GameMap game_map;
    game_map.LoadMap(g_name_map);
    game_map.LoadTiles(g_screen);

    CharacterObject p_player;
    p_player.LoadImg("IMG//player_right.png", g_screen);
    p_player.SetClip();

    PlayPower player_power;
    player_power.Init(g_screen);

    PlayerMoney player_money;
    player_money.Init(g_screen);

    vector<ThreatObject*> threat_list = MakeThreatList();

    vector<BossObject*> boss;
    BossObject* bossObject = new BossObject();
    bossObject->LoadImg("IMG//boss_object.png", g_screen);
    bossObject->set_clips();
    int xPosBoss = (MAX_MAP_X * TILE_SIZE) - SCREEN_WIDTH * 0.6 - 11000;
    bossObject->set_xpos(xPosBoss);
    bossObject->set_ypos(10);
    bossObject->InitBullet(g_screen);
    boss.push_back(bossObject);
    int bossdied = 0;

    Explosion exp_threat;
    bool tRet = exp_threat.LoadImg("IMG//explosion.png", g_screen);
    if (!tRet) return -1;
    exp_threat.set_clip();

    ResultObject vic;
    bool vicRet = vic.LoadImg("IMG//Victory.png", g_screen);
    if (!vicRet) return -1;
    vic.set_clips();
    ResultObject def;
    bool defRet = def.LoadImg("IMG//Defeat.png", g_screen);
    if (!defRet) return -1;
    def.set_clips();

    Explosion exp_main;
    Explosion exp_left;
    bool lRet = exp_left.LoadImg("IMG//died_left.png", g_screen);
    exp_left.set_clip();
    if (!lRet) return -1;

    Explosion exp_right;
    bool rRet = exp_right.LoadImg("IMG//died_right.png", g_screen);
    exp_right.set_clip();
    if (!rRet) return -1;

    p_player.setDie(0);

    Text time_game;
    time_game.SetColor(Text::WHITE_TEXT);
    Text mark_game;
    mark_game.SetColor(Text::WHITE_TEXT);
    unsigned int mark_value = 0;
    Text money_game;
    money_game.SetColor(Text::WHITE_TEXT);

    int checkmusic = 0;
	checkvictory = -1;
	checkdefeat = -1;
	Time timer;
	timer.start();
    while (!is_quit) {
        fps_time.start();
        playtime = timer.get_tick();
        while (SDL_PollEvent(&g_event) != 0)
        {
            switch (g_event.type)
            {
            case SDL_QUIT:
                {
                    is_quit = true;
                    break;
                }
            case SDL_KEYDOWN:
                {
                    if (g_event.key.keysym.sym == SDLK_RETURN) {
                        checkmusic++;
                        if (!Mix_PlayingMusic() || checkmusic % 2 == 1) {
                            if (!Mix_PlayingMusic()) Mix_PlayMusic(g_music, -1);
                            else Mix_ResumeMusic();
                        }
                        else if (Mix_PlayingMusic() && checkmusic % 2 == 0) {
                            Mix_PauseMusic();
                        }
                    }

                    else if (g_event.key.keysym.sym == SDLK_ESCAPE) {
                        int check = 0;
                        if (Mix_PausedMusic() == 0) {
                            Mix_PauseMusic();
                            check = 1;
                        }
                        timer.paused();
                        if (MessageBox(NULL, "Do you want to resume game?", "Message", MB_YESNO | MB_ICONINFORMATION) == IDNO) {
                            Sleep(500);
                            Mix_HaltMusic();
                            menu1:
                                timer.stop();
                                int ret_menu = SDLCommonFunction::ShowMenuFinal(g_screen, font_menu, "Play Again", "Help", "Exit", "IMG//menu_background.png");
                                if (ret_menu == 2) {
                                    is_quit = true;
                                }
                                else if (ret_menu == 1) {
                                    int ret_menuHelp = SDLCommonFunction::ShowMenuHelp(g_screen, font_time, "<-- Go Back", "IMG//HelpMenu.png");
                                    if (ret_menuHelp == 0) goto menu1;
                                }
                                else {
                                    is_quit = false;
                                    goto again_label;
                                }
                        }
                        else {
                            timer.unpaused();
                            playtime = timer.get_tick();
                            if (check == 1) {
                                Mix_ResumeMusic();
                                check = 0;
                            }
                        }
                    }
                    break;
                }
            }

            p_player.HandleInputAction(g_event, g_screen, g_sound_bullet);
        }
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);


        g_background.Render(g_screen, NULL);

        //game_map.DrawMap(g_screen);
        Map map_data = game_map.getMap();

        p_player.HandleBullet(map_data, g_screen);
        p_player.SetMapXY(map_data.start_x, map_data.start_y);
        p_player.Doplayer(map_data, g_sound_effect);

        if (p_player.getHeart() == true) {
            player_power.InitCrease();
            p_player.setHeart(false);
        }
        p_player.Show(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);
        Graphic(p_player, mark_game, money_game, time_game, player_power, player_money, mark_value);

        if (p_player.player_left() == true) {
            exp_main = exp_right;
        }
        else if (p_player.player_left() == false) {
            exp_main = exp_left;
        }

        int time_val = SDL_GetTicks() / 1000;
        if (come_back_ == true && check_come_back_ == -1) {
            time_val_temp = time_val;
            check_come_back_++;
        }
        if ((time_val - time_val_temp) > IMMORTAL_TIME) {
            come_back_ = false;
            check_come_back_ = -1;
        }

        if (player_power.getNum() > 0) {
            if (p_player.getComeBack() == true) {
                come_back_ = true;
                check_come_back_ = -1;
                p_player.setComeBack(false);
                p_player.CountDie();
                p_player.SetRect(0, 0);
                p_player.set_comeback_time(60);
                SDL_Delay(1000);
                player_power.Decrease();
                player_power.Render(g_screen);
            }
        }
        else if (player_power.getNum() <= 0) {
            checkdefeat = 0;
        }

        for (int i = 0; i < threat_list.size(); i++) {
            ThreatObject* p_threat = threat_list.at(i);
            if (p_threat != NULL) {
                p_threat->SetMapXY(map_data.start_x, map_data.start_y);
                p_threat->ImpMoveType(g_screen);
                p_threat->DoPlayer(map_data);
                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(g_screen);

                if (player_power.getNum() > 0 && come_back_ == false) {
					SDL_Rect rect_player = p_player.GetRectFrame();
					bool bCol1 = false;
					vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();

					for (int j = 0; j < tBullet_list.size(); j++) {
						BulletObject* pt_bullet = tBullet_list.at(j);

						if (pt_bullet) {
							bCol1 = SDLCommonFunction::CheckCollision(pt_bullet->GetRect(), rect_player);

							if (bCol1) {
								p_threat->ResetBullet(pt_bullet);
								break;
							}
						}
					}

					SDL_Rect rect_threat = p_threat->GetRectFrame();
					bool bCol2 = SDLCommonFunction::CheckCollision(rect_player, rect_threat);

					if (bCol1 || bCol2) {
                        come_back_ = true;
                        check_come_back_ = -1;
						int width_exp_frame = exp_main.get_width_frame();
						int height_exp_frame = exp_main.get_height_frame();

						for (int ex = 0; ex < 4; ex++) {
							int x_pos = (p_player.GetRect().x + p_player.get_width_frame() * 0.5) - width_exp_frame * 0.5;
							int y_pos = (p_player.GetRect().y + p_player.get_height_frame() * 0.5) - height_exp_frame * 0.5;
							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.Show(g_screen);
							SDL_RenderPresent   (g_screen);
						}
                        Mix_PlayChannel(-1, g_sound_exp[0], 0);
						p_player.CountDie();
						p_player.SetRect (0, 0);
						p_player.set_comeback_time(60);
						SDL_Delay(1000);
						player_power.Decrease();
						player_power.Render(g_screen);

					}
				}
				else if (player_power.getNum() < 0) {
                    checkdefeat = 0;
				}
			}
        }


        int frame_exp_width = exp_threat.get_width_frame();
        int frame_exp_height = exp_threat.get_height_frame();

        vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
        for (int i = 0; i < bullet_arr.size(); i++) {
            BulletObject* p_bullet = bullet_arr.at(i);
            if (p_bullet != NULL) {
                for (int j = 0; j < threat_list.size(); j++) {
                    ThreatObject* obj_threat = threat_list.at(j);
                    if (obj_threat != NULL) {
                        SDL_Rect tRect;
                        tRect.x = obj_threat->GetRect().x;
                        tRect.y = obj_threat->GetRect().y;
                        tRect.w = obj_threat->get_width_frame();
                        tRect.h = obj_threat->get_height_frame();

                        SDL_Rect bRect = p_bullet->GetRect();
                        bool bCol = SDLCommonFunction::CheckCollision(bRect, tRect);
                        if (bCol) {
                            mark_value++;
                            for (int ex = 0; ex < 4; ex++) {
                                int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

                                exp_threat.set_frame(ex);
                                exp_threat.SetRect(x_pos, y_pos);
                                exp_threat.Show(g_screen);
                            }
                            Mix_PlayChannel(-1, g_sound_exp[1], 0);
                            p_player.RemoveBullet(i);
                            obj_threat->Free();
                            threat_list.erase(threat_list.begin() + j);
                        }
                    }
                }
            }
        }
        if (checkvictory == 0) {
            checkvictory = 1;
        }

        int val = MAX_MAP_X * TILE_SIZE - (map_data.start_x + p_player.GetRect().x);
		if (val <= SCREEN_WIDTH + 11000) {
			if (bossdied < 25) {
				bossObject->SetMapXY(map_data.start_x, map_data.start_y);
				bossObject->DoPlayer(map_data);
				bossObject->MakeBullet(g_screen, 400, 400);
				bossObject->Show(g_screen);
				if (player_power.getNum() > 0 && come_back_ == false) {
					SDL_Rect rect_player = p_player.GetRectFrame();
					bool bCol1 = false;
					vector<BulletObject*> tBullet_list = bossObject->get_bullet_list();
					for (int j = 0; j < tBullet_list.size(); j++) {
						BulletObject* pt_bullet = tBullet_list.at(j);
						if (pt_bullet) {
							bCol1 = SDLCommonFunction::CheckCollision(pt_bullet->GetRect(), rect_player);
							if (bCol1) {
								bossObject->RemoveBullet(j);
								break;
							}
						}
					}
					SDL_Rect rect_boss = bossObject->GetRectFrame();
					bool bCol2 = SDLCommonFunction::CheckCollision(rect_player, rect_boss);
					if (bCol2 || bCol1) {
						come_back_ = true;
						check_come_back_ = -1;
						int width_exp_frame = exp_main.get_width_frame();
						int height_exp_frame = exp_main.get_height_frame();

						for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
						{
							int x_pos = (p_player.GetRect().x + p_player.get_width_frame() * 0.5) - width_exp_frame * 0.5;
							int y_pos = (p_player.GetRect().y + p_player.get_height_frame() * 0.5) - height_exp_frame * 0.5;

							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.Show(g_screen);
							SDL_RenderPresent(g_screen);
						}
						Mix_PlayChannel(-1, g_sound_exp[0], 0);
						p_player.CountDie();
						p_player.SetRect(0, 0);
						p_player.set_comeback_time(60);
						SDL_Delay(1000);
                        if (player_power.getNum() >= 2) {
							player_power.Decrease();
							player_power.Decrease();
						}
						else if (player_power.getNum() < 2) {
							player_power.Decrease();
						}
						player_power.Render(g_screen);
					}
				}
				else if (player_power.getNum() <= 0) {checkdefeat = 0;}
				bullet_arr = p_player.get_bullet_list();
				for (int i = 0; i < bullet_arr.size(); i++)
				{
					BulletObject* p_bullet = bullet_arr.at(i);
					if (p_bullet != NULL) {

						SDL_Rect tRect;
						tRect.x = bossObject->GetRect().x;
						tRect.y = bossObject->GetRect().y;
						tRect.w = bossObject->get_width_frame();
						tRect.h = bossObject->get_height_frame();

						SDL_Rect bRect = p_bullet->GetRect();
						bool bCol = SDLCommonFunction::CheckCollision(bRect, tRect);
						int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
						int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;
						if (bCol) {
							for (int ex = 0; ex < NUM_FRAME_EXP; ex++) {
								exp_threat.set_frame(ex);
								exp_threat.SetRect(x_pos, y_pos);
								exp_threat.Show(g_screen);
							}
							Mix_PlayChannel(-1, g_sound_exp[1], 0);
							p_player.RemoveBullet(i);
							bossdied++;
							if (bossdied >= 25) {
								mark_value += 10;
								bossObject->Free();
								boss.pop_back();
								checkvictory = 0;
							}
						}
					}
				}
			}
		}

        Graphic(p_player, mark_game, money_game, time_game, player_power, player_money, mark_value);
        if (checkdefeat == 0) {
			Mix_PlayChannel(-1, g_sound_result[1], 0);
			Mix_PlayChannel(-1, g_sound_result[1], 0);
			Mix_HaltMusic();
			int resultCheck = result(def, p_player, is_quit, "GAME OVER", "INFORMATION", MB_OK | MB_ICONINFORMATION);
			if (resultCheck == 0) {
				goto again_label;
				continue;
			}
        result1:
			if (resultCheck == 1)
			{
				int ret_menuHelp = SDLCommonFunction::ShowMenuHelp(g_screen, font_time, "<-- Go Back", "img//HelpMenu.png");
				if (ret_menuHelp == 0) {
					int ret_menu = SDLCommonFunction::ShowMenuFinal(g_screen, font_menu, "Play Again", "Help", "Exit", "img//menu.png");
					if (ret_menu == 2)
					{
						is_quit = true;
					}
					else if (ret_menu == 1) {goto result1;}
					else if (ret_menu == 0) {goto again_label;}
				}
			}
		}
		if (checkvictory == 1) {
			Mix_PlayChannel(-1, g_sound_result[0], 0);
			Mix_PlayChannel(-1, g_sound_result[0], 0);
			Mix_HaltMusic();
			int resultCheck = result(vic, p_player, is_quit, "WINNER", "INFORMATION", MB_OK | MB_ICONINFORMATION);
			if (resultCheck == 0) {
				goto again_label;
				continue;
			}
		result2:
			if (resultCheck == 1)
			{
				int ret_menuHelp = SDLCommonFunction::ShowMenuHelp(g_screen, font_time, "<-- Go Back", "img//HelpMenu.png");
				if (ret_menuHelp == 0) {
					int ret_menu = SDLCommonFunction::ShowMenuFinal(g_screen, font_menu, "Play Again", "Help", "Exit", "img//menu.png");
					if (ret_menu == 2)
					{
						is_quit = true;
					}
					else if (ret_menu == 1) { goto result2; }
					else if (ret_menu == 0) { goto again_label; }
				}
			}
		}
        SDL_RenderPresent(g_screen);
        int real_imp_time = fps_time.get_tick();
		int time_one_frame = 1000 / FRAME_PER_SECOND;

		if (real_imp_time < time_one_frame) {
			int delay_time = time_one_frame - real_imp_time;
			if (delay_time >= 0) {
				SDL_Delay(delay_time);
			}
		}
    }
    for (int i = 0; i < threat_list.size(); i++) {
        ThreatObject* p_threat = threat_list.at(i);
        if (p_threat) {
            p_threat->Free();
            p_threat = NULL;
        }
    }
    threat_list.clear();

    close();
    return 0;
}
