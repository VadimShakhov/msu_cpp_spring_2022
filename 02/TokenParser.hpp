#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <vector> // нужен только для тестов:
                  // возвращаемые значения callback-ов записываются в вектор
                  // и проверяются в тестах;
                  // распарсенные токены тоже записываются в вектора и проверяются в тестах


class TokenParser
{
public:
    TokenParser() = default;

    void SetStartCallback(std::function<uint64_t ()>);

    void SetEndCallback(std::function<uint64_t ()>);

    void SetDigitTokenCallback(std::function<uint64_t (uint64_t)>);

    void SetStringTokenCallback(std::function<uint64_t (std::string)>);

    void Parse(const std::string &);

    std::vector<uint64_t> log; // сюда записываются возвращаемые значения callback-ов
    std::vector<uint64_t> log_digit; // сюда записываются распарсенные uint64_t
    std::vector<std::string> log_string; // сюда записываются распарсенные строки


private:
    std::function<uint64_t ()> StartCallback;
    std::function<uint64_t ()> EndCallback;
    std::function<uint64_t (uint64_t)> DigitCallback;
    std::function<uint64_t (std::string)> StringCallback;

    const std::string MAX_VALUE = "18446744073709551615"; // максимальное значение uint64_t
};
