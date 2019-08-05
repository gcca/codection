#include <algorithm>
#include <iostream>
#include <queue>

template <class Object> class ObjectPool {
public:
  ObjectPool() { ClearMetrics(); }

  Object &Allocate() {
    Object *object;

    if (objectPool_.empty()) {
      object = new Object;
      metrics_.totalAllocated++;
    } else {
      object = objectPool_.back();
      objectPool_.pop();
      metrics_.totalRealeased--;
    }

    return *object;
  }

  void Release(Object &object) {
    objectPool_.push(&object);
    metrics_.totalRealeased++;
  }

  void Collect() {
    std::queue<Object *> empty;
    std::swap(objectPool_, empty);

    std::for_each(empty.cbegin(), empty.cend(),
                  [](const Object *const object) { delete object; });

    const std::size_t objectsInUse =
        metrics_.totalAllocated - metrics_.totalRealeased;
    ClearMetrics(objectsInUse);
  }

  void ClearMetrics(const std::size_t allocated = 0) {
    metrics_.totalAllocated = allocated;
    metrics_.totalRealeased = 0;
  }

private:
  std::queue<Object *> objectPool_;

  class {
  public:
    std::size_t totalRealeased;
    std::size_t totalAllocated;
  } metrics_;
};

class Person {
public:
  std::string name;
  std::size_t age;
};

int main() {
  ObjectPool<Person> personPool;

  Person &firstPerson = personPool.Allocate();
  Person &secondPerson = personPool.Allocate();

  return 0;
}
