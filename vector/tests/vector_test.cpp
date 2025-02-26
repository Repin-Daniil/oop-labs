#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

#include <vector.h>
#include <vector.h>  // check include guards

namespace container {

template <class T>
void Equal(const vector<T>& real, const std::vector<T>& required) {
  REQUIRE(real.size() == required.size());
  for (size_t i = 0u; i < real.size(); ++i) {
    REQUIRE(real[i] == required[i]);
  }
}

TEST_CASE("Member Types", "[vector]") {
  REQUIRE((std::is_same_v<vector<int>::ValueType, int>));
  REQUIRE((std::is_same_v<vector<int>::Pointer, decltype(std::declval<vector<int>>().data())>));
  REQUIRE((std::is_same_v<vector<int>::ConstPointer, decltype(std::declval<const vector<int>>().data())>));
  REQUIRE((std::is_same_v<vector<int>::Reference, decltype(std::declval<vector<int>>()[0])>));
  REQUIRE((std::is_same_v<vector<int>::Reference, decltype(std::declval<vector<int>>().at(0))>));
  REQUIRE((std::is_same_v<vector<int>::Reference, decltype(std::declval<vector<int>>().front())>));
  REQUIRE((std::is_same_v<vector<int>::Reference, decltype(std::declval<vector<int>>().back())>));
  REQUIRE((std::is_same_v<vector<int>::ConstReference, decltype(std::declval<const vector<int>>()[0])>));
  REQUIRE((std::is_same_v<vector<int>::ConstReference, decltype(std::declval<const vector<int>>().at(0))>));
  REQUIRE((std::is_same_v<vector<int>::ConstReference, decltype(std::declval<const vector<int>>().front())>));
  REQUIRE((std::is_same_v<vector<int>::ConstReference, decltype(std::declval<const vector<int>>().back())>));
  REQUIRE((std::is_same_v<vector<int>::SizeType, decltype(std::declval<const vector<int>>().size())>));
  REQUIRE((std::is_same_v<vector<int>::SizeType, decltype(std::declval<const vector<int>>().capacity())>));
}

TEST_CASE("Default", "[Constructor]") {
  const vector<int> v;
  REQUIRE(v.size() == 0u);
  REQUIRE(v.capacity() == 0u);
  REQUIRE(v.data() == nullptr);
  REQUIRE(v.empty());
}

TEST_CASE("Single Parameter", "[Constructor]") {
  {
    const vector<std::string> v(5u);
    Equal(v, std::vector<std::string>(5u));
    REQUIRE(v.capacity() == 5u);
    REQUIRE_FALSE(v.empty());
  }

  {
    const vector<std::unique_ptr<int>> v(200u);
    Equal(v, std::vector<std::unique_ptr<int>>(200u));
    REQUIRE(v.capacity() == 200u);
    REQUIRE_FALSE(v.empty());
  }

  REQUIRE_FALSE((std::is_convertible_v<unsigned, vector<int>>));
}

TEST_CASE("FillInitialization", "[Constructor]") {
  {
    const vector<int> v(0, 5);
    REQUIRE(v.size() == 0u);
    REQUIRE(v.capacity() == 0u);
    REQUIRE(v.data() == nullptr);
  }

  {
    std::string_view filler = "abacababacacabacacbbcabcabracadabra";

    const vector<std::string> v(5u, std::string(filler));
    Equal(v, std::vector<std::string>(5u, std::string(filler)));
    REQUIRE(v.capacity() == 5u);
  }
}

TEST_CASE("Iterators", "[Constructor]") {
  const int arr[] = {1, 2, 3, 4};

  {
    const vector<int> v(arr, arr);
    REQUIRE(v.size() == 0u);
    REQUIRE(v.capacity() == 0u);
    REQUIRE(v.data() == nullptr);
  }

  {
    const vector<int> v(arr + 1, arr + 4);
    Equal(v, std::vector<int>(arr + 1, arr + 4));
  }

  {
    std::vector<std::unique_ptr<int>> p;
    p.push_back(std::make_unique<int>(1));
    p.push_back(std::make_unique<int>(2));

    const vector<std::unique_ptr<int>> v(std::make_move_iterator(p.begin()), std::make_move_iterator(p.end()));
    REQUIRE(*v[0] == 1);
    REQUIRE(*v[1] == 2);
    REQUIRE(p == std::vector<std::unique_ptr<int>>(2));
  }
}

TEST_CASE("InitializerList", "[Constructor]") {
  {
    const vector<int> v{};
    REQUIRE(v.size() == 0u);
    REQUIRE(v.capacity() == 0u);
    REQUIRE(v.data() == nullptr);
  }

  {
    const vector<int> v{1, 2, 3, 4, 5};
    Equal(v, std::vector<int>{1, 2, 3, 4, 5});
  }
}

TEST_CASE("Copy Constructor", "[Constructor]") {
  {
    const vector<int> empty;
    const auto v = empty;
    REQUIRE(empty.size() == 0u);
    REQUIRE(empty.capacity() == 0u);
    REQUIRE(empty.data() == nullptr);
    REQUIRE(v.size() == 0u);
    REQUIRE(v.capacity() == 0u);
    REQUIRE(v.data() == nullptr);
  }

  {
    const vector<std::vector<int>> values{{1, 2}, {3, 4, 5}};
    const auto v = values;
    Equal(v, std::vector<std::vector<int>>{{1, 2}, {3, 4, 5}});
    Equal(values, std::vector<std::vector<int>>{{1, 2}, {3, 4, 5}});
  }
}

TEST_CASE("Move Constructor", "[Constructor]") {
  {
    vector<int> empty;
    const auto v = std::move(empty);
    REQUIRE(empty.size() == 0u);
    REQUIRE(empty.capacity() == 0u);
    REQUIRE(empty.data() == nullptr);
    REQUIRE(v.size() == 0u);
    REQUIRE(v.capacity() == 0u);
    REQUIRE(v.data() == nullptr);
  }

  {
    vector<std::vector<int>> values{{1, 2}, {3, 4, 5}};
    const auto v = std::move(values);
    Equal(v, std::vector<std::vector<int>>{{1, 2}, {3, 4, 5}});
    REQUIRE(values.size() == 0u);
    REQUIRE(values.capacity() == 0u);
    REQUIRE(values.data() == nullptr);
  }
}

TEST_CASE("Copy Assignment", "[Assignment]") {
  SECTION("Empty to empty") {
    const vector<int> empty;
    vector<int> v;
    v = empty;
    REQUIRE(empty.size() == 0u);
    REQUIRE(empty.capacity() == 0u);
    REQUIRE(empty.data() == nullptr);
    REQUIRE(v.size() == 0u);
    REQUIRE(v.capacity() == 0u);
    REQUIRE(v.data() == nullptr);

    v = v;
    REQUIRE(v.size() == 0u);
    REQUIRE(v.capacity() == 0u);
    REQUIRE(v.data() == nullptr);
  }

  SECTION("Empty to filled") {
    const vector<int> empty;
    vector<int> v{1, 2, 3};
    v = empty;
    REQUIRE(empty.size() == 0u);
    REQUIRE(empty.capacity() == 0u);
    REQUIRE(empty.data() == nullptr);
    REQUIRE(v.size() == 0u);
  }

  SECTION("Filled to empty") {
    const vector<int> values{1, 2, 3};
    vector<int> v;
    v = values;
    Equal(v, std::vector<int>{1, 2, 3});
    Equal(values, std::vector<int>{1, 2, 3});

    v = v;
    Equal(v, std::vector<int>{1, 2, 3});
    Equal(values, std::vector<int>{1, 2, 3});
  }

  SECTION("Small to large") {
    vector<int> large(1000, 11);
    const vector<int> small{1, 2, 3};
    large = small;
    Equal(large, std::vector<int>{1, 2, 3});
    Equal(small, std::vector<int>{1, 2, 3});
  }

  SECTION("Large to small") {
    const vector<int> large(1000, 11);
    vector<int> small{1, 2, 3};
    small = large;
    Equal(large, std::vector<int>(1000, 11));
    Equal(small, std::vector<int>(1000, 11));
  }

  SECTION("Deep copy") {
    const vector<std::vector<int>> values{{1, 2}, {3, 4, 5}};
    vector<std::vector<int>> v;
    v = values;
    Equal(v, std::vector<std::vector<int>>{{1, 2}, {3, 4, 5}});
    Equal(values, std::vector<std::vector<int>>{{1, 2}, {3, 4, 5}});

    v = v;
    Equal(v, std::vector<std::vector<int>>{{1, 2}, {3, 4, 5}});
    Equal(values, std::vector<std::vector<int>>{{1, 2}, {3, 4, 5}});
  }
}

TEST_CASE("Move Assignment", "[Assignments]") {
  SECTION("Empty to empty") {
    vector<int> empty;
    vector<int> v;

    v = std::move(empty);
    REQUIRE(empty.size() == 0u);
    REQUIRE(empty.capacity() == 0u);
    REQUIRE(empty.data() == nullptr);
    REQUIRE(v.size() == 0u);
    REQUIRE(v.capacity() == 0u);
    REQUIRE(v.data() == nullptr);

    v = vector<int>{};
    REQUIRE(v.size() == 0u);
    REQUIRE(v.capacity() == 0u);
    REQUIRE(v.data() == nullptr);
  }

  SECTION("Empty to filled") {
    vector<int> empty;
    vector<int> v{1, 2, 3};
    v = std::move(empty);
    REQUIRE(empty.size() == 0u);
    REQUIRE(empty.capacity() == 0u);
    REQUIRE(empty.data() == nullptr);
    REQUIRE(v.size() == 0u);

    v = vector<int>{1, 2, 3};
    v = vector<int>{};
    REQUIRE(v.size() == 0u);
  }

  SECTION("Filled to empty") {
    vector<int> values{1, 2, 3};
    const auto p_values = values.data();
    vector<int> v;
    v = std::move(values);
    Equal(v, std::vector<int>{1, 2, 3});
    REQUIRE(p_values == v.data());
    REQUIRE(values.size() == 0u);
    REQUIRE(values.capacity() == 0u);
    REQUIRE(values.data() == nullptr);

    v = vector<int>{4, 5, 6};
    Equal(v, std::vector<int>{4, 5, 6});
    REQUIRE(p_values != v.data());
  }

  SECTION("Small to large") {
    vector<int> large(1000, 11);
    vector<int> small{1, 2, 3};
    const auto p_small = small.data();
    large = std::move(small);
    Equal(large, std::vector<int>{1, 2, 3});
    REQUIRE(p_small == large.data());
    REQUIRE(small.size() == 0u);
    REQUIRE(small.capacity() == 0u);
    REQUIRE(small.data() == nullptr);
  }

  SECTION("Large to small") {
    vector<int> large(1000, 11);
    vector<int> small{1, 2, 3};
    const auto p_large = large.data();
    small = std::move(large);
    Equal(small, std::vector<int>(1000, 11));
    REQUIRE(p_large == small.data());
    REQUIRE(large.size() == 0u);
    REQUIRE(large.capacity() == 0u);
    REQUIRE(large.data() == nullptr);
  }
}

TEST_CASE("DataAccess", "[Methods]") {
  vector<int> v{1, 2, 3, 4, 5};

  {
    REQUIRE(v.front() == 1);
    v.front() = -1;
    REQUIRE(std::as_const(v).front() == -1);
  }

  {
    REQUIRE(v.back() == 5);
    v.back() = -5;
    REQUIRE(std::as_const(v).back() == -5);
  }

  {
    REQUIRE(v[1] == 2);
    v[1] = -2;
    REQUIRE(std::as_const(v)[1] == -2);
  }

  {
    REQUIRE(v.at(2) == 3);
    v.at(2) = -3;
    REQUIRE(std::as_const(v).at(2) == -3);
    REQUIRE_THROWS_AS(v.at(5), std::out_of_range);                 // NOLINT
    REQUIRE_THROWS_AS(std::as_const(v).at(5), std::out_of_range);  // NOLINT
  }
}

TEST_CASE("Swap", "[DataManipulation]") {
  SECTION("Empty to empty") {
    vector<int> a;
    vector<int> b;
    a.swap(b);
    REQUIRE(a.data() == nullptr);
    REQUIRE(a.size() == 0u);
    REQUIRE(a.capacity() == 0u);
    REQUIRE(b.data() == nullptr);
    REQUIRE(b.size() == 0u);
    REQUIRE(b.capacity() == 0u);
  }

  SECTION("Empty to filled") {
    vector<int> a;
    vector<int> b{1, 2, 3};
    const auto pb = b.data();
    a.swap(b);
    Equal(a, std::vector<int>{1, 2, 3});
    REQUIRE(a.data() == pb);
    REQUIRE(b.data() == nullptr);
    REQUIRE(b.size() == 0u);
    REQUIRE(b.capacity() == 0u);
  }

  SECTION("Small to large") {
    vector<int> large(1000, 11);
    vector<int> small{1, 2, 3};
    const auto p_small = small.data();
    const auto p_large = large.data();
    small.swap(large);
    Equal(small, std::vector<int>(1000, 11));
    Equal(large, std::vector<int>{1, 2, 3});
    REQUIRE(small.data() == p_large);
    REQUIRE(large.data() == p_small);
  }
}

TEST_CASE("Clear", "[DataManipulation]") {
  {
    vector<std::unique_ptr<int>> empty;
    empty.clear();
    REQUIRE(empty.data() == nullptr);
    REQUIRE(empty.size() == 0u);
    REQUIRE(empty.capacity() == 0u);
  }

  {
    vector<int> v(1000, 11);
    v.clear();
    REQUIRE(v.size() == 0u);
    REQUIRE(v.empty());
  }

  {
    vector<std::unique_ptr<int>> v(2);
    v[0] = std::make_unique<int>(1);
    v[1] = std::make_unique<int>(2);
    v.clear();
    REQUIRE(v.size() == 0u);
    REQUIRE(v.empty());
  }
}

TEST_CASE("Resize", "[ReallocationStrategy]") {
  {
    vector<std::unique_ptr<int>> v;
    v.resize(0u);
    REQUIRE(v.data() == nullptr);
    REQUIRE(v.size() == 0u);
    REQUIRE(v.capacity() == 0u);
  }

  {
    vector<std::unique_ptr<int>> v;
    v.resize(5u);
    Equal(v, std::vector<std::unique_ptr<int>>(5u));
    REQUIRE(v.capacity() >= 5u);
    REQUIRE(v.capacity() <= 10u);
  }

  {
    vector<int> v;
    v.resize(5u, 11);
    Equal(v, std::vector<int>(5u, 11));
    REQUIRE(v.capacity() >= 5u);
    REQUIRE(v.capacity() <= 10u);
  }

  {
    vector<int> v(10u, 5);
    const auto pv = v.data();
    v.resize(10u);
    Equal(v, std::vector<int>(10, 5));
    REQUIRE(pv == v.data());
  }

  {
    vector<std::unique_ptr<int>> v(100);
    for (int i = 0; i < 100; ++i) {
      v[i] = std::make_unique<int>(i);
    }
    REQUIRE(v.capacity() < 1000u);
    v.resize(1000);

    REQUIRE(v.size() == 1000u);
    REQUIRE(v.capacity() >= 1000u);
    REQUIRE(v.capacity() <= 2000u);
    for (int i = 0; i < 100; ++i) {
      REQUIRE(*v[i] == i);
    }
    for (int i = 100; i < 1000; ++i) {
      REQUIRE(v[i] == nullptr);
    }
  }

  {
    vector<int> v(100u, 11);
    REQUIRE(v.capacity() < 1000u);
    v.resize(1000u, -11);

    REQUIRE(v.size() == 1000u);
    REQUIRE(v.capacity() >= 1000u);
    REQUIRE(v.capacity() <= 2000u);
    for (int i = 0; i < 100; ++i) {
      REQUIRE(v[i] == 11);
    }
    for (int i = 100; i < 1000; ++i) {
      REQUIRE(v[i] == -11);
    }
  }

  {
    vector<int> v(1000u, 11);
    const auto pv = v.data();

    v.resize(400u, -1);
    Equal(v, std::vector<int>(400u, 11));
    REQUIRE(pv == v.data());

    v.resize(100u);
    Equal(v, std::vector<int>(100u, 11));
    REQUIRE(pv == v.data());

    v.resize(500u, -11);
    for (int i = 0; i < 100; ++i) {
      REQUIRE(v[i] == 11);
    }
    for (int i = 100; i < 500; ++i) {
      REQUIRE(v[i] == -11);
    }
    REQUIRE(v.size() == 500u);
    REQUIRE(pv == v.data());

    v.resize(750);
    for (int i = 0; i < 100; ++i) {
      REQUIRE(v[i] == 11);
    }
    for (int i = 100; i < 500; ++i) {
      REQUIRE(v[i] == -11);
    }
    REQUIRE(v.size() == 750u);
    REQUIRE(pv == v.data());
  }
}

TEST_CASE("Reserve", "[ReallocationStrategy]") {
  {
    vector<std::unique_ptr<int>> v;
    v.reserve(0u);
    REQUIRE(v.data() == nullptr);
    REQUIRE(v.size() == 0u);
    REQUIRE(v.capacity() == 0u);
  }

  {
    vector<int> empty;
    empty.reserve(10u);
    Equal(empty, std::vector<int>{});
    REQUIRE(empty.capacity() >= 10u);
    REQUIRE(empty.data() != nullptr);
  }

  {
    vector<std::unique_ptr<int>> empty;
    empty.reserve(10u);
    Equal(empty, std::vector<std::unique_ptr<int>>{});
    REQUIRE(empty.capacity() >= 10u);
    REQUIRE(empty.data() != nullptr);
  }

  {
    vector<int> v(10u, 5);
    const auto pv = v.data();

    v.reserve(10u);
    Equal(v, std::vector<int>(10u, 5));
    REQUIRE(pv == v.data());

    v.reserve(5u);
    Equal(v, std::vector<int>(10u, 5));
    REQUIRE(pv == v.data());
  }

  {
    vector<std::unique_ptr<int>> v(100u);
    for (int i = 0; i < 100; ++i) {
      v[i] = std::make_unique<int>(i);
    }
    REQUIRE(v.capacity() < 1000u);
    v.reserve(1000u);

    REQUIRE(v.size() == 100u);
    REQUIRE(v.capacity() >= 1000u);
    REQUIRE(v.capacity() <= 2000u);
    for (int i = 0; i < 100; ++i) {
      REQUIRE(*v[i] == i);
    }
  }
}

TEST_CASE("ShrinkToFit", "[ReallocationStrategy]") {
  {
    vector<int> empty;
    empty.shrink_to_fit();
    REQUIRE(empty.data() == nullptr);
    REQUIRE(empty.size() == 0u);
    REQUIRE(empty.capacity() == 0u);
  }

  {
    vector<std::unique_ptr<int>> empty;
    empty.reserve(10u);
    empty.shrink_to_fit();
    REQUIRE(empty.data() == nullptr);
    REQUIRE(empty.size() == 0u);
    REQUIRE(empty.capacity() == 0u);
  }

  {
    vector<std::unique_ptr<int>> v(16u);
    for (int i = 0; i < 16; ++i) {
      v[i] = std::make_unique<int>(i);
    }
    v.reserve(100u);
    v.shrink_to_fit();
    for (int i = 0; i < 16; ++i) {
      REQUIRE(*v[i] == i);
    }
    REQUIRE(v.size() == 16u);
    REQUIRE(v.capacity() == 16u);
  }

  {
    vector<int> v(10u, 10);
    v.reserve(1000u);
    const auto pv = v.data();
    v.shrink_to_fit();
    Equal(v, std::vector<int>(10u, 10));
    REQUIRE(v.capacity() == 10u);
    REQUIRE(pv != v.data());
  }
}

TEST_CASE("PushBack", "[ReallocationStrategy]") {
  {
    vector<std::unique_ptr<int>> v;
    for (int i = 0; i < 100; ++i) {
      v.push_back(std::make_unique<int>(i));
      REQUIRE(v.size() == static_cast<unsigned>(i + 1));
      REQUIRE(v.capacity() >= v.size());
      REQUIRE(v.capacity() <= 2 * v.size());
    }
    for (int i = 0; i < 100; ++i) {
      REQUIRE(*v[i] == i);
    }
  }

  {
    vector<int> v(10u);
    for (int i = 0; i < 10; ++i) {
      v[i] = i;
    }
    for (int i = 10; i < 100; ++i) {
      v.push_back(i);
      REQUIRE(v.size() == static_cast<unsigned>(i + 1));
      REQUIRE(v.capacity() >= v.size());
      REQUIRE(v.capacity() <= 2 * v.size());
    }
    for (int i = 0; i < 100; ++i) {
      REQUIRE(v[i] == i);
    }
  }
}

TEST_CASE("PopBack", "[ReallocationStrategy]") {
  {
    vector<std::unique_ptr<int>> v;
    for (int i = 0; i < 100; ++i) {
      v.push_back(std::make_unique<int>(i));
    }
    const auto capacity = v.capacity();
    for (int i = 0; i < 50; ++i) {
      v.pop_back();
      REQUIRE(v.size() == static_cast<unsigned>(100 - i - 1));
    }
    REQUIRE(capacity == v.capacity());
    for (int i = 0; i < 50; ++i) {
      REQUIRE(*v[i] == i);
    }
  }

  {
    vector<int> v(10u);
    for (int i = 0; i < 10; ++i) {
      v[i] = i;
    }
    for (int i = 10; i < 100; ++i) {
      v.push_back(i);
    }
    const auto capacity = v.capacity();
    for (int i = 0; i < 50; ++i) {
      v.pop_back();
      REQUIRE(v.size() == static_cast<unsigned>(100 - i - 1));
    }
    REQUIRE(capacity == v.capacity());
    for (int i = 0; i < 50; ++i) {
      REQUIRE(v[i] == i);
    }
  }
}

TEST_CASE("Stress", "[ReallocationStrategy]") {
  vector<std::unique_ptr<int>> v;
  for (int i = 0; i < 1'000'000; ++i) {
    v.push_back(std::make_unique<int>(i));
    REQUIRE(v.size() == static_cast<unsigned>(i + 1));
    REQUIRE(v.capacity() >= v.size());
    REQUIRE(v.capacity() <= 2 * v.size());
  }
  const auto capacity = v.capacity();
  for (int i = 0; i < 500'000; ++i) {
    v.pop_back();
    REQUIRE(v.size() == static_cast<unsigned>(1'000'000 - i - 1));
  }
  REQUIRE(capacity == v.capacity());
  for (int i = 0; i < 500'000; ++i) {
    REQUIRE(*v[i] == i);
  }
}

template <class T>
void CheckComparisonEqual(const vector<T>& lhs, const vector<T>& rhs) {
  REQUIRE(lhs == rhs);
  REQUIRE(lhs <= rhs);
  REQUIRE(lhs >= rhs);
  REQUIRE_FALSE(lhs != rhs);
  REQUIRE_FALSE(lhs < rhs);
  REQUIRE_FALSE(lhs > rhs);
}

template <class T>
void CheckComparisonLess(const vector<T>& lhs, const vector<T>& rhs) {
  REQUIRE_FALSE(lhs == rhs);
  REQUIRE(lhs <= rhs);
  REQUIRE_FALSE(lhs >= rhs);
  REQUIRE(lhs != rhs);
  REQUIRE(lhs < rhs);
  REQUIRE_FALSE(lhs > rhs);
}

template <class T>
void CheckComparisonGreater(const vector<T>& lhs, const vector<T>& rhs) {
  REQUIRE_FALSE(lhs == rhs);
  REQUIRE_FALSE(lhs <= rhs);
  REQUIRE(lhs >= rhs);
  REQUIRE(lhs != rhs);
  REQUIRE_FALSE(lhs < rhs);
  REQUIRE(lhs > rhs);
}

TEST_CASE("Comparisons", "[vector]") {
  {
    vector<int> a;
    vector<int> b;
    CheckComparisonEqual(a, b);
  }

  {
    vector<int> a;
    vector<int> b(1, 2);
    CheckComparisonLess(a, b);
    CheckComparisonGreater(b, a);
  }

  {
    vector<int> a{1, 3};
    vector<int> b{2};
    CheckComparisonLess(a, b);
    CheckComparisonGreater(b, a);
  }

  {
    vector<int> a{1, 2, 3};
    vector<int> b{1, 1};
    CheckComparisonLess(b, a);
    CheckComparisonGreater(a, b);
  }

  {
    vector<int> a{1, 2, 3, 4};
    vector<int> b{1, 2, 3, 4};
    CheckComparisonEqual(a, b);
  }

  {
    vector<int> a{1, 2, 3, 4};
    vector<int> b{1, 2, 3};
    CheckComparisonLess(b, a);
    CheckComparisonGreater(a, b);
  }

  {
    vector<int> a{1, 4, 6, 8};
    vector<int> b{2, 3, 5, 7};
    CheckComparisonLess(a, b);
    CheckComparisonGreater(b, a);
  }

  {
    vector<int> a{1, 2, 3, 5};
    vector<int> b{1, 2, 4, 5};
    CheckComparisonLess(a, b);
    CheckComparisonGreater(b, a);
  }
}

TEST_CASE("Iterator", "[Iterators]") {
  {
    using Iterator = vector<int>::Iterator;
    REQUIRE((std::is_same_v<Iterator, decltype(std::declval<vector<int>>().begin())>));
    REQUIRE((std::is_same_v<Iterator, decltype(std::declval<vector<int>>().end())>));

    using Traits = std::iterator_traits<Iterator>;
    REQUIRE((std::is_same_v<Traits::value_type, int>));
    REQUIRE((std::is_same_v<Traits::reference, decltype(*std::declval<Iterator>())>));
    REQUIRE((std::is_base_of_v<std::random_access_iterator_tag, Traits::iterator_category>));
  }

  {
    vector<int> v(10u);
    int i = 0;
    for (auto& x : v) {
      x = ++i;
    }
    i = 0;
    for (auto& x : v) {
      REQUIRE(x == ++i);
    }
  }

  {
    vector<int> v(10u, -1);
    std::fill(v.begin() + 5, v.end(), 1);
    for (int i = 0; i < 5; ++i) {
      REQUIRE(v[i] == -1);
    }
    for (int i = 5; i < 10; ++i) {
      REQUIRE(v[i] == 1);
    }
  }
}

TEST_CASE("ConstIterator", "[Iterators]") {
  {
    using ConstIterator = vector<int>::ConstIterator;
    REQUIRE((std::is_same_v<ConstIterator, decltype(std::declval<vector<int>>().cbegin())>));
    REQUIRE((std::is_same_v<ConstIterator, decltype(std::declval<vector<int>>().cend())>));
    REQUIRE((std::is_same_v<ConstIterator, decltype(std::declval<const vector<int>>().begin())>));
    REQUIRE((std::is_same_v<ConstIterator, decltype(std::declval<const vector<int>>().end())>));

    using Traits = std::iterator_traits<ConstIterator>;
    REQUIRE((std::is_same_v<Traits::value_type, int>));
    REQUIRE((std::is_same_v<Traits::reference, decltype(*std::declval<ConstIterator>())>));
    REQUIRE((std::is_base_of_v<std::random_access_iterator_tag, Traits::iterator_category>));
  }

  {
    vector<int> v(10u);
    int i = 0;
    for (auto& x : v) {
      x = ++i;
    }

    i = 0;
    for (auto& x : std::as_const(v)) {
      REQUIRE(x == ++i);
    }

    i = 0;
    for (auto it = v.cbegin(); it != v.cend(); ++it) {
      REQUIRE(*it == ++i);
    }
  }
}

TEST_CASE("ReverseIterator", "[Iterators]") {
  {
    using ReverseIterator = vector<int>::ReverseIterator;
    REQUIRE((std::is_same_v<ReverseIterator, decltype(std::declval<vector<int>>().rbegin())>));
    REQUIRE((std::is_same_v<ReverseIterator, decltype(std::declval<vector<int>>().rend())>));
    REQUIRE((std::is_same_v<ReverseIterator, std::reverse_iterator<vector<int>::Iterator>>));

    using Traits = std::iterator_traits<ReverseIterator>;
    REQUIRE((std::is_same_v<Traits::value_type, int>));
    REQUIRE((std::is_same_v<Traits::reference, decltype(*std::declval<ReverseIterator>())>));
    REQUIRE((std::is_base_of_v<std::random_access_iterator_tag, Traits::iterator_category>));
  }

  {
    vector<int> v(10u);
    int i = 0;
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
      *it = ++i;
    }
    i = 11;
    for (auto& x : v) {
      REQUIRE(x == --i);
    }
  }

