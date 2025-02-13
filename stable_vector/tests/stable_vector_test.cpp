#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <string_view>
#include <vector>
#include <type_traits>

#include <stable_vector.h>
#include <stable_vector.h> // check include guards

namespace container {

  template <class T>
  void Equal(const stable_vector<T>& real, const std::vector<T>& required) {
    REQUIRE(real.Size() == required.size());
    for (size_t i = 0u; i < real.Size(); ++i) {
      REQUIRE(real[i] == required[i]);
    }
  }

//TODO нужны тесты на отсутствие реаоллокаций (передать тип NonCopyable)
  //TODO нужны тесты на делитер
  //TODO тесты на пуш в начало

  TEST_CASE("Member Types", "[stable_vector]") {
    REQUIRE((std::is_same_v<stable_vector<int>::ValueType, int>));
    REQUIRE((std::is_same_v<stable_vector<int>::Pointer, decltype(std::declval<stable_vector<int>>().Data())>));
    REQUIRE((std::is_same_v<stable_vector<int>::ConstPointer, decltype(std::declval<const stable_vector<int>>().Data())>));
    REQUIRE((std::is_same_v<stable_vector<int>::Reference, decltype(std::declval<stable_vector<int>>()[0])>));
    REQUIRE((std::is_same_v<stable_vector<int>::Reference, decltype(std::declval<stable_vector<int>>().At(0))>));
    REQUIRE((std::is_same_v<stable_vector<int>::Reference, decltype(std::declval<stable_vector<int>>().Front())>));
    REQUIRE((std::is_same_v<stable_vector<int>::Reference, decltype(std::declval<stable_vector<int>>().Back())>));
    REQUIRE((std::is_same_v<stable_vector<int>::ConstReference, decltype(std::declval<const stable_vector<int>>()[0])>));
    REQUIRE((std::is_same_v<stable_vector<int>::ConstReference, decltype(std::declval<const stable_vector<int>>().At(0))>));
    REQUIRE((std::is_same_v<stable_vector<int>::ConstReference, decltype(std::declval<const stable_vector<int>>().Front())>));
    REQUIRE((std::is_same_v<stable_vector<int>::ConstReference, decltype(std::declval<const stable_vector<int>>().Back())>));
    REQUIRE((std::is_same_v<stable_vector<int>::SizeType, decltype(std::declval<const stable_vector<int>>().Size())>));
    REQUIRE((std::is_same_v<stable_vector<int>::SizeType, decltype(std::declval<const stable_vector<int>>().Capacity())>));
  }

  TEST_CASE("Default", "[Constructor]") {
    const stable_vector<int> v;
    REQUIRE(v.Size() == 0u);
    REQUIRE(v.Capacity() == 0u);
    REQUIRE(v.Data() == nullptr);
    REQUIRE(v.Empty());
  }

  TEST_CASE("Single Parameter", "[Constructor]") {
    {
      const stable_vector<std::string> v(5u);
      Equal(v, std::vector<std::string>(5u));
      REQUIRE(v.Capacity() == 5u);
      REQUIRE_FALSE(v.Empty());
    }

    {
      const stable_vector<std::unique_ptr<int>> v(200u);
      Equal(v, std::vector<std::unique_ptr<int>>(200u));
      REQUIRE(v.Capacity() == 200u);
      REQUIRE_FALSE(v.Empty());
    }

    REQUIRE_FALSE((std::is_convertible_v<unsigned, stable_vector<int>>));
  }

  TEST_CASE("FillInitialization", "[Constructor]") {
    {
      const stable_vector<int> v(0, 5);
      REQUIRE(v.Size() == 0u);
      REQUIRE(v.Capacity() == 0u);
      REQUIRE(v.Data() == nullptr);
    }

    {
      std::string_view filler = "abacababacacabacacbbcabcabracadabra";

      const stable_vector<std::string> v(5u, std::string(filler));
      Equal(v, std::vector<std::string>(5u, std::string(filler)));
      REQUIRE(v.Capacity() == 5u);
    }
  }

  TEST_CASE("Iterators", "[Constructor]") {
    const int arr[] = {1, 2, 3, 4};

    {
      const stable_vector<int> v(arr, arr);
      REQUIRE(v.Size() == 0u);
      REQUIRE(v.Capacity() == 0u);
      REQUIRE(v.Data() == nullptr);
    }

    {
      const stable_vector<int> v(arr + 1, arr + 4);
      Equal(v, std::vector<int>(arr + 1, arr + 4));
    }

    {
      std::vector<std::unique_ptr<int>> p;
      p.push_back(std::make_unique<int>(1));
      p.push_back(std::make_unique<int>(2));

      const stable_vector<std::unique_ptr<int>> v(std::make_move_iterator(p.begin()), std::make_move_iterator(p.end()));
      REQUIRE(*v[0] == 1);
      REQUIRE(*v[1] == 2);
      REQUIRE(p == std::vector<std::unique_ptr<int>>(2));
    }
  }

  TEST_CASE("InitializerList", "[Constructor]") {
    {
      const stable_vector<int> v{};
      REQUIRE(v.Size() == 0u);
      REQUIRE(v.Capacity() == 0u);
      REQUIRE(v.Data() == nullptr);
    }

    {
      const stable_vector<int> v{1, 2, 3, 4, 5};
      Equal(v, std::vector<int>{1, 2, 3, 4, 5});
    }
  }

  TEST_CASE("Copy Constructor", "[Constructor]") {
    {
      const stable_vector<int> empty;
      const auto v = empty;
      REQUIRE(empty.Size() == 0u);
      REQUIRE(empty.Capacity() == 0u);
      REQUIRE(empty.Data() == nullptr);
      REQUIRE(v.Size() == 0u);
      REQUIRE(v.Capacity() == 0u);
      REQUIRE(v.Data() == nullptr);
    }

    {
      const stable_vector<std::vector<int>> values{{1, 2}, {3, 4, 5}};
      const auto v = values;
      Equal(v, std::vector<std::vector<int>>{{1, 2}, {3, 4, 5}});
      Equal(values, std::vector<std::vector<int>>{{1, 2}, {3, 4, 5}});
    }
  }

