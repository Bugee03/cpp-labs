#include <iostream>

class Buffer {
private:
    int* data;
    int size;

    public:
    Buffer(int s) : size(s) {
        data = new int[size];
        std::cout << "Allocated memory for Buffer" << std::endl;
    }

    //copy constructor
    Buffer(const Buffer& other) : size(other.size) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
            std::cout <<"Copied buffer at " << i << std::endl;
        }
    }

    //copy assigment
    Buffer& operator=(const Buffer& other) {
        if (this == &other) {
            return *this;
        }

        delete[] data;
        size = other.size;
        data = new int[size];

        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];

        std::cout << "Assigned\n";
        return *this;
    }

    ~Buffer() {
        delete[] data;
        std::cout << "Destroyed\n";
    }

    //move constructor
    Buffer(Buffer&& other) noexcept: size(other.size), data(other.data) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "Moved\n";
    }

    //Move assigment
    Buffer& operator=(Buffer&& other) noexcept {
        if (this == &other) return *this;

        delete[] data;
        data = other.data;
        size = other.size;

        other.data = nullptr;
        other.size = 0;

        std::cout << "Move assigned\n";
        return *this;
    }

    void fill(int value) {
        for (int i = 0; i < size; i++) {
            data[i] = value;
        }
    }


    void print() const {
        std::cout << "[size=" << size << "] ";
        if (!data) {
            std::cout << "(null)\n";
            return;
        }
        for (int i = 0; i < size; ++i)
            std::cout << data[i] << " ";
        std::cout << "\n";
    }
};


int main() {
    Buffer b1(5);          // Allocated
    b1.fill(7);
    b1.print();

    Buffer b2 = b1;        // Copy constructor
    b2.print();

    Buffer b3 = std::move(b1);  // Move constructor
    b3.print();

    // After move, b1 is valid but empty
    b1.print();

    return 0;
}
