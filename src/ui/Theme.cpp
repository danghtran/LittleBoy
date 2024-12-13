#include <Theme.h>

ThemeRegister* ThemeRegister::instance;


ThemeRegister::ThemeRegister()
{
}

ThemeRegister::~ThemeRegister()
{
}

ThemeRegister* ThemeRegister::getInstance() 
{
	if (instance == NULL)
	{
		instance = new ThemeRegister();
	}
	return instance;
}

std::string ThemeRegister::getTilePath(TileType type, Theme theme)
{
	return registeredTiles[{theme, type}];
}

std::string ThemeRegister::getObstaclePath(TileType type, Theme theme)
{
	return registeredObstacles[{theme, type}];
}

void ThemeRegister::registerTile(TileType type, Theme theme, std::string path)
{
	registeredTiles[{theme, type}] = path;
}

void ThemeRegister::registerObstacle(TileType type, Theme theme, std::string path)
{
	registeredObstacles[{theme, type}] = path;
}
