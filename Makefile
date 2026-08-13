CXX = clang++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)