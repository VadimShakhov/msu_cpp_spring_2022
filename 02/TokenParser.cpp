#include <iostream>
#include <string>
#include <sstream>
#include "TokenParser.hpp"


void TokenParser::SetStartCallback(std::function<uint64_t ()> CustomSCb){
    StartCallback = CustomSCb;
}

void TokenParser::SetEndCallback(std::function<uint64_t ()> CustomECb){
    EndCallback = CustomECb;
}

void TokenParser::SetDigitTokenCallback(std::function<uint64_t (uint64_t)> CustomDCb){
    DigitCallback = CustomDCb;
}

void TokenParser::SetStringTokenCallback(std::function<uint64_t (std::string)> CustomStrCb){
    StringCallback = CustomStrCb;
}

void TokenParser::Parse(const std::string &str){
    log.clear();
    if (StartCallback){
        log.push_back(StartCallback());
    }
    bool digit = true; // является ли токен числом
    size_t start = 0; // начало токена
    size_t length = 0; // длина токена
    size_t front_zeros = 0; // нули в начале токена
    bool valid_front_zeros = true; // true, если в токене ещё не встретился ненулевой символ
    for (size_t i=0; i<str.length(); i++){
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'){
            length++;
            if ((int) str[i] < (int) '0' || (int) str[i] > (int) '9'){
                digit = false;
                valid_front_zeros = false;
            }
            else if(valid_front_zeros){
                if (str[i] == '0'){
                    front_zeros++;
                }
                else{
                    valid_front_zeros = false;
                }
            }
        }
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || i == str.length() - 1){
            if (digit){
                std::string true_digit = str.substr(start + front_zeros, length - front_zeros);
                digit = true_digit.size() <= MAX_VALUE.size()
                        && (true_digit.size() < MAX_VALUE.size() 
                        || true_digit.compare(MAX_VALUE) <= 0);
                
                if (digit){
                    std::istringstream stream (true_digit);
                    uint64_t num;
                    stream >> num;
                    log_digit.push_back(num);
                    if (DigitCallback){
                        log.push_back(DigitCallback(num));
                    }
                }
                else{
                    log_string.push_back(str.substr(start, length));
                    if (StringCallback){
                        log.push_back(StringCallback(str.substr(start, length)));
                    }
                }
                
            }
            else{
                log_string.push_back(str.substr(start, length));
                if (StringCallback){
                    log.push_back(StringCallback(str.substr(start, length)));
                }
            }
            start = i + 1;
            digit = true;
            length = 0;
            front_zeros = 0;
            valid_front_zeros = true;
        }
    }
    if (EndCallback){
        log.push_back(EndCallback());
    }
}
