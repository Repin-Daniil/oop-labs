#pragma once
#define VECTOR_MEMORY_IMPLEMENTED
#include <iostream>
#include <stdexcept>
#include <utility>

namespace container {


//TODO Нужен, наверное, vector_base,
//TODO Нужен делитер
//TODO shrink_to_fit
//TODO Cвой аллокатор?
//TODO Вообще через SFINAE можно определять, что тип примитивный и его можно делать memcpy() (там векторизированные инструкции, все шустрее)
//TODO вынести в construct/destruct
//TODO template <class T, class Allocator = allocator<T> >

/**
 *@brief Hand-made Vector
 *@author GitHub: Repin-Daniil <daniil.r4@yandex.ru>
 */
template <typename T>
class vector {
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

  vector() : arr_(nullptr), size_(0), capacity_(0) {
  }

  explicit vector(const size_t &size) : size_(0), capacity_(0) {
    if (size == 0) {
      arr_ = nullptr;
    } else {
      try {
        arr_ = reinterpret_cast<T *>(new int8_t[size * sizeof(T)]); //FIXME Наверное, как Балун лучше
      } catch (std::bad_alloc &e) {
        arr_ = nullptr;
        throw;
      }

      size_t i;
      try {
        for (i = 0; i < size; ++i) {
          new (arr_ + i) T();
        }

        size_ = size;
        capacity_ = size;
      } catch (std::exception &e) {
        for (size_t j = 0; j < i; ++j) {
          (arr_ + j)->~T();
        }

        delete[] reinterpret_cast<int8_t *>(arr_);
        arr_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
    }
  }

  vector(const size_t &size, const T &value) : size_(0), capacity_(0) {
    if (size == 0) {
      arr_ = nullptr;
    } else {
      try {
        arr_ = reinterpret_cast<T *>(new int8_t[size * sizeof(T)]);
      } catch (std::bad_alloc &e) {
        arr_ = nullptr;
        throw;
      }

      size_t i;

      try {
        for (i = 0; i < size; ++i) {
          new (arr_ + i) T(value);
        }

        size_ = size;
        capacity_ = size;
      } catch (std::exception &e) {
        for (size_t j = 0; j < i; ++j) {
          (arr_ + j)->~T();
        }

        delete[] reinterpret_cast<int8_t *>(arr_);
        arr_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
    }
  }

  vector(const std::initializer_list<ValueType> &list) {
    size_ = list.size();
    capacity_ = list.size();

    if (size_ == 0) {
      arr_ = nullptr;
    } else {
      try {
        arr_ = reinterpret_cast<T *>(new int8_t[capacity_ * sizeof(T)]);
      } catch (std::bad_alloc &e) {
        arr_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }

      size_t i = 0;

      try {
        for (auto j = list.begin(); j != list.end(); ++j) {
          new (arr_ + i++) T(*j);
        }
      } catch (std::exception &e) {
        for (size_t j = 0; j < i; ++j) {
          (arr_ + j)->~T();
        }

        delete[] reinterpret_cast<int8_t *>(arr_);
        arr_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
    }
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  vector(Iterator first, Iterator last) {
    size_ = last - first;
    capacity_ = last - first;

    if (capacity_ == 0) {
      arr_ = nullptr;
    } else {
      size_t i = 0;

      try {
        arr_ = reinterpret_cast<T *>(new int8_t[capacity_ * sizeof(T)]);
      } catch (std::bad_alloc &e) {
        arr_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }

      try {
        for (Iterator it = first; it != last; ++it) {
          new (arr_ + i++) T(*it);
        }
      } catch (std::exception &e) {
        for (size_t j = 0; j < i; ++j) {
          (arr_ + j)->~T();
        }

        delete[] reinterpret_cast<int8_t *>(arr_);
        arr_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }
    }
  }

  vector(const vector &other) {
    if (other.size_ == 0) {
      size_ = 0;
      capacity_ = 0;
      arr_ = nullptr;
    } else {
      try {
        arr_ = reinterpret_cast<T *>(new int8_t[other.capacity_ * sizeof(T)]);
      } catch (std::bad_alloc &e) {
        arr_ = nullptr;
        size_ = 0;
        capacity_ = 0;
        throw;
      }

      size_t i;

      try {
        for (i = 0; i < other.size_; ++i) {
          new (arr_ + i) T(other.arr_[i]);
        }

        size_ = other.size_;
        capacity_ = other.capacity_;
      } catch (std::exception &e) {
        for (size_t j = 0; j < i; ++j) {
          (arr_ + j)->~T();
        }

        delete[] reinterpret_cast<int8_t *>(arr_);
        size_ = 0;
        capacity_ = 0;
        arr_ = nullptr;
        throw;
      }
    }
  }

  vector(vector &&other) noexcept {
    size_ = other.size_;
    capacity_ = other.capacity_;
    arr_ = other.arr_;
    other.size_ = 0;
    other.capacity_ = 0;
    other.arr_ = nullptr;
  }

  vector &operator=(const vector<T> &other) {
    if (this != &other) {
      auto temp = vector<T>(other);
      temp.Swap(*this);
      temp.Clear();
    }

    return *this;
  }

  vector &operator=(vector &&other) noexcept {
    if (this != &other) {
      auto temp = vector(std::move(other));
      temp.Swap(*this);
      temp.Clear();
    }

    return *this;
  }

  vector &operator=(const std::initializer_list<ValueType> &list) {
    auto temp = vector(list);
    temp.Swap(*this);
    temp.Clear();
    return *this;
  }

  void Reserve(SizeType n) {
    if (n <= capacity_) {
      return;
    }

    T *new_arr = nullptr;

    try {
      new_arr = reinterpret_cast<T *>(new int8_t[n * sizeof(T)]);
    } catch (std::bad_alloc &e) {
      throw;
    }

    for (size_t i = 0; i < size_; ++i) {
      new (new_arr + i) T(std::move(arr_[i]));
    }

    for (size_t i = 0; i < size_; ++i) {
      (arr_ + i)->~T();
    }

    delete[] reinterpret_cast<int8_t *>(arr_);
    capacity_ = n;
    arr_ = new_arr;
  }

  SizeType Capacity() const {
    return capacity_;
  }
  SizeType Size() const {
    return size_;
  }
  bool Empty() const {
    return (size_ == 0);
  }

  Reference operator[](SizeType pos) {
    return arr_[pos];
  }

  ConstReference operator[](SizeType pos) const {
    return arr_[pos];
  }

  Reference At(SizeType pos) {
    if (pos >= size_) {
      throw std::out_of_range("");
    }

    return arr_[pos];
  }

  ConstReference At(SizeType pos) const {
    if (pos >= size_) {
      throw std::out_of_range("");
    }

    return arr_[pos];
  }

  Reference Front() {
    return arr_[0];
  }

  ConstReference Front() const {
    return arr_[0];
  }

  Reference Back() {
    return arr_[size_ - 1];
  }

  ConstReference Back() const {
    return arr_[size_ - 1];
  }

  Pointer Data() {
    return arr_;
  }

  ConstPointer Data() const {
    return arr_;
  }

  void Swap(vector<T> &other) {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  void Resize(size_t new_size) {
    if (new_size > capacity_) {
      T *temp_arr = nullptr;
      size_t pos = 0;

      try {
        temp_arr = reinterpret_cast<T *>(new int8_t[new_size * sizeof(T)]);
      } catch (std::bad_alloc &e) {
        throw;
      }

      for (size_t i = 0; i < size_; ++i) {
        new (temp_arr + i) T(std::move(arr_[i]));
      }

      try {
        for (pos = size_; pos < new_size; ++pos) {
          new (temp_arr + pos) T();
        }
      } catch (std::exception &e) {
        for (size_t i = 0; i < size_; ++i) {
          new (arr_ + i) T(std::move(temp_arr[i]));
        }

        for (size_t j = size_; j < pos; ++j) {
          (temp_arr + j)->~T();
        }

        delete[] reinterpret_cast<int8_t *>(temp_arr);
        throw;
      }

      Clear();
      delete[] reinterpret_cast<int8_t *>(arr_);
      arr_ = temp_arr;
      size_ = new_size;
      capacity_ = new_size;
    } else if (new_size >= size_) {
      size_t i;

      try {
        for (i = size_; i < new_size; ++i) {
          new (arr_ + i) T();
        }
      } catch (std::exception &e) {
        for (size_t j = size_; j < i; ++j) {
          (arr_ + j)->~T();
        }

        throw;
      }

      size_ = new_size;
    } else {
      for (size_t i = size_ - 1; i >= new_size; --i) {
        (arr_ + i)->~T();
      }

      size_ = new_size;
    }
  }

  void Resize(size_t new_size, const T &value) {
    if (new_size > capacity_) {
      T *temp_arr = nullptr;
      size_t pos = 0;

      try {
        temp_arr = reinterpret_cast<T *>(new int8_t[new_size * sizeof(T)]);
      } catch (std::bad_alloc &e) {
        throw;
      }

      for (size_t i = 0; i < size_; ++i) {
        new (temp_arr + i) T(std::move(arr_[i]));
      }

      try {
        for (pos = size_; pos < new_size; ++pos) {
          new (temp_arr + pos) T(value);
        }
      } catch (std::exception &e) {
        for (size_t i = 0; i < size_; ++i) {
          new (arr_ + i) T(std::move(temp_arr[i]));
        }
        for (size_t j = size_; j < pos; ++j) {
          (temp_arr + j)->~T();
        }
        delete[] reinterpret_cast<int8_t *>(temp_arr);
        throw;
      }

      Clear();
      delete[] reinterpret_cast<int8_t *>(arr_);
      arr_ = temp_arr;
      size_ = new_size;
      capacity_ = new_size;
    } else if (new_size >= size_) {
      size_t i;

      try {
        for (i = size_; i < new_size; ++i) {
          new (arr_ + i) T(value);
        }
      } catch (std::exception &e) {
        for (size_t j = size_; j < i; ++j) {
          (arr_ + j)->~T();
        }

        throw;
      }

      size_ = new_size;
    } else {
      for (size_t i = size_ - 1; i >= new_size; --i) {
        (arr_ + i)->~T();
      }

      size_ = new_size;
    }
  }

  void ShrinkToFit() {
    if (size_ == 0 || size_ == capacity_) {
      capacity_ = size_;

      if (size_ == 0) {
        Clear();
        delete[] reinterpret_cast<int8_t *>(arr_);
        arr_ = nullptr;
      }
    } else {
      T *new_arr = nullptr;

      try {
        new_arr = reinterpret_cast<T *>(new int8_t[size_ * sizeof(T)]);
      } catch (std::bad_alloc &e) {
        throw;
      }

      for (size_t i = 0; i < size_; ++i) {
        new (new_arr + i) T(std::move(arr_[i]));
      }

      for (size_t i = 0; i < size_; ++i) {
        (arr_ + i)->~T();
      }

      delete[] reinterpret_cast<int8_t *>(arr_);
      capacity_ = size_;
      arr_ = new_arr;
    }
  }

  void Clear() {
    for (size_t i = 0; i < size_; ++i) {
      (arr_ + i)->~T();
    }

    size_ = 0;
  }

  void PushBack(const ValueType &elem) {
    bool reserved = false;

    if (size_ >= capacity_) {
      Reserve((capacity_ == 0) ? 1 : capacity_ * 2);
      reserved = true;
    }

    try {
      new (arr_ + size_) T(std::forward<ConstReference>(elem)); //FIXME тут исправил
    } catch (...) {
      (arr_ + size_)->~T();
      if (reserved) {
        ShrinkToFit();
      }

      throw;
    }

    ++size_;
  }

  void PushBack(T &&elem) {
    if (size_ >= capacity_) {
      Reserve((capacity_ == 0) ? 1 : capacity_ * 2);
    }

    new (arr_ + size_++) T(std::move(elem));
  }

  void PopBack() {
    if (size_ > 0) {
      (arr_ + size_ - 1)->~T();
      --size_;
    } else {
      throw;
    }
  }

  template <typename... Arguments>
  void EmplaceBack(Arguments &&... values) {
    if (size_ >= capacity_) {
      Reserve((capacity_ == 0) ? 1 : capacity_ * 2);
    }

    new (arr_ + size_++) T(std::move(values)...);
  }

  Pointer begin() {  // NOLINT
    return arr_;
  }

  Pointer end() {  // NOLINT
    return arr_ + size_;
  }

  ConstPointer begin() const {  // NOLINT
    return arr_;
  }

  ConstPointer end() const {  // NOLINT
    return arr_ + size_;
  }

  ConstPointer cbegin() const {  // NOLINT
    return arr_;
  }

  ConstPointer cend() const {  // NOLINT
    return arr_ + size_;
  }

  ReverseIterator rbegin() {  // NOLINT
    return std::reverse_iterator<T *>(end());
  }

  ReverseIterator rend() {  // NOLINT
    return std::reverse_iterator<T *>(begin());
  }

  ConstReverseIterator rbegin() const {  // NOLINT
    return std::reverse_iterator<const T *>(cend());
  }

  ConstReverseIterator rend() const {  // NOLINT
    return std::reverse_iterator<const T *>(cbegin());
  }

  ConstReverseIterator crbegin() const {  // NOLINT
    return std::reverse_iterator<const T *>(cend());
  }

  ConstReverseIterator crend() const {  // NOLINT
    return std::reverse_iterator<const T *>(cbegin());
  }

  ~vector() {
    for (size_t i = 0; i < size_; ++i) {
      (arr_ + i)->~T();
    }

    if (arr_ != nullptr) {
      delete[] reinterpret_cast<int8_t *>(arr_);
    }
  }

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

