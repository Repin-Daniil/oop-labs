#pragma once
#define VECTOR_MEMORY_IMPLEMENTED
#include <iostream>

#include <stdexcept>
#include <type_traits>
#include <utility>

namespace container {

// TODO Cвой аллокатор? template <class T, class Allocator = allocator<T> >
// TODO Ревью GPT
// TODO Лекция Мещерина
// TODO Сравнить с версией Ильи
// TODO Залить в контест
// TODO Включить автодополнение
// TODO Заменить на всякие Referene и так далее
// TODO переименовать типы члены

namespace detail {

template <typename T>
class vector_base {
 public:
  vector_base(const vector_base&) = delete;
  vector_base& operator=(const vector_base& other) = delete;

 protected:
  vector_base() = default;

  explicit vector_base(std::size_t size)
      : arr_(size == 0 ? nullptr : reinterpret_cast<T*>(operator new(size * sizeof(T)))), capacity_(size) {
  }

  vector_base(vector_base&& other) noexcept : arr_(other.arr_), size_(other.size_), capacity_(other.capacity_) {
    other.arr_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  vector_base& operator=(vector_base&& other) noexcept {
    if (this != &other) {
      for (std::size_t i = size_; i > 0; --i) {
        std::destroy_at(arr_ + (i - 1));
      }

      operator delete(arr_);

      arr_ = other.arr_;
      size_ = other.size_;
      capacity_ = other.capacity_;

      other.arr_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }

    return *this;
  }

  void swap(vector_base& other) noexcept {
    using std::swap;
    swap(arr_, other.arr_);
    swap(capacity_, other.capacity_);
    swap(size_, other.size_);
  }

  ~vector_base() {
    for (std::size_t i = size_; i > 0; --i) {
      std::destroy_at(arr_ + (i - 1));
    }

    operator delete(arr_);
  }

 protected:
  T* arr_{nullptr};
  std::size_t size_{0};
  std::size_t capacity_{0};
};
}  // namespace detail

/**
 *@brief Hand-made Vector
 *@author GitHub: Repin-Daniil <daniil.r4@yandex.ru>
 */
template <typename T>
class vector : private detail::vector_base<T> {
 public:
  using ValueType = T;
  using SizeType = std::size_t;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using Iterator = T*;
  using ConstIterator = const T*;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

  vector() = default;
  explicit vector(const std::size_t& size, bool initialize_elements = true) : detail::vector_base<ValueType>(size) {
    if (initialize_elements) {
      for (std::size_t i = 0; i < size; ++i) {
        std::construct_at(arr_ + i);
        ++size_;
      }
    }
  }

  vector(const std::size_t& size, const T& value) : detail::vector_base<ValueType>(size) {
    for (std::size_t i = 0; i < size; ++i) {
      std::construct_at(arr_ + i, value);
      ++size_;
    }
  }

  vector(const std::initializer_list<ValueType>& list) : detail::vector_base<ValueType>(list.size()) {
    for (const auto& value : list) {
      std::construct_at(arr_ + size_, value);
      ++size_;
    }
  }

  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  vector(Iterator first, Iterator last) : detail::vector_base<ValueType>(last - first) {
    for (auto it = first; it != last; ++it) {
      std::construct_at(arr_ + size_, *it);
      ++size_;
    }
  }

  vector(const vector& other) : detail::vector_base<T>(other.size_) {
    while (size_ < other.size_) {
      std::construct_at(arr_ + size_, other.arr_[size_]);
      ++size_;
    }
  }

  vector(vector&& other) noexcept = default;  // since C++ 20

  vector& operator=(const vector<T>& other) {
    if (this != &other) {
      vector temp(other);
      swap(temp);
    }

    return *this;
  }

  vector& operator=(vector&& other) noexcept = default;  // since C++ 20
  vector& operator=(const std::initializer_list<ValueType>& list) {
    vector temp(list);
    swap(temp);

    return *this;
  }

  [[nodiscard]] SizeType capacity() const noexcept {
    return capacity_;
  }

  [[nodiscard]] SizeType size() const noexcept {
    return size_;
  }

  [[nodiscard]] bool empty() const noexcept {
    return size_ == 0;
  }

  Reference operator[](SizeType pos) {
    return arr_[pos];
  }

  ConstReference operator[](SizeType pos) const {
    return arr_[pos];
  }

  Reference at(SizeType pos) {
    if (pos >= size_) {
      throw std::out_of_range("");  // FIXME название
    }

    return arr_[pos];
  }

