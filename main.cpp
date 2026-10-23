#include <iostream>
#include "leitor-instancias/src/Data.h"
#include "Branch-and-Cut.h"
#include <limits>

using namespace std;
// typedef vector<vector<double>> vvd;

#define INF numeric_limits<int>::max()

int main(int argc, char** argv) {

    auto data = Data(2, argv[1]);
    data.read();

    size_t n = data.getDimension();

    // Grafo G vai estar indexado em 1 <- mudando de ideia sobre isso aq

	vvd cost(n, vector<double>(n));
	for (int i = 0; i < n; i++){
        cost[i][i] = INF;
		for (int j = i+1; j < n; j++){
            double c = data.getDistance(i+1, j+1);
            cost[i][j] = cost[j][i] = c;
		}
	}

    cout << "INF = " << INF << endl;

    // Soluciona(cost, n, {});

    return 0;
}
