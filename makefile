CC       := g++
CFLAGS   := -g -Wall -Werror -pedantic
PACKAGES := glfw3 glew glm gl libpng

CPP_FILES := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,$(CPP_FILES))
HEADERS   := $(wildcard src/*.hpp) $(wildcard src/*/*.hpp)

LIBS   := $(shell pkg-config --libs $(PACKAGES))
CFLAGS += $(shell pkg-config --cflags $(PACKAGES))

.PHONY: clean run

all: bin/main.out

run: bin/main.out
	./bin/main.out

clean:
	rm obj/* -rf
	rm bin/* -rf

obj/%.o: src/%.cpp $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

bin/main.out: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@