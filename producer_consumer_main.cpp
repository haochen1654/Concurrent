#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

std::mutex m;
std::condition_variable cv;
bool isEmpty = true;

int main() {
  int c = 0;
  bool done = false;

  queue<int> goods;

  thread producer([&]() {
    for (int i = 0; i < 100; ++i) {
      {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] { return isEmpty; });
        goods.push(i);
        c++;
        std::cout << "Push " << i << " to the queue.\n";
        isEmpty = false;
      }
      cv.notify_all();
    }

    done = true;
  });

  thread consumer([&]() {
    while (!done) {
      {
        std::lock_guard<std::mutex> lk(m);
        while (!goods.empty()) {
          int i = goods.front();
          goods.pop();
          c--;
          std::cout << "Pop " << i << " out of the queue.\n";
        }
        isEmpty = true;
      }
      cv.notify_all();
    }
  });

  producer.join();
  consumer.join();
  cout << "Net: " << c << endl;
}