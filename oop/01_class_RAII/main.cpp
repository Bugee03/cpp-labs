#include <iostream>


class GPIO {
private:
    int pinNumber;
    bool state;

    public: GPIO(int pin) : pinNumber(pin), state(false) {
        std::cout << "GPIO pin number: " << pinNumber << " initilazed\n";
    }

    ~GPIO() {
        std::cout << "GPIO " << pinNumber << " destroyed\n";
    }

    void setHigh() {
        if (state) return;
        state = true;
        std :: cout << "GPIO " << pinNumber << " set high\n";
    }

    void setLow() {
        if (!state) return;
        state = false;
        std :: cout << "GPIO " << pinNumber << " set low\n";
    }

    //why const? = func does not change object state!
    bool read() const{
        return state;
    }

    void toggle() {
        state = !state;
    }

    // Copying is prohibited!!
    GPIO(const GPIO&) = delete;
    //ex:
    //GPIO led1(13);
    //GPIO led2 = led1;

    //copy assigment is prohibited!!
    GPIO &operator=(const GPIO &) = delete;
    //ex:
    //GPIO led1(13);
    //GPIO led2(12);
    //led2 = led1;   

};

void lesson3() {
    GPIO led(13);

    led.setHigh();
    led.setLow();
}

int main() {
    lesson3();
}
