#include "producer.h"

void Producer::produce(const int number) {
  product_queue_->push_back(number);
}