  {
    vector<int> v(10u, -1);
    std::fill(v.rbegin() + 5, v.rend(), 1);
    for (int i = 0; i < 5; ++i) {
      REQUIRE(v[i] == 1);
    }
    for (int i = 5; i < 10; ++i) {
      REQUIRE(v[i] == -1);
    }
  }
}

TEST_CASE("ConstReverseIterator", "[Iterators]") {
  {
    using ConstReverseIterator = vector<int>::ConstReverseIterator;
    REQUIRE((std::is_same_v<ConstReverseIterator, decltype(std::declval<vector<int>>().crbegin())>));
    REQUIRE((std::is_same_v<ConstReverseIterator, decltype(std::declval<vector<int>>().crend())>));
    REQUIRE((std::is_same_v<ConstReverseIterator, decltype(std::declval<const vector<int>>().rbegin())>));
    REQUIRE((std::is_same_v<ConstReverseIterator, decltype(std::declval<const vector<int>>().rend())>));
    REQUIRE((std::is_same_v<ConstReverseIterator, std::reverse_iterator<vector<int>::ConstIterator>>));

    using Traits = std::iterator_traits<ConstReverseIterator>;
    REQUIRE((std::is_same_v<Traits::value_type, int>));
    REQUIRE((std::is_same_v<Traits::reference, decltype(*std::declval<ConstReverseIterator>())>));
    REQUIRE((std::is_base_of_v<std::random_access_iterator_tag, Traits::iterator_category>));
  }

  {
    vector<int> v(10u);
    int i = 0;
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
      *it = ++i;
    }

    i = 0;
    for (auto it = std::as_const(v).rbegin(); it != std::as_const(v).rend(); ++it) {
      REQUIRE(*it == ++i);
    }

    i = 0;
    for (auto it = v.crbegin(); it != v.crend(); ++it) {
      REQUIRE(*it == ++i);
    }
  }
}

