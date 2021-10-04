#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

#include "inc/Vec2.h"
#include "inc/Entity.h"
#include "inc/Map.h"
#include "util/Macros.h"

#define MAX_PLAYERS 4

class Game
{
private:

public:
  /* init values */
  int turn = 0;
  int myID;
  Entity players[MAX_PLAYERS];
  std::vector<Entity> mines;
  Map* map;

  Game(void);
  ~Game(void);

  void Read(void);
};

#endif /* GAME_H */
