#include <GameMap.h>
#include <Actor.h>
#include <ViewRenderer.h>

class Game
{
public:
	Game();
	~Game();
	void update();
	void init();
	void clear();
	void render(ViewRenderer* viewRenderer);
	void initPlayer();
	void movePlayer(int dir);
	void loadTheme(Theme theme, std::string file);
	void reset();
	bool checkCollision();
private:
	GameMap* map;
	Player* player;
	std::list<MapLine*>::iterator plPos;
};