class Exception {};

class Throwable {
  std::unique_ptr<int> p_ = std::make_unique<int>();  // check d-tor is called

 public:
  static int until_throw;

  Throwable() {
    --until_throw;
    if (until_throw <= 0) {
      throw Exception{};
    }
  }

  Throwable(const Throwable&) : Throwable() {
  }

  Throwable(Throwable&&) noexcept = default;

  Throwable& operator=(const Throwable&) {
    --until_throw;
    if (until_throw <= 0) {
      throw Exception{};
    }
    return *this;
  }

  Throwable& operator=(Throwable&&) noexcept = default;
};

int Throwable::until_throw = 0;

TEST_CASE("Size Constructor", "[Safety]") {
  Throwable::until_throw = 5;
  REQUIRE_THROWS_AS(vector<Throwable>(10u), Exception);  // NOLINT
}

TEST_CASE("Value Constructor", "[Safety]") {
  Throwable::until_throw = 5;
  REQUIRE_THROWS_AS(vector<Throwable>(10u, Throwable{}), Exception);  // NOLINT

  try {  // no memory management case
    Throwable::until_throw = 15;
    vector<Throwable> v(10u, Throwable{});
  } catch (Exception) {
  }
}

TEST_CASE("Iterators Constructor", "[Safety]") {
  Throwable::until_throw = 210;
  const std::vector<Throwable> values(100u, Throwable{});
  Throwable::until_throw = 50;
  REQUIRE_THROWS_AS(vector<Throwable>(values.begin(), values.end()), Exception);  // NOLINT

  try {  // no memory management case
    Throwable::until_throw = 150;
    vector<Throwable> v(values.begin(), values.end());
  } catch (Exception) {
  }
}

