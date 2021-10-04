#include "inc/Map.h"

#include <iostream>
#include <sstream>

#include "inc/Utils.h"

Map::Map(void)
{
  this->numMines = 0;

  std::cin >> this->size; std::cin.ignore();
  for (int i = 0; i < this->size; i++)
  {
    std::string line;
    getline(std::cin, line);
    
    grid.push_back(line);
    for (int j = 0; j < line.length(); ++j)
    {
      if (line[j] == 'T')
      {
        Entity tavern;
        tavern.type = TAVERN;
        tavern.id = -1;
        tavern.pos.x = j;
        tavern.pos.y = i;
        tavern.life = 0;
        tavern.gold = 0;
        this->taverns.push_back(tavern);
      }
    }
  }

  // fill graph from read input
  this->FillGraph();

  // adjust graph with floyd warshell ~ 15 ms
  this->FloydWarshall();

  #ifdef DEBUG
    this->PrintGraph();
  #endif
}

Map::~Map(void)
{
}

void Map::FillGraph(void)
{
  // only add direct neighbours (cost 1) to graph 
  for (int y = 0; y < this->size; ++y)
  {
    for (int x = 0; x < this->size; ++x)
    {
      //look for neighbours only if cell is not a wall
      if (!this->IsWall(Vec2i(x, y)))
      {
        Vec2i curPos = Vec2i(x, y);
        for (auto const &dir : this->directions)
        {
          if (this->IsInside(curPos + dir.second))
          {
            // if neighbour is no wall save cost in graph
            if (this->grid[(curPos + dir.second).y][(curPos + dir.second).x] != '#')
            {
              this->graph[x + y * this->size][(curPos + dir.second).x + (curPos + dir.second).y * this->size] = 1;
              this->graph[(curPos + dir.second).x + (curPos + dir.second).y * this->size][x + y * this->size] = 1;
            }
          }
        }
      }
      else
      {
        this->graph[x + y * this->size][x + y * this->size] = INF;
      }
    }
  }

  // fill empty costs in graph
  for (int i = 0; i < this->size*this->size; ++i)
  {
    for (int j = 0; j < this->size*this->size; ++j)
    {
      if (this->graph[i][j] != 1)
      {
        if (i == j && this->graph[i][j] != INF)
        {
          this->graph[i][j] = 0;
        } 
        else
        {
          this->graph[i][j] = INF;
        }
      }
    }
  }
}

void Map::FloydWarshall(void)
{
  // calculate shortest distances from one to another
  for (int k = 0; k < this->size*this->size; k++)
  {
    // Pick all vertices as source one by one 
    for (int i = 0; i < this->size*this->size; i++)
    {
      // Pick all vertices as destination for the 
      // above picked source 
      for (int j = 0; j < this->size*this->size; j++)
      {
        // If vertex k is on the shortest path from 
        // i to j, then update the value of graph[i][j] 
        if (this->graph[i][k] != INF &&
          this->graph[k][j] != INF &&
          this->graph[i][k] + this->graph[k][j] < this->graph[i][j])
          this->graph[i][j] = this->graph[i][k] + this->graph[k][j];
      }
    }
  }
}

void Map::PrintGraph(void)
{
  for (int i = 0; i < this->size*this->size; ++i)
  {
    if (i == this->size / 2 - 1)
    {
      for (int j = 0; j < this->size*this->size; ++j)
      {
        if (this->graph[i][j] == INF)
        {
          std::cerr << "INF\t";
        }
        else
        {
          std::cerr << this->graph[i][j] << "\t";
        }
        if(j % this->size == this->size - 1)
          std::cerr << std::endl;
      }
      std::cerr << std::endl;
    }
  }
}

bool Map::IsInside(const Vec2i &pos)
{
  return pos.x >= 0 && pos.x < this->size && pos.y >= 0 && pos.y < this->size;
}

bool Map::IsWall(const Vec2i &pos)
{
  return this->grid[pos.y][pos.x] == '#';;
}

std::vector<Vec2i> Map::GetNeighbours(Vec2i* const &v)
{
  std::vector<Vec2i> neighbours;
  for (auto dir : this->directions)
  {
    Vec2i neighbour = *v + dir.second;
    if (this->IsInside(neighbour))
    {
      if (!this->IsWall(neighbour))
      {
        neighbours.push_back(neighbour);
      }
    }
  }
  return neighbours;
}

const int Map::GetStraightDistance(const Vec2i &start, const Vec2i &end)
{
  if (this->IsInside(start) && this->IsInside(end))
  {
    return (end-start).length();
  }
  else
  {
    return INF;
  }
}

const int Map::GetManhattenDistance(const Vec2i &start, const Vec2i &end)
{
  if (this->IsInside(start) && this->IsInside(end))
  {
    return abs(end.y - start.y) + abs(end.x - start.x);
  }
  else
  {
    return INF;
  }
}

const int Map::GetShortestDistance(const Vec2i &start, const Vec2i &end)
{
  if (this->IsInside(start) && this->IsInside(end))
  {
    return this->graph[start.x + start.y * this->size][end.x + end.y * this->size];
  }
  else
  {
    return INF;
  }
}

std::pair<std::string, Vec2i> Map::GetNextCell(const Vec2i &start, const Vec2i &end)
{
  int shortestDist = INF;
  std::pair<std::string, Vec2i> shortestDir;
  for (auto const &dir : this->directions)
  {
    if (shortestDir.second == Vec2i())
    {
      shortestDir = dir;
    }
    else
    {
      if (start + dir.second == end)
      {
        return dir;
      }
      int curDist = this->GetShortestDistance(start + dir.second, end);
      if (curDist < shortestDist)
      {
        shortestDist = curDist;
        shortestDir = dir;
      }
    }
  }
  return shortestDir;
}