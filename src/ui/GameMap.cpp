#include <GameMap.h>

MapTile::~MapTile()
{
	if (obstacle != NULL) 
	{
		delete obstacle;
		obstacle = NULL;
	}
}

void MapTile::scroll(int delta)
{
	this->renderRect->y += delta;
	if (obstacle != NULL)
	{
		obstacle->scroll(delta);
	}
}

void MapTile::setObstacle(SDL_Texture* texture, SDL_Rect* sprite)
{
	SDL_Rect* rect = new SDL_Rect();
	rect->h = this->renderRect->h;
	rect->w = this->renderRect->w;
	rect->x = this->renderRect->x;
	rect->y = this->renderRect->y;
	obstacle = new StaticObstacle(texture, sprite, rect);
}

void MapTile::draw(ViewRenderer* viewRenderer)
{
	Drawable::draw(viewRenderer);
	if (obstacle != NULL)
	{
		obstacle->draw(viewRenderer);
	}	
}

bool MapTile::movable()
{
	if (obstacle != NULL)
	{
		return obstacle->isPassable();
	}
	return true;
}

template<class T>
void BaseMap<T>::clear()
{
	for each (T* element in elements)
	{
		delete element;
	}
	elements.clear();
}

template<class T>
BaseMap<T>::BaseMap()
{
}

template<class T>
BaseMap<T>::~BaseMap()
{
}

MapLine::MapLine(int yAxis, SpriteSheet* spriteSheet)
{
	y = yAxis;
	for (int i = 0; i < 12; i++)
	{
		SDL_Rect* renderRect = new SDL_Rect();
		renderRect->x = i * 50; 
		renderRect->y = yAxis; 
		renderRect->w = 50;
		renderRect->h = 50;

		MapTile* tile = new MapTile(spriteSheet->getTexture(), spriteSheet->getRandomSprite(), renderRect);
		elements.push_back(tile);
	}
}

MapLine::~MapLine()
{
	clear();
}

int MapLine::getY()
{
	return y;
}

int MapLine::getPreviousLineY()
{
	return y - 50;
}

bool MapLine::isPassedScreenTop()
{
	return y > 0;
}

bool MapLine::movable(int x)
{
	for each (auto ele in elements)
	{
		if (ele->getX() == x)
		{
			return ele->movable();
		}
	}
	return false;
}

void MapLine::scroll(int delta)
{
	y += delta;
	for each (MapTile* tile in elements)
	{
		tile->scroll(delta);
	}
}

void MapLine::init()
{

}

void MapLine::render(ViewRenderer* viewRenderer)
{
	for each (MapTile* tile in elements)
	{
		tile->draw(viewRenderer);
	}
}

void GrassLine::generateObstacles(int num, SpriteSheet* obstacleSheet)
{
	for (auto iter = elements.begin(); iter != elements.end(); ++iter)
	{
		if (rand() % 5 == 0)
		{
			(*iter)->setObstacle(obstacleSheet->getTexture(), obstacleSheet->getRandomSprite());
		}
	}
}

void RoadLine::generateObstacles(int num, SpriteSheet* obstacleSheet)
{
	SDL_Rect* rect = new SDL_Rect();
	rect->h = 50;
	rect->w = 50;
	rect->x = 100;
	rect->y = y;
	MovingObstacle* obstacle = new MovingObstacle(obstacleSheet->getTexture(), obstacleSheet->getRandomSprite(), rect);
	obstacle->setSpeed(rand() % 5 + 1);
	obstacles.push_back(obstacle);
}

void RoadLine::scroll(int delta)
{
	for each (auto obs in obstacles)
	{
		obs->scroll(delta);
		obs->move(0);
	}
	MapLine::scroll(delta);
}

void RoadLine::render(ViewRenderer* viewRenderer)
{
	MapLine::render(viewRenderer);
	for each (auto obs in obstacles)
	{
		obs->draw(viewRenderer);
	}
}

