CXX = gcc
LIBS = -lSDL -lm
CXX_FLAGS = -O2

.PHONY: all

all: hex mixer

hex: hex.c
	$(CXX) $(CXX_FLAGS) $^ $(LIBS) -o $@

mixer: mixer.c
	$(CXX) $(CXX_FLAGS) $^ $(LIBS) -o $@
