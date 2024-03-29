#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    typename std::set<T> intersection;
    // Adding only what s1 and s2 have in common
    for (typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it)
    {
        if (s2.find(*it) != s2.end()) 
            {
                intersection.insert(*it);
            }
    }
    return intersection;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    typename std::set<T> s_union;
    typename std::set<T>::iterator it;
    // Adding everything from s1
    for (it = s1.begin(); it != s1.end(); ++it) 
    {
        s_union.insert(*it);
    }
    // Adding everything from s2 that does not intersect with s1
    for (it = s2.begin(); it != s2.end(); ++it) 
    {
        if (s_union.find(*it) == s_union.end()) 
            {
                s_union.insert(*it);
            }
    }
    return s_union;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
