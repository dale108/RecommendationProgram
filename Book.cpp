// Author: Dale Berg, CPSC 2430 02
// Filename: Book.cpp
// Assignment: P1, Recommendations
// Date: 4/20/2019

// Purpose: This is the implementation of the Book interface. This file
// contains implementations of both the BookInventory class, and it's internal
// Book struct. Books are simple objects containing information: the title,
// author, year and ISBN number. BookInventory has fields for capacity, size,
// and inventory. Capacity represents the total amount
// of books BookInventory is capable of holding.
// Size represents how many Books have been added to the list.
// Inventory is the actual array of Book objects.


#include "Book.h"

#include<iostream> // used for printing list of books to console.

using namespace std;



//+++++++++++++++++++++++++++++++
//     BOOK STRUCT
//+++++++++++++++++++++++++++++++


Book::Book() {
   title = "x";
   isbn =0;
}

// Pre: Takes in all information to instatntiate a book object as arguments.
// Post: Creates a new book object.
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


//+++++++++++++++++++++++++++++++
//     BOOK INVENTORY
//+++++++++++++++++++++++++++++++

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


//Overloaded = operator
BookInventory& BookInventory::operator =( const BookInventory &inv2 ) {
    if( this != &inv2 ) {

       delete [] inventory;

       capacity = inv2.capacity;
       size = inv2.size;
       inventory = new Book[capacity];

       for( int i = 0; i < size; i++ ) {
          inventory[i] = inv2.inventory[i];
       }
    }

       return *this;
}


// Purpose: Create a new Book object and add it to the BookInventory
// Pre: Argument represent all information for instatntiating new books objects.
//Post: Book added to the BookInventory.
void BookInventory::addBook( string author, string title, string year, int isbn ) {
    if( size >= capacity ) {
       ensureCapacity();
    }
    Book b(author, title, year, isbn);
    inventory[size] = b;
    size++;
 }


// Purpose: Ensures that the BookInventory has enough space allocated for more
// books to be added. Ensures that we will not overrun our allocated memory.
// Post: Capacity of BookInventory is incresed twofold.
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

string BookInventory::getAuthor( int n ) {
   return inventory[n].getAuthor();
}

// Purpose: Returns books located at index postition in BookInventory
// Pre: Index of book in BookInventory
//Post: Returns Book at position passed as argument.
Book& BookInventory::getBook( int index ) {
    return inventory[index];
 }

 // Purpose: Returns the total cpacity of the BookInventory
 int BookInventory::getCapacity() {
    return capacity;
 }


 // Purpose: Returns the title of the book located at the given index.
 // Pre: Index of Book in BookInventory
 //Post: Returns title of book at position n as a string.
 string BookInventory::getTitle( int n ) {
    return inventory[n].getTitle();
}


// Purpose: Resturns numeric representation of how many elements
// have been added to the list.
int BookInventory::getSize() {
   return size;
}


// Purpose: Prints list of all books in BookInventory to the console.
void BookInventory::seeAllBooks() {
   for(int i = 0; i < size; i++ ) {
      cout << inventory[i].getTitle() << ", ";
    }
}

// Purpose: returns a string representation of all books in the inventory
// seperated by commas.
string BookInventory::allBooksString() {
   string rs = "";
   for(int i = 0; i < size; i++) {
      Book b = inventory[i];
      rs += b.getAuthor();
      rs += ", ";
      rs += b.getTitle();
      rs += ", ";
      rs += b.getYear();
      rs += "\n";
   }
   return rs;
}
