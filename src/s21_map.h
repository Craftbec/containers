#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include <iostream>

#include "./s21_vector.h"

namespace s21 {
template <class Key, class T>
class Map {
  class Node;
  class MapConstIterator;
  class MapIterator;

 public:
  using key_type = Key;
  using size_type = size_t;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MapIterator;
  using const_iterator = MapConstIterator;

  Map();
  Map(std::initializer_list<value_type> const &items);
  Map(const Map &m);
  Map(Map &&m);
  ~Map();
  Map &operator=(Map &&m) noexcept;
  Map &operator=(const Map &m);

  T &at(const Key &key);
  T &operator[](const Key &key);

  bool empty() const noexcept;
  iterator end() noexcept;
  iterator begin() noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear() noexcept;
  void swap(Map &other) noexcept;
  void erase(iterator pos);
  void merge(Map &other);
  bool contains(const Key &key) const;
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);

  // ============ Start Emplace ============ //

  template <class... Args>
  Vector<std::pair<iterator, bool>> emplace(Args &&...args) {
    Vector<std::pair<iterator, bool>> out;
    for (auto val : {std::forward<Args>(args)...}) out.push_back(insert(val));
    return out;
  }
  // ============= End Emplace ============ //

 private:
  void clear_recursion(Node *root);
  std::pair<iterator, bool> insert_recursion(Node *tmp_r, const Key &key,
                                             const T &obj);
  Node *at_recursion(Node *root, const Key &key);
  bool contains_recursion(Node *root, const Key &key) const;
  void copy_recursion(Node *root);
  void init_map_size();
  Node *start_node(Node *root);
  Node *end_node(Node *root);

  Node *root_;
  size_t m_size;
  Node *map_size_;
};

// ========== Start Implementation Inner Classes ==================== //

template <typename Key, typename T>
class Map<Key, T>::Node {
 public:
  Node(Key f = Key(), T s = T(), Node *left = nullptr, Node *right = nullptr,
       Node *parent = nullptr)
      : pr_(std::make_pair(f, s)) {
    left_ = left;
    right_ = right;
    parent_ = parent;
  }
  Node *parent_;
  Node *left_;
  Node *right_;
  std::pair<Key, T> pr_;
};

template <typename Key, typename T>
class Map<Key, T>::MapConstIterator {
  friend class Map;

 public:
  MapConstIterator() : mp_(nullptr), iter_(nullptr) {}
  MapConstIterator(Map<Key, T> *mp, Node *iter) : mp_(mp), iter_(iter) {}

  const_reference operator*() { return this->iter_->pr_; }

  bool operator==(const_iterator other) {
    return this->iter_ == other.iter_ ? 1 : 0;
  }

  bool operator!=(const_iterator other) {
    return this->iter_ != other.iter_ ? 1 : 0;
  }

  const_iterator &operator++() {
    Node *root = iter_;
    Key k = iter_->pr_.first;
    while (root->parent_) root = root->parent_;
    if (iter_->right_) {
      iter_ = iter_->right_;
      while (iter_->left_) iter_ = iter_->left_;
    } else {
      if (!iter_->parent_ && !iter_->right_) {
        iter_ = mp_->map_size_;
      } else if (iter_->parent_->left_ &&
                 k == iter_->parent_->left_->pr_.first) {
        iter_ = iter_->parent_;
      } else if (iter_->parent_->right_ &&
                 k == iter_->parent_->right_->pr_.first) {
        if (k != max_val()) {
          while (iter_->parent_->pr_.first < k) {
            iter_ = iter_->parent_;
          }
          iter_ = iter_->parent_;
        } else {
          iter_ = mp_->map_size_;
        }
      }
    }
    return *this;
  }

  const_iterator &operator--() {
    Node *root = iter_;
    Key k = iter_->pr_.first;
    while (root->parent_) root = root->parent_;
    if (iter_->left_) {
      iter_ = iter_->left_;
      while (iter_->right_) iter_ = iter_->right_;
    } else {
      if (!iter_->parent_ && !iter_->left_) {
        iter_ = mp_->map_size_;
      } else if (iter_->parent_->right_ &&
                 k == iter_->parent_->right_->pr_.first) {
        iter_ = iter_->parent_;
      } else if (iter_->parent_->left_ &&
                 k == iter_->parent_->left_->pr_.first) {
        if (k != min_val()) {
          while (iter_->parent_->pr_.first > k) {
            iter_ = iter_->parent_;
          }
          iter_ = iter_->parent_;
        } else {
          iter_ = mp_->map_size_;
        }
      }
    }
    return *this;
  }

