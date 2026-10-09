#ifndef SIMPLE_MIN_CUT_H
#define SIMPLE_MIN_CUT_H

#include "Max-Back.h"
#include <limits>

#define INF numeric_limits<int>::max()

double SimpleMinCut(const vvd &, vvb &, vector<int> &);
void Shrink(vvd &, vector<bool> &);

#endif