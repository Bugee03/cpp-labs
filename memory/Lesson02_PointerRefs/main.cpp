// basics/lesson2_memory_control.cpp
#include <iostream>
#include <cstdint>

// 4) Simulated hardware register (volatile)
volatile uint32_t fakeRegister = 0;

// 1) Pointer: function receives pointer and modifies the pointed value
void modify(int* value) {
    if (value == nullptr) return;   // safety check
    *value += 10;
}

// 2) Reference: function receives reference and modifies the original
void modifyRef(int& value) {
    value += 10;
}

// Helper: demonstrate const pointer variations
void constPointerExamples() {
    int a = 5;
    int b = 20;

    // (A) Pointer to const: cannot change *p, but can change p
    const int* pToConst = &a;
    // *pToConst = 7; // ERROR
    pToConst = &b;     // OK

    // (B) Const pointer: cannot change p, but can change *p
    int* const constPtr = &a;
    *constPtr = 7;     // OK
    // constPtr = &b;  // ERROR

    // (C) Const pointer to const: neither p nor *p can change
    const int* const constPtrToConst = &a;
    (void)constPtrToConst; // suppress unused warning
}

// 4) Volatile register usage example
void volatileRegisterDemo() {
    fakeRegister = 0;

    // simulate "hardware" changing the register (in real MCU, hardware does it)
    fakeRegister = 0xABCD1234;

    // force real memory reads (compiler must not cache fakeRegister)
    uint32_t read1 = fakeRegister;
    uint32_t read2 = fakeRegister;

    std::cout << "fakeRegister read1: 0x" << std::hex << read1 << "\n";
    std::cout << "fakeRegister read2: 0x" << std::hex << read2 << "\n";
    std::cout << std::dec;
}

int main() {
    std::cout << "Lesson 02 — memory control: pointer, reference, const, volatile\n\n";

    int x = 10;
    std::cout << "Initial x: " << x << "\n";

    modify(&x);
    std::cout << "After modify(int*): " << x << "\n";

    modifyRef(x);
    std::cout << "After modifyRef(int&): " << x << "\n\n";

    constPointerExamples();
    std::cout << "Const pointer examples compiled OK.\n\n";

    volatileRegisterDemo();

    return 0;
}

