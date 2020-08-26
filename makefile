# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  GameEngine_config = debug

else ifeq ($(config),release)
  GameEngine_config = release

else ifeq ($(config),dist)
  GameEngine_config = dist

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := GameEngine

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

GameEngine:
ifneq (,$(GameEngine_config))
	@echo "==== Building GameEngine ($(GameEngine_config)) ===="
	@${MAKE} --no-print-directory -C . -f GameEngine.make config=$(GameEngine_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f GameEngine.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo "  dist"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   GameEngine"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"