CXX = g++
CXXFLAGS = -std=c++11 $(shell python3-config --cflags)
LIBS = -lpthread -ldl -lsqlite3 -lpython3.10

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = engine

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