  TEST_CASE("Move Constructor", "[Constructor]") {
    {
      stable_vector<int> empty;
      const auto v = std::move(empty);
      REQUIRE(empty.Size() == 0u);
      REQUIRE(empty.Capacity() == 0u);
      REQUIRE(empty.Data() == nullptr);
      REQUIRE(v.Size() == 0u);
      REQUIRE(v.Capacity() == 0u);
      REQUIRE(v.Data() == nullptr);
    }

    {
      stable_vector<std::vector<int>> values{{1, 2}, {3, 4, 5}};
      const auto v = std::move(values);
      Equal(v, std::vector<std::vector<int>>{{1, 2}, {3, 4, 5}});
      REQUIRE(values.Size() == 0u);
      REQUIRE(values.Capacity() == 0u);
      REQUIRE(values.Data() == nullptr);
    }
  }

  TEST_CASE("Copy Assignment", "[Assignment]") {
    SECTION("Empty to empty") {
      const stable_vector<int> empty;
      stable_vector<int> v;
      v = empty;
      REQUIRE(empty.Size() == 0u);
      REQUIRE(empty.Capacity() == 0u);
      REQUIRE(empty.Data() == nullptr);
      REQUIRE(v.Size() == 0u);
      REQUIRE(v.Capacity() == 0u);
      REQUIRE(v.Data() == nullptr);

      v = v;
      REQUIRE(v.Size() == 0u);
      REQUIRE(v.Capacity() == 0u);
      REQUIRE(v.Data() == nullptr);
    }

    SECTION("Empty to filled") {
      const stable_vector<int> empty;
      stable_vector<int> v{1, 2, 3};
      v = empty;
      REQUIRE(empty.Size() == 0u);
      REQUIRE(empty.Capacity() == 0u);
      REQUIRE(empty.Data() == nullptr);
      REQUIRE(v.Size() == 0u);
    }

    SECTION("Filled to empty") {
      const stable_vector<int> values{1, 2, 3};
      stable_vector<int> v;
      v = values;
      Equal(v, std::vector<int>{1, 2, 3});
      Equal(values, std::vector<int>{1, 2, 3});

      v = v;
      Equal(v, std::vector<int>{1, 2, 3});
      Equal(values, std::vector<int>{1, 2, 3});
    }

    SECTION("Small to large") {
      stable_vector<int> large(1000, 11);
      const stable_vector<int> small{1, 2, 3};
      large = small;
      Equal(large, std::vector<int>{1, 2, 3});
      Equal(small, std::vector<int>{1, 2, 3});
    }

    SECTION("Large to small") {
      const stable_vector<int> large(1000, 11);
      stable_vector<int> small{1, 2, 3};
      small = large;
      Equal(large, std::vector<int>(1000, 11));
      Equal(small, std::vector<int>(1000, 11));
    }

    SECTION("Deep copy") {
      const stable_vector<std::vector<int>> values{{1, 2}, {3, 4, 5}};
      stable_vector<std::vector<int>> v;
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
      stable_vector<int> empty;
      stable_vector<int> v;

      v = std::move(empty);
      REQUIRE(empty.Size() == 0u);
      REQUIRE(empty.Capacity() == 0u);
      REQUIRE(empty.Data() == nullptr);
      REQUIRE(v.Size() == 0u);
      REQUIRE(v.Capacity() == 0u);
      REQUIRE(v.Data() == nullptr);

      v = stable_vector<int>{};
      REQUIRE(v.Size() == 0u);
      REQUIRE(v.Capacity() == 0u);
      REQUIRE(v.Data() == nullptr);
    }

    SECTION("Empty to filled") {
      stable_vector<int> empty;
      stable_vector<int> v{1, 2, 3};
      v = std::move(empty);
      REQUIRE(empty.Size() == 0u);
      REQUIRE(empty.Capacity() == 0u);
      REQUIRE(empty.Data() == nullptr);
      REQUIRE(v.Size() == 0u);

      v = stable_vector<int>{1, 2, 3};
      v = stable_vector<int>{};
      REQUIRE(v.Size() == 0u);
    }

    SECTION("Filled to empty") {
      stable_vector<int> values{1, 2, 3};
      const auto p_values = values.Data();
      stable_vector<int> v;
      v = std::move(values);
      Equal(v, std::vector<int>{1, 2, 3});
      REQUIRE(p_values == v.Data());
      REQUIRE(values.Size() == 0u);
      REQUIRE(values.Capacity() == 0u);
      REQUIRE(values.Data() == nullptr);

      v = stable_vector<int>{4, 5, 6};
      Equal(v, std::vector<int>{4, 5, 6});
      REQUIRE(p_values != v.Data());
    }

    SECTION("Small to large") {
      stable_vector<int> large(1000, 11);
      stable_vector<int> small{1, 2, 3};
      const auto p_small = small.Data();
      large = std::move(small);
      Equal(large, std::vector<int>{1, 2, 3});
      REQUIRE(p_small == large.Data());
      REQUIRE(small.Size() == 0u);
      REQUIRE(small.Capacity() == 0u);
      REQUIRE(small.Data() == nullptr);
    }

    SECTION("Large to small") {
      stable_vector<int> large(1000, 11);
      stable_vector<int> small{1, 2, 3};
      const auto p_large = large.Data();
      small = std::move(large);
      Equal(small, std::vector<int>(1000, 11));
      REQUIRE(p_large == small.Data());
      REQUIRE(large.Size() == 0u);
      REQUIRE(large.Capacity() == 0u);
      REQUIRE(large.Data() == nullptr);
    }
  }

