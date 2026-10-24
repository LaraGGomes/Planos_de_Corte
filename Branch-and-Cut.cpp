#include "Branch-and-Cut.h"

double Soluciona(vvd &G, int V, vvi &restricoes, vvb &xFinal) {
    /*
        Recebe o TSPinit, retorna com o resolvedor cada variável binária
        da solução ótima encontrada  das arestas utilizadas.

        Deve receber também os subconjuntos que violam a restrição de subtour para
        adicionar as restrições do subtour no modelo.
        A restrição colocada sobre o subtour é de que o somatório das arestas dos 
        vértices do subconjunto para fora dele devem ser >= 2 
        (conectar o subconjunto com o resto).

        Acho que é uma boa ler cada variável binária e armazenar
        numa matriz de adjacência do grafo ótimo para o TSPinit, para o
        acesso ficar em tempo constante.
        Então o retorno em si fica como vector<vector<bool>>, indexado em 1.

        O grau de todo vértice daqui é 2.
    */

    IloEnv env;
    IloModel model(env);

    IloArray<IloNumVarArray> x(env, V);     // matriz de variáveis

    for(int i = 0; i < V; i++) {
        x[i] = IloNumVarArray(env, V, 0, 1, ILOBOOL);   // add linhas da matriz
        IloExpr somatorio = IloSum(x[i]);               // somatório das variáveis da linha
        somatorio -= x[i][i];

        model.add(IloRange(env, 2, somatorio, 2));      // restrição Σx[i] = 2

        somatorio.end();
    }

    // Restrições para os subconjuntos violados
    for(auto S : restricoes) {
        IloExpr somatorioS; // todas arestas pra restrição desse subconjunto

        for(int v = 0; v < S.size(); v++) {
            IloExpr arestasV = IloSum(x[S[v]]); // todas as arestas do vértice v ∈ S

            // tirar as arestas para vértices que ∈ S
            for(int i = 0; i < S.size(); i++) {
                arestasV -= x[S[v]][i];
            }

            somatorioS += arestasV;

            arestasV.end();
        }

        model.add(IloRange(env, 2, somatorioS, IloInfinity));   // somatório das arestas do subconjunto para fora do subc >= 2

        somatorioS.end();
    }

    // Adicionar função objetivo
    IloExpr objetivo(env);

    for(int i = 0; i < V; i++) {
        for(int j = i; j < V; j++) {
            model.add(IloRange(env, 0, x[i][j] - x[j][i], 0));  // linhas = colunas
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

    for(int i = 0; i < V; i++) {
        xFinal[i][i] = 0;
        for(int j = i+1; j < V; j++) {
            xFinal[i][j] = cplex.getValue(x[i][j]);
            xFinal[j][i] = cplex.getValue(x[i][j]);
            cout << x[i][j] << ' ';
        }
        cout << endl;
    }

    double val = cplex.getObjValue();
    cout << "Objetive: " << val;

    // Finalização
    cplex.clear();
    env.end();

    return val;
}

double CuttingPlanes(vvd &G, int V) {
    vvi R = {};

    while (1) {
        vvb x(V, vector<bool>(V));
        double custo = Soluciona(G, V, R, x);

        // Aqui fazer as opções de escolha entre algoritmos de separação
        // Mas antes tenho que confirmar qual o tipo de retorno que cada uma da quando a solução é viável

        // Vou supor primeiro que o M_MaxBack retorna um conjunto vazio de subtours

        vvi S = MaxBackM(G, x);

        if (S.size() == 0) {    // viável
            // retornar valor do x*
        }
        else {
            // Adiciona restrição em R
        }
    }
}