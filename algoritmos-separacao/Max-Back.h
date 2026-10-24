#ifndef MAX_BACK_H
#define MAX_BACK_H

#include <vector>
#include <algorithm>
// #include <utility>

using namespace std;
typedef vector<vector<double>> vvd;
typedef vector<vector<bool>> vvb;
typedef vector<vector<int>> vvi;

double MaxBack(const vvd &, vector<int> &, const vvb &, int, pair<int,int> &);
vvi MaxBackM(const vvd &, const vvb &);

#endif