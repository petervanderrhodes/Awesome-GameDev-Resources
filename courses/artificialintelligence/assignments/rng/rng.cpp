// add your imports here
#include <iostream>

using namespace std;
unsigned int SeedConvert(unsigned int seed)
{
  seed = seed xor (seed << 13);
  seed = seed xor (seed >> 17);
  seed = seed xor (seed << 5);
  return seed;
}
int main(){
  // code here
  unsigned int seed, numbersToGenerate, randomMin, randomMax, value;
  cin >> seed >> numbersToGenerate >> randomMin >> randomMax;
  for (int i = 0; i < numbersToGenerate; i++)
  {
    seed = SeedConvert(seed);
    value = randomMin + (seed % (randomMax - randomMin + 1));
    cout << value << endl;
  }
}