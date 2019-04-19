//Rating.hpp
// Dale Berg, CPSC 2430 02
// P1, Recommendations
// 4/9/2019

/*
* Purpose: This class represents a collection of ratings. It contains a struct called
* Rating and a custom vector of ratings submitted by users in the past.
* Each rating has three pieces of information: Rating, Rating and integer score
* which represents the score the user has assigned to the Rating. Users may only
* rate a Rating with the following integer values:
* Hated it: -5
* Disliked it: -3
* Haven't read (default): 0
* Ok: 1
* Liked it: 3
* Loved it: 5
*/

#ifndef RATING_H
#define RATING_H

#include "Book.h" // rating has a book field.

using namespace std;

class Rating {

public:
   // *******************
   // * CONSTRUCTORS     *
   // *******************
   Rating();

   Rating( Book book, int memberNumber, int rating );


   // *******************
   // * METHODS     *
   // *******************
   string getBookTitle();

   int getMemberNumber();

   int getScore();

   void setRating(int n);


private:

   // constants representing possible book ratings
   const static int HATED_IT = -5;
   const static int DIDNT_LIKE = -3;
   const static int HAVENT_READ = 0;
   const static int OK = 1;
   const static int LIKE = 3;
   const static int REALLY_LIKE = 5;

   Book book;
   int memberNumber;
   int rating; // numerical rating of book

   bool validateRating( int rating ); // private validation method

};


class RatingList {

private:

   int bookCapacity; // number of columns.
   int memberCapacity; // number of rows.
   int bookSize; // number of books in each row.
   int memberSize; // number of rows actually in use;.
   Rating **inventory;

public:

      //**** CONSTRUCTORS ****

      // Basic constructor
      RatingList( int bookCapacity, int memberCapacity );
      // Copy constructor
      RatingList( const RatingList& );
      ~RatingList();

      RatingList& operator =( const RatingList& );

      //*** Getters/Setters
      // *************
      // * METHODS   *
      // **************

      void addRating( Book &book, int memberNumber, int score );

      void allUserRatings( int accountNumber );

      Rating& getRating ( int index );

      Rating& getRating( int accountNumber, int isbn );

      int getNumberRatings(); // Total number of Ratings in the inventory

      void ensureMemberCapacity();

      void ensureBookCapacity();

      int getBookCapacity();

      int getBookSize();

      int getMostSimilar( int accountNumber );

      int getMemberCapacity();

      int getMemberSize();

      void seeAllRatings();

      void setBookSize( int numberBooks );

      void setMemberSize( int numberMembers );

      void updateRating( int , int, int);

};

#endif
