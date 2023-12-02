#include "serial.h"

Serial::Serial (uint8_t port) {
    this->port = port;
}

void Serial::attach (uint8_t TX, uint8_t RX) {
    this->TX = TX;
    this->RX = RX;
}

void Serial::begin (uint32_t baudrate) {
    this->baudrate = baudrate;
    if ((this -> port) == 0) {
        uart_init(UART_0, baudrate);
        gpio_set_function(this->TX, GPIO_FUNC_UART);
        gpio_set_function(this->RX, GPIO_FUNC_UART);
    } else if ((this -> port) == 1) {
        uart_init(UART_1, baudrate);
        gpio_set_function(this->TX, GPIO_FUNC_UART);
        gpio_set_function(this->RX, GPIO_FUNC_UART);
    }
}

bool Serial::available () {
    if ((this -> port) == 0) {
        return uart_is_readable(UART_0);
    } else if ((this -> port) == 1) {
        return uart_is_readable(UART_1);
    }
    return false;
}

std::optional<char> Serial::read () {
    if ((this -> port) == 0) {
        if (uart_is_readable(UART_0)) {
            return uart_getc(UART_0);
        }
    } else if ((this -> port) == 1) {
        if (uart_is_readable(UART_1)) {
            return uart_getc(UART_1);
        }
    }
    return std::nullopt;
}

std::optional<std::string> Serial::readStringUntil (char terminator) {
    std::string str = "";
    for (int i = 0;i < MAX_LOOP; i++) {
        if (this->available()) {
            char c = this->read().value();
            if (c == terminator) {
                return str;
            } else {
                str += c;
            }
        }
    }
    return std::nullopt;
}

std::optional<std::string> Serial::readString () {
    return this->readStringUntil('\n');
}

std::optional<unsigned int> Serial::write (char data) {
    if ((this -> port) == 0) {
        if (uart_is_writable(UART_0)) {
            uart_putc(UART_0, data);
            return 1;
        }
    } else if ((this -> port) == 1) {
        if (uart_is_writable(UART_1)) {
            uart_putc(UART_1, data);
            return 1;
        }
    }
    return std::nullopt;
}