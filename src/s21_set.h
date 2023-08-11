#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include <iostream>

#include "s21_vector.h"

namespace s21 {
template <typename T>
class Set {
  class Iterator;
  class ConstIterator;

 public:
  using value_type = T;
  using Key = value_type;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  Set();
  Set(std::initializer_list<value_type> const& items);
  Set(const Set& s);
  Set(Set&& s);
  ~Set();
  Set& operator=(Set&& s) noexcept;
  Set& operator=(const Set& s);

  iterator end();
  iterator begin();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(Set& other) noexcept;
  void merge(Set& other);
  iterator find(const Key& key);
  bool contains(const Key& key);

  // ============ Start Emplace ============ //

  template <class... Args>
  Vector<std::pair<iterator, bool>> emplace(Args&&... args) {
    Vector<std::pair<iterator, bool>> out;
    for (auto val : {std::forward<Args>(args)...}) {
      out.push_back(insert(val));
    }
    return out;
  }
  // ============= End Emplace ============ //

 protected:
  class Node {
   public:
    T data_;
    Node *left_, *right_, *parent_;
    int balance_;
    Node(T data_ = T(), Node* left_ = nullptr, Node* right_ = nullptr,
         Node* parent_ = nullptr, int balance_ = 0) {
      this->data_ = data_;
      this->left_ = left_;
      this->right_ = right_;
      this->parent_ = parent_;
      this->balance_ = balance_;
    }
    ~Node() {}
  };

  iterator find_node(Node* tmp, const Key& key);
  bool insert_node(Node*(&tmp), const value_type& value, Node* parent);
  iterator find_min_node(Node* tmp);
  iterator find_max_node(Node* tmp);
  void clear_help(Node*(&tmp));
  void set_balance(Node* tmp);
  void turn_left(Node*(&tmp), Node* parent);
  void turn_right(Node*(&tmp), Node* parent);
  void copy_set(Node* tmp);
  void moving(Set& s);
  void del(iterator pos);
  void del_left(iterator pos);
  void del_right(iterator pos);
  void turn(Node*(&tmp));

  int height();
  int height_help(Node* tmp);

  size_t m_size;
  Node* root;
};

template <typename T>
class Set<T>::Iterator {
  friend class Set;
  friend class Miltiset;

 protected:
  Node* iter_;

 public:
  Iterator() : iter_(nullptr) {}
  Iterator(Node* iter) : iter_(iter) {}
  reference operator*() { return this->iter_->data_; }
  Iterator& operator++() {
    if (iter_->right_) {
      iter_ = iter_->right_;
      while (iter_->left_) iter_ = iter_->left_;
    } else {
      Node* tmp = iter_->parent_;
      while (tmp != nullptr && iter_ == tmp->right_) {
        iter_ = tmp;
        tmp = tmp->parent_;
      }
      *this = tmp;
    }
    return *this;
  }

