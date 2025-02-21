#pragma once
#define VECTOR_MEMORY_IMPLEMENTED
#include <iostream>
#include <stdexcept>
#include <utility>

namespace container {

// TODO Нужен, наверное, vector_base,
// TODO Нужен делитер
// TODO shrink_to_fit
// TODO Cвой аллокатор?
// TODO Вообще через SFINAE можно определять, что тип примитивный и его можно
// делать memcpy() (там векторизированные инструкции, все шустрее)
// TODO вынести в construct/destruct
// TODO template <class T, class Allocator = allocator<T> >

/**
 *@brief Hand-made Vector
 *@author GitHub: Repin-Daniil <daniil.r4@yandex.ru>
 */



class vector_basae {};

template <typename T> class vector {
public:
  using ValueType = T;
  using Pointer = T *;
  using ConstPointer = const T *;
  using Reference = T &;
  using ConstReference = const T &;
  using SizeType = size_t;
  using Iterator = T *;
  using ConstIterator = const T *;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  template <class Iterator,
            class = std::enable_if_t<std::is_base_of_v<
                std::forward_iterator_tag,
                typename std::iterator_traits<Iterator>::iterator_category>>>

  vector();
  explicit vector(const size_t &size);

  vector(const size_t &size, const T &value);
  vector(const std::initializer_list<ValueType> &list);

  vector(Iterator first, Iterator last);

  vector(const vector &other);

  vector(vector &&other) noexcept;

  vector &operator=(const vector<T> &other);
  vector &operator=(vector &&other) noexcept;
  vector &operator=(const std::initializer_list<ValueType> &list);

  SizeType Capacity() const;
  SizeType Size() const;
  bool Empty() const;

  Reference operator[](SizeType pos);
  ConstReference operator[](SizeType pos);

  Reference At(SizeType pos);

  ConstReference At(SizeType pos) const;

  Reference Front();
  ConstReference Front() const;

  Reference Back();
  ConstReference Back();
  Pointer Data();
  ConstPointer Data() const;

  void Swap(vector<T> &other);

  void Resize(size_t new_size);
  void Resize(size_t new_size, const T &value);
  void ShrinkToFit();

  void Clear();

  void PushBack(const ValueType &elem);
  void PushBack(T &&elem);

  void PopBack();

  template <typename... Arguments>
  void EmplaceBack(Arguments &&...values);

  Pointer begin();
  Pointer end();

  ConstPointer begin() const;
  ConstPointer end() const;

  ConstPointer cbegin() const;
  ConstPointer cend() const;

  ReverseIterator rbegin();
  ReverseIterator rend();

  ConstReverseIterator rbegin() const { // NOLINT
    return std::reverse_iterator<const T *>(cend());
  }

  ConstReverseIterator rend() const { // NOLINT
    return std::reverse_iterator<const T *>(cbegin());
  }

  ConstReverseIterator crbegin() const { // NOLINT
    return std::reverse_iterator<const T *>(cend());
  }

  ConstReverseIterator crend() const { // NOLINT
    return std::reverse_iterator<const T *>(cbegin());
  }

  ~vector();

private:
  ValueType *arr_ = nullptr;
  SizeType size_;
  SizeType capacity_;
};

template <class T>
bool operator<(const vector<T> &first, const vector<T> &second) {
  size_t i = 0;
  while (i < first.Size() && i < second.Size()) {
    if (first[i] != second[i]) {
      return first[i] < second[i];
    }

    ++i;
  }

  return (first.Size() < second.Size());
}

template <class T>
bool operator>(const vector<T> &first, const vector<T> &second) {
  return (second < first);
}

template <class T>
bool operator==(const vector<T> &first, const vector<T> &second) {
  return !(first < second) && !(second < first);
}

template <class T>
bool operator!=(const vector<T> &first, const vector<T> &second) {
  return ((first < second) || (second < first));
}

template <class T>
bool operator<=(const vector<T> &first, const vector<T> &second) {
  return !(second < first);
}

template <class T>
bool operator>=(const vector<T> &first, const vector<T> &second) {
  return !(first < second);
}

template <>
class vector<bool> {
  //TODO Реализация для булей
};

} // namespace container