TEST_CASE("Initializer List Constructor", "[Safety]") {
  Throwable::until_throw = 6;
  REQUIRE_THROWS_AS(vector<Throwable>({Throwable{}, Throwable{}, Throwable{}, Throwable{}}), Exception);  // NOLINT

  try {  // no memory management case
    Throwable::until_throw = 10;
    vector<Throwable> v({Throwable{}, Throwable{}, Throwable{}, Throwable{}});
  } catch (Exception) {
  }
}

TEST_CASE("Copy Constructor Safety", "[Safety]") {
  Throwable::until_throw = 210;
  const vector<Throwable> values(100u, Throwable{});
  Throwable::until_throw = 50;
  REQUIRE_THROWS_AS(vector<Throwable>(values), Exception);  // NOLINT

  try {  // no memory management case
    Throwable::until_throw = 150;
    vector<Throwable> v(values);
  } catch (Exception) {
  }
}

TEST_CASE("Move Constructor Safety", "[Safety]") {
  Throwable::until_throw = 210;
  vector<Throwable> values(100u, Throwable{});
  Throwable::until_throw = 1;
  REQUIRE_NOTHROW(vector<Throwable>(std::move(values)));  // NOLINT
}

TEST_CASE("Copy Assignment Safety", "[Safety]") {
  {
    Throwable::until_throw = 12;
    const vector<Throwable> values(5u);

    vector<Throwable> v;
    Throwable::until_throw = 3;
    REQUIRE_THROWS_AS(v = values, Exception);  // NOLINT
    REQUIRE(v.capacity() >= v.size());

    try {  // no memory management case
      vector<Throwable> vv;
      Throwable::until_throw = 8;
      vv = values;
    } catch (Exception) {
    }
  }

  {
    Throwable::until_throw = 100;
    const vector<Throwable> values(10u);
    vector<Throwable> v(35u);
    Throwable::until_throw = 5;
    REQUIRE_THROWS_AS(v = values, Exception);  // NOLINT
    REQUIRE(v.capacity() >= v.size());
  }
}

