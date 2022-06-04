#pragma once


#include <string>
#include <sstream>
#include <iostream>
#include "my_exceptions.hpp"


enum class State
{
    String,
    Brackets
};


template<typename T>
concept ConceptName =
    requires (T t) {
        { std::cout << t };
    };

template<ConceptName T>
std::string check_stream(T&&, size_t);

template<typename T>
std::string check_stream(T&&, size_t);

template <class... ArgsT>
std::string format(const std::string& str, ArgsT&&... args);

template <class T, class... ArgsT>
std::string get_arg(size_t, size_t, size_t, T&&, ArgsT&&...);

std::string get_arg(size_t, size_t, size_t);

uint64_t convert(const std::string&, size_t);

#include "format.tpp"
