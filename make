# // TODO compiled header .cph hardening options .
# Compiler and Flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -I.

# Directories
LIB_DIR := lib
SRC_DIR := strata
BUILD_DIR := build


# Source Files
GL_SRC := C:\Program Files (x86)\Windows Kits\10\Include\10.0.22000.0\um\gl
GL_LIBx64 := C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um\x64\OpenGL32.lib
GL_LIBx86 := C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um\x86\OpenGL32.lib
GL_LIBarm := C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um\arm\OpenGL32.lib
GL_LIBarm64 := C:\Program Files (x86)\Windows Kits\10\Lib\10.0.22000.0\um\arm64\OpenGL32.lib

SDL_SRC := $(LIB_DIR)/SDL/include/SDL3
SDL_LIB := $(LIB_DIR)/SDL/VisualC/x64/SDL3.lib
VK_SRC := $(LIB_DIR)/vk/
VK_LIB := $(VK_SRC)/vulkan.lib
VK_LIBx64 := 
VK_LIBx86 :=
VK_Ox64 := 
VK_Ox86 := 
# Libraries
SDL_LIB := $()/libmodule1.a
 := $(MODULE2_DIR)/libmodule2.a
// TODO
# Output Executable
TARGET := strata

# Object Files
OBJS := $(BUILD_DIR)/strata.exe \
		$(BUILD_DIR)/strata.

# Rules
all: $(TARGET)

# Create output executable
$(TARGET): $(OBJS) $(MODULE1_LIB) $(MODULE2_LIB)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) -L$(MODULE1_DIR) -lmodule1 -L$(MODULE2_DIR) -lmodule2

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/module1.o: $(MODULE1_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/module2.o: $(MODULE2_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean
