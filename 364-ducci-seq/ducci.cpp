#include <iostream>
#include <set>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cassert>

using std::cout;
using std::set;
using std::vector;

void print(vector<int> x)
{
  for (int i=0; i < x.size(); i++)
    cout << x[i] << (i == x.size() - 1 ? "\n" : " ");
}

vector<int> diff(vector<int> x)
{
  size_t len = x.size();
  vector<int> out(len);
  for (int i=0; i < len - 1; i++)
    out[i] = abs(x[i] - x[i + 1]);
  out[len - 1] = abs(x[0] - x[len - 1]);
  return out;
}

int ducci(vector<int> x, int step, set< vector<int> > p)
{
  print(x);
  p.insert(x);
  x = diff(x);
  if (std::all_of(x.begin(), x.end(), [](int i) { return !i; }) ||
        p.find(x) != p.end()) {
    print(x);
    cout << ++step << " steps\n";
    return step;
  } else {
    return ducci(x, ++step, p);
  }
}

int main(int argc, char *argv[])
{
  assert(ducci({0,653,1854,4063}, 1, {}) == 24);
  assert(ducci({1, 5, 7, 9, 9}, 1, {}) == 23);
  assert(ducci({1, 2, 1, 2, 1, 0}, 1, {}) == 3);
  assert(ducci({10, 12, 41, 62, 31, 50}, 1, {}) == 22);
  assert(ducci({10, 12, 41, 62, 31}, 1, {}) == 30);

  return 0;
}
