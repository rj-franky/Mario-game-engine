/*
	My first programming project over the summer
	Making a working mario clone for the first level :)
	creted by: Raheem Frankson
	Created on: 05/20/2024
	
	
	to do: 	create specific block types
		make 
		create enemies
		create score
		add sound effects
		add music
		make level
			
	05/21/2024:	Added camera follows player
			Added background environment to properly visualize camera movement
			Added some basic jumping, and physics
	05/22/2024:	Added block structure for environment
			Added collisions for box
	05/24/2024: 	fixed box collisions
			fixing movement functions and structures
	05/25/2024 	fixed being able to jump when freefalling
	09/01/2024:	revamped and fixed collision system with blocks
	10/02/2024:	fixed collision system with pipes
			added goomba
			
			
				
*/
#include"raylib.h"
#include"player.h"
#include"functions.cpp"
#include<string>

// Entry point
int main(){
	int screenWidth = 800;
	int screenHeight = 450;
	
	InitWindow(screenWidth, screenHeight, "window");
	SetTargetFPS(60);
	InitAudioDevice();
	
	//Music music = LoadMusicStream("audio/mario_music.mp3");
	//PlayMusicStream(music);
	
	Background_art env;
	Player mario;
	
	//Goomba goomba_array= {}
	Goomba goomba;
	
	MushroomPowerUp mushroom = MushroomPowerUp(685, 156, true);
	MysteryBlock mystery = MysteryBlock(685, 156, mushroom);
	
	Block blocks[] = {{0, 404, 2152, 63}, {497, 281}, {0,-100, 10, 1000}, {623, 281}, {655, 281}, {687, 281}};
	int blocks_length = sizeof(blocks)/sizeof(blocks[0]);
	
	Pipe test_Pipe[] = {{878, 344}};
	int pipe_Length = sizeof(test_Pipe)/sizeof(test_Pipe[0]);
	
	
	
	
	//camera setup
	Camera2D camera = { 0 };
	camera.target = (Vector2){mario.position.x + 20, mario.position.y + 20};
	camera.offset = (Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
	camera.rotation = 0.0;
	camera.zoom = 1.0;
	
	//Main Loop
	while (!WindowShouldClose())
	{

		float delta_time = GetFrameTime();
		//UpdateMusicStream(music);
		BeginDrawing();
		
		BeginMode2D(camera);
		
		env.draw_environment(); //draws background
		ClearBackground(WHITE);

		camera.target = (Vector2){mario.position.x + 20, mario.position.y + 20};
		
		goomba.goomba_update_movement(&delta_time);
		
		mushroom.drawPowerUp();
		mystery.draw_hitbox();
		mystery.drawBlock();
		
		mario.update_entity();//draws entity at new position
		gravity_update(&mario);
		gravity_update(&goomba);
		mario.player_movement(&delta_time);
		player_collisions(&mario, blocks, &blocks_length, test_Pipe, &pipe_Length,  &delta_time);
		enemy_collisions(&goomba, blocks, &blocks_length, test_Pipe, &pipe_Length,  &delta_time);
		
		
		draw_All_Hitboxes(blocks, blocks_length, test_Pipe, pipe_Length);
		
		EndMode2D();
		
		EndDrawing();
	}
	
	//StopMusicStream(music);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
