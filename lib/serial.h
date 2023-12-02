// Library for Raspberry pico Serial 1.0.0 by @IkerCs / @aizer-egl
#include <optional>
#include <string>
#include "hardware/uart.h"
#include "hardware/gpio.h"
#define UART_0 ((uart_inst_t *)uart0_hw)
#define UART_1 ((uart_inst_t *)uart1_hw)
#define MAX_LOOP 10'000
#ifndef SERIAL_H
#define SERIAL_H

class Serial {
    public:
        Serial (uint8_t port);
        void attach (uint8_t TX, uint8_t RX);
        void begin (uint32_t baudrate);
        bool available ();
        std::optional<char> read();
        std::optional<std::string> readString();
        std::optional<std::string> readStringUntil(char terminator);
        std::optional<unsigned int> write(char data);

        template <typename T> std::optional<unsigned int> print (T data) {
            std::string str = std::to_string(data);
            for (int i = 0;i<str.length();i++) {
                this->write(str[i]);
            }
            return str.length();
        }

        template <typename T> std::optional<unsigned int> println (T data) {
            std::string str = std::to_string(data);
            for (int i = 0;i<str.length();i++) {
                this->write(str[i]);
            }
            this->write('\n');
            return str.length() + 1;
        }
    private:
        uint8_t port;
        uint8_t TX;
        uint8_t RX;
        uint32_t baudrate;
};

#endif