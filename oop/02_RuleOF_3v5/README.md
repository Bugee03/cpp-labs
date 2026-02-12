# Modern C++: Rule of Five & Move Semantics

## Overview

This lesson explains:

- Why move is faster than copy
- Why we must nullify moved objects
- Why move constructors should be `noexcept`
- Why `std::vector` uses move semantics
- Engineering comparison table

---

# 1️⃣ Why Move is Faster Than Copy

## Copy Operation

Copy constructor:

```cpp
data = new int[size];
for (int i = 0; i < size; ++i)
    data[i] = other.data[i];
````

Copy:

* Allocates new memory
* Copies each element
* Time complexity: **O(n)**

For large buffers this is expensive.

---

## Move Operation

Move constructor:

```cpp
data = other.data;
other.data = nullptr;
```

Move:

* Does NOT allocate memory
* Does NOT copy elements
* Transfers ownership
* Time complexity: **O(1)**

---

## Performance Comparison

| Operation        | Copy   | Move        |
| ---------------- | ------ | ----------- |
| Allocates memory | ✔ Yes  | ❌ No        |
| Copies data      | ✔ Yes  | ❌ No        |
| Time complexity  | O(n)   | O(1)        |
| Performance      | Slower | Much Faster |

The larger the buffer, the bigger the performance difference.

---

# 2️⃣ Why Must We Nullify `other.data`?

Correct move constructor:

```cpp
Buffer(Buffer&& other) noexcept
    : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
}
```

If we forget:

```cpp
other.data = nullptr;
```

Then:

* Both objects point to the same memory
* Both destructors call `delete[]`
* Double free occurs
* Undefined behavior
* Possible crash

After move, the source object must be:

> Valid but empty

---

# 3️⃣ Why Move Constructor Should Be `noexcept`

```cpp
Buffer(Buffer&& other) noexcept
```

### Reason 1 — Logical guarantee

Move only transfers pointers.
It should not throw exceptions.

### Reason 2 — STL optimization

`std::vector` uses move only if it is `noexcept`.

If move may throw:

* Vector will use copy instead
* Performance decreases

---

# 4️⃣ Why `std::vector` Uses Move

When vector grows:

1. Allocates larger memory block
2. Transfers old elements
3. Deletes old storage

Without move:

* Every element is copied
* Expensive for large objects

With move:

* Ownership is transferred
* No deep copying
* Much faster

---

## Example

If we store 100 buffers of 1MB:

Copy:

* 100MB copied

Move:

* 100 pointer transfers

Huge performance difference.

---

# 5️⃣ Engineering Summary

Move semantics:

* Transfer ownership
* Avoid deep copy
* Prevent double free
* Improve performance
* Reduce heap fragmentation

---

# 6️⃣ Rule of Five

If a class manages a resource, implement:

1. Destructor
2. Copy constructor
3. Copy assignment
4. Move constructor
5. Move assignment

Otherwise:

* Memory leaks
* Double free
* Performance issues

---

# Final Conclusion

Move semantics provide:

* Deterministic resource transfer
* Better performance
* Safer memory handling
* Modern C++ best practice

For resource-managing classes, move semantics are essential.

