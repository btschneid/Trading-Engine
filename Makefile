CXX = g++
CXXFLAGS = -std=c++11 $(shell python3-config --cflags)
LIBS = -lpthread -ldl -lsqlite3 -lpython3.10

# Include directories for Python headers
PYTHON_INCLUDE = $(shell python3 -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())")

SRCS = main.cpp Stock-Market/stock_market.cpp Trader/trader.cpp Trader/portfolio.cpp Trader/TradingStrats/moving_avg.cpp Trader/TradingStrats/mean_reversion.cpp Trading-Engine/engine.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = engine

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(PYTHON_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
