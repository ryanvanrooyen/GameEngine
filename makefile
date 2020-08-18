
CC = g++
CFLAGS = --std=c++11 -Wall

LIB_GLAD = -L libs/glad -l glad
HEADERS_GLAD = -I libs/glad/include
LIB_GLFW = -L libs/glfw-3.3.2/lib -l glfw3
HEADERS_GLFW = -I libs/glfw-3.3.2/include
VENDOR_HEADERS = -I vendor/glm -I vendor/stb

FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

COMPILE = ${CC} $(CFLAGS) $(HEADERS_GLAD) $(HEADERS_GLFW) $(VENDOR_HEADERS)
LINK = ${CC} $(CFLAGS) $(LIB_GLAD) $(LIB_GLFW) $(FRAMEWORKS)

HEADER_FILES = $(shell find source -type f -name '*.h*')
CPP_FILES = $(shell find source -type f -name '*.cpp')
OBJ_FILES = $(patsubst %.cpp,$(OUTDIR)/%.o, $(CPP_FILES))

VENDOR_CPP_FILES = $(shell find vendor/stb -type f -name '*.cpp')
# VENDOR_CPP_FILES += $(shell find vendor/ -type f -name '*.cpp')
VENDOR_OBJ_FILES = $(patsubst %.cpp,$(OUTDIR)/%.o, $(VENDOR_CPP_FILES))

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

$(EXECUTABLE): $(OBJ_FILES) $(VENDOR_OBJ_FILES)
	# Linking $@
	@$(LINK) -o $(EXECUTABLE) $(OBJ_FILES) $(VENDOR_OBJ_FILES)
	# Build Succeeded

# Compile individual source files:
$(OUTDIR)/source/%.o: source/%.cpp $(HEADER_FILES)
	# Compiling $< -> $@
	@mkdir -p $(@D)
	@$(COMPILE) -c $< -o $@

# Compile individual vendor files:
$(OUTDIR)/vendor/%.o: vendor/%.cpp
	# Compiling $< -> $@
	@mkdir -p $(@D)
	@$(COMPILE) -c $< -o $@

mk_dir:
	mkdir -p $(OUTDIR)

# tests: behavior_tree.hpp $(wildcard tests/*.*pp)
# 	$(CC) $(CFLAGS) tests/tests.cpp -o tests/tests

clean:
	rm -rf bin
