#include <stdio.h>

class Dog {
public:
  int eat() {return printf("Dog::eat\n");}
  virtual void bark() {printf("Dog:::Bark\n");}
  virtual ~Dog() = default;
};

class Husky : public Dog {
public:
  Husky(const double weight): weight_(weight) {}

  double const getWeight() {return weight_;}
  int eat() {return printf("husky eat\n");}
  virtual void bark() override {printf("husky bark\n");}
  virtual void mascot() {printf("husky mascot");}
private:
  double weight_;
};

int main() {
  Husky husky(40.0);
  Dog *pDog = &husky;
  Dog &dog = *pDog;
  // dog.bark();
  // husky.mascot();
  pDog->mascot();
}