ROOT_DIR = ..\..

BIN_DIR = $(ROOT_DIR)\Bin
OBJ_DIR = $(ROOT_DIR)\Obj
LIB_DIR = $(ROOT_DIR)\Lib
INCLUDE_DIR = $(ROOT_DIR)\Include
SRC_DIR = $(ROOT_DIR)\Src

PLATFORM_TARGET = x64
PLATFORM_NAME = MacOS

CONFIGURATION = Debug
CONFIGURATION_MACRO = DEBUG

PROJECT_NAME = Kaleid.Math

TARGET_EXT = dylib
TARGET_NAME = Kaleid.Math.$(TARGET_EXT)

OUT_DIR = $(BIN_DIR)\$(PLATFORM_NAME)\$(CONFIGURATION)\$(PLATFORM_TARGET)
INT_DIR = $(OBJ_DIR)\$(PLATFORM_NAME)\$(CONFIGURATION)\$(PLATFORM_TARGET)

TARGET = $(OUT_DIR)\$(TARGET_NAME)

INCLUDE_DIRS = -I$(ROOT_DIR)\Include -I$(SRC_DIR)\ -I$(SRC_DIR)\Math\
#INCLUDE_HEADERS = $(wildcard $(INCLUDE_DIR)\*.hpp)
#SOURCE_HEADERS = $(wildcard $(SRD_DIR)\*.hpp) $(wildcard $(SRD_DIR)\Math\*.hpp)
#HEADERS = $(INCLUDE_HEADERS) $(SOURCE_HEADERS)

SOURCE_FILES = $(wildcard $(SRD_DIR)\*.cpp) $(wildcard $(SRD_DIR)\Math\*.cpp)

PREPROCCESOR_MACROS = -D KALEID_MATH_DLL

OBJ = $(SOURCE_FILES:%.cpp=$(INT_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

CXX = g++
CXXFLAGS = -dynamiclib -v $(INCLUDE_DIRS) $(PREPROCCESOR_MACROS)

# Build Rules
build : $(PROJECT_NAME)

$(PROJECT_NAME) : $(OUT_DIR)

$(OUT_DIR) : $(OBJ) 
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

-include $(DEP)

$(INT_DIR)/%.o : %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@
	
.PHONY : clean
clean :
	-rm $(OUT_DIR) $(OBJ) $(DEP)
	-rm $(INT_DIR) $(OBJ) $(DEP)