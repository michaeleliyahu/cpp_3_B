#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <string>

using namespace std;
using namespace ariel;
map<string, double> unit_change_num;
map<string, string> unit_change_str;

map<string, double> unit_change_num_rev;
map<string, string> unit_change_str_rev;
void NumberWithUnits::read_units(std::ifstream &stram)
{
    string keep;
    char x = 0;
    int i = 0;
    string word1;
    string word2;
    while (stram >> keep)
    {
        if (i == 1)
        {
            word1 = keep;
        }
        if (i == 3)
        {
            word2 = keep;
        }
        if (i == 4)
        {
            // cout<<"1. "<<word1<<" 2."<<word2<<" 3. "<<keep<<" ";
            unit_change_num.insert(pair<string, double>(word1, atof(word2.c_str())));
            unit_change_str.insert(pair<string, string>(word1, keep));
            unit_change_str_rev.insert(pair<string, string>(keep, word1));
            // cout << "1. " << keep << " 2." << word1 << " ";
            word1.clear();
            word2.clear();
            i = 0;
        }
        else
        {
            i++;
        }
    }
    // cout << "start";
    // for (std::map<string, string>::iterator it = unit_change_str.begin(); it != unit_change_str.end(); ++it)
    // {
    //     cout << "1. " << it->first << " 2." << unit_change_str[it->first] << "\n";
    //     // unit_change_num_rev.insert(pair<string, int>(it->first, unit_change_num[unit_change_str_rev[it->first]]));
    // }
}
double ariel::change_unit(const string &str, const NumberWithUnits &two)
{

    string str_temp;
    double int_temp = 0;
    ;

    int_temp = two._num;
    str_temp = two._str;

    bool reverse = false;
    bool forward = false;
    if (str != str_temp)
    {
        // int counter = 0;
        // cout << "start \n";
        while (unit_change_str.find(str_temp) != unit_change_str.end() && !forward)
        {
            // cout << str_temp << ", " << int_temp << ",";
            if (unit_change_str[str] == str_temp)
            {
                int_temp = int_temp / unit_change_num[str];
                forward = true;
            }
            else
            {
                int_temp = int_temp * unit_change_num[str_temp];
                str_temp = unit_change_str[str_temp];
            }
            // cout<<str_temp<<", ";
            if (str == str_temp)
            {
                forward = true;
            }
        }
        if (!forward)
        {
            // cout<<"here "<<two._str<<" "<<str<<"\n";
            str_temp = str;
            int_temp = two._num;
            while (unit_change_str.find(str_temp) != unit_change_str.end() && !reverse)
            {
                // cout<<"1." << str_temp << "2."<< str<<"3."<<unit_change_str_rev[str_temp]<<", ";

                int_temp = int_temp / unit_change_num[str_temp];
                str_temp = unit_change_str[str_temp];
                if (str_temp == two._str)
                {
                    // cout << int_temp << ", ";
                    reverse = true;
                }
            }
        }
        if (!reverse && !forward)
        {
            // str_temp = two._str;
            // int_temp = two._num;
            // int i =0;
            // while (unit_change_str.find(str_temp) != unit_change_str.end() && !reverse)
            // {
            //     // cout<<"1." << str_temp << "2."<< str<<"3."<<unit_change_str_rev[str_temp]<<", ";
            //     cout <<i<< str_temp << ", ";
            //     i++;
            //     int_temp = int_temp * unit_change_num[str_temp];
            //     str_temp = unit_change_str[str_temp];
            //     if (str_temp == str)
            //     {
            //         // cout << int_temp << ", ";
            //         reverse = true;
            //     }
            // }
            if (!reverse)
            {
                throw " bad";
            }
        }
    }
    return int_temp;
}
void ariel::check_exist(const std::string &str, double num)
{

    if (unit_change_str.find(str) == unit_change_str.end() && unit_change_str_rev.find(str) == unit_change_str_rev.end())
    {
        throw " not found";
    }
}
NumberWithUnits NumberWithUnits::operator-() const
{

    return NumberWithUnits(-_num, _str);
}
NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &nl) const
{
    double x = change_unit(_str, nl);
    return NumberWithUnits(_num - x, _str);
}
NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &nl)
{
    double x = change_unit(_str, nl);
    _num -= x;
    return *this;
}

NumberWithUnits NumberWithUnits::operator+() const
{
    return NumberWithUnits(_num, _str);
}
NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &nl) const
{
    double x = change_unit(_str, nl);
    return NumberWithUnits(_num + x, _str);
}
NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &nl)
{
    double x = change_unit(_str, nl);
    _num += x;
    return *this;
}