  ConstReference at(SizeType pos) const {
    if (pos >= size_) {
      throw std::out_of_range("");  // FIXME название
    }

    return arr_[pos];
  }

  Reference front() {
    return arr_[0];
  }

  ConstReference front() const {
    return arr_[0];
  }

  Reference back() {
    return arr_[size_ - 1];
  }

  ConstReference back() const {
    return arr_[size_ - 1];
  }

  Pointer data() {
    return arr_;
  }

  ConstPointer data() const {
    return arr_;
  }

  void swap(vector<T>& other) noexcept {
    this->vector_base::swap(other);  // FIXME Тут точно все в порядке?
  }

  void reserve(std::size_t new_capacity) {  // FIXME тут безопасности исключений нет
    if (new_capacity > capacity_) {
      vector temp(new_capacity, false);

      if constexpr (std::is_trivially_copyable_v<T>) {
        std::memcpy(temp.data(), arr_, size_ * sizeof(T));
        temp.size_ = size_;
      } else {
        while (temp.size_ < size_) {
          if constexpr (std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>) {
            temp.push_back(std::move(arr_[temp.size_]));
          } else {
            temp.push_back(arr_[temp.size_]);
          }
        }
      }

      swap(temp);
    }
  }

  void resize(std::size_t new_size) {
    if (size_ < new_size) {
      static_assert(std::is_default_constructible_v<ValueType>,
                    "ValueType must be default-constructible for Resize(size_t)");

      if (new_size > capacity_) {
        SizeType new_capacity = new_size;

        if (new_capacity > capacity_) {
          vector temp(new_capacity, false);

          if constexpr (std::is_trivially_copyable_v<T>) {
            std::memcpy(temp.data(), arr_, size_ * sizeof(T));
            temp.size_ = size_;
          } else {
            while (temp.size_ < size_) {
              if constexpr (std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>) {
                temp.push_back(std::move(arr_[temp.size_]));
              } else {
                temp.push_back(arr_[temp.size_]);
              }
            }
          }

          while (temp.size_ < new_size) {
            std::construct_at(temp.arr_ + temp.size_);
            ++temp.size_;
          }
          // TODO Можно ли как-то вынести в отдельную функцию??
          swap(temp);
        }
      } else {
        while (size_ < new_size) {
          std::construct_at(arr_ + size_);
          ++size_;
        }
      }
    } else {
      while (size_ > new_size) {
        std::destroy_at(arr_ + size_ - 1);
        --size_;
      }
    }
  }

  void resize(std::size_t new_size, const T& value) {
    if (size_ < new_size) {
      if (new_size > capacity_) {
        SizeType new_capacity = new_size;

        if (new_capacity > capacity_) {
          vector temp(new_capacity, false);

          if constexpr (std::is_trivially_copyable_v<T>) {
            std::memcpy(temp.data(), arr_, size_ * sizeof(T));
            temp.size_ = size_;
          } else {
            while (temp.size_ < size_) {
              if constexpr (std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>) {
                temp.push_back(std::move(arr_[temp.size_]));
              } else {
                temp.push_back(arr_[temp.size_]);
              }
            }
          }

          while (temp.size_ < new_size) {
            std::construct_at(temp.arr_ + temp.size_, value);
            ++temp.size_;
          }
          // TODO Можно ли как-то вынести в отдельную функцию??
          swap(temp);
        }
      } else {
        while (size_ < new_size) {
          std::construct_at(arr_ + size_, value);
          ++size_;
        }
      }
    } else {
      while (size_ > new_size) {
        std::destroy_at(arr_ + size_ - 1);
        --size_;
      }
    }
  }

  void shrink_to_fit() {
    if (capacity_ > size_) {
      vector temp(size_, false);

      if constexpr (std::is_trivially_copyable_v<T>) {
        std::memcpy(temp.data(), arr_, size_ * sizeof(T));
        //TODO нужно повызывать деструкторы для тех, кто остался в arr_???
      } else {
        if constexpr (std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>) {
          std::uninitialized_move(arr_, arr_ + size_, temp.data());
        } else {
          std::uninitialized_copy(arr_, arr_ + size_, temp.data());
        }
      }
      temp.size_ = size_;

      swap(temp);
    }
  }


  void clear() {
    vector<T> temp;
    swap(temp);
  }

