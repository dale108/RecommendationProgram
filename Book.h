// Author: Dale Berg, CPSC 2430 02
// Filename: Book.h
// Assignment: P1, Recommendations
// Date: 4/20/2019

// Purpose: This class represents a collection of Book objects. The collection,
// BookInventory, is implemented as a dynamic array of Book objects. Each Book
// object has 4 pieces of information: author, title, year and isbn.

#ifndef BOOKINVENTORY_H
#define BOOKINVENTORY_H

#include<string>

using namespace std;

struct Book {

public:
   // copy constructor impicit, does not need definition here.
   // struct constructor
   Book();
   Book(string author, string title, string year, int isbn);

   // Getters and setters
   // order is alphabetical
   int getIsbn() const;
   string getTitle() const;
   string getYear() const;
   string getAuthor() const;


private:

   string author;
   string title;
   string year;
   int isbn;

};

class  BookInventory {


public:

   BookInventory( int setCapacity );
   // Copy constructor
   BookInventory( const BookInventory& );
   ~BookInventory();

   BookInventory& operator =( const BookInventory& );


   // order is alphabetical
   void addBook(string author, string title, string year, int isbn);

   string allBooksString();

   void ensureCapacity();

   string getAuthor(int n);

   Book& getBook ( int index );

   int getNumberBooks();

   string getTitle(int n);

   int getCapacity();

   int getSize();

   int indexOf( string bookTitle );

   void seeAllBooks();

private:

   int capacity;
   int size;
   Book *inventory; // Pointer to the array


};



#endif
