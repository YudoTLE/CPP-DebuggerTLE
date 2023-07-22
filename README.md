# CPP-DebuggerTLE
CPP-DebuggerTLE is a boost library that can print various data types including
`std::pair`,
`std::tuple`,
`std::vector`,
`std::set`,
`std::multiset`,
`std::map`,
`std::multimap`,
`std::unordered_set`,
`std::unordered_multiset`,
`std::unordered_map`,
`std::unordered_multimap`,
`std::stack`,
`std::queue`,
`std::deque`,
`std::priority_queue`,
and even `__gnu_pbds::tree`.
It can also print items inside a pointer or an iterator.
Besides printing data types, CPP-DebuggerTLE also supports creating lines with customizable patterns and lengths to make debugging process easier.

## Getting Started
1. Clone the repository.
2. Create files named "tle" inside your include file. The include file is commonly located in `C:\msys64\ucrt64\include` for mysys2 or `C:\MinGW\include` for MinGW.
   You can look for others online if you do not use mysys2 or MinGW.
3. Copy and paste the `debug`, `debug.h`, and `debug.cpp` files inside the "tle" folder from before.

## How to Use?
You just need to write `#include <tle/debug>` in your code to use this library.
```C++
#include <tle/debug>
```
See example below for further details.

## Debugging

### Function Call 1
```C++
template <typename _Tps>
debug(_Tps... _items)
```

|Parameters|Description                            |
|----------|---------------------------------------|
|_items    |List of items to debug.                |

### Example 1
#### C++ code
```C++
int x = 1;
string y = "two";
double* z = new double(3.0);

debug(x, y, z);
cout << '\n';

vector<int> A{1,2,3,4,5};
set<char> B{'a','b','c','d','e'};

debug(A, B);
```

##### Output
```C++
> x = 1
> y = two
> z = *3

> A = [1 2 3 4 5]
> B = {a b c d e}
```

### Function Call 2
```C++
template <typename _Tps>
debug(_Tps... _items)(int _unfold_depth)
```

|Parameters   |Description                                                                              |
|-------------|-----------------------------------------------------------------------------------------|
|_items       |List of items to debug.                                                                  |
|_unfold_depth|Optional parameter that specify the maximum depth for the output to unfold (`default=1`).|

### Example 2
#### C++ code
```C++
int x = 1;
string y = "two";
double* z = new double(3.0);

debug(x, y, z)(0);
cout << '\n';
debug(x, y, z)(1);
cout << '\n';

vector<int> A{1,2,3,4,5};
set<char> B{'a','b','c','d','e'};

debug(A, B)(0);
cout << '\n';
debug(A, B)(1);
cout << '\n';
debug(A, B)(2);
```

#### Output
```C++
> x = 1, y = two, z = *3

> x = 1
> y = two
> z = *3

> A = [1 2 3 4 5], B = {a b c d e}

> A = [1 2 3 4 5]
> B = {a b c d e}

> A = [
|  1 
|  2 
|  3 
|  4 
|  5
|]
> B = {
|  a 
|  b 
|  c 
|  d 
|  e
|}
```

### Function Call 3
```C++
template <typename _Tps>
debug(_Tps... _items)(bool _force_horizontal)
```

|Parameters       |Description                                                                          |
|-----------------|-------------------------------------------------------------------------------------|
|_items           |List of items to debug.                                                              |
|_force_horizontal|Optional parameter that force the output to be horizontally printed(`default=false`).|

### Example 3
#### C++ code
```C++
int x = 1;
string y = "two";
double* z = new double(3.0);

debug(x, y, z)(false);
cout << '\n';
debug(x, y, z)(true);
cout << '\n';

vector<int> A{1,2,3,4,5};
set<char> B{'a','b','c','d','e'};

debug(A, B)(false);
cout << '\n';
debug(A, B)(true);
```

#### Output
```C++
> x = 1
> y = two
> z = *3

> x, y, z = 1, two, *3

> A = [1 2 3 4 5]
> B = {a b c d e}

> A, B = [1 2 3 4 5], {a b c d e}
```

## Creating Lines

### Function Call 1
```C++
template <typename _Tps>
dline(_Tps... _patterns)
```

|Parameters|Description              |
|----------|-------------------------|
|_patterns |The pattern of the lines.|

### Example 4
#### C++ code
dline("-");
dline("=");
dline("-1-2-3");
cout << '\n';
dline("a", "b", "c");
```

##### Output
```C++
--------------------------------------------------
==================================================
-1-2-3-1-2-3-1-2-3-1-2-3-1-2-3-1-2-3-1-2-3-1-2-3-1

aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
cccccccccccccccccccccccccccccccccccccccccccccccccc
```

### Function Call 2
```C++
template <typename _Tps>
dline(_Tps... _patterns)(size_t _length)
```

|Parameters|Description              |
|----------|-------------------------|
|_patterns |The pattern of the lines.|
|_length   |The length of the lines(`default=50`).|

### Example 5
#### C++ code
```C++
dline("-")(75);
dline("=")(50);
cout << '\n';
dline("a", "b", "c")(25);
```

##### Output
```C++
---------------------------------------------------------------------------
==================================================

aaaaaaaaaaaaaaaaaaaaaaaaa
bbbbbbbbbbbbbbbbbbbbbbbbb
ccccccccccccccccccccccccc
```
