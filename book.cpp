#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) : 
    Product(category, name, price, qty)
{
    isbn_ = isbn;
    author_ = author;
}

std::set<std::string> Book::keywords() const
{
    set<string> key = parseStringToWords(getName());
    set<string> key2 = parseStringToWords(author_);
    key = setUnion(key, key2);
    key.insert(isbn_);
    return key;
}

std::string Book::displayString() const
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
    s += "\nAuthor: " + author_ + " ISBN: " + isbn_;
    s += "\n" + newprice + " " + to_string(qty_) + " left."; 
    return s;
}

void Book::dump(std::ostream& os) const
{
    Product::dump(os);
    os << isbn_ << "\n" << author_ << endl;
}