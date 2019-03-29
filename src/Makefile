#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Assume-se uma distribuição Linux como sistema operacional padrão
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#O compilador
COMPILER = g++
# Comando para remover pasras
RMDIR = rm -rdf
#Comando para remover arquivos
RM = rm -f

#"Flags" para a geração automática de dependências
DEP_FLAGS = -M -MT $@  -MT $(BIN_PATH)/$(*F).o -MP -MF $@
#Bibliotecas a serem linkadas
LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
#Caminho dos includes
INC_PATHS = -I$(INC_PATH) $(addprefix -I,$(SDL_INC_PATHS))

#Diretivas de compilação
FLAGS = -std=c++11 -Wall -pedantic -Wextra -Wno-unused-parameter -Werror=init-self
#Diretivas extras para debug
DFLAGS = -ggdb -O0 -DDEBUG
#Diretivas extras para release
RFLAGS = -O3 -mtune=native

INC_PATH = include
SRC_PATH = src
BIN_PATH = bin
DEP_PATH = dep

# Uma lista de arquivos por extensão:
CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
INC_FILES = $(wildcard $(INC_PATH)/*.h)
FILE_NAMES = $(sort $(notdir $(CPP_FILES:.cpp=)) $(notdir $(INC_FILES:.h=)))
DEP_FILES	=	$(addprefix	$(DEP_PATH)/,$(addsufix	.d,$(FILE_NAMES)))
OBJ_FILES	=	$(addprefix	$(BIN_PATH)/,$(notdir	$(CPP_FILES:.cpp=.o)))

# Nome do executável
EXEC = src
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Caso o sistema seja vírus, quer dizer, windows
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Caso o sistema seja caro, quer dizer, Mac
#-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

################################################################################################################################################################################
#Regra geral
all:	$(EXEC)

#Gera o executável
$(EXEC):	$(OBJ_FILES)
	$(COMPILER) -o $@ $^ $(LINK_PATH) $(LIBS) $(FLAGS)

#Gera os arquivos objertos
$(BIN_PATH)/%.o: $(DEP_PATH)/%.d | folders
	$(COMPILER) $(INC_PATHS) $(addprefix $(SRC_PATH)/,$(notdir $(<:;d=cpp))) -c $(FLAFS) -o $@

#Gera os arquivos de dependência
$(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< $(DEP_FLAGS) $(FLAGS)

.SECONDEXPANSION:
-include $$(DEP_FILES)

clean:
	-$(RMDIR) $(DEP_PATH)
	-$(RMDIR) $(BIN_PATH)
	-$(RM) $(EXEC)
