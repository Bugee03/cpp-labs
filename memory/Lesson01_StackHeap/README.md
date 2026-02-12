# Lesson 01 — Stack vs Heap, sizeof, array addresses, pointers, range-based for

## Code summary
This lesson demonstrates:
- `sizeof` for basic types (`int`, `float`, `char`, `bool`)
- Why array element addresses go sequentially in memory
- Dynamic allocation with `new` / `delete`
- Passing arrays to functions via pointer (`int* buffer`) + size
- Simulating ADC samples and printing with range-based `for`

## Key concepts (answers)

### 1) Why array element addresses are sequential?
Arrays are stored in **contiguous memory**.  
So `&array[i+1] = &array[i] + sizeof(int)` (address step equals element size).

### 2) Why `sizeof(bool)` can be 1, but not required?
The standard guarantees only `sizeof(bool) >= 1`.  
It’s often 1 byte, but the compiler/ABI may choose a different size for alignment/implementation reasons.

### 3) What happens if you forget `delete`?
You get a **memory leak** (and the destructor won’t run), which can also leak resources and increase heap fragmentation.

### 4) Why embedded avoids `new/delete`?
Because heap allocation can be **non-deterministic**, causes **fragmentation**, and is risky with small RAM and real-time constraints.  
Typical embedded approach: static/stack allocation or fixed memory pools.

## Notes about this code
- `simulate_adc(int* buffer, int size)` writes values into the passed array using indexing.
- `rand() % 4096` imitates a 12-bit ADC range (0–4095).
- `for (int value : adcBuffer)` is a **range-based for** that iterates over each element of the array.

## Build & Run
```bash
g++ -std=c++17 main.cpp -o lesson1
./lesson1

