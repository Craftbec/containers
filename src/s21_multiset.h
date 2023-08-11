#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_

#include <iostream>

#include "s21_set.h"

namespace s21 {
template <typename T>
class Multiset : public Set<T> {
 public:
  using value_type = typename Set<T>::value_type;
  using Key = typename Set<T>::Key;
  using reference = typename Set<T>::reference;
  using const_reference = typename Set<T>::const_reference;
  using size_type = typename Set<T>::size_type;
  using iterator = typename Set<T>::iterator;
  using const_iterator = typename Set<T>::const_iterator;

  Multiset();
  Multiset(std::initializer_list<value_type> const& items);
  Multiset(const Multiset& ms);
  Multiset(Multiset&& ms);
  ~Multiset();

  Multiset& operator=(Multiset&& ms) noexcept;
  Multiset& operator=(const Multiset& ms);

  iterator insert(const value_type& value);
  void erase(iterator pos);
  void merge(Multiset& other);
  size_type count(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);

  // ============ Start Emplace ============ //

  template <class... Args>
  Vector<std::pair<iterator, bool>> emplace(Args&&... args) {
    Vector<std::pair<iterator, bool>> out;
    for (auto val : {std::forward<Args>(args)...}) {
      size_t tmp_size = this->m_size;
      auto tmp = this->insert(val);
      out.push_back(
          std::pair<iterator, bool>(tmp, tmp_size < this->m_size ? 1 : 0));
    }
    return out;
  }
  // ============= End Emplace ============ //

 private:
  void copy_multiset(typename Set<T>::Node* tmp);
  void insert_node(typename Set<T>::Node*(&tmp), const value_type& value,
                   typename Set<T>::Node* parent);
};

template <typename T>
Multiset<T>::Multiset() : Set<T>() {}

template <typename T>
Multiset<T>::Multiset(std::initializer_list<value_type> const& items)
    : Multiset() {
  for (auto it = items.begin(); it != items.end(); it++) {
    this->insert(*it);
  }
}

template <typename T>
Multiset<T>::Multiset(const Multiset& ms) : Multiset() {
  copy_multiset(ms.root);
  this->m_size = ms.m_size;
}

template <typename T>
Multiset<T>::Multiset(Multiset&& ms) : Multiset() {
  this->moving(ms);
}

template <typename T>
Multiset<T>::~Multiset() {
  this->clear();
}

template <typename T>
void Multiset<T>::copy_multiset(typename Set<T>::Node* tmp) {
  if (tmp) {
    this->insert(tmp->data_);
    this->copy_multiset(tmp->left_);
    this->copy_multiset(tmp->right_);
  }
}

template <typename T>
Multiset<T>& Multiset<T>::operator=(Multiset&& ms) noexcept {
  this->clear();
  this->moving(ms);
  return *this;
}

template <typename T>
Multiset<T>& Multiset<T>::operator=(const Multiset& ms) {
  this->clear();
  copy_multiset(ms.root);
  this->m_size = ms.m_size;
  return *this;
}

template <typename T>
typename Multiset<T>::iterator Multiset<T>::insert(const value_type& value) {
  if (!this->root) {
    this->root = new typename Set<T>::Node(value, nullptr, nullptr, nullptr, 0);
    this->m_size++;
  } else {
    insert_node(this->root, value, this->root->parent_);
  }
  return this->find(value);
}

template <typename T>
void Multiset<T>::insert_node(typename Set<T>::Node*(&tmp),
                              const value_type& value,
                              typename Set<T>::Node* parent) {
  if (tmp == nullptr) {
    tmp = new typename Set<T>::Node(value, nullptr, nullptr, parent, 0);
    this->m_size++;
  } else {
    if (value >= tmp->data_) {
      insert_node(tmp->right_, value, tmp);
      if (this->height_help(tmp->right_) - this->height_help(tmp->left_) > 1) {
        if (this->height_help(tmp->right_->right_) <
            this->height_help(tmp->right_->left_))
          this->turn_right(tmp->right_, tmp);
        this->turn_left(tmp, tmp->parent_);
      }
    } else {
      if (value <= tmp->data_) {
        insert_node(tmp->left_, value, tmp);
        if (this->height_help(tmp->left_) - this->height_help(tmp->right_) >
            1) {
          if (this->height_help(tmp->left_->left_) <
              this->height_help(tmp->left_->right_))
            this->turn_left(tmp->left_, tmp->left_->parent_);
          this->turn_right(tmp, tmp->parent_);
        }
      }
      this->set_balance(tmp);
    }
  }
}

template <typename T>
void Multiset<T>::merge(Multiset& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    this->insert(*it);
  }
  other.clear();
}

template <typename T>
typename Multiset<T>::size_type Multiset<T>::count(const Key& key) {
  size_type res = 0;
  if (lower_bound(key) != nullptr && *lower_bound(key) == key) {
    res = 1;
    if (lower_bound(key) == upper_bound(key)) {
      res = 1;
    } else {
      res = 0;
      for (auto it = lower_bound(key); it != upper_bound(key); ++it) {
        res++;
      }
    }
  }
  return res;
}

template <typename T>
void Multiset<T>::erase(iterator pos) {
  pos = lower_bound(*pos);
  Set<T>::erase(pos);
}

template <typename T>
std::pair<typename Multiset<T>::iterator, typename Multiset<T>::iterator>
Multiset<T>::equal_range(const Key& key) {
  return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
}

template <typename T>
typename Multiset<T>::iterator Multiset<T>::lower_bound(const Key& key) {
  iterator res = this->begin();
  while (res != nullptr && *res != key) ++res;
  return res;
}

template <typename T>
typename Multiset<T>::iterator Multiset<T>::upper_bound(const Key& key) {
  iterator res = lower_bound(key);
  while (res != nullptr && *res == key) {
    ++res;
  }
  return res;
}
};      // namespace s21
#endif  // SRC_S21_MULTISET_H_