# An Introduction to C

C is a general-purpose programming language that is widely used in the development of operating systems (Windows: C#,
Mac OS: Objective-C), compilers, and other software tools.

C is a low-level language, which means that it is closer to the hardware than other languages. This makes it possible
to write programs that are more efficient than those written in higher-level languages.

C is also a statically typed language, which means that the type of a variable is determined at compile time. This
makes it possible to catch many errors at compile time, rather than at run time. In contrast, languages like Python
or Javascript are dynamically typed, which means that the type of a variable is determined at run time. This makes
it easier to write programs, on a cost of performance. This means, if writing the program is the most time-consuming
part, then Python saves you a lot of time. Whereas, if the program is going to be run for days, months, then C is the
way to go. In general, C would be ~100x faster than Python, ~10x faster than JavaScript.

Many low-level languages are similar to C, for example, C++, Java, C# and Swift. So you should really know C if you
plan to do some high performance programming.

## Headers

Analogous to `import` in Python, C uses `#include` to include header files, which contain declarations of
functions and variables. For example:

```c
#include <stdio.h>

int main() {
    printf("Hello, world!\n");
    return 0;
}
```

To use the `printf` function, we need to include the `stdio.h` header file.

## Variables

We need to declare variables in C before we can use them. For example:

```c
int x;
```

This declares a variable `x` of type `int`. We can then assign a value to `x`:

```c
x = 5;
```

The best practice is to declare and initialize a variable in the same line:

```c
int x = 5;
```

so that we don't get some random value of `x` that's left over in the memory.

## Types

In Python, we have types like `int`, `float`, `str`, `bool`, etc. In C, they corresponds to

| Python | C              |
| ------ | -------------- |
| int    | int            |
| float  | float / double |
| str    | char\*         |
| bool   | int / bool     |
| None   | void           |

Examples:

```c
int x = 5;
float y = 3.14;
char* s = "Hello, world!";
bool b = true;
```

For scientific computing, I would recommend using `double` instead of `float` because it's more precise and memory is
cheap nowadays.

## Functions

Functions in C are declared as follows:

```c
int add(int x, int y) {
    return x + y;
}
```

We see that both the input parameters and the return type are declared. If there is no return type, we use `void`.
For example:

```c
void print_hello() {
    printf("Hello, world!\n");
}
```

In old standards of C, the main function was declared as `void`:

```c
void main() {
    printf("Hello, world!\n");
}
```

But today, you'll probably receive a warning. Just changing `void` to `int` will fix the warning:

```c
int main() {
    printf("Hello, world!\n");
    return 0;
}
```

`return 0` means that the program exited successfully. If we want to return an error code (e.g. 1), we can `return 1`.

## Arrays

Analogous to Python lists, C has arrays. For example:

```c
int arr[5] = {1, 2, 3, 4, 5};
int empty_arr[5];
int zero_arr[5] = {0};
```

Unlike Python, you need to specify the size and the type of the array when you declare it. Here, we've declared an
array of size 5, type `int` and initialized with the values 1, 2, 3, 4, 5, an uninitialized array, and an array of
zeros. When initializing an all-zero array, you can just write `{0}` instead of `{0, 0, 0, 0, 0}`.

Accessing elements of an array is just like Python:

```c
arr[0] = 1;
printf(arr[0]);
```

## Scope of Variables

In C, variables have a tighter scope than in Python. Variables are only visible within the block `{}` they are
declared in. For example:

```c
int main() {
    int x = 5;
    {
        int y = 10;
        printf("%d\n", x); // 5
        printf("%d\n", y); // 10
    }
    printf("%d\n", x); // 5
    printf("%d\n", y); // Error: y is not defined
}
```

Example different from Python:

```c
int main() {
    for (int i = 0; i < 5; i++) {
        printf("%d\n", i); // 0, 1, 2, 3, 4
    }
    printf("%d\n", i); // Error: i is not defined
}
```

```python
for i in range(5):
    print(i) # 0, 1, 2, 3, 4
print(i) # 4
```

## For Loops

For loops in C are similar to Python:

```python
# Python
for i in range(5):
    print(i)
```

Analogous to

```c
// C
for (int i = 0; i < 5; i++) {
    printf("%d\n", i);
}
```

The `()` following `for` consists of three parts: initialization, condition, and update.

```c
int i = 0;
```

initializes the temporary variable `i` to 0.

```c
i < 5
```

is the condition. The loop will continue as long as the condition is true.

```c
i++
```

is the update, executed after each iteration of the loop.

Note that `i++` is equivalent to `i = i + 1`.

## Comments

Example:

```c
// This is a single-line comment
/* This is a
   multi-line comment */
```
