# Alg
Alg is a C++17 header-only library to make algorithms. It support simultaneous implementations and allows to choose which one to use very easily.
```cpp
// Use the default implementation of the foo algorithm
auto result = foo(param);

// use the bar implementation of the foo algorithm
auto result = foo.bar(param);
```
It also helps you to have multiple

```cpp
// Tries to use a library. If that implementations fail, tries with a fallback.
auto result = foo.with_lib_or_fallback(param);
```

### Why Alg
If you make a program in C++ is to make it efficient. Algorithms are a big part on that. It's normal for an algorithms to have many implementations (just look at a simple sort).

This library helps to collect them all together in a single object. This means that you have a default version, but you can choose an implementation better suited for your needs (usually data structure) without changing the code much.

It also provides helpers to bundle multiple implementations together.

It supports `constexpr`, `auto` and `noexcept` in the implementations.

### Example algorithm
What we want to achieve:
```cpp
// We want to make an algorithm that returns 2 to the power of x
// The user of this algorithm could do:
unsigned result;
result = power2(10);       // Default
result = power2.mul(10);   // Using multiplication loop
result = power2.shift(10); // Using shift operator

std::vector<unsigned> vec{1, 2, 3, 4, 5, 6};
power2(vec); // saves the result in vec itself
```
How it's done:
```cpp
struct Power2 : Algorithm<Power2> {

    // Using multiplication and a loop
    static constexpr auto mul = [](unsigned x) constexpr noexcept {
        unsigned r = 1;
        for (unsigned i = 0; i<x; ++i) {
            r = r*2;
        }
        return r;
    };

    // Using left shift operator
    static constexpr auto shift = [](unsigned x) constexpr noexcept {
        return 1<<x;
    };

    // For containers
    static constexpr auto multi_in_place = [](auto& container) constexpr noexcept {
        for (auto& element : container) {
            element = 1<<element;
        }
    };

    // Set the default (overloading the shift implementation and the multi_in_place)
    static constexpr auto default_ = overload_ {
        multi_in_place,
        shift
    };
};
[[maybe_unused]] constexpr Power2 const power2;
```

### Grouping multiple callable objects

```cpp
// Overlod makes an overloading of the different callable objects.
constexpr auto default_ = overload {
    multi_in_place,
    shift
};

// Prioritize tries to execute the first implementation with the parameters given.
//  If it is not callable with that parameter types, tries with the next one.
constexpr auto multiple = prioritize {
    gpu,
    parallel,
    regular
};

// Call_if executes the function if the second one return true.
//  Returns a std::optional or a alg::utils::void_optional
constexpr auto div10 = call_if {
    [](double i) constexpr noexcept {
        return 10.0/i;
    },
    [](double i) constexpr noexcept {
        return i!=0;
    }
};

// Fallback tries functions until succeeds.
//  Returns a std::optional or a alg::utils::void_optional
constexpr auto save = fallback {
    save_online,
    save_locally
}
```
