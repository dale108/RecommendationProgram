//Book.h

// Dale Berg, CPSC 2430 02
// P1, Recommendations
// 4/9/2019
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
   int getIsbn() const;
   string getTitle() const;
   string getYear() const;
   string getAuthor() const;
   void setIsbn( int newIsbn );
   void setTitle( string newTitle );
   void setYear( string newYear );
   void setAuthor( string newAuthor );

private:

   string author;
   string title;
   string year;
   int isbn;

};

class  BookInventory {

private:

   int assignIsbn;
   int capacity;
   int size;

   Book *inventory; // Pointer to the array


public:

   //**** CONSTRUCTORS ****

   // Basic constructor
   BookInventory( int setCapacity );
   // Copy constructor
   BookInventory( const BookInventory& );
   ~BookInventory();

   //BookInventory& operator =( const BookInventory& );

   //*** Getters/Setters
   // Book name collisions will be handled by a sub menu in which the user will
   // choose from a list of authors.

   void addBook(string author, string title, string year, int isbn);

   int getNumberBooks(); // Total number of books in the inventory

   string getAuthor(int n);

   Book& getBook ( int index );

   string getTitle(int n);

   void ensureCapacity();

   int indexOf( string bookTitle );

   int getCapacity();

   int getSize();

   void seeAllBooks();

};



#endif
