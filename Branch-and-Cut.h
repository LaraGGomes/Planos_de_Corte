#ifndef BRANCH_AND_CUT_H
#define BRANCH_AND_CUT_H

#include <ilcplex/cplex.h>
#include <ilcplex/ilocplex.h>
#include "algoritmos-separacao/Max-Back.h"
#include <numeric>

using namespace std;

vvb Soluciona(vvd &, int, vvi &);
double CuttingPlanes(vvd &, int );

#endif