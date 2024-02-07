#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : 
    Product(category, name, price, qty)
{
    size_ = size;
    brand_ = brand;
}

std::set<std::string> Clothing::keywords() const
{
    set<string> key = parseStringToWords(getName());
    set<string> key2 = parseStringToWords(brand_);
    key = setUnion(key, key2);
    return key;
}

std::string Clothing::displayString() const
{
    string s = getName();
    string price = to_string(price_);
    string newprice;
    bool valid = false;
    int counter = 0;
    
    // Setting to only 2 decimal places
    for (unsigned int i=0; i < price.size(); ++i)
    {
        if (valid || price[i] == '.')
        {
            valid = true;
            if (counter == 3) {break;}
            counter++;
        } 
        newprice += price[i];
    }
    s += "\nSize: " + size_ + " Brand: " + brand_;
    s += "\n" + newprice + " " + to_string(qty_) + " left."; 
    return s;
}

void Clothing::dump(std::ostream& os) const
{
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}