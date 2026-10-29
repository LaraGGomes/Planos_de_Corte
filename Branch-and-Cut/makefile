# ==========================================
# Makefile para Windows (MSVC + nmake) 
# ==========================================

# Versao e diretorios com as libs do CPLEX no Windows
CPLEXVERSION = 222
CPLEXDIR   = E:\Program Files\IBM\ILOG\CPLEX_Studio$(CPLEXVERSION)\cplex
CONCERTDIR = E:\Program Files\IBM\ILOG\CPLEX_Studio$(CPLEXVERSION)\concert

CPLEXLIBDIR   = $(CPLEXDIR)\lib\x64_windows_msvc14\stat_mda
CONCERTLIBDIR = $(CONCERTDIR)\lib\x64_windows_msvc14\stat_mda

# Define o compilador do MSVC
CPPC = cl
#############################

# Opcoes de compilacao e includes
# /EHsc = excecoes C++ | /O2 = otimizacao | /MD = runtime dinamico | /DIL_STD = macro do CPLEX
CCOPT = /EHsc /O2 /MD /DNDEBUG /DIL_STD
CONCERTINCDIR = $(CONCERTDIR)\include
CPLEXINCDIR   = $(CPLEXDIR)\include
CCFLAGS = $(CCOPT) /I"$(CPLEXINCDIR)" /I"$(CONCERTINCDIR)" /I".\include"
#############################

# Flags e bibliotecas do Linker no Windows
CCLNFLAGS = /link /LIBPATH:"$(CPLEXLIBDIR)" /LIBPATH:"$(CONCERTLIBDIR)" cplex2220.lib concert.lib ilocplex.lib ws2_32.lib
#############################

# Diretorios com os source files e com os objs files
SRCDIR = src
OBJDIR = obj
#############################

# Nome do executavel final
TARGET = bnc.exe
#############################

all: setup $(TARGET)

setup:
	@if not exist $(OBJDIR) mkdir $(OBJDIR)

$(TARGET):
	@echo Verificando arquivos em $(SRCDIR)...
	@if not exist $(SRCDIR) ( \
		echo ERRO: A pasta '$(SRCDIR)' nao foi encontrada! & \
		exit /b 1 \
	)
	@if exist sources.txt del sources.txt
	@if exist objects.rsp del objects.rsp
	-@dir /b $(SRCDIR)\*.cpp > sources.txt
	@echo Compilando arquivos fonte...
	@for /f "tokens=*" %%i in (sources.txt) do $(CPPC) $(CCFLAGS) /c $(SRCDIR)\%%i /Fo$(OBJDIR)/
	@echo Gerando arquivo de resposta de objetos...
	@for /f "tokens=*" %%i in (sources.txt) do @echo $(OBJDIR)\%%~ni.obj >> objects.rsp
	@if exist sources.txt del sources.txt
	@echo Realizando o link para gerar $(TARGET)...
	$(CPPC) /Fe:$(TARGET) @objects.rsp $(CCLNFLAGS)
	@if exist objects.rsp del objects.rsp
############################

# Deleta objetos e arquivos gerados
clean:
	@echo Limpando o diretorio $(OBJDIR) e arquivos gerados...
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	@if exist $(TARGET) del /f /q $(TARGET)
	@if exist *.ilk del /f /q *.ilk
	@if exist *.pdb del /f /q *.pdb
	@if exist sources.txt del sources.txt
	@if exist objects.rsp del objects.rsp

rebuild: clean all