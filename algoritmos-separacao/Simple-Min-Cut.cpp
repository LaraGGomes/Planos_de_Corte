#include "Simple-Min-Cut.h"

double SimpleMinCut(vvd &G, vvb &x, vector<int> &graus, vector<int> &S) {
    int V = x.size();
    int mincut_val = INF;

    for(int k = 1; k < V; k++) {
        pair<int,int> st;
        vector<int> Saux = {k}; // not sure
        double cut_val = MaxBack(G, Saux, x, graus, V, st);

        if (cut_val < mincut_val) {
            mincut_val = cut_val;
            S.push_back(st.second);
        }

        Shrink(G, x, st);
    }

    return mincut_val;
}

void Shrink(vvd &G, vvb & x, pair<int,int> &st) {
    int V = x.size();

    vvd Vnew(V-1, vector<double>(V-1));
    int v1 = st.first;
    int v2 = st.second;

    // Pode ser que essa solução não funcione para dar shrink nas próximas iterações

    // adicionando os mesmos valores de arestas exceto v2, e combinando os v1 e v2
    for(int i = 1; i <= V; i++) {    // vou estar indexando em 1 mesmo se pa
        if (i == v2) continue;  // pulando v2

        vector<double> E;

        if(i == v1) {           // se for v1 precio somar com v2 nos valores das arestas
            for(int j = 1; j <= V; j++) {
                if (j == i) E.push_back(0);     // identidade
                else {
                    if (j == v2) j++;           // pular v2
                    if (j <= V) E.push_back(G[v1][j] + G[v2][j]);
                }
            }
        }
        else {
            for(int j = 1; j <= V; j++) {
                if (j == v1) E.push_back(G[i][j] + G[i][v2]);
                else {
                    if (j == v2) j++;
                    if (j <= V) E.push_back(G[i][j]);   // não tem v1 nem v2 envolvido
                }
            }
        }

        Vnew.push_back(E);
    }
    
    // nova soluçaõ x*
    vvb xNew(V-1, vector<bool>(V-1));
    for(int i = 1; i <= V; i++) {
        if(i == v2) continue;

        vector<bool> xlinha;
        
        if (i == v1) {
            for(int j = 1; j <= V; j++) {
                if(j == v2) j++;

                if(j <= V) xlinha.push_back( (x[v1][j] || x[v2][j]) ? 1 : 0 );  // se x[v1][j] ou x[v2][j] == true, então true
            }
        }
        else {
            for(int j = 1; j <= V; j++) {
                if(j == v2) j++;

                if(j <= V) xlinha.push_back(x[i][j]);
            }
        }

        xNew.push_back(xlinha);
    }

    G = Vnew;
    x = xNew;
}