  void push_back(const ValueType& value) {
    if (size_ == capacity_) {
      SizeType new_capacity = (capacity_ > 0 ? 2 * capacity_ : 1);

      if (new_capacity > capacity_) {
        vector temp(new_capacity, false);

        if constexpr (std::is_trivially_copyable_v<T>) {
          std::memcpy(temp.data(), arr_, size_ * sizeof(T));
          temp.size_ = size_;
        } else {
          while (temp.size_ < size_) {
            if constexpr (std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>) {
              temp.push_back(std::move(arr_[temp.size_]));
            } else {
              temp.push_back(arr_[temp.size_]);
            }
          }
        }

        std::construct_at(temp.arr_ + temp.size_, value);  // FIXME Мы все помували, а тут исключение в копировании
        ++temp.size_;

        swap(temp);
      }
    } else {
      std::construct_at(arr_ + size_, value);
      ++size_;
    }

    // TODO Тут по идее try-catch с shrink-to-fit без последнего
    // FIXME или не стоит, вдруг при копировании обратно все тоже отвалится, тодга без reserve
  }

  void push_back(T&& value) {
    if (size_ == capacity_) {
      SizeType new_capacity = (capacity_ > 0 ? 2 * capacity_ : 1);

      if (new_capacity > capacity_) {
        vector temp(new_capacity, false);

        if constexpr (std::is_trivially_copyable_v<T>) {
          std::memcpy(temp.data(), arr_, size_ * sizeof(T));
          temp.size_ = size_;
        } else {
          while (temp.size_ < size_) {
            if constexpr (std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_assignable_v<T>) {
              temp.push_back(std::move(arr_[temp.size_]));
            } else {
              temp.push_back(arr_[temp.size_]);
            }
          }
        }

        std::construct_at(temp.arr_ + temp.size_, std::move(value));
        ++temp.size_;

        swap(temp);
      }
    } else {
      std::construct_at(arr_ + size_, std::move(value));
      ++size_;
    }

    // if (size_ == capacity_) {
    //   reserve(capacity_ > 0 ? 2 * capacity_ : 1);
    // }
    //
    // std::construct_at(arr_ + size_, std::move(value));
    // ++size_;
    // TODO Тут по идее try-catch с shrink-to-fit без последнего
    // FIXME или не стоит, вдруг при копировании обратно все тоже отвалится, тодга без reserve
  }

  void pop_back() {
    if (size_ == 0) {
      throw std::range_error("vector pop_back() called on an empty vector");
    }

    --size_;
    std::destroy_at(arr_ + size_);
  }

  template <typename... Arguments>
  void emplace_back(Arguments&&... values) {
    if (size_ == capacity_) {
      reserve(capacity_ > 0 ? 2 * capacity_ : 1);
    }

    std::construct_at(arr_ + size_, ValueType(std::forward<Arguments>(values)...));
    ++size_;
  }

  Pointer begin() {
    return arr_;
  }

  ConstPointer begin() const {
    return arr_;
  }

  Pointer end() {
    return arr_ + size_;
  }

  ConstPointer end() const {
    return arr_ + size_;
  }

  ConstPointer cbegin() const {
    return arr_;
  }

  ConstPointer cend() const {
    return arr_ + size_;
  }

  ReverseIterator rbegin() {
    return std::reverse_iterator<T*>(end());
  }

  ReverseIterator rend() {
    return std::reverse_iterator<T*>(begin());
  }

  ConstReverseIterator rbegin() const {
    return std::reverse_iterator<const T*>(end());
  }

  ConstReverseIterator rend() const {
    return std::reverse_iterator<const T*>(begin());
  }

  ConstReverseIterator crbegin() const {
    return std::reverse_iterator<const T*>(cend());
  }

  ConstReverseIterator crend() const {
    return std::reverse_iterator<const T*>(cbegin());
  }

 private:
  using detail::vector_base<T>::arr_;
  using detail::vector_base<T>::size_;
  using detail::vector_base<T>::capacity_;
};

template <class T>
bool operator<(const vector<T>& first, const vector<T>& second) {
  std::size_t i = 0;
  while (i < first.size() && i < second.size()) {
    if (first[i] != second[i]) {
      return first[i] < second[i];
    }

    ++i;
  }

  return (first.size() < second.size());
}

template <class T>
bool operator>(const vector<T>& first, const vector<T>& second) {
  return (second < first);
}

template <class T>
bool operator==(const vector<T>& first, const vector<T>& second) {
  return !(first < second) && !(second < first);
}

template <class T>
bool operator!=(const vector<T>& first, const vector<T>& second) {
  return ((first < second) || (second < first));
}

template <class T>
bool operator<=(const vector<T>& first, const vector<T>& second) {
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

