#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

class BigInt
{
private:
    std::vector<int> number;
    bool positive;
    int base;
    unsigned int skip;
    static const int default_base = 1000000000;

public:
    //Constructors
    BigInt();
    BigInt(int64_t);
    BigInt(std::string);
    BigInt(const BigInt& b);

    //Adding
    BigInt operator+(BigInt const &) const;
    BigInt &operator+=(BigInt const &);
    BigInt operator+(int64_t const &) const;
    BigInt &operator+=(int64_t);

    //Subtraction
    BigInt operator-(BigInt const &) const;
    BigInt &operator-=(BigInt const &);

    //Multiplication
    BigInt operator*(BigInt const &);
    BigInt &operator*=(BigInt const &);
    BigInt operator*(int64_t const &);
    BigInt &operator*=(int const &);

    //Compare
    bool operator<(const BigInt &) const;
    bool operator>(const BigInt &) const;
    bool operator<=(const BigInt &) const;
    bool operator>=(const BigInt &) const;
    bool operator==(const BigInt &) const;
    bool operator!=(const BigInt &) const;

    //Allocation
    BigInt operator=(const int64_t &);

    //Access
    int operator[](int const &);

    //Input&Output
    friend std::istream &operator>>(std::istream &, BigInt &);
    friend std::ostream &operator<<(std::ostream &, BigInt const &);

    //Helpers
    void clear();
    BigInt &abs();

    //Power
    BigInt &pow(int const &);

    //Trivia
    int digits() const;
    int trailing_zeros() const;
private:
    int segment_length(int) const;
    BigInt pow(int const &, std::map<int, BigInt> &);
    int compare(BigInt const &) const; //0 a == b, -1 a < b, 1 a > b
};

BigInt abs(BigInt);
std::string to_string(BigInt const &);
BigInt factorial(int);
