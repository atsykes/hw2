#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>
#include <deque>
#include "datastore.h"

class MyDataStore : public DataStore {
public:
    ~MyDataStore();
    void addProduct(Product *p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    bool addToCart(std::string u, Product *p);
    bool userExists(std::string u);
    std::vector<Product*> viewCart(std::string u);
    void buyCart(std::string u);

private:
    std::vector<Product*> prod_;
    std::vector<User*> users_;
    std::map<std::string, std::deque<Product*> *> carts_;
    std::map<std::string, std::set<Product*>> maps_;
};

#endif