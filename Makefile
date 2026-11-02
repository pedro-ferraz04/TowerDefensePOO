

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

TARGET_GRAFICO = jogo
TARGET_TEXTO   = jogo_texto


HEADERS = armas.h inimigos.h mapa.h jogador.h rodadas.h grafico.h


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


ifneq ($(RAYLIB_DIR),)
    INCLUDES += -I$(RAYLIB_DIR)/include
    LDFLAGS  += -L$(RAYLIB_DIR)/lib
endif


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