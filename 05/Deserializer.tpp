#pragma once

#include "Error.hpp"


template <class T, class... ArgsT>
Error Deserializer::process(T& value, ArgsT&&... args){
    if (process(value) == Error::CorruptedArchive){
        return Error::CorruptedArchive;
    }
    else{
        return process(args...);
    }
}
