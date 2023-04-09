#include <iostream>
#include <string>

struct Node {
  char val_;
  Node *next;
  Node() {
    val_ = ' ';
    next = nullptr;
  }
  ~Node() {}
};
class List {
private:
  Node *root_;

public:
  List() { root_ = new Node(); }
  ~List() {
    while (root_ != nullptr) {
      Node *next = root_->next;
      delete root_;
      root_ = next;
    }
  }
  void AddElements(std::string val) {
    for (int i = 0; i < val.size(); i++) {
      Node *temp = new Node();
      temp->val_ = val[i];
      temp->next = nullptr;
      if (root_->val_ == ' ') {
        delete root_;
        root_ = temp;
        continue;
      }
      Node *new_node = FindLastNode(root_);
      new_node->next = temp;
    }
  }
  Node *FindLastNode(Node *head) {
    Node *last = head;
    if (last->next == nullptr) {
      return last;
    }
    last = FindLastNode(last->next);
    return last;
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
  void SetRoot(Node *root) {
    delete root_;
    root_ = root;
  }
};

int main() {
  std::string a;
  std::getline(std::cin, a);
  List *linked_list = new List();
  linked_list->AddElements(a);
  List *reversed = new List();
  Node *head = reversed->GetRoot();
  head = linked_list->reverseList(linked_list->GetRoot());
  reversed->SetRoot(head);
  reversed->printElements(head);
  delete reversed;
  return 0;
}
