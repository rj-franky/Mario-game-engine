#include"player.h"
#include"env.h"


void gravity_update(Entity *entity){
	entity->position.y += entity->vertical_speed;
	if (!entity->jump_flag){
		entity->vertical_speed += 0.1;
	}else{
		entity->vertical_speed = 0;
	}
}

void draw_All_Hitboxes(Block *blocks, int blocks_length, Pipe *Pipes, int pipe_Length){
	for (int i = 0; i < blocks_length; i++){
		blocks[i].draw_block_hitbox();
	}
	for (int i = 0; i < pipe_Length; i++){
		Pipes[i].draw_block_hitbox();
	}
}
void draw_All_Entites(Goomba* goomba_Array, int goomba_Length){
	for (int i = 0; i < goomba_Length; i++){
		goomba_Array[i].update_entity();
	}
}
//player collisions
void player_collisions(Player *mario, Block *blocks, int *blocks_length, Pipe *pipes, int *pipes_Length, float *delta){
	bool jump_flag2 = false;
	bool jump_flag1 = false;
	
	bool move_right1 = true;
	bool move_right2 = true;
	
	bool move_left1 = true;
	bool move_left2 = true;
	
	//statements to check the collision with a pipe
	for (int i = 0; i < *pipes_Length; i++){
		//pipe top
		if (pipes[i].get_hitbox().x <= mario->position.x + mario->get_width() &&
		    pipes[i].get_hitbox().x + pipes[i].get_hitbox().width >= mario->position.x &&
		    pipes[i].get_hitbox().y >= mario->position.y + mario->get_height() &&
		    pipes[i].get_hitbox().y <= mario->position.y + mario->vertical_speed + mario->get_height())
		{
			mario->position.y = pipes[i].position.y-mario->get_height();
			mario->vertical_speed = 0;
			jump_flag2 = true;
			break;
		}/*pipe bottom*/else if (pipes[i].get_hitbox().x <= mario->position.x + mario->get_width() &&
		    pipes[i].get_hitbox().x + pipes[i].get_hitbox().width >= mario->position.x &&
		    pipes[i].get_hitbox().y + pipes[i].get_hitbox().height < mario->position.y &&
		    pipes[i].get_hitbox().y + pipes[i].get_hitbox().height >= mario->position.y + mario->vertical_speed){
			mario->vertical_speed = 0;
		}/*pipe left*/else if (pipes[i].get_hitbox().x  - 27.5 <= mario->position.x + mario->speed * *delta &&
		    IsKeyDown(KEY_D) &&
		    mario->position.x < pipes[i].get_hitbox().x &&
		    pipes[i].get_hitbox().y + pipes[i].get_hitbox().height > mario->position.y &&
		    pipes[i].get_hitbox().y < mario->position.y + mario->get_height()){
			move_right1 = false;
			mario->position.x = pipes[i].get_hitbox().x - mario->get_width() - 2;
		}/*pipe right*/else if (pipes[i].get_hitbox().x + pipes[i].get_hitbox().width >= mario->position.x - mario->speed * *delta &&
		    IsKeyDown(KEY_A) &&
		    mario->position.x > pipes[i].get_hitbox().x &&
		    pipes[i].get_hitbox().y + blocks[i].get_hitbox().height> mario->position.y &&
		    pipes[i].get_hitbox().y < mario->position.y + mario->get_height()){
			move_left1 = false;
			mario->position.x = pipes[i].get_hitbox().x + pipes[i].get_hitbox().width;
		}
		
	}
	//statements to check the collision with a block
	for (int i = 0; i < *blocks_length; i++){
		/*block top*/if (blocks[i].get_hitbox().x <= mario->position.x + mario->get_width() &&
		    blocks[i].get_hitbox().x + blocks[i].get_hitbox().width >= mario->position.x &&
		    blocks[i].get_hitbox().y >= mario->position.y + mario->get_height() &&
		    blocks[i].get_hitbox().y <= mario->position.y + mario->vertical_speed + mario->get_height())
		{
			mario->position.y = blocks[i].position.y-mario->get_height();
			mario->vertical_speed = 0;
			jump_flag1 = true;
			break;
		}/*block bottom*/else if (blocks[i].get_hitbox().x <= mario->position.x + mario->get_width() &&
		    blocks[i].get_hitbox().x + blocks[i].get_hitbox().width >= mario->position.x &&
		    blocks[i].get_hitbox().y + blocks[i].get_hitbox().height < mario->position.y &&
		    blocks[i].get_hitbox().y + blocks[i].get_hitbox().height >= mario->position.y + mario->vertical_speed){
			mario->vertical_speed = 0;
		}/*blocks left*/else if (blocks[i].get_hitbox().x - blocks[i].get_hitbox().width <= mario->position.x + mario->speed * *delta &&
		    IsKeyDown(KEY_D) &&
		    mario->position.x < blocks[i].get_hitbox().x &&
		    blocks[i].get_hitbox().y + blocks[i].get_hitbox().height > mario->position.y &&
		    blocks[i].get_hitbox().y < mario->position.y + mario->get_height()){
			move_right2 = false;
			mario->position.x = blocks[i].get_hitbox().x - mario->get_width() - 2;
		}/*blocks right/*/else if (blocks[i].get_hitbox().x + blocks[i].get_hitbox().width >= mario->position.x - mario->speed * *delta &&
		    IsKeyDown(KEY_A) &&
		    mario->position.x >= blocks[i].get_hitbox().x &&
		    blocks[i].get_hitbox().y + blocks[i].get_hitbox().height> mario->position.y &&
		    blocks[i].get_hitbox().y < mario->position.y + mario->get_height()){
			move_left2 = false;
			mario->position.x = blocks[i].get_hitbox().x + blocks[i].get_hitbox().width;
		}
		
	}
	
	if (jump_flag1 || jump_flag2){
		mario->jump_flag = true;
	}else{
		mario->jump_flag = false;
	}
	
	if (!move_right1 || !move_right2){
		mario->move_right_flag = false;
	}else{
		mario->move_right_flag = true;
	}
	
	if (!move_left1 || !move_left2){
		mario->move_left_flag = false;
	}else{
		mario->move_left_flag = true;
	}
}
void enemy_collisions(EnemyEntity *entity, Block *blocks, int *blocks_length, Pipe *pipes, int *pipes_Length, float *delta){
	bool jump_flag2 = false;
	bool jump_flag1 = false;
	
	bool move_right1 = true;
	bool move_right2 = true;
	
	bool move_left1 = true;
	bool move_left2 = true;
	
	//statements to check the collision with a pipe
	for (int i = 0; i < *pipes_Length; i++){
		//pipe top
		if (!jump_flag2 &&
		    pipes[i].get_hitbox().x <= entity->position.x + entity->get_width() &&
		    pipes[i].get_hitbox().x + pipes[i].get_hitbox().width >= entity->position.x &&
		    pipes[i].get_hitbox().y >= entity->position.y + entity->get_height() &&
		    pipes[i].get_hitbox().y <= entity->position.y + entity->vertical_speed + entity->get_height())
		{
			entity->vertical_speed = 0;
			jump_flag2 = true;
		}/*pipe bottom*/else if (pipes[i].get_hitbox().x <= entity->position.x + entity->get_width() &&
		    pipes[i].get_hitbox().x + pipes[i].get_hitbox().width >= entity->position.x &&
		    pipes[i].get_hitbox().y + pipes[i].get_hitbox().height < entity->position.y &&
		    pipes[i].get_hitbox().y + pipes[i].get_hitbox().height >= entity->position.y + entity->vertical_speed){
			entity->vertical_speed = 0;
		}/*pipe left*/else if (pipes[i].get_hitbox().x  - 27.5 <= entity->position.x + entity->speed * *delta &&
		    entity->move_State &&
		    entity->position.x < pipes[i].get_hitbox().x &&
		    pipes[i].get_hitbox().y + pipes[i].get_hitbox().height > entity->position.y &&
		    pipes[i].get_hitbox().y < entity->position.y + entity->get_height()){
			move_right1 = false;
			entity->position.x = pipes[i].get_hitbox().x - entity->get_width() - 2;
		}/*pipe right*/else if (pipes[i].get_hitbox().x + pipes[i].get_hitbox().width >= entity->position.x - entity->speed * *delta &&
		    !entity->move_State &&
		    entity->position.x > pipes[i].get_hitbox().x &&
		    pipes[i].get_hitbox().y + blocks[i].get_hitbox().height> entity->position.y &&
		    pipes[i].get_hitbox().y < entity->position.y + entity->get_height()){
			move_left1 = false;
			entity->position.x = pipes[i].get_hitbox().x + pipes[i].get_hitbox().width;
		}
		
	}
	//statements to check the collision with a block
	for (int i = 0; i < *blocks_length; i++){
		/*block top*/if (!jump_flag1 &&
		    blocks[i].get_hitbox().x <= entity->position.x + entity->get_width() &&
		    blocks[i].get_hitbox().x + blocks[i].get_hitbox().width >= entity->position.x &&
		    blocks[i].get_hitbox().y >= entity->position.y + entity->get_height() &&
		    blocks[i].get_hitbox().y <= entity->position.y + entity->vertical_speed + entity->get_height())
		{
			entity->vertical_speed = 0;
			jump_flag1 = true;
		}/*block bottom*/else if (blocks[i].get_hitbox().x <= entity->position.x + entity->get_width() &&
		    blocks[i].get_hitbox().x + blocks[i].get_hitbox().width >= entity->position.x &&
		    blocks[i].get_hitbox().y + blocks[i].get_hitbox().height < entity->position.y &&
		    blocks[i].get_hitbox().y + blocks[i].get_hitbox().height >= entity->position.y + entity->vertical_speed){
			entity->vertical_speed = 0;
		}/*blocks left*/else if (blocks[i].get_hitbox().x - blocks[i].get_hitbox().width <= entity->position.x + entity->speed * *delta &&
		    entity->move_State &&
		    entity->position.x < blocks[i].get_hitbox().x &&
		    blocks[i].get_hitbox().y + blocks[i].get_hitbox().height > entity->position.y &&
		    blocks[i].get_hitbox().y < entity->position.y + entity->get_height()){
			move_right2 = false;
			entity->position.x = blocks[i].get_hitbox().x - entity->get_width() - 2;
		}/*blocks right*/else if (blocks[i].get_hitbox().x + blocks[i].get_hitbox().width >= entity->position.x - entity->speed * *delta &&
		    !entity->move_State &&
		    entity->position.x >= blocks[i].get_hitbox().x &&
		    blocks[i].get_hitbox().y + blocks[i].get_hitbox().height> entity->position.y &&
		    blocks[i].get_hitbox().y < entity->position.y + entity->get_height()){
			move_left2 = false;
			entity->position.x = blocks[i].get_hitbox().x + blocks[i].get_hitbox().width;
		}
		
	}
	
	if (jump_flag1 || jump_flag2){
		entity->jump_flag = true;
	}else{
		entity->jump_flag = false;
	}
	
	if (!move_right1 || !move_right2){
		entity->move_State = false;
	}else if (!move_left1 || !move_left2){
		entity->move_State = true;
	}
}
