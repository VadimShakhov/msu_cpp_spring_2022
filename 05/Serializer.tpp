#pragma once

#include "Error.hpp"


template <class T, class... ArgsT>
Error Serializer::process(T&& arg, ArgsT&&... args){
    if (process(arg) == Error::CorruptedArchive){
        return Error::CorruptedArchive;
    }
    else{
        return process(args...);
    }
}

