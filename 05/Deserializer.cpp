#include <sstream> 
#include <string>
#include "Deserializer.hpp"
#include "Error.hpp"


Error Deserializer::process(bool& value){
    std::string text;
    in_ >> text;

    if (text == "true")
        value = true;
    else if (text == "false")
        value = false;
    else
        return Error::CorruptedArchive;

    return Error::NoError;
}


Error Deserializer::process(uint64_t& value){
    std::string text1;
    in_ >> text1;
    std::stringstream stream;
    stream << text1;
    uint64_t check;
    stream >> check;
    stream.str(std::string());
    stream.clear();
    stream << check;
    std::string text2;
    stream >> text2;
    if (text1 != text2){
        return Error::CorruptedArchive;
    }
    else{
        value = check;
        return Error::NoError;
    }
}
