# Trading Engine

A high-performance trading engine that utilizes real historical stock data to analyze and test various trading strategies.

## Project Structure

```
Trading-Engine/
├── src/                      # Source code
│   ├── core/                # Core engine implementation
│   │   ├── engine.cpp
│   │   └── engine.h
│   ├── market/              # Stock market implementation
│   │   ├── stock_market.cpp
│   │   ├── stock_market.h
│   │   ├── stock_data.cpp
│   │   └── stock_data.h
│   ├── trader/              # Trading strategies
│   │   ├── trader.cpp
│   │   ├── trader.h
│   │   ├── portfolio.cpp
│   │   ├── portfolio.h
│   │   └── strategies/      # Trading strategies
│   │       ├── moving_avg.cpp
│   │       ├── moving_avg.h
│   │       ├── mean_reversion.cpp
│   │       └── mean_reversion.h
│   └── main.cpp             # Main entry point
│
├── python/                  # Python scripts
│   └── get_stock_data.py    # Stock data fetcher
│
├── data/                    # Data files
│   └── stock_data.db        # SQLite database
│
├── build/                   # Build directory (generated)
│   └── bin/                 # Executables
│
├── scripts/                 # Build and setup scripts
│   ├── build.sh            # Build script
│   └── setup.sh            # Setup script
│
├── config/                  # Configuration files
│   ├── python_requirements.txt
│   └── cpp_requirements.txt
│
├── CMakeLists.txt          # CMake configuration
├── README.md               # This file
└── .gitignore             # Git ignore file
```

## Features

- Selection of specific stocks and time frames for analysis
- Implementation of multiple trading strategies:
  - Moving Average
  - Mean Reversion
- Efficient request handling through object pooling
- High-performance processing (thousands of requests per second)
- Real historical stock data integration
- SQLite database for data persistence

## Dependencies

### C++ Dependencies
- C++17 compatible compiler (g++ >= 11.0.0)
- CMake (>= 3.14.0)
- Make
- SQLite3 development libraries
- Python3 development headers

### Python Dependencies
- yfinance (>= 0.2.36)
- pandas (>= 2.0.0)
- numpy (>= 1.24.0)

## Quick Start

1. Clone the repository:
```bash
git clone https://github.com/yourusername/Trading-Engine.git
cd Trading-Engine
```

2. Run the setup script:
```bash
chmod +x scripts/setup.sh
./scripts/setup.sh
```

3. Activate the Python virtual environment:
```bash
source venv/bin/activate
```

4. Build the project:
```bash
./scripts/build.sh
```

5. Run the program:
```bash
./build/bin/TradingEngine
```

## Usage

When running the program, you can:
1. Use default settings (AAPL stock from 5 years ago to today)
2. Enter custom settings:
   - Stock symbol (case sensitive)
   - Start date (YYYY-MM-DD)
   - End date (YYYY-MM-DD)

## Author

Brian Schneider
