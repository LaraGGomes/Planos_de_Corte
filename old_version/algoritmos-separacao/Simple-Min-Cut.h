#ifndef SIMPLE_MIN_CUT_H
#define SIMPLE_MIN_CUT_H

#include "Max-Back.h"
#include <limits>

#define INF numeric_limits<int>::max()

vector<int> SimpleMinCut(vvd, vvb);
void Shrink(vvd &, vvb &, pair<int,int> &, vvi &);

#endif