  TEST_CASE("DataAccess", "[Methods]") {
    stable_vector<int> v{1, 2, 3, 4, 5};

    {
      REQUIRE(v.Front() == 1);
      v.Front() = -1;
      REQUIRE(std::as_const(v).Front() == -1);
    }

    {
      REQUIRE(v.Back() == 5);
      v.Back() = -5;
      REQUIRE(std::as_const(v).Back() == -5);
    }

    {
      REQUIRE(v[1] == 2);
      v[1] = -2;
      REQUIRE(std::as_const(v)[1] == -2);
    }

    {
      REQUIRE(v.At(2) == 3);
      v.At(2) = -3;
      REQUIRE(std::as_const(v).At(2) == -3);
      REQUIRE_THROWS_AS(v.At(5), std::out_of_range);                 // NOLINT
      REQUIRE_THROWS_AS(std::as_const(v).At(5), std::out_of_range);  // NOLINT
    }
  }

  TEST_CASE("Swap", "[DataManipulation]") {
    SECTION("Empty to empty") {
      stable_vector<int> a;
      stable_vector<int> b;
      a.Swap(b);
      REQUIRE(a.Data() == nullptr);
      REQUIRE(a.Size() == 0u);
      REQUIRE(a.Capacity() == 0u);
      REQUIRE(b.Data() == nullptr);
      REQUIRE(b.Size() == 0u);
      REQUIRE(b.Capacity() == 0u);
    }

    SECTION("Empty to filled") {
      stable_vector<int> a;
      stable_vector<int> b{1, 2, 3};
      const auto pb = b.Data();
      a.Swap(b);
      Equal(a, std::vector<int>{1, 2, 3});
      REQUIRE(a.Data() == pb);
      REQUIRE(b.Data() == nullptr);
      REQUIRE(b.Size() == 0u);
      REQUIRE(b.Capacity() == 0u);
    }

    SECTION("Small to large") {
      stable_vector<int> large(1000, 11);
      stable_vector<int> small{1, 2, 3};
      const auto p_small = small.Data();
      const auto p_large = large.Data();
      small.Swap(large);
      Equal(small, std::vector<int>(1000, 11));
      Equal(large, std::vector<int>{1, 2, 3});
      REQUIRE(small.Data() == p_large);
      REQUIRE(large.Data() == p_small);
    }
  }

  TEST_CASE("Clear", "[DataManipulation]") {
    {
      stable_vector<std::unique_ptr<int>> empty;
      empty.Clear();
      REQUIRE(empty.Data() == nullptr);
      REQUIRE(empty.Size() == 0u);
      REQUIRE(empty.Capacity() == 0u);
    }

    {
      stable_vector<int> v(1000, 11);
      v.Clear();
      REQUIRE(v.Size() == 0u);
      REQUIRE(v.Empty());
    }

    {
      stable_vector<std::unique_ptr<int>> v(2);
      v[0] = std::make_unique<int>(1);
      v[1] = std::make_unique<int>(2);
      v.Clear();
      REQUIRE(v.Size() == 0u);
      REQUIRE(v.Empty());
    }
  }

  TEST_CASE("Resize", "[ReallocationStrategy]") {
    {
      stable_vector<std::unique_ptr<int>> v;
      v.Resize(0u);
      REQUIRE(v.Data() == nullptr);
      REQUIRE(v.Size() == 0u);
      REQUIRE(v.Capacity() == 0u);
    }

    {
      stable_vector<std::unique_ptr<int>> v;
      v.Resize(5u);
      Equal(v, std::vector<std::unique_ptr<int>>(5u));
      REQUIRE(v.Capacity() >= 5u);
      REQUIRE(v.Capacity() <= 10u);
    }

    {
      stable_vector<int> v;
      v.Resize(5u, 11);
      Equal(v, std::vector<int>(5u, 11));
      REQUIRE(v.Capacity() >= 5u);
      REQUIRE(v.Capacity() <= 10u);
    }

    {
      stable_vector<int> v(10u, 5);
      const auto pv = v.Data();
      v.Resize(10u);
      Equal(v, std::vector<int>(10, 5));
      REQUIRE(pv == v.Data());
    }

    {
      stable_vector<std::unique_ptr<int>> v(100);
      for (int i = 0; i < 100; ++i) {
        v[i] = std::make_unique<int>(i);
      }
      REQUIRE(v.Capacity() < 1000u);
      v.Resize(1000);

      REQUIRE(v.Size() == 1000u);
      REQUIRE(v.Capacity() >= 1000u);
      REQUIRE(v.Capacity() <= 2000u);
      for (int i = 0; i < 100; ++i) {
        REQUIRE(*v[i] == i);
      }
      for (int i = 100; i < 1000; ++i) {
        REQUIRE(v[i] == nullptr);
      }
    }

    {
      stable_vector<int> v(100u, 11);
      REQUIRE(v.Capacity() < 1000u);
      v.Resize(1000u, -11);

      REQUIRE(v.Size() == 1000u);
      REQUIRE(v.Capacity() >= 1000u);
      REQUIRE(v.Capacity() <= 2000u);
      for (int i = 0; i < 100; ++i) {
        REQUIRE(v[i] == 11);
      }
      for (int i = 100; i < 1000; ++i) {
        REQUIRE(v[i] == -11);
      }
    }

    {
      stable_vector<int> v(1000u, 11);
      const auto pv = v.Data();

      v.Resize(400u, -1);
      Equal(v, std::vector<int>(400u, 11));
      REQUIRE(pv == v.Data());

      v.Resize(100u);
      Equal(v, std::vector<int>(100u, 11));
      REQUIRE(pv == v.Data());

      v.Resize(500u, -11);
      for (int i = 0; i < 100; ++i) {
        REQUIRE(v[i] == 11);
      }
      for (int i = 100; i < 500; ++i) {
        REQUIRE(v[i] == -11);
      }
      REQUIRE(v.Size() == 500u);
      REQUIRE(pv == v.Data());

      v.Resize(750);
      for (int i = 0; i < 100; ++i) {
        REQUIRE(v[i] == 11);
      }
      for (int i = 100; i < 500; ++i) {
        REQUIRE(v[i] == -11);
      }
      REQUIRE(v.Size() == 750u);
      REQUIRE(pv == v.Data());
    }
  }

