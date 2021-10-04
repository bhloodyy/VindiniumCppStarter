#include "inc/Utils.h"

#include <string>
#include <vector>

Utils::Utils(void)
{

}

Utils::~Utils(void)
{

}

std::vector<std::string> Utils::SplitString(std::string text, char delimiter)
{
  std::vector<std::string> out;
  std::string tmp = "";

  for(char c : text)
  {
    if(c != delimiter)
    {
      tmp += c;
    }
    else
    {
      out.push_back(tmp);
      tmp = "";
    }
  }
  out.push_back(tmp);

  return out;
}