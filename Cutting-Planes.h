#ifndef CUTTING_PLANES
#define CUTTING_PLANES

#include <ilcplex/cplex.h>
#include <ilcplex/ilocplex.h>
#include "algoritmos-separacao/Max-Back.h"
#include "algoritmos-separacao/Simple-Min-Cut.h"
#include <numeric>

double Soluciona(vvd &, int, vvi &, vvb &);
double CuttingPlanes(vvd &, int, string);

#endif