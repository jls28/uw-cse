//cpp linked list 
#include <string>
#include <iostream>
#include <cstddef>
using namespace std;
class StringNode { // single node in a linked list of strings
 public:
   string value_; // value in this node
   StringNode * next_; // next node in the list or nullptr if none
   // convenience constructor - initialize new node with string s
   // and next pointer p
   StringNode(string s, StringNode *p): value_(s), next_(p) { }
};

class StringLinkedList {
 public:
   // construct empty StringLinkedList
    StringLinkedList() : first_(nullptr), last_(nullptr) { }
    void operator+=(string other) {
        StringNode * temp = new StringNode(other, nullptr);
        if (first_ == nullptr && last_ == nullptr) {
          first_ = temp;
          last_ = temp;
        } else {
          last_->next_ = temp;
          last_ = last_->next_;
        }
    }
    void print() {
      StringNode * cur = first_;
      if (cur == nullptr) { return; }
      while (cur != last_) {
        std::cout << cur->value_ << std::endl;
        cur = cur->next_;
      }
      std:cout << cur->value_ << std::endl;
    }
    ~StringLinkedList() {
      StringNode * cur = first_;
      while (cur != last_) {
        StringNode * todie = cur;
        cur = cur->next_;
        delete todie;
      }
      delete cur;
    }
 // additional operations omitted...
 private:
   StringNode * first_; // first node in list
   StringNode * last_; // last node in list
   // first_ = last_ = nullptr if the
  // list is empty.
};

int main() {

  StringLinkedList s;
  s += "stefan";
  s += "dierauf";
  s += "has";
  s += "nice boobies";
  s.print();
  // delete s;
}
