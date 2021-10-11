#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <unordered_map>

#include "inc/Vec2.h"
#include "inc/Entity.h"

const std::string  HERO = "HERO", MINE = "MINE", TAVERN = "TAVERN",
              WEST = "WEST", NORTHWEST = "NORTHWEST",
              NORTH = "NORTH", NORTHEAST = "NORTHEAST",
              EAST = "EAST", SOUTHEAST = "SOUTHEAST",
              SOUTH = "SOUTH", SOUTHWEST = "SOUTHWEST";
const int MAX_SIZE = 24;

class Map
{
private:
  void FillGraph(void);
  void FloydWarshall(void);

public:
  /* init values */
  int size;
  std::vector<std::string> grid;
  std::vector<Entity> taverns;
  std::unordered_map<Vec2i, Entity> mines;
  int graph[MAX_SIZE*MAX_SIZE][MAX_SIZE*MAX_SIZE];

  std::unordered_map<std::string, Vec2i> directions =
  {
    { WEST, Vec2i(-1, 0) },
    //{ NORTHWEST, Vec2i(-1, -1) },
    { NORTH, Vec2i(0, -1) },
    //{ NORTHEAST, Vec2i(1, -1) },
    { EAST, Vec2i(1, 0) },
    //{ SOUTHEAST, Vec2i(1, 1) },
    { SOUTH, Vec2i(0, 1) },
    //  { SOUTHWEST, Vec2i(-1, 1) }
  };

  Map(void);
  ~Map(void);

  void Read(void);
  void Prepare(void);
  void PrintGraph(void);
  void UpdateMap(std::vector<Entity>& players);
  bool IsInside(const Vec2i &pos);
  bool IsWall(const Vec2i &pos);
  bool IsMine(const Vec2i &pos);
  bool IsTavern(const Vec2i &pos);
  bool IsPlayer(const Vec2i &pos);
  bool IsAccessible(const Vec2i &pos);
  std::vector<Vec2i> GetNeighbours(Vec2i* const &v);
  const int GetStraightDistance(const Vec2i &start, const Vec2i &end);
  const int GetManhattenDistance(const Vec2i &start, const Vec2i &end);
  const int GetShortestDistance(const Vec2i &start, const Vec2i &end);
  Vec2i GetNextCell(const Vec2i &start, const Vec2i &end);
};

#endif /* MAP_H */
