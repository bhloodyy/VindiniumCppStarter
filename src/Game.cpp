#include "inc/Game.h"

#include <iostream>
#include <sstream>
#include <map>

#include "inc/Utils.h"

Game::Game(void)
{
  this->turn = 0;
  
  this->map.Read();
  std::cin >> this->myID; std::cin.ignore();
  #ifdef DEBUG_INPUT
    if(DEBUG_INPUT)
    {
      std::cerr << this->myID << std::endl;
    }
  #endif

  this->map.Prepare();
}

Game::~Game(void)
{

}

void Game::Read(void)
{
  int entityCount; // the number of entities
  std::cin >> entityCount; std::cin.ignore();
  #ifdef DEBUG_INPUT
    if(DEBUG_INPUT)
    {
      std::cerr << entityCount << std::endl;
    }
  #endif
  std::vector<Entity> entities(entityCount);
  for (Entity entity : entities)
  {
    entity.Read();
    if (entity.type == HERO)
    {
      if(this->turn == 0)
      {
        entity.spawn = entity.pos;
        this->players.push_back(entity);
      }
      else
      {
        this->players[entity.id] = entity;
      }
    }
    /* MINE */
    else
    {
      if (this->turn == 0)
      {
        this->map.mines.insert(std::pair<Vec2i, Entity>(entity.pos, entity));
      }
      this->map.mines[entity.pos] = entity;
      if(entity.id != -1)
      {
        this->players[entity.id].numMines += 1;
      }
    }
  }

  this->map.UpdateMap(this->players);

  #ifdef DEBUG
    if(DEBUG)
    {
      for(auto player : this->players)
      {
        std::cerr << player << std::endl;
      }
      for(auto mine : this->map.mines)
      {
        std::cerr << mine.second << std::endl;
      }
      for(auto tavern : this->map.taverns)
      {
        std::cerr << tavern << std::endl;
      }
    }
  #endif
}

Entity* Game::GetClosestEnemy(std::vector<Entity>& vec, Entity* player)
{
  int shortestDist = INF;
  Entity* closest = nullptr;
  for(auto e : vec)
  {
    if(e.id != player->id)
    {
      int currDist = this->map.GetShortestDistance(this->players[player->id].pos, e.pos);

      if(currDist < shortestDist)
      {
        shortestDist = currDist;
        closest = Utils::GetElementPtr(vec, e);
      }
    }
  }

  return closest;
}

Entity* Game::GetClosestTavern(std::vector<Entity>& vec, Entity* player)
{
  int shortestDist = INF;
  Entity* closest = nullptr;
  for(auto e : vec)
  {
    int currDist = this->map.GetShortestDistance(this->players[player->id].pos, e.pos);
    if(currDist < shortestDist)
    {
      shortestDist = currDist;
      closest = Utils::GetElementPtr(vec, e);
    }
  }

  return closest;
}

Entity* Game::GetClosestMine(std::unordered_map<Vec2i, Entity>& map, Entity* player)
{
  int shortestDist = INF;
  Entity* closest = nullptr;
  for(auto p : map)
  {
    if(p.second.id != player->id)
    {
      for(auto dir : this->map.directions)
      {
        Vec2i curPos = p.second.pos + dir.second;

        if( this->map.IsInside(curPos) &&
            this->map.IsAccessible(curPos))
        {
          int currDist = this->map.GetShortestDistance(this->players[player->id].pos, curPos);

          if(currDist < shortestDist)
          {
            shortestDist = currDist;
            closest = &map[p.second.pos];
          }
        }
      }
    }
  }

  return closest;
}

Entity* Game::GetEnemyMostMines(void)
{
  int numMines = 0;
  Entity* most = nullptr;
  for(Entity e : this->players)
  {
    if(e.id != this->myID)
    {
      int currMines = e.numMines;

      if(numMines <= currMines)
      {
        numMines = currMines;
        most = &this->players[e.id];
      }
    }
  }

  return most;
}

std::vector<Vec2i> Game::GetClostestAdjacentCells(Entity* player, Vec2i target)
{
  int shortestDist = INF;
  std::vector<Vec2i> closestVec;
  for(auto const &dir : this->map.directions)
  {
    Vec2i curPos = player->pos + dir.second;
    if( this->map.IsInside(curPos) &&
        this->map.IsAccessible(curPos))
    {
      int dist = this->map.GetShortestDistance(curPos, target);
      if(dist < shortestDist)
      {
        closestVec.clear();
        closestVec.push_back(curPos);
        shortestDist = dist;
      }
      else if(dist == shortestDist)
      {
        closestVec.push_back(curPos);
      }
    }
  }

  return closestVec;
}
