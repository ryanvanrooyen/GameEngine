
CC = g++
CFLAGS = --std=c++11 -Wall

VENDOR_HEADERS = -I vendor/glfw/include -I vendor/glad -I vendor/imgui -I vendor/glm -I vendor/stb
VENDOR_LIBS = -L vendor/glfw/build -l glfw3 -L vendor/glad -l glad

FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

COMPILE = ${CC} $(CFLAGS) $(VENDOR_HEADERS)
LINK = ${CC} $(CFLAGS) $(VENDOR_LIBS) $(FRAMEWORKS)

HEADER_FILES = $(shell find source -type f -name '*.h*')
CPP_FILES = $(shell find source -type f -name '*.cpp')
OBJ_FILES = $(patsubst %.cpp,$(OUTDIR)/%.o, $(CPP_FILES))

VENDOR_CPP_FILES = $(shell find vendor/stb -type f -name '*.cpp')
VENDOR_CPP_FILES += $(shell find vendor/imgui -type f -name '*.cpp')
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

# tests: behavior_tree.hpp $(wildcard tests/*.*pp)
# 	$(CC) $(CFLAGS) tests/tests.cpp -o tests/tests

clean:
	rm -rf bin
