#include "engine.h"
#include "../Trader/trader.h"

/**
 * @brief Constructs a new Engine instance and starts the processing thread
 * 
 * Initializes the stopProcessing flag to false and creates a new thread
 * that will handle the processing of trading requests.
 */
Engine::Engine() : stopProcessing(false) {
  // Create thread to process data
  processingThread = std::thread(&Engine::processRequests, this);
}

/**
 * @brief Destructor that ensures clean shutdown of the processing thread
 * 
 * Sets the stopProcessing flag, notifies the processing thread, and waits
 * for it to complete before destruction.
 */
Engine::~Engine() {
  stopProcessing = true;
  condition.notify_one();
  processingThread.join();
}

/**
 * @brief Queues a buy request for processing
 * 
 * Thread-safe method that adds a buy request to the processing queue
 * and notifies the processing thread.
 * 
 * @param trader Reference to the trader making the request
 * @param price The price at which to execute the buy
 */
void Engine::processBuy(Trader& trader, double price) {
  std::string action = "buy";
  std::unique_lock<std::mutex> lock(requestMutex);
  requestQueue.push(std::make_pair(std::ref(trader), std::make_pair(action, price)));
  condition.notify_one();
}

/**
 * @brief Queues a sell request for processing
 * 
 * Thread-safe method that adds a sell request to the processing queue
 * and notifies the processing thread.
 * 
 * @param trader Reference to the trader making the request
 * @param price The price at which to execute the sell
 */
void Engine::processSell(Trader& trader, double price) {
  std::string action = "sell";
  std::unique_lock<std::mutex> lock(requestMutex);
  //std::cout << action << " " << price << "\n";
  requestQueue.push(std::make_pair(std::ref(trader), std::make_pair(action, price)));
  condition.notify_one();
}

/**
 * @brief Main processing loop for handling trading requests
 * 
 * Continuously processes requests from the queue until stopProcessing is set to true.
 * Uses a condition variable to efficiently wait for new requests.
 * 
 * The processing loop:
 * 1. Waits for new requests or stop signal
 * 2. Processes all queued requests
 * 3. Executes the appropriate trader action (buy/sell)
 * 4. Maintains thread safety using mutex locks
 */
void Engine::processRequests() {
  while (true) {
    // Wait for new requests or stop signal
    std::unique_lock<std::mutex> lock(requestMutex);
    condition.wait(lock, [this] { return !requestQueue.empty() || stopProcessing; });

    if (stopProcessing) {
      break;
    }

    // Process all queued requests
    while (!requestQueue.empty()) {
      auto request = requestQueue.front();
      requestQueue.pop();
      lock.unlock();

      // Extract request details
      Trader& trader = request.first;
      std::string& action = request.second.first;
      double price = request.second.second;

      // Execute the appropriate trading action
      if (action == "buy") {
        trader.buy(price);
      } else if (action == "sell") {
        trader.sell(price);
      }

      lock.lock();
    }
  }
}