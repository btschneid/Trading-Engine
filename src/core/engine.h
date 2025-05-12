/**
 * @file engine.h
 * @brief Core trading engine that processes buy and sell requests from traders
 * 
 * This file defines the Engine class which serves as the central processing unit
 * for the trading system. It manages a queue of trading requests and processes
 * them asynchronously using a dedicated thread.
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <utility>
#include <condition_variable>

class Trader;

/**
 * @class Engine
 * @brief Core trading engine that processes trading requests asynchronously
 * 
 * The Engine class manages a queue of trading requests and processes them
 * in a separate thread. It provides thread-safe methods for traders to submit
 * buy and sell requests.
 */
class Engine {
  public:
    /**
     * @brief Constructs a new Engine instance
     * 
     * Initializes the engine and starts the processing thread.
     */
    Engine();

    /**
     * @brief Destructor for the Engine
     * 
     * Ensures proper cleanup by stopping the processing thread and waiting
     * for it to finish.
     */
    ~Engine();

    /**
     * @brief Processes a buy request from a trader
     * 
     * @param trader Reference to the trader making the request
     * @param price The price at which to execute the buy
     */
    void processBuy(Trader& trader, double price);

    /**
     * @brief Processes a sell request from a trader
     * 
     * @param trader Reference to the trader making the request
     * @param price The price at which to execute the sell
     */
    void processSell(Trader& trader, double price);

  private:
    /**
     * @brief Main processing loop for handling trading requests
     * 
     * Continuously processes requests from the queue until stopProcessing
     * is set to true.
     */
    void processRequests();

    std::thread processingThread;  ///< Thread that processes trading requests
    std::queue<std::pair<Trader&, std::pair<std::string, double>>> requestQueue;  ///< Queue of pending trading requests
    std::mutex requestMutex;  ///< Mutex for thread-safe queue access
    std::condition_variable condition;  ///< Condition variable for thread synchronization
    bool stopProcessing;  ///< Flag to control the processing thread's lifecycle
};

#endif // ENGINE_H
