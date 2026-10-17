#ifndef BRANCH_AND_CUT_H
#define BRANCH_AND_CUT_H

#include <ilcplex/cplex.h>
#include <ilcplex/ilocplex.h>
#include "Max-Back.h"
#include <numeric>

using namespace std;

vector<bool> Soluciona(vvd &G, int V);
double CuttingPlanes();

#endif