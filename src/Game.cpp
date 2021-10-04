#include "inc/Game.h"

#include <iostream>
#include <sstream>

#include "inc/Utils.h"

Game::Game(void)
{
  this->turn = 0;

  this->map = new Map();
  std::cin >> this->myID; std::cin.ignore();
}

Game::~Game(void)
{
  delete this->map;
}

void Game::Read(void)
{
  int entityCount; // the number of entities
  std::cin >> entityCount; std::cin.ignore();
  std::vector<Entity> entities(entityCount);

  for(Entity p : this->players)
  {
    p.numMines = 0;
  }

  for (Entity entity : entities)
  {
    entity.Read(); 
    if (entity.type == HERO)
    {
      this->players[entity.id] = entity;
    }
    /* MINE */
    else
    {
      if (this->turn == 0)
      {
        this->mines.push_back(entity);
      }
      this->players[entity.id].numMines += 1;
    }
  }
  if (this->turn == 0)
  {
    this->map->numMines = entityCount - 4;
  }

  #ifdef DEBUG
    for(Entity player : this->players)
    {
      std::cerr << player << std::endl;
    }
    for(Entity tavern : this->map->taverns)
    {
      std::cerr << tavern << std::endl;
    }
  #endif
}

