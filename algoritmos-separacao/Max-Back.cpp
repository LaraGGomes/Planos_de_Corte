#include "Max-Back.h"

double MaxBack(vvd &G, vector<int> &So, vvi &x, vector<int> &grau, int V, pair<int,int> &vf) {
    vector<double> maxback_val(V+1);    // quanto cada vértice recebe dos vértices pertencentes ao subconjunto
    vector<bool> Vrestante(V+1, true);  // V\So
    Vrestante[0] = false;               // indexando em 1

    for(int j = 1; j <= V; j++) {
        double soma = 0;

        for(int i : So) {
            Vrestante[i] = false;
            soma += (G[i][j]*x[i][j]);
        }

        maxback_val[j] = soma;
    }

    double cut_val = 0;

    for(int i : So) {
        for(int j = 1; j <= V; j++) {
            if (Vrestante[j])
                cut_val += (G[i][j]*x[i][j]);
        }
    }

    double mincut_val = cut_val;

    vector<int> Vfinais;
    vvi S;
    S[0] = So;

    for(int k = 1; k <= V - S[0].size(); k++) {
        // inserir o de vértice com maior max-back no conjunto
        int i = 1;
        for(int j = 2; j <= V; j++) {
            if (maxback_val[j] > maxback_val[i]) i = j;
        }

        S[k] = S[k-1];
        S[k].push_back(i);
        Vrestante[i] = false;

        // mudanças nos valores de corte e maxbacks com a adição do vértice
        cut_val += grau[i] - (2* maxback_val[i]);

        for (int j = 1; j <= V; j++) {
            if(Vrestante[j])
                maxback_val[j] += (G[i][j]*x[i][j]);
        }

        if(cut_val < mincut_val) {
            mincut_val = cut_val;
            So = S[k];
        }

        // Guardando os dois últimos vértices
        if(k >= (V - S[0].size() -1)) 
            Vfinais.push_back(i);
    }

    vf = {Vfinais[0], Vfinais[1]};

    // O subconjunto tá sendo retornado no próprio conjunto inicial (So)

    return mincut_val;
}

vvi MaxBackM(vvd &G, vvi &x, vector<int> &grau) {
    int n = x.size();
    pair<int,int> st;
    vvi S;
    double cut_val;

    vector<bool> vis(n+1, false);

    while(1) {
        int v = 0;
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                v = i;
                break;
            }
        }

        if (!v) break;

        vector<int> Sk = {v};

        cut_val = MaxBack(G, Sk, x, grau, n, st);

        S.push_back(Sk);

        for(int vertice : Sk) vis[vertice] = true;
    }

    return S;
}