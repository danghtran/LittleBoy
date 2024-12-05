#include <GameMap.h>

class Game
{
public:
	Game();
	~Game();
	void update();
	void clear();
private:
	GameMap* map;

};
