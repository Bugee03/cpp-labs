#include <iostream>
#include <cstdlib>

void simulate_adc(int* buffer,int size) {
    for(int i=0;i<size;i++) {
        buffer[i] = rand() % 4096;
    }
}


void lesson1() {
    int a = 10;
    float b = 3.15f;
    char c = 'A';
    bool temp = true;

    std::cout << "size of int:" << sizeof(a) << "\n";
    std::cout << "size of float: " << sizeof(b) << "\n";
    std::cout << "size of char: " << sizeof(c) << "\n";
    std::cout << "size of bool: " << sizeof(temp) << "\n";

    int array[10];

    std::cout << "Array addresses: \n";

    for ( int i = 0; i < 10 ;i++) {
        std::cout << &array[i] << "\n";
    }

    int* HeapValue = new int(10);
    std::cout<< "Heap Value: " << *HeapValue << "\n";
    delete HeapValue;

    int adcBuffer[10];
    simulate_adc(adcBuffer, 10);

    std::cout << "\n ADC simulation \n";
    for (int value : adcBuffer) {
        std::cout << value << "\n";
    }


}


void lesson1();

int main() {
    lesson1();
    return 0;
}

