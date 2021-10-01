#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

#include "inc/Vec2.h"

class Game
{
private:

public:
  /* init values */
  int turn = 0;

  Game(void);
  ~Game(void);

  void Read(void);
};

#endif /* GAME_H */
