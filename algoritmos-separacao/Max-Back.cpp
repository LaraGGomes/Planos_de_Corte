#include "Max-Back.h"

double MaxBack(const vvd &G, vector<int> &So, const vvb &x, int V, pair<int,int> &vf) {
    vector<double> maxback_val(V);      // quanto cada vértice recebe dos vértices pertencentes ao subconjunto
    vector<bool> Vrestante(V, true);    // V\So

    vector<double> grau(V);             // soma grau ponderado das arestas de cada vértice
    double cut_val = 0;
    double cut_valR;

    for(int v : So) Vrestante[v] = false;

    for(int j = 0; j < V; j++) {

        if(!Vrestante[j]) {             // soma todas as arestas na borda do subconjunto
            for(int i = 0; i < V; i++) {
                if(Vrestante[i])
                    cut_val += (G[i][j]*x[i][j]);
            }
        }

        double soma = 0;
        double total = 0;

        for(int i = 0; i < V; i++) {
            if(!Vrestante[i]) {             // maxback
                soma += (G[i][j]*x[i][j]);  // verificar dps se ele multiplica por 1 (ou se ta * true)
            }

            total += (G[i][j]*x[i][j]);     // total das arestas de cada vértice
        }

        maxback_val[j] = soma;
        grau[j] = total;
    }

    double mincut_val = cut_val;

    vector<int> Vfinais;
    vvi S(V - So.size() + 1);
    S[0] = So;
    int bestS = 0;
    
    for(int k = 1; k <= V - S[0].size(); k++) {
        // inserir o de vértice com maior max-back no conjunto
        int i = 0;
        while(!Vrestante[i]) i++;       // acho q ta tudo bem não ter verificação de i < V, pela quantidae de iterações do for principal
        for(int j = i+1; j < V; j++) {
            if (Vrestante[j] && maxback_val[j] > maxback_val[i]) i = j;
        }
        
        S[k] = S[k-1];
        S[k].push_back(i);
        Vrestante[i] = false;
        
        /*
        Aqui basicamente eu to pegando o penúltimo resultado do cut_val para ser retornado no SimpleMinCut, já que o
        último sempre vai ser 0, dado que é o corte do conjunto inteiro com o resto (que é vazio).
        Mas eu quis manter essa iteração acontecendo por que é ela que retorna pro Max-Back Múltiplo o conjunto de todos os vértices 
        */
        if(k == V - S[0].size()) cut_valR = cut_val;

        // mudanças nos valores de corte e maxbacks com a adição do vértice
        cut_val += grau[i] - (2* maxback_val[i]);
        
        for (int j = 0; j < V; j++) {
            if(Vrestante[j])
                maxback_val[j] += (G[i][j]*x[i][j]);
        }

        if(cut_val < mincut_val) {
            mincut_val = cut_val;
            bestS = k;
        }

        // Guardando os dois últimos vértices
        if(k >= (V - S[0].size() -1)) 
            Vfinais.push_back(i);
    }
    
    vf = {Vfinais[0], V > 2 ? Vfinais[1] : -1}; // v2 retorna -1 quando só tem 1 vértice inserido
    So = S[bestS];      // o subconjunto tá sendo retornado no próprio conjunto inicial (So)

    return cut_valR;

    // Retorna o valor do último corte, o subconjunto e os últimos dois vértices adicionados
}

vvi MaxBackM(const vvd &G, const vvb &x) {
    int V = x.size();
    pair<int,int> st;
    vvi S;
    double cut_val;

    vector<bool> vis(V, false);

    while(1) {
        int v = -1;
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                v = i;
                break;
            }
        }

        if (v == -1) break;  // todos os vértices foram visitadoss

        vector<int> Sk = {v};

        cut_val = MaxBack(G, Sk, x, V, st);

        S.push_back(Sk);

        for(int vertice : Sk) vis[vertice] = true;  // adicionando vértices do subconjunto encontrado nos visitados
    }

    return S;
}