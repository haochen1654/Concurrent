#ifndef _CONCURRENT_PRODUCER_
#define _CONCURRENT_PRODUCER_

#include "product_queue.h"

class Producer {
 public:
  explicit Producer(std::shared_ptr<ProductQueue> product_queue)
      : product_queue_(std::move(product_queue)){};

  ~Producer(){};
  Producer(const Producer& product_queue) = delete;
  Producer& operator=(const Producer& product_queue) = delete;
  Producer(Producer&& product_queue) = delete;
  Producer& operator=(Producer&& product_queue) = delete;

  void produce(int number);

 private:
  std::shared_ptr<ProductQueue> product_queue_;
};

#endif