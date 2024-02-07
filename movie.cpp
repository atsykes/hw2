#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : 
    Product(category, name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}

std::set<std::string> Movie::keywords() const
{
    set<string> key = parseStringToWords(getName());
    set<string> key2 = parseStringToWords(genre_);
    key = setUnion(key, key2);
    return key;
}

std::string Movie::displayString() const
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
    s += "\nGenre: " + genre_ + " Rating: " + rating_;
    s += "\n" + newprice + " " + to_string(qty_) + " left."; 
    return s;
}

void Movie::dump(std::ostream& os) const
{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}