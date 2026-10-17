#include "Branch-and-Cut.h"

vector<bool> Soluciona(vvd &G, int V) {
    /*
        Recebe o TSPinit, retorna com o resolvedor cada variável binária
        da solução ótima encontrada  das arestas utilizadas.

        Acho que é uma boa ler cada variável binária e armazenar
        numa matriz de adjacência do grafo ótimo para o TSPinit, para o
        acesso ficar em tempo constante.
        Então o retorno em si fica como vector<vector<bool>>, indexado em 1.

        Pensando também na descrição das variáveis binárias na matriz
        ir preenchendo um vetor de grau de cada vértice (indexado em 1).
    */

    IloEnv env;
    IloModel model(env);

    IloArray<IloNumVarArray> x(env, V);     // matriz de variáveis

    for(int i = 0; i < V; i++) {
        x[i] = IloNumVarArray(env, V, 0, 1, ILOBOOL);   // add linhas da matriz
        IloExpr somatorio = IloSum(x[i]);               // somatório das variáveis da linha

        model.add(IloRange(env, 2, somatorio, 2));      // restrição Σx[i] = 2

        somatorio.end();
    }

    // Adicionar função objetivo
    IloExpr objetivo(env);

    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            objetivo += G[i][j]*x[i][j];
        }
    }

    model.add(IloMinimize(env, objetivo));
    objetivo.end();

    // Resolvendo
    IloCplex cplex(env);
    cplex.extract(model);
    if (cplex.solve()) {
        cout << "Ta funcionando\n";
    }
    else {
        cout << "Vish\n";
    }

    // Finalização
    cplex.clear();
    env.end();

    vector<bool> placeholder;

    return placeholder;
}

double CuttingPlanes() {
    
}