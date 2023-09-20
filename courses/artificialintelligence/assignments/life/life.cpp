#include <iostream>
//#include <vector>

using namespace std;

int gRows, gColumns;
bool checkSpot(char input)
{
  if (input == '#')
  {
    return true;
  }
  else
  {
    return false;
  }
};

char placeSpot(bool input)
{
  if (input)
  {
    return '#';
  }
  else
  {
    return '.';
  }
};

int checkNeighbors(bool **array, int xInput, int yInput)
{
  int count = 0;
  //cout << "checking neighbors of (" << xInput << ", " << yInput << ")\n";
  for (int xAddition = -1; xAddition <= 1; xAddition++)
  {
    int trueX = xInput;
    trueX += xAddition;
    if (trueX >= gColumns)
    {
      trueX = 0;
    }
    if (trueX < 0)
    {
      trueX = gColumns-1;
    }
    for (int yAddition = -1; yAddition <= 1; yAddition++)
    {
      int trueY = yInput;
      trueY += yAddition;
      if (trueY >= gRows)
      {
        trueY = 0;
      }
      if (trueY < 0)
      {
        trueY = gRows-1;
      }
      if ((xAddition != 0 || yAddition != 0) && array[trueX][trueY])
      {
        //cout << "neighbor of (" << xInput << ", " << yInput << "): (" << trueX << ", " << trueY << ") is " << array[trueX][trueY] << endl;
        count++;
      }
    }
  }
  return count;
}

int main()
{
  int rows, columns, time;
  cin >> columns >> rows >> time;
  gColumns = columns;
  gRows = rows;

  //setting up arrays
  bool** board;
  bool** nextBoard;
  board = new bool*[columns];
  nextBoard = new bool*[columns];
  for (int i = 0; i < columns; i++)
  {
    board[i] = new bool[rows];
    nextBoard[i] = new bool[rows];
  }

  //inputting into array
  for (int y = 0; y < rows; y++)
  {
    for (int x = 0; x < columns; x++)
    {
      char nextSpot;
      cin >> nextSpot;
      board[x][y] = checkSpot(nextSpot);
    }
  }
  //iterating
  //int testNeighborCount = checkNeighbors(board, 0, 1);
  //cout << "count is " << testNeighborCount << endl;
  //time = 1;
  for (int t = 0; t < time; t++)
  {
    for (int y = 0; y < rows; y++)
    {
      for (int x = 0; x < columns; x++)
      {
        int neighborCount = checkNeighbors(board, x, y);
        //cout << "neighbor count at " << x << ", " << y  <<" is " << neighborCount << endl;
        if (board[x][y])
        {
          if (neighborCount < 2 || neighborCount > 3)
          {
            //cout << "death at (" << x << ", " << y << ")\n";
            nextBoard[x][y] = false;
          }
          else
          {
            //cout << "survive at ("  << x << ", " << y << ")\n";
            nextBoard[x][y] = true;
          }
        }
        else {
          if (neighborCount == 3)
          {
            //cout << "sex\n";
            nextBoard[x][y] = true;
          }
          else
          {
            nextBoard[x][y] = false;
          }
        }
      }
    }
    for (int y = 0; y < rows; y++)
    {
      for (int x = 0; x < columns; x++)
      {
        if (nextBoard[x][y])
        {
          //cout << "living at (" << x << ", " << y << ")\n";
        }
        board[x][y] = nextBoard[x][y];
      }
    }
  }
  //outputting from array
  for (int y = 0; y < rows; y++)
  {
    for (int x = 0; x < columns; x++)
    {
      cout << placeSpot(board[x][y]);
    }
    cout << endl;
  }
  //deleting arrays
  for (int i = 0; i < columns; i++)
  {
    delete board[i];
    delete nextBoard[i];
  }
  delete board;
  delete nextBoard;
  return 0;
};