// add your imports here
#include <iostream>
#include <vector>
#include <stack>
int pseudoRand[100] = {72, 99, 56, 34, 43, 62, 31, 4, 70, 22, 6, 65, 96, 71, 29, 9, 98, 41, 90, 7, 30, 3, 97, 49, 63, 88, 47, 82, 91, 54, 74, 2, 86, 14, 58, 35, 89, 11, 10, 60, 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5, 24, 33, 77, 53, 51, 59, 20, 42, 80, 61, 1, 0, 38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13, 12, 78, 75, 73, 84, 81, 8, 32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};
using namespace std;

vector<bool> verticals, horizontals, visited;
int randIndex;

struct Point2D{

  int x, y;
};

enum class Direction{
  Up = 0,
  Right = 1,
  Down = 2,
  Left = 3
};


string DirectionToString(Direction d)
{
  switch (d)
  {
    case Direction::Up:
      return "Up";
    case Direction::Right:
      return "Right";
    case Direction::Down:
      return "Down";
    case Direction::Left:
      return "Left";
  }
}

string PointToString(Point2D p)
{
  string output = "(";
  output += to_string(p.x);
  output += ", ";
  output += to_string(p.y);
  output += ")";
  return output;
}

stack<Point2D> frontier;

Point2D limits;

void GenerateMap(){
  verticals.resize((limits.x+1)*(limits.y+1));
  horizontals.resize((limits.x+1)*(limits.y+1));
  visited.resize(limits.x*limits.y);
  for (auto && i : visited)
  {
    i=false;
  }
  for (auto && horizontal : horizontals)
  {
    horizontal=true;
  }
  for (auto && vertical : verticals)
  {
    vertical=true;
  }
}

void BreakWall(Point2D p, Direction d)
{
  switch(d)
  {
    case Direction::Up:
    {
      horizontals[limits.x * p.y + p.x] = false;
      break;
    }
    case Direction::Right:
    {
      verticals[limits.x * p.y + p.x + 1] = false;
      break;
    }
    case Direction::Down:
    {
      horizontals[(limits.x) * (p.y+1) + p.x] = false;
      break;
    }
    case Direction::Left:
    {
      verticals[limits.x * p.y + p.x] = false;
      break;
    }
  }
}

bool IsThereWall(Point2D p, Direction d)
{
  switch(d)
  {
    case Direction::Up:
    {
      return horizontals[limits.x * p.y + p.x];
    }
    case Direction::Right:
    {
      return verticals[limits.x * p.y + p.x + 1];
    }
    case Direction::Down:
    {
      return horizontals[(limits.x) * (p.y+1) + p.x];
    }
    case Direction::Left:
    {
      return verticals[limits.x * p.y + p.x];
    }
  }
}

void setVisited(Point2D p, bool state)
{
  visited[limits.x*p.y+p.x] = state;
}

bool getVisited(Point2D p)
{
  {
    if (p.x<0 || p.x > limits.x || p.y<0 || p.y > limits.y) {
      return true;
    }
    return visited[limits.x*p.y+p.x];
  }
}

char wallOutput (Point2D p, Direction d)
{
  switch(d)
  {
    case Direction::Up:
    {
      if (IsThereWall(p, d))
      {
        return '_';
      } else
      {
        return ' ';
      }
    }
    case Direction::Left:
    {
      if (IsThereWall(p, d))
      {
        return '|';
      } else
      {
        return ' ';
      }
    }
    case Direction::Down:
    {
      if (IsThereWall(p, d))
      {
        return '_';
      } else
      {
        return ' ';
      }
    }
    case Direction::Right:
    {
      if (IsThereWall(p, d))
      {
        return '|';
      } else
      {
        return ' ';
      }
    }
    default:
      return ' ';
  }
}

void PrintGraph()
{
  for (int y = 0; y < limits.y + 1; y++)
  {
    for (int x = 0; x < limits.x + 1; x++)
    {
      if (y == 0) {
        if (x != limits.x)
        {
          cout << " ";
          cout << wallOutput(Point2D(x, y), Direction::Up);
        }
        else
        {
          cout << "  ";
        }
      } else if (x != limits.x)
      {
        cout << wallOutput(Point2D(x,y-1), Direction::Left);
        cout << wallOutput(Point2D(x,y-1), Direction::Down);
      } else {
        cout << wallOutput(Point2D(x-1,y-1), Direction::Right) << " ";
      }

    }
    cout << endl;
  }
}

vector<Direction> checkNeighborDirections(Point2D p) {
  vector<Direction> output;
  if (p.y > 0 && !getVisited(Point2D(p.x, p.y-1)))
  {
    output.push_back(Direction::Up);
  }
  if (p.x < limits.x-1 && !getVisited(Point2D(p.x+1, p.y)))
  {
    output.push_back(Direction::Right);
  }
  if (p.y < limits.y-1 && !getVisited(Point2D(p.x, p.y+1)))
  {
    output.push_back(Direction::Down);
  }
  if (p.x > 0 && !getVisited(Point2D(p.x-1, p.y)))
  {
    output.push_back(Direction::Left);
  }
  return output;
}

vector<Point2D> checkNeighbors(Point2D p)
{
  vector<Point2D> output;
  vector<Direction> directionList = checkNeighborDirections(p);
  for (auto & i : directionList)
  {
    switch(i)
    {
      case Direction::Up:
        output.push_back(Point2D(p.x, p.y-1));
        break;
      case Direction::Right:
        output.push_back(Point2D(p.x+1, p.y));
        break;
      case Direction::Down:
        output.push_back(Point2D(p.x, p.y+1));
        break;
      case Direction::Left:
        output.push_back(Point2D(p.x-1, p.y));
        break;
    }

  }
  return output;
}

void GenerateMaze()
{
  frontier.push(Point2D(0,0));
  while (!frontier.empty())
  {
    Point2D pointToCheck = frontier.top();
    setVisited(pointToCheck, true);
    Point2D neighbor;
    Direction direction;
    vector<Direction> directionList = checkNeighborDirections(pointToCheck);
    vector<Point2D> neighbors = checkNeighbors(pointToCheck);
    if (neighbors.empty())
    {
      frontier.pop();
    } else
      {
        if (neighbors.size() == 1)
        {
          neighbor = neighbors.at(0);
          direction = directionList.at(0);
        } else {
          int random = pseudoRand[randIndex % 100] % neighbors.size();
          neighbor = neighbors.at(random);
          direction = directionList.at(random);
          randIndex++;
        }
        BreakWall(pointToCheck, direction);
        frontier.push(neighbor);
     }
  }
}



int main(){
  // code here
  int columns, lines, index;
  cin >> columns >> lines >> index;
  limits.x = columns;
  limits.y = lines;
  randIndex = index;
  GenerateMap();
  GenerateMaze();
  PrintGraph();
}