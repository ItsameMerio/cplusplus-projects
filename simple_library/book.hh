#ifndef BOOK_HH
#define BOOK_HH
#include <string>
#include<iostream>
#include "date.hh"

using namespace std;

class Book
{
public:

   Book ( const string& author, const string&  name);
   void loan(const Date &date);
   void renew();
   void give_back();
   void print() const;


private:
    const string author_;
    const string name_;
    Date loan_date_ ;
    Date return_date_ ;
    bool available_ ;



};

#endif // BOOK_HH
