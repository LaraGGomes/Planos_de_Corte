#include <iostream>
#include "leitor-instancias/src/Data.h"
#include <vector>

using namespace std;
typedef vector<vector<double>> vvd;

int main(int argc, char** argv) {

    auto data = Data(2, argv[1]);
    data.read();

    size_t n = data.getDimension();

	vvd cost(n, vector<double>(n));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
            cost[i][j] = data.getDistance(i+1,j+1);
		}
	}

    return 0;
}
