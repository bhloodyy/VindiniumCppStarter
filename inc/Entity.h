#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <iostream>

#include "inc/Vec2.h"
#include "util/Macros.h"

class Entity
{
public:
  std::string type;
  int id;
  Vec2i pos;
  int life;
  int gold;
  int numMines;
  Entity() {};
  bool operator == (const Entity &e) { return this->type == e.type && this->id == e.id && this->pos == e.pos && this->life == e.life && this->gold == e.gold; };
  friend std::ostream &operator << (std::ostream &os, const Entity &e)
  {
    return os << "Type: " << e.type << ", Id: " << e.id << ", X: " << e.pos.x << ", Y: " << e.pos.y << ", Life: " << e.life << ", Gold: " << e.gold << ", numMines: " << e.numMines;
  };
  void Read()
  {
    std::cin >> this->type >> this->id >> this->pos.x >> this->pos.y >> this->life >> this->gold; std::cin.ignore();
    #ifdef DEBUG_INPUT
      std::cerr << *this << std::endl;
    #endif
  };
};

#endif /* ENTITY_H */
