#include <iostream>
#include <string>

struct Node {
  char val_;
  Node *next;
  Node() {
    val_ = ' ';
    next = nullptr;
  }
};
class List {
private:
  Node *root_;

public:
  List() { root_ = new Node(); }
  List(std::string val) {
    root_ = new Node();
    for (int i = 0; i < val.size(); i++) {
      AddElement(val[i]);
    }
  }
  ~List() {
    while (root_ != nullptr) {
      Node *next = root_->next;
      delete root_;
      root_ = next;
    }
  }
  void AddElement(char a) {
    Node *new_node = new Node();
    new_node->val_ = a;
    new_node->next = nullptr;
    if (root_->val_ == ' ') {
      delete root_;
      root_ = new_node;
      return;
    } else {
      Node *last = FindLastNode(root_);
      last->next = new_node;
      return;
    }
  }

  Node *FindLastNode(Node *head) {
    Node *last = head;
    if (last->next == nullptr) {
      return last;
    }
    Node *next = FindLastNode(last->next);
    return next;
  }
  void printElements(Node *next) {
    Node *temp = next;
    if (temp->next == nullptr) {
      std::cout << temp->val_;
      return;
    }
    std::cout << temp->val_;
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
  void SetRoot(Node *root) { root_ = root; }
};

int main() {
  std::string a;
  std::getline(std::cin, a);
  List *linked_list = new List(a);
  linked_list->SetRoot(linked_list->reverseList(linked_list->GetRoot()));
  List *reversed = new List();
  reversed->SetRoot(linked_list->GetRoot());
  reversed->printElements(reversed->GetRoot());
  return 0;
}
