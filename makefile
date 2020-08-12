
CC = g++
CFLAGS = --std=c++11

LIB_GLAD = -L libs/glad -l glad
HEADERS_GLAD = -I libs/glad/include
LIB_GLFW = -L libs/glfw-3.3.2/lib -l glfw3
HEADERS_GLFW = -I libs/glfw-3.3.2/include

FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit
# COMPILE = ${CC} $(CFLAGS) $(LIB_GLFW) $(HEADERS_GLFW) $(FRAMEWORKS)
COMPILE = ${CC} $(CFLAGS) $(LIB_GLAD) $(HEADERS_GLAD) $(LIB_GLFW) $(HEADERS_GLFW) $(FRAMEWORKS)

DEBUG = n
OUTDIR = bin/release

ifeq ($(DEBUG), y)
	CFLAGS += -g -D DEBUG
	OUTDIR = bin/debug
endif

main: main.cpp mk_dir
	$(COMPILE) main.cpp -o $(OUTDIR)/main

# Examples:
# example%: $(OBJS) mk_dir
# 	$(CC) $(CFLAGS) examples/$@.cpp -o $(OUTDIR)/$@

# Source files:
mk_dir:
	mkdir -p $(OUTDIR)

# tests: behavior_tree.hpp $(wildcard tests/*.*pp)
# 	$(CC) $(CFLAGS) tests/tests.cpp -o tests/tests

clean:
	rm -rf bin