TEST_CASE("Move Assignment Safety", "[Safety]") {
  {
    Throwable::until_throw = 12;
    vector<Throwable> values(5u);
    vector<Throwable> v;
    Throwable::until_throw = 1;
    REQUIRE_NOTHROW(v = std::move(values));  // NOLINT
  }

  {
    Throwable::until_throw = 100;
    vector<Throwable> values(10u);
    vector<Throwable> v(35u);
    Throwable::until_throw = 1;
    REQUIRE_NOTHROW(v = std::move(values));  // NOLINT
  }
}

TEST_CASE("Swap Safety", "[Safety]") {
  Throwable::until_throw = 12;
  vector<Throwable> values(5u);
  vector<Throwable> v;
  Throwable::until_throw = 1;
  REQUIRE_NOTHROW(v.swap(values));  // NOLINT
}

TEST_CASE("Resize Safety", "[Safety]") {
  Throwable::until_throw = 200;
  vector<Throwable> v(90u);
  const auto capacity = v.capacity();
  const auto data = v.data();

  REQUIRE_NOTHROW(v.resize(90u));  // NOLINT
  REQUIRE_NOTHROW(v.resize(50u));  // NOLINT
  REQUIRE_NOTHROW(v.resize(10u));  // NOLINT

  Throwable::until_throw = 10;
  REQUIRE_THROWS_AS(v.resize(200u), Exception);  // NOLINT
  REQUIRE(v.size() == 10u);
  REQUIRE(v.capacity() == capacity);
  REQUIRE(v.data() == data);

  try {  // no memory management case
    Throwable::until_throw = 300;
    v.resize(200, {});
  } catch (Exception) {
    REQUIRE(v.size() == 10u);
    REQUIRE(v.capacity() == capacity);
    REQUIRE(v.data() == data);
  }
}

