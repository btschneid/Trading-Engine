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

class Engine {
  public:
    Engine();
    ~Engine();

    void processBuy(Trader& trader, double price);
    void processSell(Trader& trader, double price);

  private:
    void processRequests();

    std::thread processingThread;
    std::queue<std::pair<Trader&, std::pair<std::string, double>>> requestQueue;
    std::mutex requestMutex;
    std::condition_variable condition;
    bool stopProcessing;
};


#endif // ENGINE_H
