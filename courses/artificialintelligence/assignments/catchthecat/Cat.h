#ifndef CAT_h
#define CAT_h
#include <queue>
#include <unordered_map>
#include <unordered_set>


#include "IAgent.h"

/*
 //real graph:
 /  \ /  \ /  \ /  \ /  \
| 0 0| 1 0| 2 0| 3 0| 4 0|
 \  / \  / \  / \  / \  / \
  | 0 1| 1 1| 2 1| 3 1| 4 1|
 /  \ /  \ /  \ /  \ /  \ /
| 0 2| 1 2| 2 2| 3 2| 4 2|
 \  / \  / \  / \  / \  / \
  | 0 3| 1 3| 2 3| 3 3| 4 3|
 /  \ /  \ /  \ /  \ /  \ /
| 0 4| 1 4| 2 4| 3 4| 4 4|
 \  / \  / \  / \  / \  /

 */



struct Cat : public IAgent {
  std::vector<bool> visited;
  void setup(int sideSize)
  {
    visited.clear();
    visited.reserve(sideSize * sideSize);
  }
  struct pair_hash // solving bs "oh you can't have a pair in a map" problem
  {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const
    {
      return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
  };

  std::vector<std::pair<int, int>> getVisitableNeighbors(std::pair<int,int> position, std::vector<bool>& visited, int sideSize, std::unordered_set<std::pair<int, int>, pair_hash> visiting)
  {
    int xMod = -1;
    std::vector<std::pair<int, int>> output;
    if (position.second % 2 == 1)
    {
      xMod = 0;
    }
    //top left
    if (position.second > 0 && position.first > (-xMod - 1) && !visited.at((position.second - 1) * sideSize + (position.first + xMod)) && !visiting.contains({(position.second - 1), (position.first + xMod)}))
    {
      output.push_back({position.first + xMod, position.second - 1});
    }
    //top right
    if (position.second > 0 && position.first < (sideSize + (-xMod - 1)) && !visited.at((position.second -1) * sideSize + (position.first + xMod + 1)) && !visiting.contains({(position.second -1), (position.first + xMod + 1)}))
    {
      output.push_back({position.first + xMod + 1, position.second - 1});
    }
    //left
    if (position.first > 0 && !visited.at((position.second) * sideSize + (position.first - 1)) && !visiting.contains({(position.second), (position.first - 1)}))
    {
      output.push_back({position.first -1, position.second});
    }
    //right
    if (position.first < (sideSize-1) && !visited.at((position.second) * sideSize + (position.first + 1)) && !visiting.contains({(position.second),(position.first + 1)}))
    {
      output.push_back({position.first +1, position.second});
    }
    //bottom left
    if (position.second < (sideSize-1) && position.first > (-xMod - 1) && !visited.at((position.second + 1) * sideSize + (position.first + xMod)) && !visiting.contains({(position.second + 1),(position.first + xMod)}))
    {
      output.push_back({position.first + xMod, position.second + 1});
    }
    //bottom right
    if (position.second < (sideSize-1) && position.first < (sideSize + (-xMod - 1)) && !visited.at((position.second +1) * sideSize + (position.first + xMod + 1)) && !visiting.contains({(position.second +1), (position.first + xMod + 1)}))
    {
      output.push_back({position.first + xMod + 1, position.second + 1});
    }
    return output;
  }

  std::vector<std::pair<int, int>> generatePath(std::vector<bool> world, std::pair<int, int> catPos, int sideSize)
  {
    std::unordered_map<std::pair<int, int>, std::pair<int,int>, pair_hash> cameFrom;
    std::queue<std::pair<int, int>> frontier;
    std::unordered_set<std::pair<int, int>, pair_hash> frontierSet;
    std::vector<bool> visited;

    frontier.push(catPos);
    frontierSet.insert(catPos);
    cameFrom.reserve(sideSize*sideSize);
    visited.resize(sideSize*sideSize); //populating visited with blocked cells


    for (int i = 0; i < sideSize * sideSize; i++)
    {
      if (world.at(i))
      {
        visited.at(i) = true;
      }
    }

    std::pair<int, int> last;
    while(!frontier.empty()) {
      auto current = frontier.back();
      frontier.pop();
      visited.at(current.second * sideSize + current.first) = true;

      auto neighbors = getVisitableNeighbors(current, visited, sideSize, frontierSet);
      for (auto & neighbor : neighbors)
      {
        cameFrom[{neighbor.first,neighbor.second}] = current;
        frontier.push(neighbor);
        frontierSet.insert(neighbor);
      }

      last = current;
      if (current.first == 0 || current.second == 0 || current.first == (sideSize-1) || current.second == (sideSize-1))
      {
        while (!frontier.empty())
        {
          frontier.pop();
        }
      }
    }
    std::vector<std::pair<int, int>> output;
    output.push_back(last);
    while (last != catPos)
    {
      last = cameFrom.at(last);
      output.push_back(last);
    }
    return output;
  }

  std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) override{
    setup(sideSize);
    int edge = sideSize / 2;
    catPos.first += edge;
    catPos.second += edge;
    auto path = generatePath(world, catPos, sideSize);
    //IF CATCHER:
    //std::pair<int, int> output = path.front();
    //IF CAT:
    int turnsMoved = 1;
    std::pair<int, int> output = path.at(path.size() - 1 - turnsMoved);
    return {output.first - edge,output.second - edge};
  }
};


#endif