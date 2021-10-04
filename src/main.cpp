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
    sw.Start();
  #endif

  // game loop
  while (true) {
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    game.Read();

    #ifdef TIMING
      if(game.turn)
      {
        sw.Start();
      }
    #endif

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    std::cout << "WAIT" << std::endl; // WAIT | NORTH | EAST | SOUTH | WEST
    
    ++game.turn;
    #ifdef TIMING
      std::cerr << sw.GetTimestep() << std::endl;
    #endif
  }
}

