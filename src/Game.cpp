#include "inc/Game.h"

#include <iostream>
#include <sstream>

#include "inc/Utils.h"

Game::Game(void)
{
  this->turn = 0;

  int size;
  std::cin >> size; std::cin.ignore();
  for (int i = 0; i < size; i++)
  {
      std::string line;
      getline(std::cin, line);
  }
  int myID; // ID of your hero
  std::cin >> myID; std::cin.ignore();
}

Game::~Game(void)
{
}

void Game::Read(void)
{
  int entityCount; // the number of entities
  std::cin >> entityCount; std::cin.ignore();
  for (int i = 0; i < entityCount; i++)
  {
      std::string entityType; // HERO or MINE
      int id; // the ID of a hero or the owner of a mine
      int x; // the x position of the entity
      int y; // the y position of the entity
      int life; // the life of a hero (-1 for mines)
      int gold; // the gold of a hero (-1 for mines)
      std::cin >> entityType >> id >> x >> y >> life >> gold; std::cin.ignore();
  }
}

