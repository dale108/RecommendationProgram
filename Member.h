//Member.h
//
#ifndef MEMBER_H
#define MEMBER_H

// MemberInventory functions as a repository for Member objects. Member is a
// private struct which contains 3 pieces of information: name, account number,
// and a boolean field representing whether the user is currently logged in.
// This class also features a p1Vector of users who are currently logged in,
// so that

#include<string>

using namespace std;


class Member {

private:

   string name; // allows duplicates
   long accountNumber; // long to feature many users
   bool loggedIn;


public:

   Member();
   Member( string name, int accountNumber );

   void login(); // toggles isLogged in
   void logout(); // toggles isLogged out

   bool isLoggedIn();

   string getName();

   int getAccountNumber();


};


class  MemberList {

private:

   int capacity;
   int size;
   int numElements;
   Member *inventory;


public:

   //**** CONSTRUCTORS ****

   // Basic constructor
   MemberList( int setCapacity );
   // Copy constructor
   MemberList( const MemberList& );

   ~MemberList();

   //Overloaded assignment operator
   MemberList& operator =( const MemberList &inv2 );


   void addMember( string name, int accountNumber );

   void addMember( Member& m );

   void ensureCapacity();

   int getCapacity();

   Member& getMember ( int index );

   Member& getMemberByNumber( int acct );

   int getNumberMembers(); // Total number of Members in the inventory

   Member& getLastMember();

    Member& getUserByNumber( int accountNum );

   int getSize();

   int indexOf( string memberName );

   void seeAllMembers();

   void printAllInfo();

};

#endif