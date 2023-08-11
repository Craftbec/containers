#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <iostream>

namespace s21 {
template <class T>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack();
  Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s);
  ~Stack();
  Stack &operator=(const Stack &s);
  Stack &operator=(Stack &&s);

  const_reference top() const;
  size_type size() const;
  bool empty() const;
  void push(const_reference value);
  void pop();
  void swap(Stack &other) noexcept;

  // ============ Start Emplace ============ //

  template <class... Args>
  void emplace_front(Args &&...args) {
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

  void copy(const Stack &s);
  void tmp_copy(const Stack &s);
  void clear();
  void moving(Stack &s);

  size_t m_size;
  Node *head;
};

template <typename T>
Stack<T>::Stack() : m_size(0U), head(nullptr) {}

template <typename T>
Stack<T>::Stack(std::initializer_list<value_type> const &items) : Stack() {
  for (auto it = items.begin(); it != items.end(); it++) {
    push(*it);
  }
}

template <typename T>
Stack<T>::Stack(const Stack &s) : Stack() {
  copy(s);
}

template <typename T>
Stack<T>::Stack(Stack &&s) : Stack() {
  moving(s);
}

template <typename T>
Stack<T>::~Stack() {
  if (!empty()) clear();
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack &s) {
  clear();
  copy(s);
  return *this;
}

template <typename T>
Stack<T> &Stack<T>::operator=(Stack &&s) {
  clear();
  moving(s);
  return *this;
}

template <typename T>
typename Stack<T>::const_reference Stack<T>::top() const {
  if (head == nullptr) {
    throw std::out_of_range("Stack is empty");
  }
  return head->value;
}

template <typename T>
size_t Stack<T>::size() const {
  return m_size;
}

template <typename T>
void Stack<T>::push(const_reference value) {
  Node *tmp = new Node(value, head);
  head = tmp;
  m_size++;
}

template <typename T>
void Stack<T>::pop() {
  if (empty()) {
    throw std::invalid_argument("Bad Argument");
  }
  m_size--;
  Node *tmp = head;
  head = head->next;
  delete tmp;
}

template <typename T>
void Stack<T>::copy(const Stack &s) {
  Stack<T> tmp_stack;
  tmp_stack.tmp_copy(s);
  tmp_copy(tmp_stack);
}

template <typename T>
void Stack<T>::tmp_copy(const Stack &s) {
  Node *tmp = s.head;
  while (tmp) {
    push(tmp->value);
    tmp = tmp->next;
  }
}

template <typename T>
void Stack<T>::clear() {
  while (!empty()) pop();
}

template <typename T>
bool Stack<T>::empty() const {
  return head ? 0 : 1;
}

template <typename T>
void Stack<T>::swap(Stack &other) noexcept {
  Stack<T> tmp(other);
  other = *this;
  *this = tmp;
}

template <typename T>
void Stack<T>::moving(Stack &s) {
  head = s.head;
  m_size = s.m_size;
  s.head = nullptr;
  s.m_size = 0U;
}
};      // namespace s21
#endif  // SRC_S21_STACK_H_
