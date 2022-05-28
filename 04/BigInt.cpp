#include <sstream>
#include "BigInt.hpp"


BigInt::BigInt(const BigInt & big_num){
    digits = big_num.digits;
    number = new int32_t[digits];
    for (size_t i=0; i < digits; i++){
        number[i] = big_num.number[i];
    }
}

BigInt::BigInt(const int32_t & num){
    int32_t num_tmp = num;
    digits = 1;
    while (num_tmp / DIGIT_MAX != 0){
        digits++;
        num_tmp = num_tmp / DIGIT_MAX;
    }
    num_tmp = num;
    number = new int32_t[digits];
    for (size_t i=0; i<digits; i++){
        number[i] = num_tmp % DIGIT_MAX;
        num_tmp = num_tmp / DIGIT_MAX;
    }
}

BigInt::BigInt(const std::string & str){
    size_t start = 0; // номер первой ненулевой цифры в str
    while (start<str.length() && str[start] == 0){
        start++;
    }
    if (start == str.length()){
        digits = 1;
        number = new int32_t[1];
        number[0] = 0;
    }
    else{
        size_t length = str.length() - start;
        digits = length / DIGIT_MAX_ORDER;
        if (length % DIGIT_MAX_ORDER != 0){
            digits++;
        }
        number = new int32_t[digits];
        for (size_t i=0; i<digits-1; i++){
            std::string chunk = str.substr(str.length() - DIGIT_MAX_ORDER * (i+1), DIGIT_MAX_ORDER);
            std::istringstream stream (chunk);
            stream >> number[i];
        }
        std::string chunk = str.substr(start, str.length() - DIGIT_MAX_ORDER*(digits-1) - start);
        std::istringstream stream (chunk);
        stream >> number[digits-1];
    }
}

BigInt::BigInt(BigInt && num){
    number = num.number;
    digits = num.digits;
    num.number = nullptr;
    num.digits = 0;
}

BigInt::~BigInt(){
    delete[] number;
}

BigInt& BigInt::operator=(const BigInt & num){
    if (num.number == number){
        return *this;
    }

    delete[] number;
    digits = num.digits;
    number = new int32_t[digits];
    for (size_t i=0; i<digits; i++){
        number[i] = num.number[i];
    }
    return *this;
}

BigInt& BigInt::operator=(const int32_t & num){
    delete[] number;
    *this = BigInt(num);
    return *this;
}

BigInt& BigInt::operator=(BigInt && num){
    if (num.number == number){
        return *this;
    }

    delete[] number;
    digits = num.digits;
    number = num.number;
    num.number = nullptr;
    num.digits = 0;
    return *this;
}

BigInt BigInt::operator+(const BigInt & num) const{
    size_t min;
    const BigInt *max;
    if (num.digits > digits){
        min = digits;
        max = &num;
    }
    else{
        min = num.digits;
        max = this;
    }

    BigInt sum;
    sum.number = new int32_t[max->digits + 1];
    int32_t v_ume = 0;
    for (size_t i=0; i<min; i++){
        int32_t step = number[i] + num.number[i] + v_ume;
        if (step >= DIGIT_MAX){
            sum.number[i] = step - DIGIT_MAX;
            v_ume = 1;
        }
        else{
            sum.number[i] = step;
            v_ume = 0;
        }
    }
    for (size_t i=min; i < max->digits; i++){
        int32_t step = max->number[i] + v_ume;
        if (step >= DIGIT_MAX){
            sum.number[i] = step - DIGIT_MAX;
            v_ume = 1;
        }
        else{
            sum.number[i] = step;
            v_ume = 0;
        }
    }
    sum.digits = max->digits;
    if (v_ume == 1){
        sum.number[sum.digits] = 1;
        sum.digits++;
    }

    return sum;
}

BigInt BigInt::operator+(const int32_t & num) const{
    return *this + BigInt(num);
}

