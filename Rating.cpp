// Author: Dale Berg, CPSC 2430 02
// Filename: Rating.h
// Assignment: P1, Recommendations
// Date: 4/20/2019

// Purpose: Implementation of the Rating struct and RatingList data structure.

#include "Rating.h"
#include <iostream>
using namespace std;

// *****************
// * RATING STRUCT *
// *****************
// deault constructor for making "dummy" values.
Rating::Rating() {

   Book b;
   memberNumber =0;
   book = b;
   memberNumber = 0;
   rating = 0;

}

Rating::Rating( Book book, int memberNumber, int rating ) {

   validateRating(rating);

   this->book = book;
   this->memberNumber = memberNumber;
   this->rating = rating;

}

int Rating::getScore() {
   return rating;
}

int Rating::getMemberNumber() {
   return memberNumber;
}

void Rating::setRating(int newRating) {
   rating = newRating;
}

// Private method to ensure that vlaues are within the bounds of accepted
// book ratings.
// Pre: numerical rating passed by user.
// Post: boolean value representing whether the value is one of the accepted
// ratings enumerated by the program.
bool Rating::validateRating( int rating ) {
   if(rating == HATED_IT || rating == DIDNT_LIKE || rating == HAVENT_READ
      || rating == OK || rating == LIKE || rating == REALLY_LIKE ) {
         return true;
      }

   return false;
}


// *****************
// * RATING LIST   *
// *****************

//PURPOSE: RatingList constructor.
//PRE: memberCapacity = number of rows, bookCapacity = number coloumns
//POST: initializes new dynamic RatingList with memberCapacity number of
// rows and bookCapacity number of coloumns
RatingList::RatingList( int memberCapacity, int bookCapacity ) { // row and col will set the size of these

   if( bookCapacity <= 0 || memberCapacity <= 0 ) {
      cout << "you can't do that" << endl;
   }

   this->bookCapacity = bookCapacity;
   this->memberCapacity = memberCapacity;
   bookSize = 0;
   memberSize = 0;
   inventory = new Rating*[memberCapacity]; // this allocates columns
   for( int i =0; i < bookCapacity; i++ ) {
      inventory[i] = new Rating[bookCapacity]; // this allocates rows
      for(int j = 0; j < bookCapacity; ++j ) {
         Rating r;
         inventory[i][j] = r;
      }
   }
}

//Purpose: copy constructor
 RatingList::RatingList( const RatingList &inv2 ) {

   this->bookCapacity = inv2.bookCapacity;
   this->memberCapacity = inv2.memberCapacity;
   bookSize = inv2.bookSize;
   memberSize = inv2.memberSize;
   inventory = new Rating*[100];

   for( int i = 0; i < memberCapacity; i++ ) {
      for( int j = 0; j < bookCapacity; j++ ) {
         inventory[i][j] = inv2.inventory[i][j];
      }
   }
 }


RatingList::~RatingList() {
   for(int i = 0; i < bookCapacity; i++ ) {
      delete [] inventory[i];
   }
   delete [] inventory;
}


   // Overloaded = operator
 RatingList& RatingList::operator =( const RatingList &inv2 ) {
    if( this != &inv2 ) {

      for(int i = 0; i < bookCapacity; i++ ) {
          delete [] inventory[i];
      }
      delete [] inventory;

      this->bookCapacity = inv2.bookCapacity;
      this->memberCapacity = inv2.memberCapacity;
      bookSize = inv2.bookSize;
      memberSize = inv2.memberSize;

      inventory = new Rating*[bookCapacity];
      for( int i =0; i < bookCapacity; i++ ){
         inventory[i] = new Rating[memberCapacity]; // number of columns should
         for(int j = 0; j < 100; ++j ) {
            Rating r;
           inventory[i][j] = r;
         }
      }


       for( int i = 0; i < bookCapacity; ++i ) {
          for(int j = 0; j < memberCapacity; ++j )
          inventory[i][j] = inv2.inventory[i][j];
       }
    }
return *this;
}


// Purpose: Add new rating at memberNumber row and isbn of book object column.
// Pre: Book object passed by reference. Passing book by reference saves us
// from having to instantiate a new object. memberNumber oof the member logging
// the rating and score, representing the numerical value of the rating
// being added.
// Post: Rating added to the list.
void RatingList::addRating( const Book &book, int memberNumber, int score ) {

   // hashing style ensures
   if( bookSize > (bookCapacity * .75) ) {
      ensureBookCapacity();
   }
   if( memberSize > (memberCapacity * .75) ) {
      ensureMemberCapacity();
   }
   Rating d(book, memberNumber, score);
   int i = book.getIsbn();
   inventory[memberNumber][i] = d;
}