  TEST_CASE("Reserve", "[ReallocationStrategy]") {
    {
      stable_vector<std::unique_ptr<int>> v;
      v.Reserve(0u);
      REQUIRE(v.Data() == nullptr);
      REQUIRE(v.Size() == 0u);
      REQUIRE(v.Capacity() == 0u);
    }

    {
      stable_vector<int> empty;
      empty.Reserve(10u);
      Equal(empty, std::vector<int>{});
      REQUIRE(empty.Capacity() >= 10u);
      REQUIRE(empty.Data() != nullptr);
    }

    {
      stable_vector<std::unique_ptr<int>> empty;
      empty.Reserve(10u);
      Equal(empty, std::vector<std::unique_ptr<int>>{});
      REQUIRE(empty.Capacity() >= 10u);
      REQUIRE(empty.Data() != nullptr);
    }

    {
      stable_vector<int> v(10u, 5);
      const auto pv = v.Data();

      v.Reserve(10u);
      Equal(v, std::vector<int>(10u, 5));
      REQUIRE(pv == v.Data());

      v.Reserve(5u);
      Equal(v, std::vector<int>(10u, 5));
      REQUIRE(pv == v.Data());
    }

    {
      stable_vector<std::unique_ptr<int>> v(100u);
      for (int i = 0; i < 100; ++i) {
        v[i] = std::make_unique<int>(i);
      }
      REQUIRE(v.Capacity() < 1000u);
      v.Reserve(1000u);

      REQUIRE(v.Size() == 100u);
      REQUIRE(v.Capacity() >= 1000u);
      REQUIRE(v.Capacity() <= 2000u);
      for (int i = 0; i < 100; ++i) {
        REQUIRE(*v[i] == i);
      }
    }
  }

  TEST_CASE("ShrinkToFit", "[ReallocationStrategy]") {
    {
      stable_vector<int> empty;
      empty.ShrinkToFit();
      REQUIRE(empty.Data() == nullptr);
      REQUIRE(empty.Size() == 0u);
      REQUIRE(empty.Capacity() == 0u);
    }

    {
      stable_vector<std::unique_ptr<int>> empty;
      empty.Reserve(10u);
      empty.ShrinkToFit();
      REQUIRE(empty.Data() == nullptr);
      REQUIRE(empty.Size() == 0u);
      REQUIRE(empty.Capacity() == 0u);
    }

    {
      stable_vector<std::unique_ptr<int>> v(16u);
      for (int i = 0; i < 16; ++i) {
        v[i] = std::make_unique<int>(i);
      }
      v.Reserve(100u);
      v.ShrinkToFit();
      for (int i = 0; i < 16; ++i) {
        REQUIRE(*v[i] == i);
      }
      REQUIRE(v.Size() == 16u);
      REQUIRE(v.Capacity() == 16u);
    }

    {
      stable_vector<int> v(10u, 10);
      v.Reserve(1000u);
      const auto pv = v.Data();
      v.ShrinkToFit();
      Equal(v, std::vector<int>(10u, 10));
      REQUIRE(v.Capacity() == 10u);
      REQUIRE(pv != v.Data());
    }
  }

  TEST_CASE("PushBack", "[ReallocationStrategy]") {
    {
      stable_vector<std::unique_ptr<int>> v;
      for (int i = 0; i < 100; ++i) {
        v.PushBack(std::make_unique<int>(i));
        REQUIRE(v.Size() == static_cast<unsigned>(i + 1));
        REQUIRE(v.Capacity() >= v.Size());
        REQUIRE(v.Capacity() <= 2 * v.Size());
      }
      for (int i = 0; i < 100; ++i) {
        REQUIRE(*v[i] == i);
      }
    }

    {
      stable_vector<int> v(10u);
      for (int i = 0; i < 10; ++i) {
        v[i] = i;
      }
      for (int i = 10; i < 100; ++i) {
        v.PushBack(i);
        REQUIRE(v.Size() == static_cast<unsigned>(i + 1));
        REQUIRE(v.Capacity() >= v.Size());
        REQUIRE(v.Capacity() <= 2 * v.Size());
      }
      for (int i = 0; i < 100; ++i) {
        REQUIRE(v[i] == i);
      }
    }
  }

  TEST_CASE("PopBack", "[ReallocationStrategy]") {
    {
      stable_vector<std::unique_ptr<int>> v;
      for (int i = 0; i < 100; ++i) {
        v.PushBack(std::make_unique<int>(i));
      }
      const auto capacity = v.Capacity();
      for (int i = 0; i < 50; ++i) {
        v.PopBack();
        REQUIRE(v.Size() == static_cast<unsigned>(100 - i - 1));
      }
      REQUIRE(capacity == v.Capacity());
      for (int i = 0; i < 50; ++i) {
        REQUIRE(*v[i] == i);
      }
    }

    {
      stable_vector<int> v(10u);
      for (int i = 0; i < 10; ++i) {
        v[i] = i;
      }
      for (int i = 10; i < 100; ++i) {
        v.PushBack(i);
      }
      const auto capacity = v.Capacity();
      for (int i = 0; i < 50; ++i) {
        v.PopBack();
        REQUIRE(v.Size() == static_cast<unsigned>(100 - i - 1));
      }
      REQUIRE(capacity == v.Capacity());
      for (int i = 0; i < 50; ++i) {
        REQUIRE(v[i] == i);
      }
    }
  }

