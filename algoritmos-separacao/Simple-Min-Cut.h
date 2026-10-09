#ifndef SIMPLE_MIN_CUT_H
#define SIMPLE_MIN_CUT_H

#include "Max-Back.h"
#include <limits>

#define INF numeric_limits<int>::max()

double SimpleMinCut(vvd &, vvb &, vector<int> &, vector<int> &);
void Shrink(vvd &, vector<bool> &, pair<int,int> &);

#endif