#ifndef ALGORITHM_DATA_STRUCTURE_LINKED_LIST_CIRCULARLY_LINKED_LIST_H_
#define ALGORITHM_DATA_STRUCTURE_LINKED_LIST_CIRCULARLY_LINKED_LIST_H_

#include <iostream>

namespace data_structure {
namespace linked_list {

template <class T>
class CircularlyLinkedList {
 public:
  class Node {
   public:
    T data_;
    Node *next_;
    friend class CircularlyLinkedList;
    explicit Node(const T &data) : data_(data), next_(NULL) {}
  };

 public:
  CircularlyLinkedList();
  ~CircularlyLinkedList();
  int Size() const;
  bool IsEmpty() const;
  void Rotate();
  bool Search(const T &data) const;
  void Insert(const T &data);
  T Remove(const T &data);

  friend std::ostream &operator<<(std::ostream &out,
                                  const CircularlyLinkedList &list) {
    if (list.IsEmpty()) {
      out << "Empty list";
    } else {
      typename CircularlyLinkedList::Node *temp = list.tail_->next_;
      out << "List: ";
      do {
        out << "[" << temp->data_ << "]->";
        temp = temp->next_;
      } while (temp != list.tail_->next_);
    }
    return out;
  }

 private:
  Node *tail_;
  int size_;
};

template <class T>
CircularlyLinkedList<T>::CircularlyLinkedList() : tail_(NULL), size_(0) {}

template <class T>
CircularlyLinkedList<T>::~CircularlyLinkedList() {
  while (!IsEmpty()) Remove(tail_->data_);
  delete tail_;
}

template <class T>
int CircularlyLinkedList<T>::Size() const {
  return size_;
}

template <class T>
bool CircularlyLinkedList<T>::IsEmpty() const {
  return (tail_ == NULL);
}

template <class T>
void CircularlyLinkedList<T>::Rotate() {
  tail_ = tail_->next_;
}

template <class T>
bool CircularlyLinkedList<T>::Search(const T &data) const {
  if (IsEmpty()) return false;
  Node *temp = tail_->next_;
  do {
    if (temp->data_ == data) return true;
    temp = temp->next_;
  } while (temp != tail_->next_);
  return false;
}

template <class T>
void CircularlyLinkedList<T>::Insert(const T &data) {
  Node *node = new Node(data);
  if (IsEmpty()) {
    tail_ = node;
    tail_->next_ = tail_;
  } else {
    node->next_ = tail_->next_;
    tail_->next_ = node;
  }
  size_++;
  Rotate();
}

template <class T>
T CircularlyLinkedList<T>::Remove(const T &data) {
  if (IsEmpty()) throw std::runtime_error("List is empty, can not remove");
  Node *old = tail_->next_, *prev;
  do {
    prev = old;
    old = old->next_;
  } while (old != tail_->next_ && old->data_ != data);
  if (old == NULL) throw std::runtime_error("Node is not exist in this list");
  T removed = old->data_;
  if (tail_->next_ == tail_) {
    tail_->next_ = NULL;
    tail_ = NULL;
  } else {
    prev->next_ = old->next_;
    if (old == tail_) tail_ = prev;
  }
  delete old;
  size_--;
  return removed;
}

}  // namespace linked_list
}  // namespace data_structure

#endif  // ALGORITHM_DATA_STRUCTURE_LINKED_LIST_CIRCULARLY_LINKED_LIST_H_