BigInt BigInt::operator-(const BigInt & num) const{
    size_t min;
    const BigInt *max;
    if (num.digits > digits){
        min = digits;
        max = &num;
    }
    else{
        min = num.digits;
        max = this;
    }

    int32_t v_ume = 0;
    int32_t zeros = 0; // нулевые старшие разряды, не должны учитываться в digits
    BigInt dif;
    dif.number = new int32_t[max->digits];
    for (size_t i=0; i<min; i++){
        int32_t step = number[i] - num.number[i] - v_ume;
        if (step < 0){
            dif.number[i] = step + DIGIT_MAX;
            v_ume = 1;
        }
        else{
            dif.number[i] = step;
            v_ume = 0;
        }
        step == 0 ? zeros++ : zeros = 0;
    }
    for (size_t i=min; i < max->digits; i++){
        int32_t step = max->number[i] - v_ume;
        if (step < 0){
            dif.number[i] = DIGIT_MAX - 1;
            v_ume = 1;
        }
        else{
            dif.number[i] = step;
            v_ume = 0;
        }
        step == 0 ? zeros++ : zeros = 0;
    }

    dif.digits = max->digits - zeros;;
    return dif;
}

BigInt BigInt::operator-(const int32_t & num) const{
    return *this - BigInt(num);
}

BigInt BigInt::operator*(const BigInt & num) const{
    if (num == BigInt(0) || *this == BigInt(0)){
        return BigInt(0);
    }

    const BigInt *min;
    const BigInt *max;
    if (num.digits > digits){
        min = this;
        max = &num;
    }
    else{
        min = &num;
        max = this;
    }

    BigInt mult;
    mult.digits = min->digits + max->digits;
    mult.number = new int32_t[mult.digits];
    for (size_t i=0; i < mult.digits; i++){
        mult.number[i] = 0;
    }

    for (size_t i=0; i < min->digits; i++){
        int32_t v_ume = 0;
        int32_t *mult_step = new int32_t[max->digits + 1];
        for (size_t j=0; j < max->digits; j++){
            int32_t step = min->number[i] * max->number[j] + v_ume;
            if (step >= DIGIT_MAX){
                v_ume = step / DIGIT_MAX;
                mult_step[j] = step - v_ume * DIGIT_MAX;
            }
            else{
                v_ume = 0;
                mult_step[j] = step;
            }
        }
        size_t mult_step_size = max->digits;
        if (v_ume != 0){
            mult_step[max->digits] = v_ume;
            mult_step_size++;
        }

        v_ume = 0;
        for (size_t j=0; j<mult_step_size; j++){
            int32_t sum = mult_step[j] + mult.number[i+j] + v_ume;
            if (sum >= DIGIT_MAX){
                mult.number[i+j] = sum - DIGIT_MAX;
                v_ume = 1;
            }
            else{
                mult.number[i+j] = sum;
                v_ume = 0;
            }
        }
        if (v_ume != 0){
            for (size_t j=mult_step_size + i; j<mult.digits; j++){
                int32_t sum = mult.number[j] + v_ume;
                if (sum >= DIGIT_MAX){
                    mult.number[j] = sum - DIGIT_MAX;
                    v_ume = 1;
                }
                else{
                    mult.number[j] = sum;
                    break;
                }
            }
        }

        delete[] mult_step;
    }

    if (mult.number[mult.digits - 1] == 0){
        mult.digits--;
    }

    return mult;
}

BigInt BigInt::operator*(const int32_t & num) const{
    return (*this) * BigInt(num);
}

bool BigInt::operator==(const BigInt & num) const{
    if (digits != num.digits){
        return false;
    }

    for (size_t i=0; i<digits; i++){
        if (number[i] != num.number[i]){
            return false;
        }
    }

    return true;
}

bool BigInt::operator<(const BigInt & num) const{
    if (digits > num.digits){
        return false;
    }

    if (digits < num.digits){
        return true;
    }

    for (size_t i=0; i<digits; i++){
        if (number[digits-i-1] < num.number[digits-i-1]){
            return true;
        }
        else if (number[digits-i-1] > num.number[digits-i-1]){
            return false;
        }
    }

    return false;
}

bool BigInt::operator>(const BigInt & num) const{
    return num < *this;
}

bool BigInt::operator<=(const BigInt & num) const{
    return (*this < num) || (*this == num);
}

bool BigInt::operator>=(const BigInt & num) const{
    return (*this > num) || (*this == num);
}

std::ostream& operator<<(std::ostream& output, const BigInt& num){
    if (num.digits == 0){
        return output;
    }

    output << num.number[num.digits - 1];
    for (size_t i=1; i<num.digits; i++){
        std::stringstream strm (std::ios_base::in | std::ios_base::out);
        strm << num.number[num.digits - i - 1];
        std::string str_num;
        strm >> str_num;
        size_t length = str_num.length();
        for (size_t i=0; i < num.DIGIT_MAX_ORDER - length; i++){
            output << 0;
        }
        output << str_num;
    }
    return output;
}
