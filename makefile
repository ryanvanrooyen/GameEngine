
CC = g++
CFLAGS = --std=c++11 -Wall

LIB_GLAD = -L libs/glad -l glad
HEADERS_GLAD = -I libs/glad/include
LIB_GLFW = -L libs/glfw-3.3.2/lib -l glfw3
HEADERS_GLFW = -I libs/glfw-3.3.2/include
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

COMPILE = ${CC} $(CFLAGS) $(HEADERS_GLAD) $(HEADERS_GLFW)
LINK = ${CC} $(CFLAGS) $(LIB_GLAD) $(LIB_GLFW) $(FRAMEWORKS)

HEADER_FILES = $(wildcard source/**.h source/**.hpp source/**/*.h source/**/*.hpp)
CPP_FILES = main.cpp $(wildcard source/**.cpp source/**/*.cpp)
OBJECT_FILES = $(patsubst %.cpp,$(OUTDIR)/%.o, $(CPP_FILES))

debug ?= 0
loglevel ?= 0
OUTDIR = bin/release

ifneq ($(debug), 0)
	CFLAGS += -g -D DEBUG
	OUTDIR = bin/debug
endif

ifneq ($(loglevel), 0)
	CFLAGS += -D LOGLEVEL=$(loglevel)
endif

EXECUTABLE = $(OUTDIR)/main

main: $(EXECUTABLE) ;

$(EXECUTABLE): $(OBJECT_FILES)
	# Linking $@
	@$(LINK) -o $(EXECUTABLE) $(OBJECT_FILES)
	# Build Succeeded

# Compile individual files:
$(OUTDIR)/%.o: %.cpp $(HEADER_FILES)
	# Compiling $< -> $@
	@mkdir -p $(@D)
	@$(COMPILE) -c $< -o $@

mk_dir:
	mkdir -p $(OUTDIR)

# tests: behavior_tree.hpp $(wildcard tests/*.*pp)
# 	$(CC) $(CFLAGS) tests/tests.cpp -o tests/tests

clean:
	rm -rf bin
