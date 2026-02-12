# Embedded C++: Resource Management & RAII

## Overview

This lesson covers:

- Why copying is forbidden in embedded drivers
- When destructors are called
- What happens with global objects
- Why RAII is better than manual init/deinit
- Engineering comparison table

---

# 1️⃣ Why Copying is Forbidden in Embedded

In embedded systems, objects often represent **unique hardware resources**:

- GPIO pin
- UART peripheral
- SPI interface
- Timer
- DMA channel

Allowing copying would create multiple objects controlling the same hardware:

```cpp
GPIO led1(13);
GPIO led2 = led1;   // ❌ dangerous
````

## Problems:

* Double initialization
* Double deinitialization
* Register conflicts
* Race conditions
* Undefined behavior

## Correct Engineering Approach

```cpp
GPIO(const GPIO&) = delete;
GPIO& operator=(const GPIO&) = delete;
```

This enforces **single ownership** of hardware resources.

---

# 2️⃣ When is the Destructor Called?

A destructor is automatically called:

## ✔ When an object leaves scope (stack)

```cpp
void foo() {
    GPIO led(13);
}  // destructor called here
```

## ✔ When delete is used (heap)

```cpp
GPIO* led = new GPIO(13);
delete led;  // destructor called
```

## ✔ When the program exits (global/static objects)

---

# 3️⃣ What Happens if Object is Global?

```cpp
GPIO led(13);  // global object
```

## Behavior

* Constructor runs **before main()**
* Destructor runs **after main()**

## Risks in Embedded

* HAL may not be initialized
* Clock may not be enabled
* Static initialization order problem
* Possible HardFault

## Best Practice

Avoid global driver objects.
Prefer controlled initialization inside `main()`.

---

# 4️⃣ Why RAII is Better Than Manual Init/DeInit

## ❌ Manual Style

```cpp
GPIO_Init();
...
GPIO_DeInit();
```

### Problems

* Easy to forget cleanup
* Cleanup not guaranteed
* Hard to track lifetime
* Error-prone

---

## ✅ RAII Style

```cpp
{
    GPIO led(13);
}  // automatic cleanup
```

### Advantages

* Automatic resource release
* Deterministic lifetime
* Scope-based management
* Safer and cleaner design
* Exception-safe

---

# Engineering Comparison Table

| Feature                  | Manual Init/DeInit | RAII     |
| ------------------------ | ------------------ | -------- |
| Cleanup Guaranteed       | ❌ No               | ✔ Yes    |
| Safe on Early Return     | ❌ No               | ✔ Yes    |
| Safe on Exceptions       | ❌ No               | ✔ Yes    |
| Lifetime Control         | Weak               | Strong   |
| Risk of Double Free      | High               | Low      |
| Ownership Model          | Implicit           | Explicit |
| Recommended for Embedded | Risky              | ✔ Yes    |

---

# Engineering Principles Applied

* Single Ownership
* Deterministic Lifetime
* Safe Resource Handling
* No Copying of Hardware Drivers
* Scope-Based Resource Control

---

# Conclusion

In embedded systems:

* Hardware resources must have one owner
* Copying must be disabled
* Lifetime must be deterministic
* RAII ensures automatic and safe cleanup

RAII leads to safer, more professional embedded driver architecture.

