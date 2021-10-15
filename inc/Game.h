#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

#include "inc/Vec2.h"
#include "inc/Entity.h"
#include "inc/Map.h"
#include "util/Macros.h"

class Game
{
private:

public:
  /* init values */
  int turn = 0;
  int myID;
  std::vector<Entity> players;
  Map map;

  Game(void);
  ~Game(void);

  void Read(void);
  void CalcPlayerSpawn(void);
  Entity* GetClosestEnemy(std::vector<Entity>& vec, Entity* player);
  Entity* GetClosestTavern(std::vector<Entity>& vec, Entity* player);
  Entity* GetClosestMine(std::unordered_map<Vec2i, Entity>& map, Entity* player);
  Entity* GetEnemyMostMines(void);
  std::vector<Vec2i> GetClostestAdjacentCells(Entity* player, Vec2i target);
};

#endif /* GAME_H */
