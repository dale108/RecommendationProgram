// Author: Dale Berg, CPSC 2430 02
// Filename: Rating.h
// Assignment: P1, Recommendations
// Date: 4/20/2019

/*
* Purpose: This class represents a collection of ratings.
* It contains a struct called Rating and a 2 dimensional dynamic
* array data structure called RatingList.
* RatingList has fields for Book and Member capacity and book and member
* size. Capacities represent how many object may be held by the strucuture, and
* sizes represent how many of each objct has been added to the list by a user.
* each row the the 2d underlying array corresponds to a user's account number
* and each column corresponds to the ISBN of a book. For example, the
* rating at row 5, column 6 represents the rating applied by a user with
* account number 5 for a book with ISBN 6.

* Each rating held by RatingList has three pieces of information: Book,
*  memberNumber and an integer score which represents user applied rating.
* Users may only rate a book with the following integer values:
* Hated it: -5
* Disliked it: -3
* Haven't read (default): 0
* Ok: 1
* Liked it: 3
* Loved it: 5
* These values may be chnged by changing the constant assignments in Rating.
*/

#ifndef RATING_H
#define RATING_H

#include "Book.h" // rating has a book field.

using namespace std;

class Rating {

public:

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

public:


      // Basic constructor
      RatingList( int bookCapacity, int memberCapacity );
      // Copy constructor
      RatingList( const RatingList& );
      ~RatingList();

      // Assignment operator
      RatingList& operator =( const RatingList& );


      // *************
      // * METHODS   *
      // **************

      // order is alphabetical
      void addRating(const Book &book, int memberNumber, int score );

      void allUserRatings( int accountNumber );

      void ensureMemberCapacity();

      void ensureBookCapacity();

      Rating& getRating ( int index );

      Rating& getRating( int accountNumber, int isbn );

      int getNumberRatings(); // Total number of Ratings in the inventory

      int getBookCapacity();

      int getBookSize();

      int getMostSimilar( int accountNumber );

      int getMemberCapacity();

      int getMemberSize();

      void seeAllRatings();

      void setBookSize( int numberBooks );

      void setMemberSize( int numberMembers );

      void updateRating( int , int, int);

   private:

      int bookCapacity; // number of columns.
      int memberCapacity; // number of rows.
      int bookSize; // number of books added by user.
      int memberSize; // number of members added by user.
      Rating **inventory;

};

#endif
