#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <ViewRenderer.h>

class SpriteSheet
{
public:
	SpriteSheet();
	~SpriteSheet();
	void load(std::string path, std::list<SDL_Rect> sprites);
	void free();
	SDL_Texture* getTexture();
	SDL_Rect* getRandomSprite();
	SDL_Rect* getSpriteAt(int pos);
private:
	SDL_Texture* spriteTexture;
	std::vector<SDL_Rect*> sprites;
};

class SpriteRegister
{
public:
	static SpriteRegister* getInstance();
	static void clearInstance();
	SpriteSheet* getSpriteSheet(std::string path);
	void freeSprites();
	void initSprite(std::string path, std::list<SDL_Rect> rects);
private:
	std::map<std::string, SpriteSheet*> registeredSprite;
	SpriteRegister();
	~SpriteRegister();
	static SpriteRegister* instance;
};
