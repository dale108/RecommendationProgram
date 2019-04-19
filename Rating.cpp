// // Rating.cpp
#include "Rating.h"
#include <iostream>
using namespace std;

//************** RATING struct *************
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

bool Rating::validateRating( int rating ) {
   if(rating == HATED_IT || rating == DIDNT_LIKE || rating == HAVENT_READ
      || rating == OK || rating == LIKE || rating == REALLY_LIKE ) {
         return true;
      }

   return false;
}


// **** CONSTRUCTORS

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


//  RatingList::RatingList( const RatingList &inv2 ) {
//
//     verticalSize = inv2.verticalSize;
//    horizontalSize = inv2.horizontalSize;
//    colNumber = inv2.colNumber;
//    rowNumber = inv2.rowNumber;
//    inventory = new Rating*[100];
//    for( int i = 0; i < 100; i++ ){
//       inventory[i] = new Rating*;
//    }
//
//    for( int i = 0; i < rowNumber; i++ ) {
//       for( int j = 0; j < colNumber; j++ ) {
//          inventory[i][j] = inv2.inventory[i][j];
//       }
//    }
//  }



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


void RatingList::addRating( Book &book, int memberNumber, int score ) {

   // hashing style ensures
   if( bookSize > (bookCapacity * .75) ) {
      ensureBookCapacity();
   }
   if( memberSize > (memberCapacity * .75) ) {
      ensureMemberCapacity();
   }
   Rating d(book, memberNumber, score);
   int i = book.getIsbn();
   cout << "Adding to row : " << memberNumber << " and col " << i << endl;
   inventory[memberNumber][i] = d;
}

void RatingList::allUserRatings( int accountNumber ) {
   cout << "[ ";
   for(int i = 0; i < bookSize; i++) {
      cout << inventory[accountNumber][i].getScore() << ", ";
   }
}

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


int RatingList::getBookSize() {
   return bookSize;
}

int RatingList::getMemberSize(){
   return memberSize;
}


int RatingList::getMostSimilar( int accountNumber ) {

   int mostSimilarUser = -1;
   int mostSimilarSum = 0;
   int compareSum = 0;

   cout << "Member size is: " << memberSize << endl;

   for(int i = 0; i < memberSize; ++i) {
      if( i == accountNumber ) {
         ++i;
      }
      else {
         cout << "Into else case " << endl;
         for(int j = 0; j < bookSize; ++j) {
            int userScore = inventory[accountNumber][j].getScore();
            int otherScore = inventory[i][j].getScore();
            compareSum += (userScore * otherScore);
         }
         if( compareSum > mostSimilarSum ) {
            mostSimilarSum = compareSum;
            mostSimilarUser = i;
         }
      }
      compareSum = 0;
   }
   return mostSimilarUser;
}



Rating& RatingList::getRating( int accountNumber, int isbn ) {
     return inventory[accountNumber][isbn];
}


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
