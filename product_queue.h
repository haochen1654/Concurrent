
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

class ProductQueue {
 public:
  ProductQueue() : limit_{10} { queue_ = std::make_unique<std::queue<int>>(); };

  explicit ProductQueue(int s) : limit_{s} {
    queue_ = std::make_unique<std::queue<int>>();
  };

  ~ProductQueue(){};
  ProductQueue(const ProductQueue& product_queue) = delete;
  ProductQueue& operator=(const ProductQueue& product_queue) = delete;
  ProductQueue(ProductQueue&& product_queue) = delete;
  ProductQueue& operator=(ProductQueue&& product_queue) = delete;
  void push_back(int number);

 private:
  std::unique_ptr<std::queue<int>> queue_;
  std::condition_variable cond_var_;
  std::mutex mutex_;
  const int limit_;
};