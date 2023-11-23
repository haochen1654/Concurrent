#ifndef _CONCURRENT_CONSUMER_
#define _CONCURRENT_CONSUMER_

#include "product_queue.h"

class Consumer {
 public:
  explicit Consumer(std::shared_ptr<ProductQueue> product_queue)
      : product_queue_(std::move(product_queue)){};

  ~Consumer(){};
  Consumer(const Consumer& product_queue) = delete;
  Consumer& operator=(const Consumer& product_queue) = delete;
  Consumer(Consumer&& product_queue) = delete;
  Consumer& operator=(Consumer&& product_queue) = delete;

  void consume();

 private:
  std::shared_ptr<ProductQueue> product_queue_;
};

#endif