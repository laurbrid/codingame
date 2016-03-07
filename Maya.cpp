#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

class Symbol
{
private:
    string lines_;
    size_t value_;
    size_t height_;
    size_t width_;
    
public:
    Symbol(string lines, size_t value, size_t height, size_t width) 
        : lines_(lines), value_(value), height_(height), width_(width) {}
    
    size_t value() const { return value_; }
    const string& lines() const { return lines_; }    
    size_t height() const { return height_; }
    size_t width() const { return width_; }
};

ostream& operator<<(ostream& os, const Symbol& symbol)
{
    for (size_t h = 0; h < symbol.height(); ++h)
    {
        os << symbol.lines().substr(h * symbol.width(), symbol.width()) << endl;        
    }
    return os;
}

class Alphabet
{
private:
    vector<Symbol> symbols_;
    size_t height_;
    size_t width_;

public:
    Alphabet(const string& lines, size_t height, size_t width, size_t num)
        : height_(height), width_(width)
    {
        assert(lines.length() == height * width * num);
        initSymbols(lines, num);
    }
    
    const Symbol* fromValue(const size_t value) const
    {
        assert(value < symbols_.size()); 
        if (value >= symbols_.size())
        {
            return nullptr;
        }
        return &symbols_[value];
    }
    
    const Symbol* fromValue(const string& lines) const
    {
        for (vector<Symbol>::const_iterator it = symbols_.cbegin();
            it != symbols_.cend(); 
            ++it)
        {
            if (it->lines().compare(lines) == 0)
            {
                return &*it;
            }
        }
        return nullptr;
    }
    
    size_t height() const { return height_; }
    size_t width() const { return width_; }
    size_t num() const { return symbols_.size(); }
    
private:
    void initSymbols(const string& lines, const size_t num)
    {
        for (size_t value = 0; value < num; ++value)
        {
            string symLines;
            for (size_t h = 0; h < height_; ++h)
            {
                symLines += lines.substr((value + h * num) * width_, width_);
            }
            symbols_.push_back(Symbol(symLines, value, height_, width_));
        }        
    }
    
};

class MayaNumber
{
private:
    vector<const Symbol*> symbols_;
    const Alphabet& alphabet_;
    
public:
    friend ostream& operator<<(ostream& os, const MayaNumber& number);
    
    MayaNumber(const Alphabet& alphabet, const string& lines)
        : alphabet_(alphabet)
    {
        size_t n = alphabet.height() * alphabet.width();
        for (int i = 0; i < lines.length(); i += n)
        {
            symbols_.push_back(alphabet.fromValue(lines.substr(i, n)));            
        }
    }
    
    MayaNumber(const Alphabet& alphabet, const int value)
        : alphabet_(alphabet)
    {
        size_t tempVal = value;
        while (tempVal >= alphabet.num())
        {
            size_t d = tempVal / alphabet.num();
            symbols_.push_back(alphabet.fromValue(d));
            tempVal %= alphabet.num(); 
        }
        symbols_.push_back(alphabet.fromValue(tempVal));
    }
    
    int intValue() const
    {
        int p = 1;
        int val = 0;
        for (vector<const Symbol*>::const_reverse_iterator it = symbols_.crbegin();
            it != symbols_.crend(); ++it)
        {
            val += (*it)->value() * p;
            p *= 20;
        }
        return val;
    }
    
    MayaNumber operator+(const MayaNumber& other) const
    {
        return MayaNumber(alphabet_, intValue() + other.intValue());
    }
    
    MayaNumber operator-(const MayaNumber& other) const
    {
        return MayaNumber(alphabet_, intValue() - other.intValue());
    }

    MayaNumber operator*(const MayaNumber& other) const
    {
        return MayaNumber(alphabet_, intValue() * other.intValue());
    }

    MayaNumber operator/(const MayaNumber& other) const
    {
        return MayaNumber(alphabet_, intValue() / other.intValue());
    }
};

ostream& operator<<(ostream& os, const MayaNumber& number)
{
    for (vector<const Symbol*>::const_iterator it = number.symbols_.cbegin();
        it != number.symbols_.cend();
        ++it)        
    {
        os << **it << endl;
    }
    return os;
}


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int L;
    int H;
    cin >> L >> H; cin.ignore();
    string num1Line;
    string lines;
    for (int i = 0; i < H; i++) {
        string numeral;
        cin >> numeral; cin.ignore();
        lines += numeral;
    }
    Alphabet alphabet(lines, H, L, 20);
    
    int S1;
    string num1Lines;
    cin >> S1; cin.ignore();
    for (int i = 0; i < S1; i++) {
        cin >> num1Line; cin.ignore();
        num1Lines += num1Line;
    }
    int S2;
    string num2Lines;
    cin >> S2; cin.ignore();
    for (int i = 0; i < S2; i++) {
        string num2Line;
        cin >> num2Line; cin.ignore();
        num2Lines += num2Line;
    }
    
    char operation;
    cin >> operation; cin.ignore();

    MayaNumber num1(alphabet, num1Lines);
    MayaNumber num2(alphabet, num2Lines);
    
    switch (operation)
    {
        case '+': cout << num1 + num2 << endl; break;
        case '-': cout << num1 - num2 << endl; break;
        case '*': cout << num1 * num2 << endl; break;
        case '/': cout << num1 / num2 << endl; break;
    }
    
}
