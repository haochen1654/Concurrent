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
  int i = 0;

  thread producer([&]() {
    while (i < 99) {
      {
        {
          std::unique_lock<std::mutex> lk(m);
          cv.wait(lk, [] { return isEmpty; });
          while (goods.size() < 10) {
            goods.push(i);
            c++;
            std::cout << "Push " << i << " to the queue.\n";
            ++i;
          }
          while (goods.size() < 10) {
            goods.push(i);
            c++;
            std::cout << "Push " << i << " to the queue.\n";
            ++i;
          }
        }
        {
          std::lock_guard<std::mutex> lk(m);
          isEmpty = false;
          std::cout << "Queue is Full.\n";
        }
        cv.notify_all();
      }
    }
    done = true;
  });

  thread consumer([&]() {
    while (!done) {
      {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] { return !isEmpty; });
        while (!goods.empty()) {
          int i = goods.front();
          goods.pop();
          c--;
          std::cout << "Pop " << i << " out of the queue.\n";
        }
      }
      {
        std::lock_guard<std::mutex> lk(m);
        isEmpty = true;
        std::cout << "Queue is Empty.\n";
      }
      cv.notify_all();
    }
  });

  producer.join();
  consumer.join();
  cout << "Net: " << c << endl;
}