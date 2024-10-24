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

struct PowerUp{
	Texture2D powerUpSprite;
	Vector2 position = {0,0};
	int scale = 1.95;
	int speed = 120;
	bool moveState = false;
	bool hitboxVisible = false;
	
	void drawPowerUp(){
		if (hitboxVisible){DrawRectangleLinesEx(get_hitbox(), 2, RED);}
		DrawTextureEx(powerUpSprite, position, 0, scale, WHITE);
	}
	
	void movePowerUp(float* delta){
		if (!moveState){
			drawPowerUp();
			position.x -= speed * *delta;
		}else{
			drawPowerUp();
			position.x += speed * * delta;
		}
	}
	Rectangle get_hitbox(){
		return Rectangle{position.x, position.y, get_width(), get_height()};
	}
	float get_width(){
		return powerUpSprite.width * scale;
	}
	float get_height(){
		return powerUpSprite.height * scale;
	}
};
struct MushroomPowerUp:PowerUp{
	
	MushroomPowerUp(float x = 0, float y = 0, bool move = false, bool visibility = false){
		position = {x, y};
		hitboxVisible = visibility;
		scale = 1.95;
		moveState = move;
		powerUpSprite = LoadTexture("texture/Mushroom Sprite.png");
	}
	
};

struct Ground{
	Vector2 position = {0, 0};
	Vector2 size = {35, 32};
	Texture2D blockSprite;
	
	Rectangle get_hitbox(){
		return Rectangle{position.x, position.y, size.x, size.y};
	}
};

struct Block:Ground{
	float scale = 1.95;
	
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

	void draw_hitbox(){
		DrawRectangleLinesEx(get_hitbox(), 2, GREEN);
	}
	void drawBlock(){
		DrawTextureEx(blockSprite, position, 0, scale, WHITE);
	}
};
struct MysteryBlock:Block{
	PowerUp powerUp;
	bool state_Used = false;	
	
	MysteryBlock(){
		size.x = 35;
		size.y = 32;
	}
	MysteryBlock(float pos_x, float pos_y, PowerUp specificPowerUp, float size_x = 35, float size_y = 32){
		position.x = pos_x;
		position.y = pos_y;
		size.x = size_x;
		size.y = size_y;
		powerUp = specificPowerUp;
		blockSprite = LoadTexture("texture/mysteryBlock.png");
	} 
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
