# Alternative GNU Make project makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

# Configurations
# #############################################

ifeq ($(origin CC), default)
  CC = clang
endif
ifeq ($(origin CXX), default)
  CXX = clang++
endif
ifeq ($(origin AR), default)
  AR = ar
endif
TARGETDIR = bin
TARGET = $(TARGETDIR)/GameEngine.app
INCLUDES += -Ivendor/spdlog/include -Ivendor/glfw/include -Ivendor/glad -Ivendor/imgui -Ivendor/glm -Ivendor/stb
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LIBS += -framework Cocoa -framework OpenGL -framework IOKit -lglfw3 -lglad
LDDEPS +=
ALL_LDFLAGS += $(LDFLAGS) -Lvendor/glfw/build -Lvendor/glad -m64
LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

ifeq ($(config),debug)
OBJDIR = obj/Debug
DEFINES += -DDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -g -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -g -std=c++17 -Wall

else ifeq ($(config),release)
OBJDIR = obj/Release
DEFINES += -DRELEASE
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -Werror -O2 -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -Werror -O2 -std=c++17 -Wall

else ifeq ($(config),dist)
OBJDIR = obj/Dist
DEFINES += -DDIST
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -Werror -O2 -Wall
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -Werror -O2 -std=c++17 -Wall

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

GENERATED += $(OBJDIR)/Engine.o
GENERATED += $(OBJDIR)/GLFWWindow.o
GENERATED += $(OBJDIR)/IndexBuffer.o
GENERATED += $(OBJDIR)/Renderer.o
GENERATED += $(OBJDIR)/Shader.o
GENERATED += $(OBJDIR)/TestColorChangingSquare.o
GENERATED += $(OBJDIR)/TestMenu.o
GENERATED += $(OBJDIR)/TestMultiImages.o
GENERATED += $(OBJDIR)/TestSecondaryWindow.o
GENERATED += $(OBJDIR)/TestSingleImage.o
GENERATED += $(OBJDIR)/Texture.o
GENERATED += $(OBJDIR)/VertexArray.o
GENERATED += $(OBJDIR)/VertexBuffer.o
GENERATED += $(OBJDIR)/VertexBufferLayout.o
GENERATED += $(OBJDIR)/Window.o
GENERATED += $(OBJDIR)/imgui.o
GENERATED += $(OBJDIR)/imgui_demo.o
GENERATED += $(OBJDIR)/imgui_draw.o
GENERATED += $(OBJDIR)/imgui_impl_glfw.o
GENERATED += $(OBJDIR)/imgui_impl_opengl3.o
GENERATED += $(OBJDIR)/imgui_widgets.o
GENERATED += $(OBJDIR)/main.o
GENERATED += $(OBJDIR)/stb_image.o
OBJECTS += $(OBJDIR)/Engine.o
OBJECTS += $(OBJDIR)/GLFWWindow.o
OBJECTS += $(OBJDIR)/IndexBuffer.o
OBJECTS += $(OBJDIR)/Renderer.o
OBJECTS += $(OBJDIR)/Shader.o
OBJECTS += $(OBJDIR)/TestColorChangingSquare.o
OBJECTS += $(OBJDIR)/TestMenu.o
OBJECTS += $(OBJDIR)/TestMultiImages.o
OBJECTS += $(OBJDIR)/TestSecondaryWindow.o
OBJECTS += $(OBJDIR)/TestSingleImage.o
OBJECTS += $(OBJDIR)/Texture.o
OBJECTS += $(OBJDIR)/VertexArray.o
OBJECTS += $(OBJDIR)/VertexBuffer.o
OBJECTS += $(OBJDIR)/VertexBufferLayout.o
OBJECTS += $(OBJDIR)/Window.o
OBJECTS += $(OBJDIR)/imgui.o
OBJECTS += $(OBJDIR)/imgui_demo.o
OBJECTS += $(OBJDIR)/imgui_draw.o
OBJECTS += $(OBJDIR)/imgui_impl_glfw.o
OBJECTS += $(OBJDIR)/imgui_impl_opengl3.o
OBJECTS += $(OBJDIR)/imgui_widgets.o
OBJECTS += $(OBJDIR)/main.o
OBJECTS += $(OBJDIR)/stb_image.o

# Rules
# #############################################

all: $(TARGET) $(dir $(TARGETDIR))PkgInfo $(dir $(TARGETDIR))Info.plist
	@:

$(dir $(TARGETDIR))PkgInfo:
$(dir $(TARGETDIR))Info.plist:

$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking GameEngine
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning GameEngine
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(GENERATED)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(GENERATED)) rmdir /s /q $(subst /,\\,$(GENERATED))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild: | $(OBJDIR)
	$(PREBUILDCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) | $(PCH_PLACEHOLDER)
$(GCH): $(PCH) | prebuild
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
$(PCH_PLACEHOLDER): $(GCH) | $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) touch "$@"
else
	$(SILENT) echo $null >> "$@"
endif
else
$(OBJECTS): | prebuild
endif


# File Rules
# #############################################

$(OBJDIR)/Engine.o: Engine/core/Engine.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/GLFWWindow.o: Engine/core/GLFWWindow.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Window.o: Engine/core/Window.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/main.o: Engine/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/IndexBuffer.o: Engine/rendering/IndexBuffer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Renderer.o: Engine/rendering/Renderer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Shader.o: Engine/rendering/Shader.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Texture.o: Engine/rendering/Texture.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/VertexArray.o: Engine/rendering/VertexArray.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/VertexBuffer.o: Engine/rendering/VertexBuffer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/VertexBufferLayout.o: Engine/rendering/VertexBufferLayout.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestColorChangingSquare.o: tests/TestColorChangingSquare.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestMenu.o: tests/TestMenu.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestMultiImages.o: tests/TestMultiImages.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestSecondaryWindow.o: tests/TestSecondaryWindow.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/TestSingleImage.o: tests/TestSingleImage.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui_impl_glfw.o: vendor/imgui/examples/imgui_impl_glfw.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui_impl_opengl3.o: vendor/imgui/examples/imgui_impl_opengl3.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui.o: vendor/imgui/imgui.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui_demo.o: vendor/imgui/imgui_demo.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui_draw.o: vendor/imgui/imgui_draw.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui_widgets.o: vendor/imgui/imgui_widgets.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/stb_image.o: vendor/stb/stb_image.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif