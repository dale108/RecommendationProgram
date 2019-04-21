#include "Rating.h"
#include "Rating.cpp"
#include <iostream>
#include "Book.cpp"
#include "Book.h"

int main() {
      Book book;
      Book book2;
      Book book3("something", "nothing", "sorrow", 6);


      RatingList ratings(10,10);

      cout << ratings.getMemberCapacity() << endl;
      cout << ratings.getMemberCapacity() << endl;
      //ratings.setMemberSize(10);
      //cout << ratings.getMemberCapacity() << endl;
      ratings.addRating(book, 0, 5);
      ratings.addRating(book3, 1, 5);
      cout << ratings.getMemberCapacity() << endl;
      ratings.addRating(book, 1, 5);
      ratings.addRating(book3, 9, 5);
      cout << ratings.getMemberCapacity() << endl;
      //ratings.populate();
      //ratings.populateRow();
      ratings.seeAllRatings();

}