  Iterator& operator--() {
    if (iter_->left_) {
      iter_ = iter_->left_;
      while (iter_->right_) iter_ = iter_->right_;
    } else {
      Node* tmp = iter_->parent_;
      while (tmp != nullptr && iter_ == tmp->left_) {
        iter_ = tmp;
        tmp = tmp->parent_;
      }
      *this = tmp;
    }
    return *this;
  }
  friend bool operator==(const Iterator& a, const Iterator& b) {
    return a.iter_ == b.iter_;
  }
  friend bool operator!=(const Iterator& a, const Iterator& b) {
    return a.iter_ != b.iter_;
  }
};

template <typename T>
class Set<T>::ConstIterator : public Set<T>::Iterator {
  const_reference operator*() { return this->iter_->data_; }
};

template <typename T>
Set<T>::Set() : m_size(0U), root(nullptr) {}

template <typename T>
Set<T>::Set(std::initializer_list<value_type> const& items) : Set() {
  for (auto it = items.begin(); it != items.end(); it++) {
    insert(*it);
  }
}

template <typename T>
Set<T>::~Set() {
  clear();
}

template <typename T>
Set<T>::Set(const Set& s) : Set() {
  copy_set(s.root);
  m_size = s.m_size;
}

template <typename T>
Set<T>::Set(Set&& s) : Set() {
  moving(s);
}

template <typename T>
Set<T>& Set<T>::operator=(Set&& s) noexcept {
  clear();
  moving(s);
  return *this;
}

template <typename T>
void Set<T>::moving(Set& s) {
  swap(s);
  s.root = nullptr;
}

template <typename T>
Set<T>& Set<T>::operator=(const Set& s) {
  clear();
  copy_set(s.root);
  m_size = s.m_size;
  return *this;
}

template <typename T>
std::pair<typename Set<T>::iterator, bool> Set<T>::insert(
    const value_type& value) {
  bool res = 1;
  if (!root) {
    root = new Node(value, nullptr, nullptr, nullptr, 0);
    m_size++;
  } else {
    res = insert_node(root, value, root->parent_);
  }
  return std::pair<typename Set<T>::iterator, bool>(find(value), res);
}

template <typename T>
bool Set<T>::insert_node(Node*(&tmp), const value_type& value, Node* parent) {
  size_t res = m_size;
  if (tmp == nullptr) {
    tmp = new Node(value, nullptr, nullptr, parent, 0);
    m_size++;
  } else {
    if (value > tmp->data_) {
      insert_node(tmp->right_, value, tmp);
      if (height_help(tmp->right_) - height_help(tmp->left_) > 1) {
        if (height_help(tmp->right_->right_) < height_help(tmp->right_->left_))
          turn_right(tmp->right_, tmp);
        turn_left(tmp, tmp->parent_);
      }
    } else {
      if (value < tmp->data_) {
        insert_node(tmp->left_, value, tmp);
        if (height_help(tmp->left_) - height_help(tmp->right_) > 1) {
          if (height_help(tmp->left_->left_) < height_help(tmp->left_->right_))
            turn_left(tmp->left_, tmp->left_->parent_);
          turn_right(tmp, tmp->parent_);
        }
      }
      set_balance(tmp);
    }
  }
  return res < m_size ? 1 : 0;
}

template <typename T>
void Set<T>::turn_left(Node*(&tmp), Node* parent) {
  Node *right, *left;
  right = tmp->right_;
  left = right->left_;
  right->left_ = tmp;
  tmp->right_ = left;
  tmp = right;
  tmp->parent_ = parent;
  tmp->left_->parent_ = tmp;
  if (tmp->left_->right_) tmp->left_->right_->parent_ = tmp->left_;
  set_balance(tmp->left_);
  set_balance(tmp);
}

template <typename T>
void Set<T>::turn_right(Node*(&tmp), Node* parent) {
  Node *right, *left;
  left = tmp->left_;
  right = left->right_;
  left->right_ = tmp;
  tmp->left_ = right;
  tmp = left;
  tmp->parent_ = parent;
  tmp->right_->parent_ = tmp;
  if (tmp->right_->left_) tmp->right_->left_->parent_ = tmp->right_;
  set_balance(tmp->right_);
  set_balance(tmp);
}

template <typename T>
typename Set<T>::iterator Set<T>::find(const typename Set<T>::Key& key) {
  iterator res;
  if (root->data_ == key) {
    res.iter_ = root;
  } else {
    res = find_node(root, key);
  }
  return res;
}

template <typename T>
typename Set<T>::iterator Set<T>::find_node(Node* tmp, const Key& key) {
  iterator res;
  if (key == tmp->data_) {
    res.iter_ = tmp;
  } else if (key < tmp->data_) {
    if (tmp->left_ != nullptr) return find_node(tmp->left_, key);
  } else if (key > tmp->data_) {
    if (tmp->right_ != nullptr) return find_node(tmp->right_, key);
  }
  if (res.iter_ == nullptr) {
    res = end();
  }

  return res;
}

template <typename T>
typename Set<T>::iterator Set<T>::end() {
  iterator res;
  res = find_max_node(root);
  return res;
}

template <typename T>
typename Set<T>::iterator Set<T>::begin() {
  iterator res;
  res = find_min_node(root);
  return res;
}

template <typename T>
typename Set<T>::iterator Set<T>::find_min_node(Node* tmp) {
  iterator res;
  if (tmp->left_ != nullptr) {
    return find_min_node(tmp->left_);
  } else {
    res.iter_ = tmp;
  }
  return res;
}

template <typename T>
typename Set<T>::iterator Set<T>::find_max_node(Node* tmp) {
  iterator res;
  if (tmp->right_ != nullptr) {
    return find_max_node(tmp->right_);
  } else {
    res.iter_ = tmp->right_;
  }
  return res;
}

template <typename T>
bool Set<T>::empty() {
  return root ? 0 : 1;
}

template <typename T>
size_t Set<T>::size() {
  return m_size;
}

template <typename T>
size_t Set<T>::max_size() {
  return SIZE_MAX / sizeof(T) / 2;
}

template <typename T>
bool Set<T>::contains(const Key& key) {
  iterator res;
  bool result = 0;
  res = find_node(root, key);
  if (res != end()) result = 1;
  return result;
}

template <typename T>
void Set<T>::clear() {
  if (root) {
    clear_help(root);
    m_size = 0;
  }
}

template <typename T>
void Set<T>::clear_help(Node*(&tmp)) {
  if (tmp) {
    clear_help(tmp->left_);
    clear_help(tmp->right_);
    delete tmp;
    tmp = nullptr;
  }
}

template <typename T>
int Set<T>::height() {
  int res = height_help(root);
  return res;
}

template <typename T>
int Set<T>::height_help(Node* tmp) {
  if (tmp == nullptr) return 0;
  int h1 = height_help(tmp->left_);
  int h2 = height_help(tmp->right_);
  if (h1 >= h2) return h1 + 1;
  return h2 + 1;
}

template <typename T>
void Set<T>::set_balance(Node* tmp) {
  if (tmp) {
    tmp->balance_ = height_help(tmp->right_) - height_help(tmp->left_);
  }
}

template <typename T>
void Set<T>::copy_set(Node* tmp) {
  if (tmp) {
    insert(tmp->data_);
    copy_set(tmp->left_);
    copy_set(tmp->right_);
  }
}

template <typename T>
void Set<T>::swap(Set& other) noexcept {
  std::swap(root, other.root);
  std::swap(m_size, other.m_size);
}

template <typename T>
void Set<T>::merge(Set& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
  other.clear();
}

template <typename T>
void Set<T>::erase(iterator pos) {
  // нет дочерних узлов;
  if (pos.iter_->left_ == nullptr && pos.iter_->right_ == nullptr) {
    del(pos);
    // есть правый
  } else if (pos.iter_->left_ == nullptr && pos.iter_->right_ != nullptr) {
    del_right(pos);
  }
  // есть левый
  else if (pos.iter_->left_ != nullptr && pos.iter_->right_ == nullptr) {
    del_left(pos);
  }
  // есть два узла
  else {
    iterator tmp_iter = pos;
    --pos;
    tmp_iter.iter_->data_ = pos.iter_->data_;
    return erase(pos);
  }
  turn(root);
}

template <typename T>
void Set<T>::del(iterator pos) {
  if (pos.iter_->parent_) {
    if (pos.iter_->data_ > pos.iter_->parent_->data_) {
      pos.iter_->parent_->right_ = nullptr;
      delete pos.iter_;
    } else {
      pos.iter_->parent_->left_ = nullptr;
      delete pos.iter_;
    }
    m_size--;
  } else {
    clear();
  }
}

template <typename T>
void Set<T>::del_left(iterator pos) {
  if (pos.iter_->parent_) {
    if (pos.iter_->data_ < pos.iter_->parent_->data_) {
      pos.iter_->parent_->left_ = pos.iter_->left_;
    } else {
      pos.iter_->parent_->right_ = pos.iter_->left_;
    }
    pos.iter_->left_->parent_ = pos.iter_->parent_;
    pos.iter_->parent_ = nullptr;
    delete pos.iter_;
  } else {
    root = pos.iter_->left_;
    delete pos.iter_;
  }
  m_size--;
}

template <typename T>
void Set<T>::del_right(iterator pos) {
  if (pos.iter_->parent_) {
    if (pos.iter_->data_ < pos.iter_->parent_->data_) {
      pos.iter_->parent_->left_ = pos.iter_->right_;
    } else {
      pos.iter_->parent_->right_ = pos.iter_->right_;
    }
    pos.iter_->right_->parent_ = pos.iter_->parent_;
    pos.iter_->parent_ = nullptr;
    delete pos.iter_;
  } else {
    root = pos.iter_->right_;
    delete pos.iter_;
  }
  m_size--;
}

template <typename T>
void Set<T>::turn(Node*(&tmp)) {
  if (height_help(tmp->right_) - height_help(tmp->left_) > 1) {
    if (height_help(tmp->right_->right_) < height_help(tmp->right_->left_))
      turn_right(tmp->right_, tmp);
    turn_left(tmp, tmp->parent_);
    set_balance(tmp);
  } else if (height_help(tmp->left_) - height_help(tmp->right_) > 1) {
    if (height_help(tmp->left_->left_) < height_help(tmp->left_->right_))
      turn_left(tmp->left_, tmp->left_->parent_);
    turn_right(tmp, tmp->parent_);
    set_balance(tmp);
  }
  if (tmp->left_) turn(tmp->left_);
  if (tmp->right_) turn(tmp->right_);
}

};      // namespace s21
#endif  // SRC_S21_SET_H_