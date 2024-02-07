#include "mydatastore.h"
#include "util.h"
#include <iostream>

using namespace std;

MyDataStore::~MyDataStore()
{   
    // Deleting products/users that have been allocated on the heap
    for (unsigned int i=0; i < prod_.size(); ++i)
    {
        delete prod_[i];
    }
    for (unsigned int i=0; i < users_.size(); ++i)
    {
        delete users_[i];
    }
    // Deleting the deques that have been allocated on the heap
    for (map<string, deque<Product*> *>::iterator it = carts_.begin(); it != carts_.end(); ++it)
    {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p)
{
    prod_.push_back(p);
    set<string> keys = p->keywords();
    // Add the product into the map, corresponding with it's keyterms
    for (set<string>::iterator it=keys.begin(); it != keys.end(); ++it)
    {
        maps_[*it].insert(p);
    }
}

void MyDataStore::addUser(User* u)
{
    users_.push_back(u);
    deque<Product*> *d = new deque<Product*>;
    // add the pair between the user's name and their cart
    carts_.insert(pair<string, deque<Product*> *>(u->getName(), d));
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    vector<Product*> prods; // matches; returning
    set<Product*> setprods;

    for (unsigned int i=0; i < terms.size(); ++i) // iterating through terms
    {
        set<Product*> temp = maps_[terms[i]];

        if (type == 0) // AND
        {
            if (setprods.empty())
            {
                setprods = temp;
            }
            setprods = setIntersection(temp, setprods);
        }
        else // OR
        {
            setprods = setUnion(temp, setprods);
        }
    }
    set<Product*>::iterator it;
    // transfer the set of prods into the vector
    for (it=setprods.begin(); it != setprods.end(); ++it)
    {
        prods.push_back(*it);
    }
    return prods;
}

void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;
    for (unsigned int i=0; i < prod_.size(); ++i)
    {
        prod_[i]->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for (unsigned int i=0; i < users_.size(); ++i)
    {
        users_[i]->dump(ofile);
    }
    ofile << "</users>" << endl;
}

bool MyDataStore::addToCart(string u, Product* p)
{
    bool valid = false;
    map<string, deque<Product*>*>::iterator it = carts_.find(u); 
    if (it != carts_.end())
    {
        it->second->push_back(p);
        valid = !valid;
    }
    return valid;
}

vector<Product*> MyDataStore::viewCart(string u)
{
    map<string, deque<Product*>*>::iterator it = carts_.find(u); 
    vector<Product*> returnee;
    for (unsigned int i=0; i < it->second->size(); ++i)
    {
        returnee.push_back(it->second->at(i));
    }
    return returnee;
}

bool MyDataStore::userExists(string u)
{
    map<string, deque<Product*>*>::iterator it = carts_.find(u); 
    return (it != carts_.end());
}

void MyDataStore::buyCart(string u)
{
    map<string, deque<Product*>*>::iterator it = carts_.find(u); 
    deque<Product*>* newCart = new deque<Product*>;
    deque<Product*>* temp;
    
    User* current;
    for (unsigned int i=0; i < users_.size(); ++i)
    {
        if (u == users_[i]->getName()) {current = users_[i];}
    }

    // Buying items
    size_t deque_s = it->second->size();
    for (unsigned int i=0; i < deque_s; ++i)
    {
        double user_balance = current->getBalance();
        int quantity = it->second->at(i)->getQty();
        double product_price = it->second->at(i)->getPrice();

        // if there are enough items, and the user has enough money
        if (quantity > 0 && user_balance >= product_price)
        {
            it->second->at(i)->subtractQty(1);
            current->deductAmount(product_price);
        }
        // adds all items that have not been bought into a separate deque
        else
        {
            newCart->push_back(it->second->at(i));
        }
    }
    temp = it->second;
    temp->clear();
    it->second = newCart;
    delete temp;
}