  TEST_CASE("Stress", "[ReallocationStrategy]") {
    stable_vector<std::unique_ptr<int>> v;
    for (int i = 0; i < 1'000'000; ++i) {
      v.PushBack(std::make_unique<int>(i));
      REQUIRE(v.Size() == static_cast<unsigned>(i + 1));
      REQUIRE(v.Capacity() >= v.Size());
      REQUIRE(v.Capacity() <= 2 * v.Size());
    }
    const auto capacity = v.Capacity();
    for (int i = 0; i < 500'000; ++i) {
      v.PopBack();
      REQUIRE(v.Size() == static_cast<unsigned>(1'000'000 - i - 1));
    }
    REQUIRE(capacity == v.Capacity());
    for (int i = 0; i < 500'000; ++i) {
      REQUIRE(*v[i] == i);
    }
  }

  template <class T>
  void CheckComparisonEqual(const stable_vector<T>& lhs, const stable_vector<T>& rhs) {
    REQUIRE(lhs == rhs);
    REQUIRE(lhs <= rhs);
    REQUIRE(lhs >= rhs);
    REQUIRE_FALSE(lhs != rhs);
    REQUIRE_FALSE(lhs < rhs);
    REQUIRE_FALSE(lhs > rhs);
  }

  template <class T>
  void CheckComparisonLess(const stable_vector<T>& lhs, const stable_vector<T>& rhs) {
    REQUIRE_FALSE(lhs == rhs);
    REQUIRE(lhs <= rhs);
    REQUIRE_FALSE(lhs >= rhs);
    REQUIRE(lhs != rhs);
    REQUIRE(lhs < rhs);
    REQUIRE_FALSE(lhs > rhs);
  }

  template <class T>
  void CheckComparisonGreater(const stable_vector<T>& lhs, const stable_vector<T>& rhs) {
    REQUIRE_FALSE(lhs == rhs);
    REQUIRE_FALSE(lhs <= rhs);
    REQUIRE(lhs >= rhs);
    REQUIRE(lhs != rhs);
    REQUIRE_FALSE(lhs < rhs);
    REQUIRE(lhs > rhs);
  }

  TEST_CASE("Comparisons", "[stable_vector]") {
    {
      stable_vector<int> a;
      stable_vector<int> b;
      CheckComparisonEqual(a, b);
    }

    {
      stable_vector<int> a;
      stable_vector<int> b(1, 2);
      CheckComparisonLess(a, b);
      CheckComparisonGreater(b, a);
    }

    {
      stable_vector<int> a{1, 3};
      stable_vector<int> b{2};
      CheckComparisonLess(a, b);
      CheckComparisonGreater(b, a);
    }

    {
      stable_vector<int> a{1, 2, 3};
      stable_vector<int> b{1, 1};
      CheckComparisonLess(b, a);
      CheckComparisonGreater(a, b);
    }

    {
      stable_vector<int> a{1, 2, 3, 4};
      stable_vector<int> b{1, 2, 3, 4};
      CheckComparisonEqual(a, b);
    }

    {
      stable_vector<int> a{1, 2, 3, 4};
      stable_vector<int> b{1, 2, 3};
      CheckComparisonLess(b, a);
      CheckComparisonGreater(a, b);
    }

    {
      stable_vector<int> a{1, 4, 6, 8};
      stable_vector<int> b{2, 3, 5, 7};
      CheckComparisonLess(a, b);
      CheckComparisonGreater(b, a);
    }

    {
      stable_vector<int> a{1, 2, 3, 5};
      stable_vector<int> b{1, 2, 4, 5};
      CheckComparisonLess(a, b);
      CheckComparisonGreater(b, a);
    }
  }

