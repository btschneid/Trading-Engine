#include "engine.h"
#include "../Trader/trader.h"

Engine::Engine() : stopProcessing(false) {
  // Create thread to process data
  processingThread = std::thread(&Engine::processRequests, this);
}

Engine::~Engine() {
  stopProcessing = true;
  condition.notify_one();
  processingThread.join();
}

// Add buy request to queue
void Engine::processBuy(Trader& trader, double price) {
  std::string action = "buy";
  std::unique_lock<std::mutex> lock(requestMutex);
  requestQueue.push(std::make_pair(std::ref(trader), std::make_pair(action, price)));
  condition.notify_one();
}

// Add sell request to queue
void Engine::processSell(Trader& trader, double price) {
  std::string action = "sell";
  std::unique_lock<std::mutex> lock(requestMutex);
  //std::cout << action << " " << price << "\n";
  requestQueue.push(std::make_pair(std::ref(trader), std::make_pair(action, price)));
  condition.notify_one();
}

// Constantly processes requests
void Engine::processRequests() {
  while (true) {
    std::unique_lock<std::mutex> lock(requestMutex);
    condition.wait(lock, [this] { return !requestQueue.empty() || stopProcessing; });

    if (stopProcessing) {
      break;
    }

    while (!requestQueue.empty()) {
      auto request = requestQueue.front();
      requestQueue.pop();
      lock.unlock();

      Trader& trader = request.first;
      std::string& action = request.second.first;
      double price = request.second.second;

      // Process the request
      if (action == "buy") {
        trader.buy(price);
      } else if (action == "sell") {
        trader.sell(price);
      }

      lock.lock();
    }
  }
}