#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

#include <iostream>

namespace s21 {
template <class T>
class Queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Queue();
  Queue(std::initializer_list<value_type> const &items);
  Queue(const Queue &q);
  Queue(Queue &&q);
  ~Queue();

  Queue &operator=(const Queue &q);
  Queue &operator=(Queue &&q);

  const_reference front() const;
  const_reference back() const;
  bool empty() const;
  size_type size() const;
  void push(const_reference value);
  void pop();
  void swap(Queue &other) noexcept;

  // ============ Start Emplace ============ //

  template <class... Args>
  void emplace_back(Args &&...args) {
    for (const auto &val : {std::forward<Args>(args)...}) push(val);
  }

  // ============= End Emplace ============ //

 private:
  class Node {
   public:
    T value;
    Node *next;
    Node(T value = T(), Node *next = nullptr) {
      this->value = value;
      this->next = next;
    }
    ~Node() {}
  };

  void copy(const Queue &q);
  void clear();
  void moving(Queue &q);

  size_t m_size;
  Node *head;
  Node *tail;
};

template <typename T>
Queue<T>::Queue() : m_size(0U), head(nullptr), tail(nullptr) {}

template <typename T>
Queue<T>::Queue(std::initializer_list<value_type> const &items) : Queue() {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
}

template <typename T>
Queue<T>::~Queue() {
  if (!empty()) clear();
}

template <typename T>
Queue<T>::Queue(const Queue &q) : Queue() {
  copy(q);
}

template <typename T>
Queue<T>::Queue(Queue &&q) : Queue() {
  moving(q);
}

template <typename T>
Queue<T> &Queue<T>::operator=(const Queue &q) {
  clear();
  copy(q);
  return *this;
}

template <typename T>
Queue<T> &Queue<T>::operator=(Queue &&q) {
  clear();
  moving(q);
  return *this;
}

template <typename T>
typename Queue<T>::const_reference Queue<T>::front() const {
  if (head == nullptr) {
    throw std::out_of_range("Queue is empty");
  }
  return head->value;
}

template <typename T>
typename Queue<T>::const_reference Queue<T>::back() const {
  if (tail == nullptr) {
    throw std::out_of_range("Queue is empty");
  }
  return tail->value;
}

template <typename T>
bool Queue<T>::empty() const {
  return head ? 0 : 1;
}

template <typename T>
size_t Queue<T>::size() const {
  return m_size;
}

template <typename T>
void Queue<T>::push(const_reference value) {
  Node *tmp = new Node(value, nullptr);

  if (head) {
    tail->next = tmp;
  } else {
    head = tmp;
  }
  tail = tmp;
  m_size++;
}

template <typename T>
void Queue<T>::pop() {
  if (empty()) {
    throw std::invalid_argument("Bad Argument");
  }
  Node *tmp = head->next;
  delete head;
  head = tmp;
  m_size--;
}

template <typename T>
void Queue<T>::swap(Queue &other) noexcept {
  Queue<T> tmp(other);
  other = *this;
  *this = tmp;
}

template <typename T>
void Queue<T>::copy(const Queue &q) {
  Node *tmp = q.head;
  while (tmp) {
    push(tmp->value);
    tmp = tmp->next;
  }
}

template <typename T>
void Queue<T>::clear() {
  while (!empty()) pop();
}

template <typename T>
void Queue<T>::moving(Queue &q) {
  head = q.head;
  tail = q.tail;
  m_size = q.m_size;
  q.head = nullptr;
  q.tail = nullptr;
  q.m_size = 0U;
}

};      // namespace s21
#endif  // SRC_S21_QUEUE_H_
