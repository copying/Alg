# Alg++
Alg++ is a C++17 library to make algorithms. It support simultaneous implementations and allows to choose which one to use very easily.
```cpp
// Use the default implementation of the foo algorithm
auto result = foo(param);

// use the bar implementation of the foo algorithm
auto result = foo.bar(param);
```
It also helps you to have multiple

```cpp
// Tries to use a
auto result = foo.with_lib_or_fallback(param);
```

### Example algorithm

```cpp
struct Power2 : Algorithm<Power2> {

    // Using multiplication and a loop
    static constexpr auto mul = [](unsigned x) {
        unsigned r = 1;
        for (unsigned i = 0; i<x; ++i) {
            r = r*2;
        }
        return r;
    };

    // Using left shift operator
    static constexpr auto shift = [](unsigned x) {
        return 1<<x;
    };

    // For containers
    static constexpr auto multi_in_place = [](auto& container) {
        for (auto& element : container) {
            element = 1<<element;
        }
    };

    // Set the default
    static constexpr auto default_ = overload_ {
        multi_in_place,
        shift
    };
};
[[maybe_unused]] constexpr Power2 const power2;
```
And to use it:
```cpp
unsigned result;
result = power2(10);
result = power2.mul(10);
result = power2.shift(10);

std::vector<unsigned> vec{1, 2, 3, 4, 5, 6};
power2(vec);
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

// Call if executes the function if the second one return true.
//  Returns an optional
constexpr auto div10 = call_if {
    [](double i) {
        return 10.0/i;
    },
    [](double i) {
        return i!=0;
    }
};

// Fallback tries functions until succeeds.
//  Returns an optional.
constexpr auto save = fallback {
    save_online,
    save_locally
}
```