TEST_CASE("Reserve Safety", "[Safety]") {
  Throwable::until_throw = 55;
  vector<Throwable> v(10u);
  REQUIRE_NOTHROW(v.reserve(30u));  // NOLINT

  const auto capacity = v.capacity();
  const auto size = v.size();
  const auto data = v.data();
  try {  // no memory management case
    Throwable::until_throw = 30;
    v.reserve(100u);
  } catch (Exception) {
    REQUIRE(v.capacity() == capacity);
    REQUIRE(v.size() == size);
    REQUIRE(v.data() == data);
  }
}

TEST_CASE("ShrinkToFit Safety", "[Safety]") {
  Throwable::until_throw = 95;
  vector<Throwable> v(20u);
  v.reserve(30u);
  REQUIRE_NOTHROW(v.shrink_to_fit());  // NOLINT

  v.resize(10);
  const auto capacity = v.capacity();
  const auto size = v.size();
  const auto data = v.data();
  try {  // no memory management case
    Throwable::until_throw = 5;
    v.shrink_to_fit();
  } catch (Exception) {
    REQUIRE(v.capacity() == capacity);
    REQUIRE(v.size() == size);
    REQUIRE(v.data() == data);
  }
}

TEST_CASE("PushBack Safety", "[Safety]") {
  Throwable::until_throw = 200;
  vector<Throwable> v;
  v.reserve(100u);
  const auto capacity = v.capacity();
  const auto data = v.data();
  Throwable::until_throw = static_cast<int>(capacity) + 2;
  for (size_t i = 0; i < capacity; ++i) {
    v.push_back({});
  }
  const Throwable object;
  REQUIRE_THROWS_AS(v.push_back(object), Exception);  // NOLINT
  REQUIRE(v.size() == capacity);
  REQUIRE(v.capacity() == capacity);
  REQUIRE(v.data() == data);

  try {  // no memory management case
    Throwable::until_throw = static_cast<int>(2 * capacity) + 1;
    v.push_back(object);
  } catch (...) {
    REQUIRE(v.size() == capacity);
    REQUIRE(v.capacity() == capacity);
    REQUIRE(v.data() == data);
  }
}

