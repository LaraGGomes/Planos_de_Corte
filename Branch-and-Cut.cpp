#include "Branch-and-Cut.h"

vector<bool> Soluciona(vvd &G, int V, vvi &restricoes) {
    /*
        Recebe o TSPinit, retorna com o resolvedor cada variável binária
        da solução ótima encontrada  das arestas utilizadas.

        Deve receber também os subconjuntos que violam a restrição de subtour para
        adicionar as restrições do subtour no modelo.
        A restrição colocada sobre o subtour pode ser que a somatória das variáveis 
        de cada aresta pertencente ao subconjunto é > |V| - 1.

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
    
    // Da pra retornar também o custo do resultado, pra retornar no CuttingPlanes caso seja ótimo
}

double CuttingPlanes(vvd &G, int V) {
    vvi R = {};

    while (1) {
        vvb x = Soluciona(G, V, R);

        // Aqui fazer as opções de escolha entre algoritmos de separação
        // Mas antes tenho que confirmar qual o tipo de retorno que cada uma da quando a solução é viável

        // Vou supor primeiro que o M_MaxBack retorna um conjunto vazio de subtours

        vvi provisorio;
        vvi S = MaxBackM(G, x, provisorio);

        if (S.size() == 0) {    // viável
            // retornar valor do x*
        }
        else {
            // Adiciona restrição em R
        }
    }
}