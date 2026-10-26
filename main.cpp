#include <iostream>
#include "leitor-instancias/src/Data.h"
#include "Branch-and-Cut.h"
#include <limits>

using namespace std;

#define INF numeric_limits<int>::max()

int main(int argc, char** argv) {

    auto data = Data(2, argv[1]);
    data.read();

    string modo = argv[2];
    size_t n = data.getDimension();

	vvd G(n, vector<double>(n));
	for (int i = 0; i < n; i++){
        G[i][i] = INF;
		for (int j = i+1; j < n; j++){
            double c = data.getDistance(i+1, j+1);
            G[i][j] = G[j][i] = c;
		}
	}

    double custo = CuttingPlanes(G, n, modo);

    cout << "Melhor custo encontrado: " << custo << endl;

    return 0;
}
