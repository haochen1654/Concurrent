#include <iostream>
#include <thread>
#include "product_queue.h"

void producer(const int number, ProductQueue* product_queue) {
  product_queue->push_back(number);
}

void consumer(ProductQueue* product_queue) {
  product_queue->pop();
}

int main() {
  ProductQueue product_queue;

  std::vector<std::thread> threads;

  for (int i = 0; i < 20; i++) {
    std::thread th(producer, i, &product_queue);
    threads.push_back(std::move(th));
  }
  for (int i = 0; i < 20; i++) {
    std::thread th(consumer, &product_queue);
    threads.push_back(std::move(th));
  }
  for (auto& th : threads) {
    th.join();
  }
  return 0;
}
