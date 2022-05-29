#pragma once

#include <iostream>
#include "Error.hpp"


class Deserializer{
public:
    Deserializer(std::istream& in) : in_(in) {}

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args){
        return process(args...);
    }

    template <class T, class... ArgsT>
    Error process(T& value, ArgsT&&...);

    Error process(bool& value);
    Error process(uint64_t& value);
    template <class T>
    Error process(T& value){ return Error::CorruptedArchive;}
    Error process(){ return Error::CorruptedArchive;}
private:
    std::istream& in_;
};


#include "Deserializer.tpp"