 private:
  Key max_val() {
    Node *tmp = iter_;
    while (tmp->parent_) tmp = tmp->parent_;
    while (tmp->right_) tmp = tmp->right_;
    return tmp->pr_.first;
  }

  Key min_val() {
    Node *tmp = iter_;
    while (tmp->parent_) tmp = tmp->parent_;
    while (tmp->left_) tmp = tmp->left_;
    return tmp->pr_.first;
  }

 protected:
  Map<Key, T> *mp_;
  Node *iter_;
};

template <typename Key, typename T>
class Map<Key, T>::MapIterator : public MapConstIterator {
 public:
  MapIterator() : MapConstIterator() {}
  MapIterator(Map<Key, T> *mp, Node *iter) : MapConstIterator(mp, iter) {}

  reference operator*() { return this->iter_->pr_; }

  bool operator==(iterator other) { return this->iter_ == other.iter_ ? 1 : 0; }

  bool operator!=(iterator other) { return this->iter_ != other.iter_ ? 1 : 0; }
};

// ================ End Implementation Inner Classes ================== //

template <typename Key, typename T>
typename Map<Key, T>::Node *Map<Key, T>::start_node(Node *root) {
  while (root->left_) root = root->left_;
  return root;
}

template <typename Key, typename T>
typename Map<Key, T>::Node *Map<Key, T>::end_node(Node *root) {
  while (root->right_) root = root->right_;
  return root;
}

template <typename Key, typename T>
void Map<Key, T>::init_map_size() {
  if (root_) {
    map_size_->left_ = end_node(root_);
    map_size_->right_ = start_node(root_);
  } else {
    map_size_ = new Node(Key(), T(), nullptr, nullptr, nullptr);
  }
}

// =================== Constructor's of class Map ===================== //