void RatingList::allUserRatings( int accountNumber ) {
   cout << "[ ";
   for(int i = 0; i < bookSize; i++) {
      cout << inventory[accountNumber][i].getScore() << ", ";
   }
   cout << "\n" <<  endl;
}

// Purpose: Ensures the underlying array has capcity for more books to be added.
// Post: Book capacity is doubled. All values previously added to the list are
// unaffected.
void RatingList::ensureBookCapacity() {

   bookCapacity = bookCapacity * 2;

   Rating **tempArr;
   tempArr = new Rating*[memberCapacity];
   for( int i =0; i < bookCapacity; i++ ) {
      tempArr[i] = new Rating[bookCapacity]; // this allocates rows
      for(int j = 0; j < bookCapacity; ++j ) {
         Rating r;
         tempArr[i][j] = r;
      }

   }

   int k = 0;
   for(int k = 0; k < memberCapacity; k++ ) {
      tempArr[k] = inventory[k];
      for(int l = 0; l < bookSize; l++) {
         tempArr[k][l] = inventory[k][l];
      }
   }

   for(int i = 0; i < memberCapacity; ++i) {
      delete [] inventory[i];
   }
   delete [] inventory;

   inventory = tempArr;
}

// Purpose: Ensures the underlying array has capcity for members to be added.
// Post: member capacity is doubled. All values previously added to the list are
// unaffected.
void RatingList::ensureMemberCapacity() {

   memberCapacity = memberCapacity * 2;

   Rating **tempArr;
   tempArr = new Rating*[memberCapacity];
   for( int i =0; i < bookCapacity; i++ ) {
      tempArr[i] = new Rating[bookCapacity]; // this allocates rows
      for(int j = 0; j < bookCapacity; ++j ) {
         Rating r;
         tempArr[i][j] = r;
      }

   }

   int k = 0;
   for(int k = 0; k < memberCapacity; k++ ) {
      tempArr[k] = inventory[k];
      for(int l = 0; l < bookSize; l++) {
         tempArr[k][l] = inventory[k][l];
      }
   }

   for(int i = 0; i < memberCapacity; ++i) {
      delete [] inventory[i];
   }
   delete [] inventory;

   inventory = tempArr;
}

// Purpose: Returns the number of books which have been added to RatingList by
// client.
int RatingList::getBookSize() {
   return bookSize;
}

// Purpose: Returns the number of members which have been added to RatingList by
// client.
int RatingList::getMemberSize(){
   return memberSize;
}

// Purpose: returns the row of ratings which most resembel
// Pre: Account number of user
// Post: Returns account number of user with ratings most similar to those of
// the member represented by account number passed in as parameter.
int RatingList::getMostSimilar( int accountNumber ) {

   // account number of most similar user
   int mostSimilarUser = -1;
   int mostSimilarSum = 0;
   int compareSum = 0;

   cout << "Member size is: " << memberSize << endl;

   for(int i = 0; i < memberSize; ++i) {
      // skip row of user's own ratings.
      if( i == accountNumber ) {
         ++i;
      }
      else {
         // perform comparisons for each rating in each row of underlying
         // 2 dimensional array.
         for(int j = 0; j < bookSize; ++j) {
            int userScore = inventory[accountNumber][j].getScore();
            int otherScore = inventory[i][j].getScore();
            compareSum += (userScore * otherScore);
         }
         // if more similar user is found update mostSimilar user number.
         if( compareSum > mostSimilarSum ) {
            mostSimilarSum = compareSum;
            mostSimilarUser = i;
         }
      }
      compareSum = 0;
   }
   return mostSimilarUser;
}


// Purpose: Returns rating (by reference) associated with account number of
//  user and isbn of
// book passed in as parameter.
// Pre: account number of user and isbn of book.
// Post: Rating input by client relating to book represented bby isbn.
Rating& RatingList::getRating( int accountNumber, int isbn ) {
     return inventory[accountNumber][isbn];
}

// Purpose: prints all names and numberical ratings by users in data strucute.
void RatingList::seeAllRatings() {
   for(int row = 0; row < memberCapacity; row++) {
      cout << "Member Number is:" << inventory[row][0].getMemberNumber() << " [ ";
      for( int col = 0; col < bookCapacity; col++) {
         cout << inventory[row][col].getScore() << ", ";
      }
      cout << endl;
   }
   cout << " ] " << endl;
   cout << endl;
}

void RatingList::setBookSize( int numberBooks ) {
   bookSize = numberBooks;
}

void RatingList::setMemberSize( int numberMembers ) {
   memberSize = numberMembers;
}

void RatingList::updateRating( int isbn, int memberNumber, int rating) {
   inventory[memberNumber][isbn].setRating(rating);
}
