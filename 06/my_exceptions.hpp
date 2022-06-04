#pragma once


#include <exception>
#include <string>
#include <sstream>


class BigIndex:public std::exception
{
public:
    BigIndex(size_t i){
        std::stringstream stream;
        stream << "Нет аргумента с номером, указанным по индексу " << i;
        getline(stream, message_);
        index_ = i;
    }
    std::string get_message() const {return message_;}
    size_t get_index() const {return index_;}
    
private:
    std::string message_ = "";
    size_t index_ = 0;
};

class HugeIndex:public std::exception
{
public:
    HugeIndex(size_t i){
        std::stringstream stream;
        stream << "Номер аргумента по индексу " << i << " не влезает в size_t";
        getline(stream, message_);
        index_ = i;
    }
    std::string get_message() const {return message_;}
    size_t get_index() const {return index_;}
    
private:
    std::string message_ = "";
    size_t index_ = 0;
};

class BadUseBracket:public std::exception
{
public:
    BadUseBracket(size_t i){
        std::stringstream stream;
        stream << "Некорректное использование фигурной скобки по индексу " << i;
        getline(stream, message_);
        index_ = i;
    }
    std::string get_message() const {return message_;}
    size_t get_index() const {return index_;}
private:
    std::string message_ = "";
    size_t index_ = 0;
};

class BadInBrackets:public std::exception
{
public:
    BadInBrackets(size_t i){
        std::stringstream stream;
        stream << "Некорректный символ в фигурных скобках по индексу " << i;
        getline(stream, message_);
        index_ = i;
    }
    std::string get_message() const {return message_;}
    size_t get_index() const {return index_;}
private:
    std::string message_ = "";
    size_t index_ = 0;
};

class BadStream:public std::exception
{
public:
    BadStream(size_t n){
        std::stringstream stream;
        stream << "Аргумент с номером " << n << " не поддержиает вывод в поток";
        getline(stream, message_);
        number_ = n;
    }
    std::string get_message() const {return message_;}
    size_t get_number() const {return number_;}
private:
    std::string message_ = "";
    size_t number_ = 0;
};
