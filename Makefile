CXX = clang++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra \
           -I src \
           -I src/core \
           -I src/geometry \
           -I src/shading \
           -I src/scene \
           -I src/io

SRCS = $(wildcard src/*.cpp src/*/*.cpp)
BUILD_DIR = build
OBJS = $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean