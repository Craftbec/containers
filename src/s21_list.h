#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <iostream>

namespace s21 {
template <class T>
class List {
  class Node;
  class ListIterator;
  class ListConstIterator;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  List();
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List<T> &l);
  List(List<T> &&l);
  ~List();

  List<T> &operator=(List<T> &&l) noexcept;

  const_reference front() const;
  const_reference back() const;
  iterator begin() noexcept;
  iterator end() noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  bool empty() const noexcept;
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void splice(const_iterator pos, List &other);
  void push_back(const_reference value);
  void push_front(const_reference value);
  void pop_back();
  void pop_front();
  void swap(List &other) noexcept;
  void merge(List &other);
  void reverse() noexcept;
  void unique();
  void sort();

  // ================ Start Emplace method's ===================== //
  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    iterator it(this, pos.ptr_);
    for (const auto &val : {std::forward<Args>(args)...}) it = insert(it, val);
    return it;
  }

  template <class... Args>
  void emplace_back(Args &&...args) {
    for (const auto &val : {std::forward<Args>(args)...}) push_back(val);
  }

  template <class... Args>
  void emplace_front(Args &&...args) {
    for (const auto &val : {std::forward<Args>(args)...}) push_front(val);
  }

  // ================ End Emplace method's ===================== //

 private:
  class Node {
   public:
    Node(T data = T(), Node *next = nullptr, Node *prev = nullptr) {
      this->data = data;
      this->next = next;
      this->prev = prev;
    }

    T data;
    Node *next;
    Node *prev;
  };

  void erase_tmp(size_type pos);
  void add_prev(Node *ptr);
  void moving(List<T> &l);
  void init();
  void throw_empty();
  void init_list_size();

  size_t m_size;
  Node *head;
  Node *tail;
  Node *list_size;
};

template <typename T>
class List<T>::ListConstIterator {
 public:
  friend class List<T>;

  ListConstIterator() : lst_(nullptr), ptr_(nullptr) {}
  ListConstIterator(List<T> *lst, Node *ptr) : lst_(lst), ptr_(ptr) {}

  const T &operator*() const { return this->ptr_->data; }
  const T &operator->() const { return this->ptr_->data; }
  const_iterator &operator++() {
    if (this->ptr_->next) {
      this->ptr_ = this->ptr_->next;
    } else {
      this->ptr_ = lst_->list_size;
    }
    return *this;
  }

  const_iterator operator++(int) {
    const_iterator out(*this);
    ++*this;
    return out;
  }

  const_iterator &operator--() {
    if (this->ptr_->prev) {
      this->ptr_ = this->ptr_->prev;
    } else {
      this->ptr_ = lst_->list_size;
    }
    return *this;
  }

  const_iterator operator--(int) {
    const_iterator out(*this);
    --*this;
    return out;
  }

  bool operator==(const_iterator other) {
    return this->ptr_ == other.ptr_ ? 1 : 0;
  }

  bool operator!=(const_iterator other) {
    return this->ptr_ != other.ptr_ ? 1 : 0;
  }

 protected:
  List<T> *lst_;
  Node *ptr_;
};

template <typename T>
class List<T>::ListIterator : public ListConstIterator {
 public:
  ListIterator() : ListConstIterator() {}
  ListIterator(List<T> *lst, Node *ptr) : ListConstIterator(lst, ptr) {}

  T &operator*() { return this->ptr_->data; }
  T &operator->() { return this->ptr_->data; }

  bool operator==(iterator other) { return this->ptr_ == other.ptr_ ? 1 : 0; }

  bool operator!=(iterator other) { return this->ptr_ != other.ptr_ ? 1 : 0; }
};

template <typename T>
List<T>::List() {
  init();
}
template <typename T>
List<T>::List(size_type n) : List() {
  while (n--) push_back(T());
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const &items) : List() {
  for (auto it = items.begin(); it != items.end(); it++) push_back(*it);
}

template <typename T>
List<T>::List(const List<T> &l) : List() {
  Node *tmp = l.head;
  while (tmp->next) {
    push_back(tmp->data);
    tmp = tmp->next;
  }
  push_back(tmp->data);
}

template <typename T>
List<T>::List(List<T> &&l) : List() {
  moving(l);
}

template <typename T>
List<T>::~List() {
  clear();
}

template <typename T>
List<T> &List<T>::operator=(List<T> &&l) noexcept {
  moving(l);
  return this;
}

template <typename T>
typename List<T>::const_reference List<T>::front() const {
  return head ? head->data : list_size->data;
}

template <typename T>
typename List<T>::const_reference List<T>::back() const {
  return tail ? tail->data : list_size->data;
}

template <typename T>
typename List<T>::iterator List<T>::begin() noexcept {
  List<T>::iterator out(this, head);
  return out;
}

template <typename T>
typename List<T>::iterator List<T>::end() noexcept {
  List<T>::iterator out(this, list_size);
  return out;
}

template <typename T>
bool List<T>::empty() const noexcept {
  return head ? 0 : 1;
}

template <typename T>
typename List<T>::size_type List<T>::size() const noexcept {
  return m_size;
}

template <typename T>
typename List<T>::size_type List<T>::max_size() const noexcept {
  return SIZE_MAX / sizeof(Node) / 2;
}

template <typename T>
void List<T>::clear() noexcept {
  while (head) {
    Node *tmp = head;
    head = head->next;
    delete tmp;
    m_size--;
  }
  delete list_size;
  tail = head = list_size = nullptr;
}

template <typename T>
void List<T>::push_back(const_reference value) {
  if (!head) {
    head = new Node(value);
    tail = head;
  } else {
    tail = new Node(value, nullptr, tail);
    tail->prev->next = tail;
  }
  m_size++;
  init_list_size();
}

template <typename T>
void List<T>::init_list_size() {
  list_size->next = head;
  list_size->prev = tail;
}

template <typename T>
void List<T>::pop_back() {
  if (m_size) {
    if (m_size == 1) {
      delete head;
      head = tail = nullptr;
    } else {
      Node *tmp = tail;
      tail = tail->prev;
      tail->next = nullptr;
      delete tmp;
      tmp = nullptr;
    }
    m_size--;
    init_list_size();
  }
}

template <typename T>
void List<T>::push_front(const_reference value) {
  if (!head) {
    head = new Node(value);
    tail = head;
  } else {
    head = new Node(value, head, nullptr);
    head->next->prev = head;
  }
  m_size++;
  init_list_size();
}

template <typename T>
void List<T>::pop_front() {
  if (m_size) {
    if (m_size == 1) {
      delete head;
      head = tail = nullptr;
    } else {
      Node *tmp = head;
      head = head->next;
      head->prev = nullptr;
      delete tmp;
      tmp = nullptr;
    }
    m_size--;
    init_list_size();
  }
}

template <typename T>
void List<T>::swap(List &other) noexcept {
  Node *tmp_head = head;
  Node *tmp_tail = tail;
  size_type tmp_size = m_size;
  head = other.head;
  tail = other.tail;
  m_size = other.m_size;
  other.head = tmp_head;
  other.tail = tmp_tail;
  other.m_size = tmp_size;
}

template <typename T>
void List<T>::merge(List &other) {
  if (!head && other.head) {
    moving(other);
  } else if (head && other.head) {
    if (head->data > other.head->data) {
      other.tail->next = head;
      head->prev = other.tail;
      head = other.head;
      list_size->next = other.head;
    } else {
      tail->next = other.head;
      other.head->prev = tail;
      tail = other.tail;
      list_size->prev = other.tail;
    }
    m_size += other.m_size;
    other.head = other.tail = nullptr;
    other.m_size = 0;
  }
}

template <typename T>
void List<T>::reverse() noexcept {
  if (head) {
    Node *tmp1 = head;
    Node *tmp2 = tmp1->next;
    tmp1->next = tmp1->prev;
    tmp1->prev = tmp2;
    while (tmp2) {
      tmp2->prev = tmp2->next;
      tmp2->next = tmp1;
      tmp1 = tmp2;
      tmp2 = tmp2->prev;
    }
    tail = head;
    head = tmp1;
  }
}

