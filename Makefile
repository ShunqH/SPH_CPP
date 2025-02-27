# 变量定义
CXX = g++
CXXFLAGS = -Wall -std=c++11
INCLUDES = -I./include

SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin
TARGET = $(BIN_DIR)/sod.sph

# 获取所有源文件 (.cpp 文件)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# 自动生成对象文件 (.o 文件)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# 目标
all: $(TARGET)

# 编译规则
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 链接规则
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# 清理中间文件
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# 创建 obj 目录（如果不存在）
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# 创建 bin 目录（如果不存在）
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: all clean