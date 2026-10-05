#ifndef MAX_BACK_H
#define MAX_BACK_H

#include <vector>
#include <algorithm>

using namespace std;
typedef vector<vector<double>> vvd;
typedef vector<vector<bool>> vvb;
typedef vector<vector<int>> vvi;

double MaxBack(vvd &, vector<int> &, vvi &, vector<int> &, int , int &);
vvi MaxBackM(vvb &);

#endif