void WaterLine::generateObstacles(int num, SpriteSheet* obstacleSheet)
{
	SDL_Rect* rect = new SDL_Rect();
	rect->h = 50;
	rect->w = 50;
	rect->x = 0;
	rect->y = y;
	MovingObstacle* obstacle = new MovingObstacle(obstacleSheet->getTexture(), obstacleSheet->getRandomSprite(), rect);
	obstacles.push_back(obstacle);
}

void WaterLine::scroll(int delta)
{
	for each (auto obs in obstacles)
	{
		obs->scroll(delta);
	}
	MapLine::scroll(delta);
}

void WaterLine::render(ViewRenderer* viewRenderer)
{
	MapLine::render(viewRenderer);
	for each (auto obs in obstacles)
	{
		obs->draw(viewRenderer);
	}
}

bool MapLine::isOutOfScreen(int max)
{
	return y >= max;
}

MapLine* GameMap::createLineAt(int y)
{
	TileFactory* factory;
	switch (rand() % 7)
	{
	case 1:
		factory = WaterTileFactory::getInstance();
		break;
	case 2:
		factory = RoadTileFactory::getInstance();
		break;
	default:
		factory = GrassTileFactory::getInstance();
		break;
	}
	return factory->getLine(y, theme);
}

GameMap::GameMap(int w, int h)
{
	width = w;
	height = h;
	applyTheme(ORIGIN);
}

GameMap::~GameMap()
{
	clear();
}

void GameMap::init()
{
	ViewRenderer* viewRenderer = ViewRenderer::getInstance();
	for (int i = 0; i < 12; i++)
	{
		MapLine* mapLine = createLineAt(i * 50);
		mapLine->init();
		elements.push_back(mapLine);
	}
}

void GameMap::scroll(int delta)
{
	for each (MapLine* line in elements)
	{
		line->scroll(delta);
	}
	if (elements.back()->isOutOfScreen(height)) 
	{
		delete elements.back();
		elements.pop_back();
	}
	if (elements.front()->isPassedScreenTop()) 
	{
		MapLine* newLine = createLineAt(elements.front()->getPreviousLineY());
		newLine->init();
		elements.push_front(newLine);
	}
}

void GameMap::render(ViewRenderer* viewRenderer)
{
	for each (MapLine* line in elements)
	{
		line->render(viewRenderer);
	}
}

void GameMap::applyTheme(Theme theme)
{
	this->theme = theme;
	// register theme...
	ThemeRegister* themeRegister = ThemeRegister::getInstance();
	themeRegister->registerTile(GRASS, theme, "res/grassnb.png");
	themeRegister->registerTile(WATER, theme, "res/river.png");
	themeRegister->registerTile(ROAD, theme, "res/street.png");
	themeRegister->registerObstacle(GRASS, theme, "res/light.png");
	themeRegister->registerObstacle(ROAD, theme, "res/car.png");
	themeRegister->registerObstacle(WATER, theme, "res/water.png");
	SpriteRegister* spriteRegister = SpriteRegister::getInstance();
	
	spriteRegister->initSprite("res/grassnb.png", 2, 2);
	spriteRegister->initSprite("res/river.png", 1, 1);
	spriteRegister->initSprite("res/street.png", 1, 1);
	spriteRegister->initSprite("res/light.png", 2, 2);
	spriteRegister->initSprite("res/car.png", 1, 1);
	spriteRegister->initSprite("res/water.png", 1, 1);
}

bool GameMap::movable(int x, int y)
{
	for each (auto ele in elements)
	{
		if (ele->getY() == y)
		{
			return ele->movable(x);
		}
	}
	return false;
}

GrassTileFactory* GrassTileFactory::instance;
WaterTileFactory* WaterTileFactory::instance;
RoadTileFactory* RoadTileFactory::instance;

TileType RoadTileFactory::getType()
{
	return ROAD;
}

RoadTileFactory::RoadTileFactory()
{
}

RoadTileFactory::~RoadTileFactory()
{
}

