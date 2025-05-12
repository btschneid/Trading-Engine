cmake_minimum_required(VERSION 3.14)
project(TradingEngine VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find required packages
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
if(NOT Python3_FOUND)
    message(FATAL_ERROR "Python3 not found. Please install Python3 development package:
    Ubuntu/Debian: sudo apt-get install python3-dev
    Fedora: sudo dnf install python3-devel
    macOS: brew install python3")
endif()

find_package(SQLite3 REQUIRED)

# Find SQLite3 with fallback options
if(NOT SQLite3_FOUND)
    # Try to find SQLite3 using pkg-config
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(SQLite3 QUIET sqlite3)
    endif()
    
    # If still not found, try to find it manually
    if(NOT SQLite3_FOUND)
        find_path(SQLite3_INCLUDE_DIR sqlite3.h
            PATHS
            /usr/include
            /usr/local/include
            /opt/local/include
        )
        find_library(SQLite3_LIBRARY
            NAMES sqlite3
            PATHS
            /usr/lib
            /usr/local/lib
            /opt/local/lib
        )
        if(SQLite3_INCLUDE_DIR AND SQLite3_LIBRARY)
            set(SQLite3_FOUND TRUE)
        endif()
    endif()
endif()

if(NOT SQLite3_FOUND)
    message(FATAL_ERROR "SQLite3 not found. Please install SQLite3 development package:
    Ubuntu/Debian: sudo apt-get install libsqlite3-dev
    Fedora: sudo dnf install sqlite-devel
    macOS: brew install sqlite3")
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${Python3_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIRS}
)

# Source files
set(SOURCES
    src/main.cpp
    src/core/engine.cpp
    src/market/stock_market.cpp
    src/market/stock_data.cpp
    src/trader/trader.cpp
    src/trader/portfolio.cpp
    src/trader/strategies/moving_avg.cpp
    src/trader/strategies/mean_reversion.cpp
)

# Header files
set(HEADERS
    src/core/engine.h
    src/market/stock_market.h
    src/market/stock_data.h
    src/trader/trader.h
    src/trader/portfolio.h
    src/trader/strategies/moving_avg.h
    src/trader/strategies/mean_reversion.h
)

# Create executable
add_executable(TradingEngine ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(TradingEngine
    PRIVATE
    ${Python3_LIBRARIES}
    SQLite::SQLite3
)

# Add compiler warnings and optimizations
if(MSVC)
    target_compile_options(TradingEngine PRIVATE /W4 /O2)
else()
    target_compile_options(TradingEngine PRIVATE 
        -Wall 
        -Wextra 
        -Wpedantic 
        -O2 
        -DNDEBUG
    )
endif()

# Install rules
install(TARGETS TradingEngine
    RUNTIME DESTINATION bin
)

# Enable testing
enable_testing()

# Add custom target for cleaning build files
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning build directory"
) 