  TEST_CASE("Iterator", "[Iterators]") {
    {
      using Iterator = stable_vector<int>::Iterator;
      REQUIRE((std::is_same_v<Iterator, decltype(std::declval<stable_vector<int>>().begin())>));
      REQUIRE((std::is_same_v<Iterator, decltype(std::declval<stable_vector<int>>().end())>));

      using Traits = std::iterator_traits<Iterator>;
      REQUIRE((std::is_same_v<Traits::value_type, int>));
      REQUIRE((std::is_same_v<Traits::reference, decltype(*std::declval<Iterator>())>));
      REQUIRE((std::is_base_of_v<std::random_access_iterator_tag, Traits::iterator_category>));
    }

    {
      stable_vector<int> v(10u);
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
      stable_vector<int> v(10u, -1);
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
      using ConstIterator = stable_vector<int>::ConstIterator;
      REQUIRE((std::is_same_v<ConstIterator, decltype(std::declval<stable_vector<int>>().cbegin())>));
      REQUIRE((std::is_same_v<ConstIterator, decltype(std::declval<stable_vector<int>>().cend())>));
      REQUIRE((std::is_same_v<ConstIterator, decltype(std::declval<const stable_vector<int>>().begin())>));
      REQUIRE((std::is_same_v<ConstIterator, decltype(std::declval<const stable_vector<int>>().end())>));

      using Traits = std::iterator_traits<ConstIterator>;
      REQUIRE((std::is_same_v<Traits::value_type, int>));
      REQUIRE((std::is_same_v<Traits::reference, decltype(*std::declval<ConstIterator>())>));
      REQUIRE((std::is_base_of_v<std::random_access_iterator_tag, Traits::iterator_category>));
    }

    {
      stable_vector<int> v(10u);
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
      using ReverseIterator = stable_vector<int>::ReverseIterator;
      REQUIRE((std::is_same_v<ReverseIterator, decltype(std::declval<stable_vector<int>>().rbegin())>));
      REQUIRE((std::is_same_v<ReverseIterator, decltype(std::declval<stable_vector<int>>().rend())>));
      REQUIRE((std::is_same_v<ReverseIterator, std::reverse_iterator<stable_vector<int>::Iterator>>));

      using Traits = std::iterator_traits<ReverseIterator>;
      REQUIRE((std::is_same_v<Traits::value_type, int>));
      REQUIRE((std::is_same_v<Traits::reference, decltype(*std::declval<ReverseIterator>())>));
      REQUIRE((std::is_base_of_v<std::random_access_iterator_tag, Traits::iterator_category>));
    }

    {
      stable_vector<int> v(10u);
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
      stable_vector<int> v(10u, -1);
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
      using ConstReverseIterator = stable_vector<int>::ConstReverseIterator;
      REQUIRE((std::is_same_v<ConstReverseIterator, decltype(std::declval<stable_vector<int>>().crbegin())>));
      REQUIRE((std::is_same_v<ConstReverseIterator, decltype(std::declval<stable_vector<int>>().crend())>));
      REQUIRE((std::is_same_v<ConstReverseIterator, decltype(std::declval<const stable_vector<int>>().rbegin())>));
      REQUIRE((std::is_same_v<ConstReverseIterator, decltype(std::declval<const stable_vector<int>>().rend())>));
      REQUIRE((std::is_same_v<ConstReverseIterator, std::reverse_iterator<stable_vector<int>::ConstIterator>>));

      using Traits = std::iterator_traits<ConstReverseIterator>;
      REQUIRE((std::is_same_v<Traits::value_type, int>));
      REQUIRE((std::is_same_v<Traits::reference, decltype(*std::declval<ConstReverseIterator>())>));
      REQUIRE((std::is_base_of_v<std::random_access_iterator_tag, Traits::iterator_category>));
    }

    {
      stable_vector<int> v(10u);
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
    REQUIRE_THROWS_AS(stable_vector<Throwable>(10u), Exception);  // NOLINT
  }

  TEST_CASE("Value Constructor", "[Safety]") {
    Throwable::until_throw = 5;
    REQUIRE_THROWS_AS(stable_vector<Throwable>(10u, Throwable{}), Exception);  // NOLINT

    try {  // no memory management case
      Throwable::until_throw = 15;
      stable_vector<Throwable> v(10u, Throwable{});
    } catch (Exception) {
    }
  }

  TEST_CASE("Iterators Constructor", "[Safety]") {
    Throwable::until_throw = 210;
    const std::vector<Throwable> values(100u, Throwable{});
    Throwable::until_throw = 50;
    REQUIRE_THROWS_AS(stable_vector<Throwable>(values.begin(), values.end()), Exception);  // NOLINT

    try {  // no memory management case
      Throwable::until_throw = 150;
      stable_vector<Throwable> v(values.begin(), values.end());
    } catch (Exception) {
    }
  }

  TEST_CASE("Initializer List Constructor", "[Safety]") {
    Throwable::until_throw = 6;
    REQUIRE_THROWS_AS(stable_vector<Throwable>({Throwable{}, Throwable{}, Throwable{}, Throwable{}}), Exception);  // NOLINT

    try {  // no memory management case
      Throwable::until_throw = 10;
      stable_vector<Throwable> v({Throwable{}, Throwable{}, Throwable{}, Throwable{}});
    } catch (Exception) {
    }
  }

  TEST_CASE("Copy Constructor Safety", "[Safety]") {
    Throwable::until_throw = 210;
    const stable_vector<Throwable> values(100u, Throwable{});
    Throwable::until_throw = 50;
    REQUIRE_THROWS_AS(stable_vector<Throwable>(values), Exception);  // NOLINT

    try {  // no memory management case
      Throwable::until_throw = 150;
      stable_vector<Throwable> v(values);
    } catch (Exception) {
    }
  }

  TEST_CASE("Move Constructor Safety", "[Safety]") {
    Throwable::until_throw = 210;
    stable_vector<Throwable> values(100u, Throwable{});
    Throwable::until_throw = 1;
    REQUIRE_NOTHROW(stable_vector<Throwable>(std::move(values)));  // NOLINT
  }

  TEST_CASE("Copy Assignment Safety", "[Safety]") {
    {
      Throwable::until_throw = 12;
      const stable_vector<Throwable> values(5u);

      stable_vector<Throwable> v;
      Throwable::until_throw = 3;
      REQUIRE_THROWS_AS(v = values, Exception);  // NOLINT
      REQUIRE(v.Capacity() >= v.Size());

      try {  // no memory management case
        stable_vector<Throwable> vv;
        Throwable::until_throw = 8;
        vv = values;
      } catch (Exception) {
      }
    }

    {
      Throwable::until_throw = 100;
      const stable_vector<Throwable> values(10u);
      stable_vector<Throwable> v(35u);
      Throwable::until_throw = 5;
      REQUIRE_THROWS_AS(v = values, Exception);  // NOLINT
      REQUIRE(v.Capacity() >= v.Size());
    }
  }

  TEST_CASE("Move Assignment Safety", "[Safety]") {
    {
      Throwable::until_throw = 12;
      stable_vector<Throwable> values(5u);
      stable_vector<Throwable> v;
      Throwable::until_throw = 1;
      REQUIRE_NOTHROW(v = std::move(values));  // NOLINT
    }

    {
      Throwable::until_throw = 100;
      stable_vector<Throwable> values(10u);
      stable_vector<Throwable> v(35u);
      Throwable::until_throw = 1;
      REQUIRE_NOTHROW(v = std::move(values));  // NOLINT
    }
  }

  TEST_CASE("Swap Safety", "[Safety]") {
    Throwable::until_throw = 12;
    stable_vector<Throwable> values(5u);
    stable_vector<Throwable> v;
    Throwable::until_throw = 1;
    REQUIRE_NOTHROW(v.Swap(values));  // NOLINT
  }

  TEST_CASE("Resize Safety", "[Safety]") {
    Throwable::until_throw = 200;
    stable_vector<Throwable> v(90u);
    const auto capacity = v.Capacity();
    const auto data = v.Data();

    REQUIRE_NOTHROW(v.Resize(90u));  // NOLINT
    REQUIRE_NOTHROW(v.Resize(50u));  // NOLINT
    REQUIRE_NOTHROW(v.Resize(10u));  // NOLINT

    Throwable::until_throw = 10;
    REQUIRE_THROWS_AS(v.Resize(200u), Exception);  // NOLINT
    REQUIRE(v.Size() == 10u);
    REQUIRE(v.Capacity() == capacity);
    REQUIRE(v.Data() == data);

    try {  // no memory management case
      Throwable::until_throw = 300;
      v.Resize(200, {});
    } catch (Exception) {
      REQUIRE(v.Size() == 10u);
      REQUIRE(v.Capacity() == capacity);
      REQUIRE(v.Data() == data);
    }
  }

  TEST_CASE("Reserve Safety", "[Safety]") {
    Throwable::until_throw = 55;
    stable_vector<Throwable> v(10u);
    REQUIRE_NOTHROW(v.Reserve(30u));  // NOLINT

    const auto capacity = v.Capacity();
    const auto size = v.Size();
    const auto data = v.Data();
    try {  // no memory management case
      Throwable::until_throw = 30;
      v.Reserve(100u);
    } catch (Exception) {
      REQUIRE(v.Capacity() == capacity);
      REQUIRE(v.Size() == size);
      REQUIRE(v.Data() == data);
    }
  }

  TEST_CASE("ShrinkToFit Safety", "[Safety]") {
    Throwable::until_throw = 95;
    stable_vector<Throwable> v(20u);
    v.Reserve(30u);
    REQUIRE_NOTHROW(v.ShrinkToFit());  // NOLINT

    v.Resize(10);
    const auto capacity = v.Capacity();
    const auto size = v.Size();
    const auto data = v.Data();
    try {  // no memory management case
      Throwable::until_throw = 5;
      v.ShrinkToFit();
    } catch (Exception) {
      REQUIRE(v.Capacity() == capacity);
      REQUIRE(v.Size() == size);
      REQUIRE(v.Data() == data);
    }
  }

  TEST_CASE("PushBack Safety", "[Safety]") {
    Throwable::until_throw = 200;
    stable_vector<Throwable> v;
    v.Reserve(100u);
    const auto capacity = v.Capacity();
    const auto data = v.Data();
    Throwable::until_throw = static_cast<int>(capacity) + 2;
    for (size_t i = 0; i < capacity; ++i) {
      v.PushBack({});
    }
    const Throwable object;
    REQUIRE_THROWS_AS(v.PushBack(object), Exception);  // NOLINT
    REQUIRE(v.Size() == capacity);
    REQUIRE(v.Capacity() == capacity);
    REQUIRE(v.Data() == data);

    try {  // no memory management case
      Throwable::until_throw = static_cast<int>(2 * capacity) + 1;
      v.PushBack(object);
    } catch (...) {
      REQUIRE(v.Size() == capacity);
      REQUIRE(v.Capacity() == capacity);
      REQUIRE(v.Data() == data);
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
      const stable_vector<InstanceCounter> v;
      REQUIRE(InstanceCounter::counter == 0u);
    }

    SECTION("Size Constructor") {
      const stable_vector<InstanceCounter> v(10u);
      REQUIRE(InstanceCounter::counter == 10u);
    }

    SECTION("Size-Value Constructor") {
      const stable_vector<InstanceCounter> v(10u, InstanceCounter{});
      REQUIRE(InstanceCounter::counter == 10u);
    }

    SECTION("Iterators Constructor") {
      const std::vector<InstanceCounter> values(100u);
      const stable_vector<InstanceCounter> v(values.begin(), values.end());
      REQUIRE(InstanceCounter::counter == 200u);
    }

    SECTION("Initializer List Constructor") {
      const stable_vector<InstanceCounter> v{InstanceCounter{}, InstanceCounter{}, InstanceCounter{}};
      REQUIRE(InstanceCounter::counter == 3u);
    }

    SECTION("Copy Constructor") {
      const stable_vector<InstanceCounter> values(100u);
      const auto v = values;
      REQUIRE(InstanceCounter::counter == 200u);
    }

    SECTION("Move Constructor") {
      stable_vector<InstanceCounter> values(100u);
      const auto v = std::move(values);
      REQUIRE(InstanceCounter::counter == 100u);
    }

    REQUIRE(InstanceCounter::counter == 0u);
  }

  TEST_CASE("Assignment Memory", "[Memory]") {
    InstanceCounter::counter = 0u;

    SECTION("Copy Assignment") {
      {
        const stable_vector<InstanceCounter> values(10u);
        stable_vector<InstanceCounter> v(100u);
        v = values;
        REQUIRE(InstanceCounter::counter == 20u);
      }
      REQUIRE(InstanceCounter::counter == 0u);

      {
        const stable_vector<InstanceCounter> values(100u);
        stable_vector<InstanceCounter> v(10u);
        v = values;
        REQUIRE(InstanceCounter::counter == 200u);
      }
    }

    SECTION("Move Assignment") {
      {
        stable_vector<InstanceCounter> values(10u);
        stable_vector<InstanceCounter> v(100u);
        v = std::move(values);
        REQUIRE(InstanceCounter::counter == 10u);
      }
      REQUIRE(InstanceCounter::counter == 0u);

      {
        stable_vector<InstanceCounter> values(100u);
        stable_vector<InstanceCounter> v(10u);
        v = std::move(values);
        REQUIRE(InstanceCounter::counter == 100u);
      }
    }

    REQUIRE(InstanceCounter::counter == 0u);
  }

  TEST_CASE("Swap Memory", "[Memory]") {
    InstanceCounter::counter = 0u;

    {
      stable_vector<InstanceCounter> a;
      stable_vector<InstanceCounter> b(10u);
      a.Swap(b);
      REQUIRE(InstanceCounter::counter == 10u);
    }
    REQUIRE(InstanceCounter::counter == 0u);

    {
      stable_vector<InstanceCounter> a(20u);
      stable_vector<InstanceCounter> b(10u);
      a.Swap(b);
      REQUIRE(InstanceCounter::counter == 30u);
    }
    REQUIRE(InstanceCounter::counter == 0u);
  }

  TEST_CASE("Clear Memory", "[Memory]") {
    InstanceCounter::counter = 0u;

    stable_vector<InstanceCounter> v(10u);
    v.Clear();
    REQUIRE(InstanceCounter::counter == 0u);
  }

  TEST_CASE("Resize Memory", "[Memory]") {
    InstanceCounter::counter = 0u;

    {
      stable_vector<InstanceCounter> v;
      v.Resize(100u);
      REQUIRE(InstanceCounter::counter == 100u);
      v.Resize(10u);
      REQUIRE(InstanceCounter::counter == 10u);
      v.Resize(1000u);
      REQUIRE(InstanceCounter::counter == 1000u);
    }
    REQUIRE(InstanceCounter::counter == 0u);

    {
      stable_vector<InstanceCounter> v;
      v.Resize(100u, InstanceCounter{});
      REQUIRE(InstanceCounter::counter == 100u);
      v.Resize(10u, InstanceCounter{});
      REQUIRE(InstanceCounter::counter == 10u);
      v.Resize(1000u, InstanceCounter{});
      REQUIRE(InstanceCounter::counter == 1000u);
    }
    REQUIRE(InstanceCounter::counter == 0u);
  }

  TEST_CASE("Reserve Memory", "[Memory]") {
    InstanceCounter::counter = 0u;

    {
      stable_vector<InstanceCounter> v;
      v.Reserve(100u);
      REQUIRE(InstanceCounter::counter == 0u);
      v.Resize(10u);
      REQUIRE(InstanceCounter::counter == 10u);
      v.Reserve(1000u);
      REQUIRE(InstanceCounter::counter == 10u);
      v.Resize(100u);
      REQUIRE(InstanceCounter::counter == 100u);
    }
    REQUIRE(InstanceCounter::counter == 0u);
  }

  TEST_CASE("ShrinkToFit Memory", "[Memory]") {
    InstanceCounter::counter = 0u;

    {
      stable_vector<InstanceCounter> v;
      v.Reserve(100u);
      REQUIRE(InstanceCounter::counter == 0u);
      v.Resize(10u);
      REQUIRE(InstanceCounter::counter == 10u);
      v.ShrinkToFit();
      REQUIRE(InstanceCounter::counter == 10u);

      v.Reserve(1000u);
      REQUIRE(InstanceCounter::counter == 10u);
      v.Resize(100u);
      REQUIRE(InstanceCounter::counter == 100u);
      v.ShrinkToFit();
      REQUIRE(InstanceCounter::counter == 100u);
    }
    REQUIRE(InstanceCounter::counter == 0u);
  }

  TEST_CASE("PushBack Memory", "[Memory]") {
    InstanceCounter::counter = 0u;

    {
      stable_vector<InstanceCounter> v;
      for (size_t i = 0; i < 100; ++i) {
        v.PushBack({});
        REQUIRE(InstanceCounter::counter == (i + 1));
      }
    }
    REQUIRE(InstanceCounter::counter == 0u);

    {
      stable_vector<InstanceCounter> v;
      InstanceCounter obj;
      for (size_t i = 0; i < 100; ++i) {
        v.PushBack(obj);
        REQUIRE(InstanceCounter::counter == (i + 2));
      }
    }
    REQUIRE(InstanceCounter::counter == 0u);
  }

  TEST_CASE("EmplaceBack Memory", "[Memory]") {
    InstanceCounter::counter = 0u;

    {
      stable_vector<InstanceCounter> v;
      for (size_t i = 0; i < 100; ++i) {
        v.EmplaceBack();
        REQUIRE(InstanceCounter::counter == (i + 1));
      }
    }
    REQUIRE(InstanceCounter::counter == 0u);

    {
      stable_vector<std::vector<int>> v;
      for (size_t i = 0; i < 10; ++i) {
        v.EmplaceBack();
        REQUIRE(v.Size() == static_cast<unsigned>(i + 1));
        REQUIRE(v.Capacity() >= v.Size());
        REQUIRE(v.Capacity() <= 2 * v.Size());
        REQUIRE(v.Back().empty());
      }
      for (size_t i = 10; i < 30; ++i) {
        v.EmplaceBack(10);
        REQUIRE(v.Size() == static_cast<unsigned>(i + 1));
        REQUIRE(v.Capacity() >= v.Size());
        REQUIRE(v.Capacity() <= 2 * v.Size());
        REQUIRE(v.Back().size() == 10u);
      }
      for (size_t i = 30; i < 70; ++i) {
        v.EmplaceBack(11, -11);
        REQUIRE(v.Size() == static_cast<unsigned>(i + 1));
        REQUIRE(v.Capacity() >= v.Size());
        REQUIRE(v.Capacity() <= 2 * v.Size());
        REQUIRE(v.Back() == std::vector<int>(11, -11));
      }
    }
  }

  TEST_CASE("PopBack Memory", "[Memory]") {
    InstanceCounter::counter = 0u;

    {
      stable_vector<InstanceCounter> v;
      for (int i = 0; i < 100; ++i) {
        v.PushBack({});
      }
      for (int i = 0; i < 50; ++i) {
        v.PopBack();
        REQUIRE(InstanceCounter::counter == static_cast<unsigned>(100 - i - 1));
      }
    }
    REQUIRE(InstanceCounter::counter == 0u);
  }

#endif
}