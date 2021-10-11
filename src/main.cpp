#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "inc/Game.h"
#include "inc/Stopwatch.h"
#include "util/Macros.h"

int main()
{
  Stopwatch sw;
  Game game;

  #ifdef TIMING
    if(TIMING)
    {
      sw.Start();
    }
  #endif

  // game loop
  while (true) {
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    game.Read();

    #ifdef TIMING
      if(TIMING && game.turn)
      {
        sw.Start();
      }
    #endif

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    Vec2i target = Vec2i();
    Entity* me = &game.players[game.myID];
    Entity* mostMinesEnemy = game.GetEnemyMostMines();
    Entity* closestEnemy = game.GetClosestEnemy(game.players, me);
    Entity* closestMine = game.GetClosestMine(game.map.mines, me);
    Entity* closestTavern = game.GetClosestTavern(game.map.taverns, me);

    #ifdef DEBUG_OUT
      if(DEBUG_OUT)
      {
        if(mostMinesEnemy != nullptr)
        {
          std::cerr << "mostMinesEnemy: " << *mostMinesEnemy << std::endl;
        }
        if(closestEnemy != nullptr)
        {
        std::cerr << "closestEnemy: " << *closestEnemy << std::endl;
        }
        if(closestMine != nullptr)
        {
        std::cerr << "closestMine: " << *closestMine << std::endl;
        }
        if(closestTavern != nullptr)
        {
        std::cerr << "closestTavern: " << *closestTavern << std::endl;
        }
      }
    #endif

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    std::cout << "WAIT" << std::endl; // WAIT | NORTH | EAST | SOUTH | WEST

    
    ++game.turn;
    #ifdef TIMING
      if(TIMING)
      {
        std::cerr << "Time taken : " << sw.GetTimestep() << " microseconds" << std::endl;
      }
    #endif
  }
}

