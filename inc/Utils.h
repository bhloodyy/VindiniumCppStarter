#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>
#include <vector>

#include "util/Macros.h"

class Utils
{
private:
  Utils(void);
  ~Utils(void);

public:
  static std::vector<std::string> SplitString(std::string text, char delimiter);

  template<class T>
  static bool IsInVector(std::vector<T> list, T element)
  {
    return (std::find(list.begin(), list.end(), element) != list.end());
  }
};

#endif
