#ifndef SRC_S21_ARRAY_H_
#define SRC_S21_ARRAY_H_

#include <iostream>

namespace s21 {
template <class T, std::size_t S>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const T *;

  Array();
  Array(std::initializer_list<value_type> const &items);
  Array(const Array &a);
  Array(Array &&a);
  ~Array();

  Array<T, S> &operator=(Array &other);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data() noexcept;
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void swap(Array &other) noexcept;
  void fill(const_reference value);

 private:
  void clean();
  void clean_memory();
  void copy(const Array &a);

  size_t m_size;
  T *arr;
};

template <typename T, std::size_t S>
Array<T, S>::Array() : m_size(S), arr(S ? new T[S]() : nullptr) {}

template <typename T, std::size_t S>
Array<T, S>::Array(std::initializer_list<value_type> const &items) : Array() {
  auto it = items.begin();
  for (size_t i = 0; i < m_size; i++) {
    if (it != items.end()) arr[i] = *it;
    it++;
  }
}

template <typename T, std::size_t S>
Array<T, S>::Array(const Array &a) : m_size(a.m_size) {
  copy(a);
}

template <typename T, std::size_t S>
Array<T, S>::Array(Array &&a) {
  m_size = a.m_size;
  arr = a.arr;
  a.clean();
}

template <typename T, std::size_t S>
Array<T, S>::~Array() {
  clean_memory();
}

template <typename T, std::size_t S>
Array<T, S> &Array<T, S>::operator=(Array<T, S> &other) {
  clean();
  copy(other);
  return *this;
}

template <typename T, std::size_t S>
void Array<T, S>::clean() {
  m_size = 0U;
  arr = nullptr;
}

template <typename T, std::size_t S>
void Array<T, S>::clean_memory() {
  m_size = 0U;
  delete[] arr;
}

template <typename T, std::size_t S>
void Array<T, S>::copy(const Array &a) {
  m_size = a.m_size;
  arr = new T[a.m_size]();
  for (size_t i = 0; i < m_size; i++) {
    arr[i] = a.arr[i];
  }
}

template <typename T, std::size_t S>
typename Array<T, S>::reference Array<T, S>::at(size_type pos) {
  if (pos > m_size - 1) {
    throw std::out_of_range("Is not within the range");
  }
  return arr[pos];
}

template <typename T, std::size_t S>
typename Array<T, S>::reference Array<T, S>::operator[](size_type pos) {
  return arr[pos];
}

template <typename T, std::size_t S>
typename Array<T, S>::const_reference Array<T, S>::front() const {
  return arr[0];
}

template <typename T, std::size_t S>
typename Array<T, S>::const_reference Array<T, S>::back() const {
  return arr[m_size - 1];
}

template <typename T, std::size_t S>
typename Array<T, S>::iterator Array<T, S>::data() noexcept {
  return arr;
}

template <typename T, std::size_t S>
typename Array<T, S>::iterator Array<T, S>::begin() noexcept {
  return arr;
}

template <typename T, std::size_t S>
typename Array<T, S>::const_iterator Array<T, S>::cbegin() const noexcept {
  return arr;
}

template <typename T, std::size_t S>
typename Array<T, S>::iterator Array<T, S>::end() noexcept {
  return arr + m_size;
}

template <typename T, std::size_t S>
typename Array<T, S>::const_iterator Array<T, S>::cend() const noexcept {
  return arr + m_size;
}

template <typename T, std::size_t S>
bool Array<T, S>::empty() const noexcept {
  return m_size == 0;
}

template <typename T, std::size_t S>
typename Array<T, S>::size_type Array<T, S>::size() const noexcept {
  return m_size;
}

template <typename T, std::size_t S>
typename Array<T, S>::size_type Array<T, S>::max_size() const noexcept {
  return m_size;
}

template <typename T, std::size_t S>
void Array<T, S>::swap(Array &other) noexcept {
  std::swap(arr, other.arr);
}

template <typename T, std::size_t S>
void Array<T, S>::fill(const_reference value) {
  for (size_t i = 0; i < m_size; i++) {
    arr[i] = value;
  }
}

};      // namespace s21
#endif  // SRC_S21_ARRAY_H_