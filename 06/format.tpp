#pragma once


template <class... ArgsT>
std::string format(const std::string& str, ArgsT&&... args){
    std::string formatted_str = "";
    size_t start = 0;
    std::string num;
    State state = State::String;
    for (size_t i=0; i<str.length(); i++){
        if (state == State::String){
            if (str[i] == '}')
                throw BadUseBracket(i);
            if (str[i] == '{'){
                state = State::Brackets;
                start = i;
            }
            else
                formatted_str.push_back(str[i]);
        }
        else{
            if (str[i] == '}'){
                state = State::String;
                if (num == "")
                    throw BadUseBracket(start);
                size_t n = convert(num, start+1);
                formatted_str += get_arg(start+1, n, n, args...);
                num = "";
            }
            else if ((int) str[i] < '0' || (int) str[i] > '9'){
                for (size_t j = i+1; j<str.length(); j++){
                    if (str[j] == '{')
                        throw BadUseBracket(start);
                    if (str[j] == '}')
                        throw BadInBrackets(i);
                }
                throw BadUseBracket(start);
            }
            else
                num.push_back(str[i]);
        }
    }
    if (state == State::Brackets)
        throw BadUseBracket(start);

    return formatted_str;
}

size_t convert(const std::string& str, size_t start){
    size_t forward_zeros = 0;
    for (size_t i=0; i<str.length(); i++){
        if (str[i] == '0')
            forward_zeros++;
        else
            break;
    }
    if (forward_zeros == str.length())
        return 0;

    std::string str_num = str.substr(forward_zeros);
    std::stringstream stream;
    stream << str_num;
    size_t num;
    stream >> num;
    stream.str(std::string());
    stream.clear();
    stream << num;
    std::string str2;
    stream >> str2;
    if (str_num == str2)
        return num;
    else
        throw HugeIndex(start);
}

template <class T, class... ArgsT>
std::string get_arg(size_t start,
                  size_t init_n,
                  size_t n,
                  T&& arg,
                  ArgsT&&... args){
    if (n == 0)
        return check_stream(arg, init_n);
    else
        return get_arg(start, init_n, n-1, args...);
}

std::string get_arg(size_t start, size_t, size_t){
    throw BigIndex(start);
}

template<ConceptName T>
std::string check_stream(T&& arg, size_t){
    std::stringstream stream;
    stream << arg;
    return stream.str();
}

template<typename T>
std::string check_stream(T&&, size_t init_n){
    throw BadStream(init_n);
}
