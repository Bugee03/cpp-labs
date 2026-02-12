# Lesson 02 — Memory Control (Pointers, References, Const, Volatile)

## 🎯 Goal

Understand low-level memory manipulation in C++ for embedded systems:

- Pointer vs Reference
- Const pointer variations
- Volatile usage
- Basic memory safety concepts

---
🧠 Answers:
Why is volatile required for registers?
Hardware can modify memory outside program control.
Compiler must not cache value.


Why are ISR variables volatile?
ISR can update variable asynchronously.


Why reference over pointer?
Cannot be null
Cleaner
Safer when object must exist


Why double pointers risky in embedded?
Hard ownership tracking
Higher memory corruption risk
Often linked to dynamic allocation
Harder debugging

| Type                 | Meaning                              |
| -------------------- | ------------------------------------ |
| `const int* p`       | Value cannot change                  |
| `int* const p`       | Pointer cannot change                |
| `const int* const p` | Neither pointer nor value can change |