template <typename Key, typename T>
Map<Key, T>::Map() : root_(nullptr), m_size(0) {
  init_map_size();
}

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const &items) : Map() {
  for (auto it = items.begin(); it != items.end(); it++) {
    insert(*it);
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(const Map &m) : Map() {
  copy_recursion(m.root_);
}

template <typename Key, typename T>
Map<Key, T>::Map(Map &&m)
    : root_(m.root_), m_size(m.m_size), map_size_(m.map_size_) {
  m.m_size = 0;
  m.map_size_ = nullptr;
  m.root_ = nullptr;
}

template <typename Key, typename T>
Map<Key, T>::~Map() {
  clear();
  delete map_size_;
}

// ============== Implementation public method's ============== //

template <typename Key, typename T>
typename Map<Key, T>::Map &Map<Key, T>::operator=(Map &&m) noexcept {
  clear();
  root_ = m.root_;
  m_size = m.m_size;
  m.m_size = 0;
  delete map_size_;
  map_size_ = m.map_size_;
  m.map_size_ = nullptr;
  m.root_ = nullptr;
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::Map &Map<Key, T>::operator=(const Map &m) {
  clear();
  copy_recursion(m.root_);
  return *this;
}

template <typename Key, typename T>
T &Map<Key, T>::at(const Key &key) {
  return at_recursion(root_, key)->pr_.second;
}

template <typename Key, typename T>
T &Map<Key, T>::operator[](const Key &key) {
  return insert(std::make_pair(key, T())).first.iter_->pr_.second;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() noexcept {
  if (!root_) {
    iterator it(this, map_size_);
    return it;
  }
  Node *tmp = root_;
  while (tmp->left_) tmp = tmp->left_;
  iterator it(this, tmp);
  return it;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() noexcept {
  iterator it(this, map_size_);
  return it;
}

template <typename Key, typename T>
bool Map<Key, T>::empty() const noexcept {
  return m_size ? 0 : 1;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::size() const noexcept {
  return m_size;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::max_size() const noexcept {
  return SIZE_MAX / sizeof(Node) / 2;
}

template <typename Key, typename T>
void Map<Key, T>::clear() noexcept {
  clear_recursion(root_);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const Key &key, const T &obj) {
  return insert_recursion(root_, key, obj);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const value_type &value) {
  return insert_recursion(root_, value.first, value.second);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  std::pair<iterator, bool> pr = insert_recursion(root_, key, obj);
  if (!pr.second) {
    Node *insrt = at_recursion(root_, key);
    insrt->pr_.second = obj;
    pr.first.iter_ = insrt;
  }
  return std::make_pair(pr.first, true);
}

template <typename Key, typename T>
void Map<Key, T>::erase(iterator pos) {
  if (!pos.iter_->left_ && !pos.iter_->right_) {
    if (!pos.iter_->parent_) {
      clear();
      return;
    }
    if (pos.iter_->parent_->left_ == pos.iter_) {
      pos.iter_->parent_->left_ = nullptr;
    } else {
      pos.iter_->parent_->right_ = nullptr;
    }
    delete pos.iter_;
    m_size--;
  } else if (!pos.iter_->left_ && pos.iter_->right_) {
    pos.iter_->right_->parent_ = pos.iter_->parent_;
    if (pos.iter_->parent_) {
      if (pos.iter_->parent_->pr_.first > pos.iter_->pr_.first) {
        pos.iter_->parent_->left_ = pos.iter_->right_;
      } else {
        pos.iter_->parent_->right_ = pos.iter_->right_;
      }
    } else {
      root_ = pos.iter_->right_;
      root_->parent_ = nullptr;
    }
    delete pos.iter_;
    m_size--;
  } else if (pos.iter_->left_ && !pos.iter_->right_) {
    pos.iter_->left_->parent_ = pos.iter_->parent_;
    if (pos.iter_->parent_) {
      if (pos.iter_->parent_->pr_.first < pos.iter_->pr_.first) {
        pos.iter_->parent_->right_ = pos.iter_->left_;
      } else {
        pos.iter_->parent_->left_ = pos.iter_->left_;
      }
    } else {
      root_ = pos.iter_->left_;
      root_->parent_ = nullptr;
    }
    delete pos.iter_;
    m_size--;
  } else {
    Node *tmp = pos.iter_;
    --pos;
    tmp->pr_ = pos.iter_->pr_;
    erase(pos);
  }
  init_map_size();
}

template <typename Key, typename T>
void Map<Key, T>::swap(Map &other) noexcept {
  size_type tmp_size = m_size;
  m_size = other.m_size;
  other.m_size = tmp_size;
  Node *tmp = root_;
  root_ = other.root_;
  other.root_ = tmp;
}

template <typename Key, typename T>
void Map<Key, T>::merge(Map &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert((*it).first, (*it).second);
  }
  other.clear();
  other.root_ = nullptr;
}

template <typename Key, typename T>
bool Map<Key, T>::contains(const Key &key) const {
  return contains_recursion(root_, key);
}

// =============== Help method's (private) =============== //

template <typename Key, typename T>
typename Map<Key, T>::Node *Map<Key, T>::at_recursion(Node *root,
                                                      const Key &key) {
  if (!root) throw std::out_of_range("No such element exists");
  if (key < root->pr_.first) return at_recursion(root->left_, key);
  if (key > root->pr_.first) return at_recursion(root->right_, key);
  return root;
}

template <typename Key, typename T>
void Map<Key, T>::clear_recursion(Node *root) {
  if (root) {
    if (root->left_) clear_recursion(root->left_);
    if (root->right_) clear_recursion(root->right_);
    m_size--;
    delete root;
  }
  root_ = nullptr;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_recursion(
    Node *tmp_r, const Key &key, const T &obj) {
  int flag = m_size;
  iterator out(this, tmp_r);
  if (!root_) {
    root_ = new Node(key, obj, nullptr, nullptr, nullptr);
    out.iter_ = root_;
    m_size++;
  } else {
    if (key < tmp_r->pr_.first) {
      if (tmp_r->left_ == nullptr) {
        tmp_r->left_ = new Node(key, obj, nullptr, nullptr, tmp_r);
        out.iter_ = tmp_r->left_;
        m_size++;
      } else {
        return insert_recursion(tmp_r->left_, key, obj);
      }
    } else if (key > tmp_r->pr_.first) {
      if (tmp_r->right_ == nullptr) {
        tmp_r->right_ = new Node(key, obj, nullptr, nullptr, tmp_r);
        out.iter_ = tmp_r->right_;
        m_size++;
      } else {
        return insert_recursion(tmp_r->right_, key, obj);
      }
    } else {
      out.iter_ = tmp_r;
    }
  }
  flag -= m_size;
  init_map_size();
  return std::make_pair(out, (bool)flag);
}

template <typename Key, typename T>
bool Map<Key, T>::contains_recursion(Node *root, const Key &key) const {
  bool out = false;
  if (root) {
    if (key == root->pr_.first) {
      out = true;
    } else {
      if (key < root->pr_.first) return contains_recursion(root->left_, key);
      if (key > root->pr_.first) return contains_recursion(root->right_, key);
    }
  }
  return out;
}

template <typename Key, typename T>
void Map<Key, T>::copy_recursion(Node *root) {
  if (root) {
    insert(root->pr_.first, root->pr_.second);
    if (root->left_) copy_recursion(root->left_);
    if (root->right_) copy_recursion(root->right_);
  }
}
};      // namespace s21
#endif  // SRC_S21_MAP_H_
