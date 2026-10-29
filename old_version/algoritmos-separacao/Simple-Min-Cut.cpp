#include "Simple-Min-Cut.h"

vector<int> SimpleMinCut(vvd G, vvb x) {
    int V = x.size();
    vector<int> S;
    int mincut_val = INF;
    
    vvi superV(V);
    for(int i = 0; i < V; i++) superV[i] = {i};

    for(int k = 1; k <= V-1; k++) { // roda V-1 vezes 
        pair<int,int> st;
        vector<int> Saux = {0};
        double cut_val = MaxBack(G, Saux, x, G.size(), st);

        if (cut_val < mincut_val) {
            mincut_val = cut_val;
            S = st.second > -1 ? superV[st.second] : superV[st.first];
        }

        if(k < V-1) Shrink(G, x, st, superV);
    }

    return S;
}

void Shrink(vvd &G, vvb &x, pair<int,int> &st, vvi &superV) {
    int V = x.size();
    int v1 = st.first;
    int v2 = st.second;

    vvd Vnew;
    vvb Xnew;

    // Adicionando todo o supervértice v2 no v1
    superV[v1].insert(superV[v1].end(), superV[v2].begin(), superV[v2].end());
    superV.erase(superV.begin() + v2);

    // adicionando os mesmos valores de arestas exceto v2, e combinando os v1 e v2
    for(int i = 0; i < V; i++) {    // vou estar indexando em 1 mesmo se pa
        if (i == v2) continue;  // pulando v2

        vector<double> E;
        vector<bool> xLinha;

        if(i == v1) {           // se for v1 preciso somar com v2 nos valores das arestas
            for(int j = 0; j < V; j++) {
                if (j == i) {   // identidade
                    E.push_back(0);
                    xLinha.push_back(false);
                }
                else {
                    if (j == v2) continue;           // pular v2
                    E.push_back(G[v1][j] + G[v2][j]);
                    xLinha.push_back(x[v1][j] || x[v2][j]);
                }
            }
        }
        else {
            for(int j = 0; j < V; j++) {
                if (j == v1) {
                    E.push_back(G[i][v1] + G[i][v2]);
                    xLinha.push_back(x[i][v1] || x[i][v2]);
                }
                else {
                    if (j == v2) continue;
                    E.push_back(G[i][j]);   // não tem v1 nem v2 envolvido
                    xLinha.push_back(x[i][j]);
                }
            }
        }

        Vnew.push_back(E);
        Xnew.push_back(xLinha);
    }

    G = Vnew;
    x = Xnew;
}