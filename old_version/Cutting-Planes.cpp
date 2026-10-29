#include "Cutting-Planes.h"

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
    for(int k = 0; k < restricoes.size(); k++) {

        IloExpr somatorioS(env); // todas arestas pra restrição desse subconjunto

        for(int j = 0; j < restricoes[k].size(); j++) {
            int v = restricoes[k][j];

            IloExpr arestasV = IloSum(x[v]); // todas as arestas do vértice v ∈ S

            // tirar as arestas para vértices que ∈ S
            for(int i = 0; i < restricoes[k].size(); i++) {
                arestasV -= x[v][restricoes[k][i]];
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

    cplex.setOut(env.getNullStream());      // limpeza para silenciar
    cplex.setWarning(env.getNullStream());  // o terminal

    cplex.extract(model);
    if (!cplex.solve()) {
        cout << "Deu problema no resolvedor\n";
    }

    for(int i = 0; i < V; i++) {
        xFinal[i][i] = 0;
        for(int j = i+1; j < V; j++) {
            xFinal[i][j] = cplex.getValue(x[i][j]);
            xFinal[j][i] = cplex.getValue(x[i][j]);
        }
    }

    double val = cplex.getObjValue();

    // Finalização
    cplex.clear();
    env.end();

    return val;
}

double CuttingPlanes(vvd &G, int V, string m) {
    vvi R = {};

    if (m == "SimpleMinCut") {
        cout << "Modo: Simple Min Cut\n";
        while(1) {
            vvb x(V, vector<bool>(V));
            
            double custo = Soluciona(G, V, R, x);
            
            // Mas antes tenho que confirmar qual o tipo de retorno que cada uma da quando a solução é viável
            // Pro SimpleMinCut, vai ser retornado um conjunto com apenas 1 elemento, que é o vértice sem ter sido unido a nenhum outro
           
           vector<int> So = {0};
           pair<int,int> vf;
           
           vector<int> S = SimpleMinCut(G, x);
           
           if(S.size() == 1) return custo; // viável
           
           else R.push_back(S);            // adiciona restrição
        }
    }
    
    else {
        cout << "Modo: Multiple Max-Back\n";
        while (1) {
            vvb x(V, vector<bool>(V));
    
            double custo = Soluciona(G, V, R, x);
    
            // Pro MaxBackM, vai ser retornado um único subconjunto, formado pelo conjunto completo
    
            vvi S = MaxBackM(G, x);
    
            if (S.size() == 1) {    // viável
                return custo;
            }
            else {
                // Adiciona restrição em R
                for(auto sub : S) {
                    R.push_back(sub);
                }
            }
        }
    }
}