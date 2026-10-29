#include "separation.h"
#include <iostream>

vector <vector<int> > MaxBack(double** x, int n) {
    vector<vector<int>> S = {};

    vector<bool> vis(n, false);

    while(1) {
        int v = -1;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                v = i;
                break;
            }
        }

        if (v == -1) break;  // todos os vértices foram visitadoss

        vector<int> Sk = {v};
        double cut_val = MB(x, n, Sk);

        if(cut_val < 2.0 - EPSILON && Sk.size() > 1 && Sk.size() < n) S.push_back(Sk);

        for(int vertice : Sk) vis[vertice] = true;  // adicionando vértices do subconjunto encontrado nos visitados
    }

    return S;
}

/*
Vou dar uma sobrecarga no MB, pra poder usar ele separadamente
no MaxBack múltiplo e no MinCut
*/

double MB(double ** x, int V, vector<int> &So) {
    // Retorna subconjunto

    vector<double> maxback_val(V);      // quanto cada vértice recebe dos vértices pertencentes ao subconjunto
    vector<bool> Vrestante(V, true);    // V\So

    Vrestante[So[0]] = false;

    vector<double> grau(V);             // soma grau ponderado das arestas de cada vértice
    double cut_val = 0;

    for(int j = 0; j < V; j++) {

        if(!Vrestante[j]) {             // soma todas as arestas na borda do subconjunto
            for(int i = 0; i < V; i++) {
                if(Vrestante[i])
                    cut_val += (x[i][j]);
            }
            continue;
        }

        double soma = 0;
        double total = 0;

        for(int i = 0; i < V; i++) {
            if (i == j) continue;
            if(!Vrestante[i]) {             // maxback
                soma += (x[i][j]);
            }

            total += (x[i][j]);     // total das arestas de cada vértice
        }

        maxback_val[j] = soma;
        grau[j] = total;
    }

    double mincut_val = cut_val;
    int bestS = 0;

    vector<vector<int>> S(V);
    S[0] = So;
    
    for(int k = 1; k <= V - 1; k++) {
        // inserir o de vértice com maior max-back no conjunto
        int i = 0;
        while(!Vrestante[i]) i++;       // acho q ta tudo bem não ter verificação de i < V, pela quantidae de iterações do for principal
        for(int j = i+1; j < V; j++) {
            if (Vrestante[j] && maxback_val[j] > maxback_val[i]) i = j;
        }
        
        S[k] = S[k-1];
        S[k].push_back(i);
        Vrestante[i] = false;

        // mudanças nos valores de corte e maxbacks com a adição do vértice
        cut_val += grau[i] - (2* maxback_val[i]);
        
        for (int j = 0; j < V; j++) {
            if(Vrestante[j])
                maxback_val[j] += (x[i][j]);
        }

        if(cut_val < mincut_val) {
            mincut_val = cut_val;
            bestS = k;
        }
    }

    So = S[bestS];
    
    return mincut_val;
}
double MB(double ** x, int V, pair<int,int> &st) {
    // So iniciado sempre como {0}

    vector<double> maxback_val(V);      // quanto cada vértice recebe dos vértices pertencentes ao subconjunto
    vector<bool> Vrestante(V, true);    // V\So

    vector<double> grau(V);             // soma grau ponderado das arestas de cada vértice
    double cut_val = 0;

    Vrestante[0] = false;
    
    for(int i = 1; i < V; i++) {
        cut_val += x[0][i];
    }

    for(int j = 1; j < V; j++) {
        double total = 0;
        
        for(int i = 0; i < V; i++) {
            if(i == j) continue;
            total += (x[j][i]);     // total das arestas de cada vértice
        }
        
        grau[j] = total;
        maxback_val[j] = x[0][j];
    }
    
    int pv;     // penúltimo vértice
    
    for(int k = 1; k < V - 1; k++) {
        // inserir o de vértice com maior max-back no conjunto
        int i = 1;
        while(!Vrestante[i]) i++;       // acho q ta tudo bem não ter verificação de i < V, pela quantidae de iterações do for principal
        for(int j = i+1; j < V; j++) {
            if (Vrestante[j] && maxback_val[j] > maxback_val[i]) i = j;
        }
        
        Vrestante[i] = false;
        
        // mudanças nos valores de corte e maxbacks com a adição do vértice
        cut_val += grau[i] - (2* maxback_val[i]);
        
        for (int j = 0; j < V; j++) {
            if(Vrestante[j])
                maxback_val[j] += (x[i][j]);
        }
        
        // Guardando o penúltimo vértice
        if(k == (V - 2)) pv = i;
        
        /*
        Diferentemente do outro MB, to parando uma iteação antes, para o cut_val ser
        exatamente o que é retornado. Só preciso procurar o último vértice.
        */
    }

    int i = 1;
    while(i < V && !Vrestante[i]) i++;    

    st = {V > 2 ? pv : 0, i}; 

    return cut_val;
}

vector <vector<int> > MinCut(double** x, int n) {
    vector<vector<int>> S;
    vector<vector<int>> superV(n);
    int tam = n;

    for(int i = 0; i < n; i++) superV[i] = {i};

    double **x_cpy = new double*[n];
    for(int i = 0; i < n; i++) {
        x_cpy[i] = new double[n];

        for(int j = 0; j < n; j++) {
            if(i == j) x_cpy[i][j] = 0;
            x_cpy[i][j] = x[i][j];
        }
    }

    for(int k = 1; k < n; k++) { // roda n-1 vezes 
        pair<int,int> st;
        
        double cut_val = MB(x_cpy, tam, st);
        
        if (cut_val < 2) {
            S.push_back(st.second > -1 ? superV[st.second] : superV[st.first]);
        }

        if(k >= n-1) break;

        double ** Xold = x_cpy;
        
        x_cpy = Shrink(x_cpy, tam, st, superV);
        tam--;

        for(int i = 0; i <= tam; i++) delete[] Xold[i];
        delete[] Xold;
    }

    for(int i = 0; i < tam; i++) delete[] x_cpy[i];
    delete[] x_cpy;

    return S;
}

double ** Shrink(double ** x, int &V, pair<int,int> st, vector<vector<int>> &superV) {
    int v1 = st.first;
    int v2 = st.second;

    double ** Xnew = new double*[V-1];
    int idx = 0;
    
    // Adicionando todo o supervértice v2 no v1
    superV[v1].insert(superV[v1].end(), superV[v2].begin(), superV[v2].end());
    superV.erase(superV.begin() + v2);
    
    // adicionando os mesmos valores de arestas exceto v2, e combinando os v1 e v2
    for(int i = 0; i < V; i++) {    // vou estar indexando em 1 mesmo se pa
        if (i == v2) continue;  // pulando v2
        
        Xnew[idx] = new double[V-1];
        int idx2 = 0;
        
        if(i == v1) {           // se for v1 preciso somar com v2 nos valores das arestas
            for(int j = 0; j < V; j++) {
                if (j == i) {   // identidade
                    Xnew[idx][idx2] = 0;
                }
                else {
                    if (j == v2) continue;           // pular v2
                    Xnew[idx][idx2] = x[v1][j] + x[v2][j];
                }
                idx2++;
            }
        }
        else {
            for(int j = 0; j < V; j++) {
                if (j == v1) {
                    Xnew[idx][idx2] = x[i][v1] + x[i][v2];
                }
                else {
                    if (j == v2) continue;
                    Xnew[idx][idx2] = x[i][j];
                }
                idx2++;
            }
        }
        
        idx++;
    }
    
    return Xnew;
}
