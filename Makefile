CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

# Lista de fuentes y ejecutables (nombre de ejecutable = nombre del archivo sin .cpp)
SOURCES := huffman.cpp huffcodeco.cpp huffmancompress.cpp huffmandecompress.cpp priority_queue.cpp
EXES := $(patsubst %.cpp,%,$(SOURCES))
BINDIR := bin
TARGETS := $(patsubst %, $(BINDIR)/%,$(EXES))

.PHONY: all clean

all: $(TARGETS)

$(BINDIR)/%: %.cpp
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -rf $(BINDIR)
