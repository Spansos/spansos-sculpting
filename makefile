CC     := g++
CFLAGS := -g -Wall -Werror -Wpedantic -Wextra -O0

# cpp and header files from own project
CPP_FILES := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
HEADERS   := $(wildcard src/*.hpp) $(wildcard src/*/*.hpp)

# packages from package manager
PACKAGES := glfw3 glew glm gl libpng
PKG_LIBS := $(shell pkg-config --libs $(PACKAGES))
CFLAGS   += $(shell pkg-config --cflags $(PACKAGES))

# imgui submodule
CPP_FILES += $(wildcard imgui/*.cpp) imgui/misc/cpp/imgui_stdlib.cpp imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_glfw.cpp
HEADERS   += $(wildcard imgui/*.h) imgui/misc/cpp/imgui_stdlib.h imgui/backends/imgui_impl_opengl3.h imgui/backends/imgui_impl_opengl3_loader.h imgui/backends/imgui_impl_glfw.h
CFLAGS    += -Iimgui -Iimgui/backends

# obj files. decided by cpp files, so last
OBJ_FILES := $(patsubst %.cpp,obj/%.o,$(CPP_FILES))

.PHONY: clean run

all: bin/main.out

run: bin/main.out
	./bin/main.out

clean:
	rm obj/* -rf
	rm bin/* -rf

obj/%.o: %.cpp $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

bin/main.out: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(PKG_LIBS) $^ -o $@