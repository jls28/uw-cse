template <typename T>
class Pair {
 public:
  Pair(const T& first, const T& second) first_(first), second_(second) {}
  T first() const { return first_; }
  T second() const { return second_; }
 private:
  T first_;
  T second_;
};