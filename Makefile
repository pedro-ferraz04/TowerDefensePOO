# ============================================================
#  Makefile - Tower defense
#
#  make            compila as duas versões (gráfica e texto)
#  make run        compila e roda a versão gráfica (raylib)
#  make run-texto  compila e roda a versão de texto
#  make clean      apaga os executáveis
#
#  Se a raylib não estiver em um caminho padrão, informe onde ela está:
#    make RAYLIB_DIR=/caminho/para/raylib
# ============================================================

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

TARGET_GRAFICO = jogo
TARGET_TEXTO   = jogo_texto

# Cabeçalhos que afetam a compilação (se algum mudar, recompila tudo)
HEADERS = armas.h inimigos.h mapa.h jogador.h rodadas.h grafico.h

# ---------- Detecção de sistema e bibliotecas da raylib ----------
ifeq ($(OS),Windows_NT)
    RAYLIB_LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
    EXE = .exe
else
    UNAME_S := $(shell uname -s)
    EXE =
    ifeq ($(UNAME_S),Darwin)
        RAYLIB_LIBS = -lraylib -framework CoreVideo -framework IOKit \
                      -framework Cocoa -framework GLUT -framework OpenGL
    else
        RAYLIB_LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    endif
endif

# Caminho opcional para a raylib instalada a partir do código-fonte
ifneq ($(RAYLIB_DIR),)
    INCLUDES += -I$(RAYLIB_DIR)/include
    LDFLAGS  += -L$(RAYLIB_DIR)/lib
endif

# ---------- Alvos ----------
.PHONY: all run run-texto clean

all: $(TARGET_GRAFICO)$(EXE) $(TARGET_TEXTO)$(EXE)

$(TARGET_GRAFICO)$(EXE): main_grafico.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) main_grafico.cpp -o $@ $(LDFLAGS) $(RAYLIB_LIBS)

$(TARGET_TEXTO)$(EXE): main_game.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) main_game.cpp -o $@

run: $(TARGET_GRAFICO)$(EXE)
	./$(TARGET_GRAFICO)$(EXE)

run-texto: $(TARGET_TEXTO)$(EXE)
	./$(TARGET_TEXTO)$(EXE)

clean:
	rm -f $(TARGET_GRAFICO) $(TARGET_GRAFICO).exe $(TARGET_TEXTO) $(TARGET_TEXTO).exe