#ifdef VECTOR_MEMORY_IMPLEMENTED

struct InstanceCounter {
  static size_t counter;

  InstanceCounter() noexcept {
    ++counter;
  }

  InstanceCounter(const InstanceCounter&) : InstanceCounter() {
  }

  InstanceCounter(InstanceCounter&&) : InstanceCounter() {
  }

  InstanceCounter& operator=(const InstanceCounter&) = default;
  InstanceCounter& operator=(InstanceCounter&&) noexcept = default;

  ~InstanceCounter() {
    --counter;
  }
};

size_t InstanceCounter::counter = 0u;

TEST_CASE("ConstructorsAndDestructors", "[Memory]") {
  InstanceCounter::counter = 0u;

  SECTION("Default Constructor") {
    const vector<InstanceCounter> v;
    REQUIRE(InstanceCounter::counter == 0u);
  }

  SECTION("Size Constructor") {
    const vector<InstanceCounter> v(10u);
    REQUIRE(InstanceCounter::counter == 10u);
  }

  SECTION("Size-Value Constructor") {
    const vector<InstanceCounter> v(10u, InstanceCounter{});
    REQUIRE(InstanceCounter::counter == 10u);
  }

  SECTION("Iterators Constructor") {
    const std::vector<InstanceCounter> values(100u);
    const vector<InstanceCounter> v(values.begin(), values.end());
    REQUIRE(InstanceCounter::counter == 200u);
  }

  SECTION("Initializer List Constructor") {
    const vector<InstanceCounter> v{InstanceCounter{}, InstanceCounter{}, InstanceCounter{}};
    REQUIRE(InstanceCounter::counter == 3u);
  }

  SECTION("Copy Constructor") {
    const vector<InstanceCounter> values(100u);
    const auto v = values;
    REQUIRE(InstanceCounter::counter == 200u);
  }

  SECTION("Move Constructor") {
    vector<InstanceCounter> values(100u);
    const auto v = std::move(values);
    REQUIRE(InstanceCounter::counter == 100u);
  }

  REQUIRE(InstanceCounter::counter == 0u);
}

TEST_CASE("Assignment Memory", "[Memory]") {
  InstanceCounter::counter = 0u;

  SECTION("Copy Assignment") {
    {
      const vector<InstanceCounter> values(10u);
      vector<InstanceCounter> v(100u);
      v = values;
      REQUIRE(InstanceCounter::counter == 20u);
    }
    REQUIRE(InstanceCounter::counter == 0u);

    {
      const vector<InstanceCounter> values(100u);
      vector<InstanceCounter> v(10u);
      v = values;
      REQUIRE(InstanceCounter::counter == 200u);
    }
  }

  SECTION("Move Assignment") {
    {
      vector<InstanceCounter> values(10u);
      vector<InstanceCounter> v(100u);
      v = std::move(values);
      REQUIRE(InstanceCounter::counter == 10u);
    }
    REQUIRE(InstanceCounter::counter == 0u);

    {
      vector<InstanceCounter> values(100u);
      vector<InstanceCounter> v(10u);
      v = std::move(values);
      REQUIRE(InstanceCounter::counter == 100u);
    }
  }

  REQUIRE(InstanceCounter::counter == 0u);
}

