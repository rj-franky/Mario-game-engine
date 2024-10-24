#ifndef PLAYER_H
#define PLAYER_H
#include"env.h"

struct Entity{
	float scale = 1;
	Vector2 position = {0, 370};
	float speed = 0;
	float jump_speed = 0;
	float vertical_speed = 0;
	Texture2D sprite;
	bool living_State = true;
	bool jump_flag = true;
	bool move_left_flag = true;
	bool move_right_flag = true;
	bool hitboxVisible = true;
	
	void update_entity(){
		if (hitboxVisible){DrawRectangleLinesEx(get_hitbox(), 2, RED);}
		DrawTextureEx(sprite, position, 0, scale, WHITE);
	}
	Rectangle get_hitbox(){
		return Rectangle{position.x, position.y, get_width(), get_height()};
	}
	float get_width(){
		return sprite.width * scale;
	}
	float get_height(){
		return sprite.height * scale;
	}
};
struct Player:Entity{
	Player(){
		scale = 0.07;
		position = {1000, 360};
		speed = 300;
		jump_speed = -5.5;
		vertical_speed = 0;
		sprite = LoadTexture("texture/mm.png");
	}
	
	void player_movement(float *delta){
		if (IsKeyDown(KEY_A)){
			if(move_left_flag)position.x -= speed * *delta;
		}
		if (IsKeyDown(KEY_D)){
			if(move_right_flag)position.x += speed * *delta;
		}
		if (IsKeyPressed(KEY_SPACE)){
			if(jump_flag){
				vertical_speed = jump_speed;
				jump_flag = false;
			}
		}
	}
};
struct EnemyEntity:Entity{
	bool move_State = false;
};
struct Goomba:EnemyEntity{
	Goomba(float x = 1300, float y = 370, float sprite_scale = 1.95){
		position = {x, y};
		scale = sprite_scale;
		speed = 100;
		sprite = LoadTexture("texture/goomba.png");
	}
	void goomba_update_movement(float* delta){
	
		if (!move_State){
			update_entity();
			position.x -= speed * *delta;
		}else{
			update_entity();
			position.x += speed * * delta;
		}
	}
};
#endif
