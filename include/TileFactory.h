#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include <vector>
#include <ViewRenderer.h>

class TileSprite
{
public:
	TileSprite();
	~TileSprite();
	void load(std::string path);
	void free();
	SDL_Texture* getSprite();
	SDL_Rect* getRandomSprite();
private:
	SDL_Texture* spriteTexture;
	std::vector<SDL_Rect*> sprites;
};

class TileFactory
{
public:
	static TileFactory* getInstance();
	static void clearInstance();
	TileSprite* getSprite(std::string path);
	void freeSprites();
private:
	std::map<std::string, TileSprite*> registeredSprite;
	TileFactory();
	~TileFactory();
	static TileFactory* instance;
};
