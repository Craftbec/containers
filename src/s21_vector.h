#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <iostream>

namespace s21 {
template <class T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  class VectorIterator;
  class VectorConstIterator;

  class VectorIterator : public VectorConstIterator {
   public:
    VectorIterator() : VectorConstIterator() {}
    VectorIterator(value_type *ptr) : VectorConstIterator(ptr) {}
    reference operator*() { return *this->m_ptr; }
  };

  class VectorConstIterator {
    friend class Vector;

   public:
    VectorConstIterator() : m_ptr(nullptr) {}
    VectorConstIterator(value_type *ptr) : m_ptr(ptr) {}
    const_reference operator*() { return *m_ptr; }
    value_type operator->() { return m_ptr; }
    T &operator++(int) { return *m_ptr++; }
    T &operator++() { return *++m_ptr; }
    T &operator--(int) { return *m_ptr--; }
    T &operator--() { return *--m_ptr; }
    T &operator+=(int n) {
      for (int i = 0; i < n; i++, m_ptr++)
        ;
      return *m_ptr;
    }
    T &operator-=(int n) {
      for (int i = 0; i < n; i++, m_ptr--)
        ;
      return *m_ptr;
    }

    T &operator-(const int n) {
      for (size_type i = 0; i < n; i++) m_ptr--;
      return *m_ptr;
    }

    T &operator+(size_type n) {
      for (size_type i = 0; i < n; i++) m_ptr++;
      return *m_ptr;
    }

    size_type operator-(VectorConstIterator &other) {
      return (this->m_ptr - other.m_ptr);
    }

    friend bool operator==(const VectorConstIterator &a,
                           const VectorConstIterator &b) {
      return a.m_ptr == b.m_ptr;
    }

    friend bool operator!=(const VectorConstIterator &a,
                           const VectorConstIterator &b) {
      return a.m_ptr != b.m_ptr;
    }

   protected:
    T *m_ptr;
  };

  using iterator = VectorIterator;
  using const_iterator = VectorConstIterator;

  Vector();
  Vector(size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v);
  ~Vector();
  Vector &operator=(const Vector &v);
  Vector &operator=(Vector &&v);

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front();
  const_reference back();
  T *data();

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity() const noexcept;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);

  // ============ Start Emplace ============ //

  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    iterator it(pos.m_ptr);
    for (const auto &val : {std::forward<Args>(args)...}) it = insert(it, val);
    return it;
  }

  template <class... Args>
  void emplace_back(Args &&...args) {
    for (const auto &val : {std::forward<Args>(args)...}) push_back(val);
  }
  // ============= End Emplace ============ //

 private:
  void clean_memory();
  void clean();
  void allocate_memory();
  void copy(const Vector &v);

  size_t m_size;
  size_t m_capacity;
  T *arr;
};
template <typename T>
Vector<T>::Vector() : m_size(0U), m_capacity(0U), arr(nullptr) {}

template <typename T>
Vector<T>::Vector(size_type n)
    : m_size(n), m_capacity(n), arr(n ? new T[n]() : nullptr) {}

template <typename T>
Vector<T>::Vector(std::initializer_list<value_type> const &items) {
  arr = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr[i] = *it;
    i++;
  }
  m_size = items.size();
  m_capacity = items.size();
}

template <typename T>
Vector<T>::Vector(const Vector &v)
    : m_size(v.m_size), m_capacity(v.m_capacity) {
  allocate_memory();
  copy(v);
}

template <typename T>
Vector<T>::Vector(Vector &&v)
    : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {
  v.clean();
}

template <typename T>
Vector<T>::~Vector() {
  clean_memory();
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &v) {
  if (this == &v) return *this;
  clean_memory();
  m_size = v.m_size;
  m_capacity = v.m_capacity;
  allocate_memory();
  copy(v);
  return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector &&v) {
  if (this == &v) return *this;
  clean_memory();
  m_size = v.m_size;
  m_capacity = v.m_capacity;
  arr = v.arr;
  v.clean();
  return *this;
}

template <typename T>
void Vector<T>::clean_memory() {
  if (m_size) delete[] arr;
  m_size = m_capacity = 0U;
}

template <typename T>
void Vector<T>::clean() {
  m_size = m_capacity = 0U;
  arr = nullptr;
}

template <typename T>
void Vector<T>::allocate_memory() {
  arr = new T[m_capacity]();
}

template <typename T>
void Vector<T>::copy(const Vector &v) {
  for (size_t i = 0; i < m_size; i++) {
    arr[i] = v.arr[i];
  }
}

template <typename T>
T &Vector<T>::at(size_type pos) {
  if (pos > m_size - 1) {
    throw std::out_of_range("Is not within the range");
  }
  return arr[pos];
}

template <typename T>
const T &Vector<T>::at(size_type pos) const {
  if (pos > m_size - 1) {
    throw std::out_of_range("Is not within the range");
  }
  return arr[pos];
}

template <typename T>
T &Vector<T>::operator[](size_type pos) {
  return arr[pos];
}

template <typename T>
const T &Vector<T>::operator[](size_type pos) const {
  return arr[pos];
}

template <typename T>
const T &Vector<T>::front() {
  return arr[0];
}

template <typename T>
const T &Vector<T>::back() {
  return arr[m_size - 1];
}

template <typename T>
T *Vector<T>::data() {
  return arr;
}

template <typename T>
bool Vector<T>::empty() const noexcept {
  return m_size == 0;
}

template <typename T>
size_t Vector<T>::size() const noexcept {
  return m_size;
}

template <typename T>
size_t Vector<T>::max_size() const noexcept {
  return SIZE_MAX / sizeof(T) / 2;
}

template <typename T>
void Vector<T>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::length_error("Invalid size");
  }
  if (size > m_capacity) {
    Vector<T> tmp(size);
    tmp.m_size = m_size;
    tmp.copy(*this);
    std::swap(*this, tmp);
  }
}

template <typename T>
size_t Vector<T>::capacity() const noexcept {
  return m_capacity;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  if (m_capacity > m_size) {
    Vector<T> tmp(m_size);
    tmp.copy(*this);
    std::swap(*this, tmp);
  }
}

template <typename T>
void Vector<T>::clear() {
  clean_memory();
}

template <typename T>
void Vector<T>::push_back(const_reference value) {
  if (m_size == m_capacity) {
    reserve(m_size == 0 ? 1 : m_capacity * 2);
  }
  arr[m_size++] = value;
}

template <typename T>
void Vector<T>::pop_back() {
  if (m_size > 0) m_size--;
}

template <typename T>
void Vector<T>::swap(Vector &other) {
  size_t tmp = other.m_size;
  other.m_size = m_size;
  m_size = tmp;
  tmp = other.m_capacity;
  other.m_capacity = m_capacity;
  m_capacity = tmp;
  T *ptr = other.arr;
  other.arr = arr;
  arr = ptr;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept {
  return arr;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept {
  return arr + m_size;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept {
  return arr;
}

template <typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept {
  return arr + m_size;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  int position = begin() - pos;
  if (position < 0) {
    position *= -1;
  }
  if (m_size == m_capacity) {
    reserve(m_size == 0 ? 1 : m_capacity * 2);
  }
  for (int i = m_size + 1; i != position; i--) arr[i] = arr[i - 1];
  arr[position] = value;
  m_size++;
  return arr + position;
}

template <typename T>
void Vector<T>::erase(iterator pos) {
  int i = 0;
  for (auto l = begin(); l != end(); l++) {
    if (pos != l) {
      arr[i] = *l;
      i++;
    }
  }
  m_size--;
}
};      // namespace s21
#endif  // SRC_S21_VECTOR_H_