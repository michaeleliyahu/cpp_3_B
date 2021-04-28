#include <iostream>
#include <map>

namespace ariel
{
    void check_exist(const std::string &str1, double num);
    class NumberWithUnits
    {
    public:
        double _num;
        std::string _str;

        // NumberWithUnits(int number, std::string str)
        // {
        //     this->number = number;
        //     this->str = str;
        // };
        NumberWithUnits(const double &num, const std::string &str) : _num(num), _str(str)
        {
            check_exist(str, num);
        }
        double num() const
        {
            return _num;
        }
        std::string str() const
        {
            return _str;
        }
        static void read_units(std::ifstream &stram);

        NumberWithUnits operator-() const;
        NumberWithUnits operator-(const NumberWithUnits &nl) const;
        NumberWithUnits &operator-=(const NumberWithUnits &nl);

        NumberWithUnits operator+() const;
        NumberWithUnits operator+(const NumberWithUnits &nl) const;
        NumberWithUnits &operator+=(const NumberWithUnits &nl);

        friend bool operator>(const NumberWithUnits &one, const NumberWithUnits &two);
        friend bool operator>=(const NumberWithUnits &one, const NumberWithUnits &two);
        friend bool operator<(const NumberWithUnits &one, const NumberWithUnits &two);
        friend bool operator<=(const NumberWithUnits &one, const NumberWithUnits &two);
        // friend bool operator==(const NumberWithUnits &one, const NumberWithUnits &two);
        bool operator==(const NumberWithUnits &nl) const;
        friend bool operator!=(const NumberWithUnits &one, const NumberWithUnits &two);

        NumberWithUnits &operator++();
        NumberWithUnits operator++(int dummy_flag_for_postfix_increment);
        NumberWithUnits &operator--();
        NumberWithUnits operator--(int dummy_flag_for_postfix_increment);

        friend NumberWithUnits operator*(double x, const NumberWithUnits &nl);
        friend NumberWithUnits operator*(const NumberWithUnits &nl, double x);
        // NumberWithUnits operator*(const double x);

        friend std::ostream &operator<<(std::ostream &input, const NumberWithUnits &nl);
        friend std::istream &operator>>(std::istream &input, NumberWithUnits &nl);
    };
    double change_unit(const std::string &str, const NumberWithUnits &two);

    static std::istream &getAndCheckNextCharIs(std::istream &input, char expectedChar);
}