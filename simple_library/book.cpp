#include "book.hh"
#include <iostream>
#include "date.cpp"
using namespace std;

Book::Book(string const &author, string const &name):
    author_(author),
    name_(name),
    loan_date_(Date()),
    return_date_(Date()),
    available_(true)
{

}



void Book::loan(const Date& date){
    if (available_){
        loan_date_ = date;
        return_date_ = loan_date_;
        return_date_.advance(28);
        available_ = false;

    } else {
        cout <<"Already loaned: cannot be loaned"<<endl;
        return;
    }
}

void Book::renew()
{
    if(available_){
        cout<<"Not loaned: cannot be renewed"<<endl;
    }
    else{
        return_date_.advance(28);
    }
}

void Book::give_back()
{
    available_ = true;

}

void Book::print() const
{
    cout << author_<< " : "<< name_<<endl;
    if (available_){
        cout << "- available"<<endl;
    }
    else {
        cout << "- loaned: ";
        loan_date_.print();
        cout << "- to be returned: ";
        return_date_.print();
    }
}