MapLine* RoadTileFactory::getLine(int y, Theme theme)
{
	SpriteSheet* spriteSheet = getTile(theme);
	RoadLine* mapLine = new RoadLine(y, spriteSheet);
	// add obstacles here
	SpriteSheet* obstacleSheet = getObstacle(theme);
	int numObs = rand() % 11; 
	mapLine->generateObstacles(numObs, obstacleSheet);
	return mapLine;
}

TileFactory* RoadTileFactory::getInstance()
{
	if (instance == NULL)
	{
		instance = new RoadTileFactory();
	}
	return instance;
}

TileType WaterTileFactory::getType()
{
	return WATER;
}

WaterTileFactory::WaterTileFactory()
{
}

WaterTileFactory::~WaterTileFactory()
{
}

MapLine* WaterTileFactory::getLine(int y, Theme theme)
{
	SpriteSheet* spriteSheet = getTile(theme);
	WaterLine* mapLine = new WaterLine(y, spriteSheet);
	// add obstacles here
	SpriteSheet* obstacleSheet = getObstacle(theme);
	int numObs = rand() % 11;
	mapLine->generateObstacles(numObs, obstacleSheet);
	return mapLine;
}

TileFactory* WaterTileFactory::getInstance()
{
	if (instance == NULL)
	{
		instance = new WaterTileFactory();
	}
	return instance;
}

GrassTileFactory::GrassTileFactory()
{
}

GrassTileFactory::~GrassTileFactory()
{
}

MapLine* GrassTileFactory::getLine(int y, Theme theme)
{
	SpriteSheet* spriteSheet = getTile(theme);
	GrassLine* mapLine = new GrassLine(y, spriteSheet);
	// add obstacles here
	SpriteSheet* obstacleSheet = getObstacle(theme);
	int numObs = rand() % 11;
	mapLine->generateObstacles(numObs, obstacleSheet);
	return mapLine;
}

TileFactory* GrassTileFactory::getInstance()
{
	if (instance == NULL)
	{
		instance = new GrassTileFactory();
	}
	return instance;
}

TileType GrassTileFactory::getType()
{
	return GRASS;
}

TileFactory::TileFactory()
{
}

TileFactory::~TileFactory()
{
}

SpriteSheet* TileFactory::getObstacle(Theme theme)
{
	ThemeRegister* themeRegister = ThemeRegister::getInstance();
	std::string path = themeRegister->getObstaclePath(getType(), theme);
	return getSpriteSheetInternal(path);
}

SpriteSheet* TileFactory::getTile(Theme theme)
{
	ThemeRegister* themeRegister = ThemeRegister::getInstance();
	std::string path = themeRegister->getTilePath(getType(), theme);
	return getSpriteSheetInternal(path);
}

SpriteSheet* TileFactory::getSpriteSheetInternal(std::string path)
{
	SpriteRegister* spriteRegister = SpriteRegister::getInstance();
	SpriteSheet* spriteSheet = spriteRegister->getSpriteSheet(path);
	if (spriteSheet == NULL)
	{
		printf("No sprite sheet available for path %s", path);
	}
	return spriteSheet;
}

std::string TileFactory::getObstaclePath(Theme theme)
{
	ThemeRegister* themeRegister = ThemeRegister::getInstance();
	return themeRegister->getObstaclePath(getType(), theme);
}

std::string TileFactory::getTilePath(Theme theme)
{
	ThemeRegister* themeRegister = ThemeRegister::getInstance();
	return themeRegister->getTilePath(getType(), theme);
}

StaticObstacle::~StaticObstacle()
{
}

bool StaticObstacle::isPassable()
{
	return false;
}

GrassLine::~GrassLine()
{
}

RoadLine::~RoadLine()
{
	for (auto ele: obstacles)
	{
		delete ele;
	}
}

WaterLine::~WaterLine()
{
	for (auto ele : obstacles)
	{
		delete ele;
	}
}

MovingObstacle::~MovingObstacle()
{
}

bool MovingObstacle::isPassable()
{
	return false;
}

void MovingObstacle::move(int dir)
{
	this->renderRect->x += speed;
	if (renderRect->x > 600)
	{
		renderRect->x = -50;
	}
}
