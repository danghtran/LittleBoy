#include <GameMap.h>
#include <Actor.h>
#include <ViewRenderer.h>

class Game
{
public:
	Game();
	~Game();
	void update();
	void clear();
	void render(ViewRenderer* viewRenderer);
	void initPlayer();
private:
	GameMap* map;
	Player* player;
};
