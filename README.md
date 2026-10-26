# Planos de Corte

Para compilar com o CPLEX no Windows, eu utilizei o **x64 Native Tools Command Prompt**.
Nele, dentro da pasta do projeto, utilizando o Makefile:
```
nmake
```

Para rodar uma instância:
```
.\programa.exe instances/nomedainsstancia.tsp Modo
```

No modo, pode ser utilizado o "SimpleMinCut" ou "MaxBackMultiplo", o default é o Max-Back.