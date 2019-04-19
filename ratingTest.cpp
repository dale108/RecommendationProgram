#include "Rating.h"
#include "Rating.cpp"
#include <iostream>
#include "Book.cpp"
#include "Book.h"

int main() {
      Book book;
      Book book2;
      Book book3("something", "nothing", "sorrow", 19);


      RatingList ratings(50,50);

      //cout << book2.getIsbn() << endl;

      //ratings.addRating(book, 0, 5);
      //ratings.addRating(book3, 1, 5);
      //ratings.addRating(book, 1, 5);
      ratings.addRating(book3, 9, 5);
      //ratings.addMember(5);
      //ratings.addMember(9);
      //ratings.populate();
      //ratings.populateRow();
      ratings.seeAllRatings();

}
