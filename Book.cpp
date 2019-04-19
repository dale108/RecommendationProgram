// Author: Dale Berg, CPSC 2430 02
// Filename: Time.cpp
// Assignment: Lab 01, Time
// Date: 4/10/2019

// Purpose:
// INPUT:
// PROCESS:
// OUTPUT:

#include "Book.h"

#include<iostream>

using namespace std;



//+++++++++++++++++++++++++++++++
//     BOOK STRUCT
//+++++++++++++++++++++++++++++++


Book::Book() {
   title = "x";
   isbn =0;
}


Book::Book(string author, string title, string year, int newIsbn) {

   isbn = newIsbn;
   this->title = title;
   this->year = year;
   this->author = author;
}

int Book::getIsbn() const {
   return isbn;
}

string Book::getTitle() const {
   return title;
}

string Book::getYear() const {
   return year;
}

string Book::getAuthor() const {
   return author;
}

void Book::setIsbn( int newIsbn ) {
   isbn = newIsbn;
}

void Book::setTitle( string newTitle ) {
   title = newTitle;
}

void Book::setYear( string newYear ) {
   cout << "Build me" << endl;
}

void Book::setAuthor( string newAuthor ) {

   cout << "Build me" << endl;
}

BookInventory::BookInventory( int setCapacity ) {

   if( setCapacity > 0 ) {
      size = 0;
      capacity = setCapacity;
      inventory = new Book[capacity];
      for(int i = 0; i < capacity; i++) {
         Book b;
         inventory[i] = b;
      }
   }
   else {
      assert( setCapacity > 0 );
   }
}

// Copy constructor
BookInventory::BookInventory( const BookInventory &inv2 ) {
    capacity = inv2.capacity;
    size = inv2.size;
    inventory = new Book[capacity];

    for( int i = 0; i < size; i++ ) {
       inventory[i] = inv2.inventory[i];
   }
 }

BookInventory::~BookInventory() {
   delete [] inventory;
}


// Overloaded = operator
// BookInventory& BookInventory::operator =( const BookInventory &inv2 ) {
//     if( this != &inv2 ) {
//
//        delete [] inventory;
//
//        capacity = inv2.capacity;
//        size = inv2.size;
//        inventory = new Book[capacity];
//
//        for( int i = 0; i < size; i++ ) {
//           inventory[i] = inv2.inventory[i];
//        }
//
//        return *this;
// }

// Purpose:
// Pre:
//Post:
void BookInventory::addBook( string author, string title, string year, int isbn ) {
    if( size >= capacity ) {
       ensureCapacity();
    }
    //Book b;
    Book b(author, title, year, isbn);
    inventory[size] = b;
    size++;
 }


// Purpose:
// Pre:
//Post:
void BookInventory::ensureCapacity() {

   capacity = capacity * 2;

   Book *tempArr;
    tempArr = new Book[capacity];

   int i = 0;
   for(; i < size; i++ ) {
      tempArr[i] = inventory[i];
   }
   for(; i < capacity; i++ ) {

      tempArr = nullptr;
   }

   delete [] inventory;

   inventory = tempArr;
}

// Purpose:
// Pre:
//Post:
string BookInventory::getAuthor( int n ) {
   return inventory[n].getAuthor();
}


// Purpose:
// Pre:
//Post:
Book& BookInventory::getBook( int index ) {
    return inventory[index];
 }

 // Purpose:
 // Pre:
 //Post:
 int BookInventory::getCapacity() {
    return capacity;
 }


 // Purpose:
 // Pre:
 //Post:
 string BookInventory::getTitle( int n ) {
    return inventory[n].getTitle();
}


// Purpose:
// Pre:
//Post:
int BookInventory::getSize() {
   return size;
}


 // Purpose:
 // Pre:
 //Post:
int BookInventory::indexOf( string bookTitle ) {

  for( int i = 0; i < size; i++ ) {
    if( inventory[i].getTitle() == bookTitle ) {
        return i;
     }
  }
  return -1;
}

// Purpose:
// Pre:
//Post:
void BookInventory::seeAllBooks() {
   for(int i = 0; i < size; i++ ) {
      cout << inventory[i].getTitle() << ", ";
    }
}