TEST_CASE("Swap Memory", "[Memory]") {
  InstanceCounter::counter = 0u;

  {
    vector<InstanceCounter> a;
    vector<InstanceCounter> b(10u);
    a.swap(b);
    REQUIRE(InstanceCounter::counter == 10u);
  }
  REQUIRE(InstanceCounter::counter == 0u);

  {
    vector<InstanceCounter> a(20u);
    vector<InstanceCounter> b(10u);
    a.swap(b);
    REQUIRE(InstanceCounter::counter == 30u);
  }
  REQUIRE(InstanceCounter::counter == 0u);
}

TEST_CASE("Clear Memory", "[Memory]") {
  InstanceCounter::counter = 0u;

  vector<InstanceCounter> v(10u);
  v.clear();
  REQUIRE(InstanceCounter::counter == 0u);
}

TEST_CASE("Resize Memory", "[Memory]") {
  InstanceCounter::counter = 0u;

  {
    vector<InstanceCounter> v;
    v.resize(100u);
    REQUIRE(InstanceCounter::counter == 100u);
    v.resize(10u);
    REQUIRE(InstanceCounter::counter == 10u);
    v.resize(1000u);
    REQUIRE(InstanceCounter::counter == 1000u);
  }
  REQUIRE(InstanceCounter::counter == 0u);

  {
    vector<InstanceCounter> v;
    v.resize(100u, InstanceCounter{});
    REQUIRE(InstanceCounter::counter == 100u);
    v.resize(10u, InstanceCounter{});
    REQUIRE(InstanceCounter::counter == 10u);
    v.resize(1000u, InstanceCounter{});
    REQUIRE(InstanceCounter::counter == 1000u);
  }
  REQUIRE(InstanceCounter::counter == 0u);
}

TEST_CASE("Reserve Memory", "[Memory]") {
  InstanceCounter::counter = 0u;

  {
    vector<InstanceCounter> v;
    v.reserve(100u);
    REQUIRE(InstanceCounter::counter == 0u);
    v.resize(10u);
    REQUIRE(InstanceCounter::counter == 10u);
    v.reserve(1000u);
    REQUIRE(InstanceCounter::counter == 10u);
    v.resize(100u);
    REQUIRE(InstanceCounter::counter == 100u);
  }
  REQUIRE(InstanceCounter::counter == 0u);
}

TEST_CASE("ShrinkToFit Memory", "[Memory]") {
  InstanceCounter::counter = 0u;
  auto& counter_ref = InstanceCounter::counter;

  {
    vector<InstanceCounter> v;
    v.reserve(100u);
    REQUIRE(InstanceCounter::counter == 0u);
    v.resize(10u);
    REQUIRE(InstanceCounter::counter == 10u);
    v.shrink_to_fit();
    REQUIRE(InstanceCounter::counter == 10u);

    v.reserve(1000u);
    REQUIRE(InstanceCounter::counter == 10u);
    v.resize(100u);
    REQUIRE(InstanceCounter::counter == 100u);
    v.shrink_to_fit();
    REQUIRE(InstanceCounter::counter == 100u);
  }
  REQUIRE(InstanceCounter::counter == 0u);
}

TEST_CASE("PushBack Memory", "[Memory]") {
  InstanceCounter::counter = 0u;

  {
    vector<InstanceCounter> v;
    for (size_t i = 0; i < 100; ++i) {
      v.push_back({});
      REQUIRE(InstanceCounter::counter == (i + 1));
    }
  }
  REQUIRE(InstanceCounter::counter == 0u);

  {
    vector<InstanceCounter> v;
    InstanceCounter obj;
    for (size_t i = 0; i < 100; ++i) {
      v.push_back(obj);
      REQUIRE(InstanceCounter::counter == (i + 2));
    }
  }
  REQUIRE(InstanceCounter::counter == 0u);
}

TEST_CASE("EmplaceBack Memory", "[Memory]") {
  InstanceCounter::counter = 0u;

  {
    vector<InstanceCounter> v;
    for (size_t i = 0; i < 100; ++i) {
      v.emplace_back();
      REQUIRE(InstanceCounter::counter == (i + 1));
    }
  }
  REQUIRE(InstanceCounter::counter == 0u);

  {
    vector<std::vector<int>> v;
    for (size_t i = 0; i < 10; ++i) {
      v.emplace_back();
      REQUIRE(v.size() == static_cast<unsigned>(i + 1));
      REQUIRE(v.capacity() >= v.size());
      REQUIRE(v.capacity() <= 2 * v.size());
      REQUIRE(v.back().empty());
    }
    for (size_t i = 10; i < 30; ++i) {
      v.emplace_back(10);
      REQUIRE(v.size() == static_cast<unsigned>(i + 1));
      REQUIRE(v.capacity() >= v.size());
      REQUIRE(v.capacity() <= 2 * v.size());
      REQUIRE(v.back().size() == 10u);
    }
    for (size_t i = 30; i < 70; ++i) {
      v.emplace_back(11, -11);
      REQUIRE(v.size() == static_cast<unsigned>(i + 1));
      REQUIRE(v.capacity() >= v.size());
      REQUIRE(v.capacity() <= 2 * v.size());
      REQUIRE(v.back() == std::vector<int>(11, -11));
    }
  }
}

TEST_CASE("PopBack Memory", "[Memory]") {
  InstanceCounter::counter = 0u;

  {
    vector<InstanceCounter> v;
    for (int i = 0; i < 100; ++i) {
      v.push_back({});
    }
    for (int i = 0; i < 50; ++i) {
      v.pop_back();
      REQUIRE(InstanceCounter::counter == static_cast<unsigned>(100 - i - 1));
    }
  }
  REQUIRE(InstanceCounter::counter == 0u);
}

#endif
}  // namespace container