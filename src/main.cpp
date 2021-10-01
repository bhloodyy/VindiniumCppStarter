#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "inc/Game.h"
#include "inc/Stopwatch.h"

#define TIMING false

int main()
{
  Stopwatch sw;

  Game game;

  if(TIMING)
  {
    sw.Start();
  }

  // game loop
  while (true) {
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    game.Read();

    if(TIMING && game.turn)
    {
      sw.Start();
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    std::cout << "WAIT" << std::endl; // WAIT | NORTH | EAST | SOUTH | WEST
    
    ++game.turn;
    if(TIMING)
    {
      std::cerr << sw.GetTimestep() << std::endl;
    }
  }
}

