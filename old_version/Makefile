# ==========================================
# Makefile para MSVC e CPLEX (Windows x64)
# ==========================================

CPLEX_DIR = E:\Program Files\IBM\ILOG\CPLEX_Studio222

# Diretórios de inclusão e bibliotecas
INCLUDES = /I"$(CPLEX_DIR)\cplex\include" /I"$(CPLEX_DIR)\concert\include"
LIBPATHS = /LIBPATH:"$(CPLEX_DIR)\cplex\lib\x64_windows_msvc14\stat_mda" /LIBPATH:"$(CPLEX_DIR)\concert\lib\x64_windows_msvc14\stat_mda"
LIBS = cplex2220.lib concert.lib ilocplex.lib ws2_32.lib

# Flags de compilação (/EHsc = exceções, /O2 = otimização, /MD = runtime dinâmico)
CXXFLAGS = /EHsc /O2 /MD /DIL_STD $(INCLUDES)

# Arquivos fonte do projeto
SRCS = leitor-instancias\src\Data.cpp *.cpp algoritmos-separacao\*.cpp

TARGET = programa.exe

all: $(TARGET)

$(TARGET):
	cl $(CXXFLAGS) $(SRCS) /Fe:$(TARGET) /link $(LIBPATHS) $(LIBS)

clean:
	if exist *.obj del *.obj
	if exist leitor-instancias\src\*.obj del leitor-instancias\src\*.obj
	if exist algoritmos-separacao\*.obj del algoritmos-separacao\*.obj
	if exist *.ilk del *.ilk
	if exist *.pdb del *.pdb