const float TOLARENCE = 0.001;
bool ariel::operator>(const NumberWithUnits &one, const NumberWithUnits &two)
{
    double x = change_unit(one._str, two);
    return (one._num > x);
}
bool ariel::operator>=(const NumberWithUnits &one, const NumberWithUnits &two)
{
    double x = change_unit(one._str, two);
    return ((abs(one._num - x) < TOLARENCE) || (one._num > x));
}
bool ariel::operator<(const NumberWithUnits &one, const NumberWithUnits &two)
{
    double x = change_unit(one._str, two);
    return (one._num < x);
}
bool ariel::operator<=(const NumberWithUnits &one, const NumberWithUnits &two)
{
    double x = change_unit(one._str, two);
    return ((abs(one._num - x) < TOLARENCE) || (one._num < x));
}
// bool ariel::operator==(const NumberWithUnits &one, const NumberWithUnits &two)
// {
//     double x = change_unit(one._str, two);
//     return (abs(one._num - x) < TOLARENCE);
// }
bool NumberWithUnits::operator==(const NumberWithUnits &nl) const
{
    double x = change_unit(_str, nl);
    return (abs(_num - x) < TOLARENCE);
}
bool ariel::operator!=(const NumberWithUnits &one, const NumberWithUnits &two)
{
    return (!(one == two));
}

NumberWithUnits &NumberWithUnits::operator++()
{
    _num++;
    return *this;
}
NumberWithUnits NumberWithUnits::operator++(int dummy_flag_for_postfix_increment)
{
    NumberWithUnits copy = *this;
    _num++;
    return copy;
}
NumberWithUnits &NumberWithUnits::operator--()
{
    _num--;
    return *this;
}
NumberWithUnits NumberWithUnits::operator--(int dummy_flag_for_postfix_increment)
{
    NumberWithUnits copy = *this;
    _num--;
    return copy;
}

NumberWithUnits ariel::operator*(double x, const NumberWithUnits &nl)
{
    return NumberWithUnits(x * nl._num, nl._str);
}
NumberWithUnits ariel::operator*(const NumberWithUnits &nl, double x)
{
    return NumberWithUnits(x * nl._num, nl._str);
}

ostream &ariel::operator<<(ostream &input, const NumberWithUnits &nl)
{
    input << nl._num << "[" << nl._str << "]";
    return input;
}
istream &ariel::operator>>(istream &input, NumberWithUnits &nl)
{
    // cout << "start \n";
    // string str;
    // string unit;
    // double val = 0;
    // int i = 0;
    // while (input >> str)
    // {
    //     if (i == 0)
    //     {
    //         val = atof(str.c_str());
    //     }
    //     if (i == 1)
    //     {
    //         getAndCheckNextCharIs(input, '[');
    //         if (str[str.length() - 1] == ']')
    //         {

    //             str.resize(str.size() - 1);
    //             unit = str;
    //             // check_exist(unit, val);
    //             nl._num = val;
    //             nl._str = unit;
    //         }
    //     }
    // }
    // cout << "start \n";
    string str;
    string unit;
    double val = 0;
    ios::pos_type start = input.tellg();

    if ((!(input >> val)) ||
        (!(getAndCheckNextCharIs(input, '['))) ||
        (!(input >> unit)) ||
        (!(getAndCheckNextCharIs(input, ']'))))
    {
        if (!unit.empty())
        {
            // cout << "1 " << val << ", " << unit << " ";
            if (unit[unit.length() - 1] == ']')
            {

                unit.resize(unit.size() - 1);
                // cout<<unit<<", ";
                // check_exist(unit, val);
                nl._num = val;
                nl._str = unit;
            }

            // cout << "1 " << val << ", " << unit << " ";
        }
        else
        {
            // cout << "2 " << val << ", " << unit << " ";
            // auto errorstate = input.rdstate();
            // // input.clear();
            // input.seekg(start);
            // input.clear(errorstate);
        }
    }
    else
    {
        // cout << "3 " << val << ", " << unit << " ";
        nl._num = val;
        nl._str = unit;
    }
    check_exist(nl._str, nl._num);

    return input;
}
static istream &ariel::getAndCheckNextCharIs(istream &input, char expectedChar)
{
    // cout << expectedChar << "ff";
    char actualChar = 0;
    input >> actualChar;
    if (!input)
    {
        return input;
    }

    if (actualChar != expectedChar)
    {
        // failbit is for format error
        input.setstate(ios::failbit);
    }
    return input;
}