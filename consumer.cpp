#include "consumer.h"

void Consumer::consume() {
  product_queue_->pop();
}