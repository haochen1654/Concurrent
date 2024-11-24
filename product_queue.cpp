#include "product_queue.h"

#include <iostream>

void ProductQueue::push_back(const int number) {
  {
    std::unique_lock<std::mutex> lk(mutex_);
    cond_var_.wait(lk, [&] { return queue_->size() < limit_; });
  }
  {
    std::lock_guard<std::mutex> lk(mutex_);
    queue_->push(number);
    std::cout << "Push " << number << " to the queue.\n";
  }
  cond_var_.notify_all();
}

void ProductQueue::pop() {
  {
    std::unique_lock<std::mutex> lk(mutex_);
    cond_var_.wait(lk, [&] { return queue_->size() > 0; });
  }
  {
    std::lock_guard<std::mutex> lk(mutex_);
    int number = queue_->front();
    queue_->pop();
    std::cout << "Pop " << number << " out of the queue.\n";
  }
  cond_var_.notify_all();
}