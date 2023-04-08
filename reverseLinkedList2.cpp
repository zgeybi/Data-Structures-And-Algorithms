#include <iostream>
#include <iterator>
#include <string>

struct Node {
  char val;
  Node *next;
  Node(char val_) {
    val = val_;
    next = nullptr;
  }
};
class List {
 private:
  Node *root_;
  Node *tail_;

 public:
  List(std::string val_) {
    root_ = new Node(' ');
    tail_ = root_;
    AddElement(val_.begin(), val_.end());
  }
  ~List() {
    while (root_ != tail_) {
      Node *next = root_->next;
      delete root_;
      root_ = next;
    }
    delete tail_;
    root_ = nullptr;
    tail_ = nullptr;
  }
  void AddElement(std::basic_string<char>::iterator begin,
                  std::basic_string<char>::iterator end) {
    if (begin == end) {
      return;
    }
    Node *new_node = new Node(*begin);
    if (root_->val == ' ') {
      root_->val = new_node->val;
      tail_ = root_;
      delete new_node;
      new_node = nullptr;
    } else {
      Node *last = tail_;
      last->next = new_node;
      tail_ = new_node;
      new_node = nullptr;
      delete new_node;
    }
    AddElement(++begin, end);
  }

  void printElements(Node *next) {
    Node *temp = next;
    if (temp->next == nullptr) {
      std::cout << temp->val;
      return;
    }
    std::cout << temp->val;
    printElements(temp->next);
  }
  Node *reverseList(Node *head) {
    if (head == nullptr || head->next == nullptr) {
      return head;
    }
    Node *previous = nullptr;
    Node *temp = reverseList(head->next);
    head->next->next = head;
    head->next = previous;
    return temp;
  }
  Node *GetRoot() { return root_; }
  void SetRoot(Node *root) {
    tail_ = root_;
    root_ = root;
  }
};

int main() {
  std::string a;
  std::getline(std::cin, a);
  List linked_list(a);
  linked_list.SetRoot(linked_list.reverseList(linked_list.GetRoot()));
  linked_list.printElements(linked_list.GetRoot());
  return 0;
}

