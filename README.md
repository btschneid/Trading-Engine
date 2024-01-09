# Trading Engine Readme

## Summary:

This project is a Trading Engine that utilizes real historical stock data, allowing users to analyze and test various trading strategies. Key features include:

- Selection of a specific stock and time frame for analysis.
- Implementation and testing of Moving Average and Mean Reversion trading strategies.
- Efficient handling of buy and sell requests through the use of object pooling techniques.
- Capability to process thousands of requests per second, ensuring scalability and performance.

## Usage:

Follow these steps to use the Trading Engine:

1. Check the `requirements.txt` file to ensure that all necessary C++ extensions are installed.
2. Compile the program by entering `make` in the command line.
3. Run the executable with `./engine`.

## Author:

Brian Schneider

## Features:

### 1. Stock and Time Frame Selection:

Choose a specific stock and time frame to analyze, providing flexibility in conducting thorough trading strategy evaluations.

### 2. Trading Strategies:

The engine supports two prominent trading strategies:

- **Moving Average:** Analyzes trends by calculating the average stock price over a specified time period.
  
- **Mean Reversion:** Explores opportunities by identifying situations where the stock price deviates from its historical average, anticipating a return to the mean.

### 3. Object Pooling Technique:

Efficiently manages buy and sell requests from numerous traders through the implementation of object pooling. This technique optimizes resource usage and enhances overall system performance.

### 4. High Performance:

Capable of handling a significant volume of requests per second, making it suitable for scenarios with a large number of simultaneous transactions.

## Compile and Run:

Ensure that the necessary C++ extensions are installed by checking the `requirements.txt` file. Compile the program with the `make` command and run the executable using `./engine`.

Feel free to explore and contribute to the codebase. If you encounter any issues or have suggestions, please reach out to the author, Brian Schneider.

Happy trading!
