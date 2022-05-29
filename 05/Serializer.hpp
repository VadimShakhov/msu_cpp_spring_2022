#pragma once

#include <iostream>
#include "Error.hpp"

class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out) : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args){
        return process(args...);
    }

    Error process(bool arg);
    Error process(uint64_t arg);

    template <class T, class... ArgsT>
    Error process(T&& arg, ArgsT&&... args);

    template <class T>
    Error process(T&&) {return Error::CorruptedArchive;}

private:
    std::ostream& out_;
};

#include "Serializer.tpp"
