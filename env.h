#ifndef env_h
#define env_h

struct Background_art{
	Vector2 position = {0, 0};
	Texture2D env_texture = LoadTexture("texture/level.png");
	
	void draw_environment()
	{
		DrawTextureEx(env_texture, position, 0, 1.95, WHITE);
	}
};

struct Ground{
	Vector2 position = {0, 0};
	Vector2 size = {35, 32};
	Texture2D env_texture;
	
	Rectangle get_hitbox(){
		return Rectangle{position.x, position.y, size.x, size.y};
	}
};

struct Block:Ground{
	Block(){
		size.x = 35;
		size.y = 32;
	}
	Block(float pos_x, float pos_y, float size_x = 35, float size_y = 32){
		position.x = pos_x;
		position.y = pos_y;
		size.x = size_x;
		size.y = size_y;
	}

	void draw_block_hitbox(){
		DrawRectangleLinesEx(get_hitbox(), 2, GREEN);
	}
};
struct Mystery_Block:Block{
	Mystery_Block(){
		size.x = 35;
		size.y = 32;
	}
	Mystery_Block(float pos_x, float pos_y, float size_x = 35, float size_y = 32){
		position.x = pos_x;
		position.y = pos_y;
		size.x = size_x;
		size.y = size_y;
	}
	 bool state_Used = false;
	 
};

struct Pipe:Block{
	Pipe(){
		size.x = 55;
		size.y = 70;
		position.x = 0;
		position.y = 338;
	}
	Pipe(float pos_x, float pos_y, float size_x = 55, float size_y = 63){
		position.x = pos_x;
		position.y = pos_y;
		size.x = size_x;
		size.y = size_y;
	}
	
};

#endif