template <typename T>
void List<T>::unique() {
  if (head && head->next) {
    Node *tmp1 = head;
    for (size_t i = 0; i < m_size - 1; ++i) {
      Node *tmp2 = tmp1->next;
      if (tmp1->data == tmp2->data) {
        erase_tmp(i);
        unique();
        break;
      }
      tmp2 = tmp2->next;
      tmp1 = tmp1->next;
    }
    add_prev(tmp1);
  }
}

template <typename T>
void List<T>::erase_tmp(size_type pos) {
  Node *tmp = head;
  for (size_t i = 1; i < pos; ++i) tmp = tmp->next;
  Node *for_clear = tmp->next;
  tmp->next = tmp->next->next;
  delete for_clear;
  m_size--;
}

template <typename T>
void List<T>::sort() {
  Node *tmp1 = head;
  if (tmp1) {
    Node *tmp2 = tmp1->next;
    Node *tmp3 = tmp1;
    while (tmp2) {
      if (tmp1->data > tmp1->next->data) {
        tmp1->next = tmp2->next;
        tmp2->next = tmp1;
        if (tmp1 == head) {
          tmp2->prev = nullptr;
          head = tmp2;
        } else {
          tmp3->next = tmp2;
        }
        tmp1 = head;
      } else {
        tmp3 = tmp1;
        tmp1 = tmp1->next;
      }
      tmp2 = tmp1->next;
    }
    add_prev(tmp1);
  }
}

template <typename T>
void List<T>::add_prev(Node *ptr) {
  ptr = head;
  while (ptr->next) {
    ptr->next->prev = ptr;
    ptr = ptr->next;
  }
  tail = ptr;
}

template <typename T>
void List<T>::moving(List<T> &l) {
  head = l.head;
  tail = l.tail;
  delete list_size;
  list_size = l.list_size;
  m_size = l.m_size;
  l.m_size = 0U;
  l.head = l.tail = l.list_size = nullptr;
}

template <typename T>
void List<T>::init() {
  m_size = 0U;
  head = tail = nullptr;
  list_size = new Node();
}

template <typename T>
void List<T>::erase(iterator pos) {
  if (pos == end()) return;
  throw_empty();
  if (m_size == 1) {
    delete head;
    pos.ptr_ = head = tail = nullptr;
  } else {
    if (!pos.ptr_->prev) {
      head = pos.ptr_->next;
      head->prev = nullptr;
      list_size->next = head;
    } else if (!pos.ptr_->next) {
      tail = pos.ptr_->prev;
      tail->next = nullptr;
      list_size->prev = tail;
    } else {
      pos.ptr_->prev->next = pos.ptr_->next;
      pos.ptr_->next->prev = pos.ptr_->prev;
    }
    delete pos.ptr_;
    pos.ptr_ = nullptr;
  }
  --m_size;
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  if (head == pos.ptr_) {
    push_front(value);
    pos.ptr_ = head;
  } else if (list_size == pos.ptr_) {
    push_back(value);
    pos.ptr_ = tail;
  } else {
    Node *tmp;
    if (pos.ptr_->next) {
      tmp = new Node(value, pos.ptr_, pos.ptr_->prev);
      pos.ptr_->prev->next = tmp;
      pos.ptr_->prev = tmp;
    } else {
      tmp = new Node(value, tail, tail->prev);
      tail->prev->next = tmp;
      tail->prev = tmp;
    }
    pos.ptr_ = tmp;
    ++m_size;
  }
  return pos;
}

template <typename T>
void List<T>::splice(const_iterator pos, List &other) {
  if (pos.ptr_ == head) {
    other.tail->next = head;
    head->prev = other.tail;
    head = other.head;
  } else if (pos.ptr_ == list_size) {
    tail->next = other.head;
    other.head->prev = tail;
    tail = other.tail;
  } else {
    pos.ptr_->prev->next = other.head;
    other.head->prev = pos.ptr_->prev;
    pos.ptr_->prev = other.tail;
    other.tail->next = pos.ptr_;
  }
  m_size += other.m_size;
  other.m_size = 0;
  other.head = other.tail = nullptr;
  list_size->next = head;
  list_size->prev = tail;
  other.clear();
}

template <typename T>
void List<T>::throw_empty() {
  if (empty()) throw std::invalid_argument("List is empty");
}
};      // namespace s21
#endif  // SRC_S21_LIST_H_
