#include <Sprite.h>

enum Theme
{
	ORIGIN, HIDDEN
};

enum TileType
{
	GRASS, WATER, ROAD
};

class ThemeRegister
{
public:
	ThemeRegister();
	~ThemeRegister();
	static ThemeRegister* getInstance();
	std::string getTilePath(TileType type, Theme theme);
	std::string getObstaclePath(TileType type, Theme theme);
	void registerTile(TileType type, Theme theme, std::string path);
	void registerObstacle(TileType type, Theme theme, std::string path);
private:
	std::map < std::pair<Theme, TileType>, std::string> registeredTiles;
	std::map < std::pair<Theme, TileType>, std::string> registeredObstacles;
	static ThemeRegister* instance;
};