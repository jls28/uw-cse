#include <iostream>

typedef int T;

class vector {
 public:
  explicit vector(size_t n = 0, T initial_value = 42)
      : size_(n), data_(new T[n]) {
    std::cerr << "constructor" << std::endl;
    for (size_t i = 0; i < n; ++i) data_[i] = initial_value;
  }

  ~vector() {
    std::cerr << "destructor" << std::endl;
    delete[] data_;
  }

  vector(const vector &other) : size_(other.size_), data_(new T[size_]) {
    std::cerr << "copy constructor" << std::endl;
    for (size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
  }

  vector &operator=(const vector &other) {
    std::cerr << "copy assignment operator" << std::endl;
    if (this != &other) {
      // alllocate new data
      T *new_data = new T[other.size_];
      // copy from other
      for (size_t i = 0; i < other.size_; ++i) new_data[i] = other.data_[i];
      // delete old data
      delete[] data_;
      // assign new data
      size_ = other.size_;
      data_ = new_data;
    }
    return *this;
  }

  size_t size() const { return size_; }
  T *data() { return data_; }

  T operator[](size_t i) const { return data_[i]; }

  T *begin() { return data_; }
  T *end() { return data_ + size_; }

 private:
  size_t size_;
  T *data_;
};

int main(void) {
  size_t n = 10;
  vector v(n);
  vector new_v;
  new_v = v;
  std::cout << new_v.size() << std::endl;
  for (T x : new_v) std::cout << x << std::endl;
}
