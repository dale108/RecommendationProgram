// Author: Dale Berg, CPSC 2430 02
// Filename: Member.h
// Assignment: P1, Recommendations
// Date: 4/20/2019

// Purpose: MemberInventory is a dynamic array of Member objects. Member is a
// private struct which contains 3 pieces of information: name, account number,
// and a boolean field representing whether the user is currently logged in.
// This class also features a p1Vector of users who are currently logged in,
// so that

#ifndef MEMBER_H
#define MEMBER_H

#include<string>

using namespace std;


struct Member {


public:

   Member();
   Member( string name, int accountNumber );

   void login(); // toggles isLogged in
   void logout(); // toggles isLogged out

   bool isLoggedIn();

   string getName();

   int getAccountNumber();

private:

   string name; // allows duplicates
   long accountNumber; // long to feature many users
   bool loggedIn; // represents whether user is logged in



};


class  MemberList {


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

   Member getMemberByNumber( int acct );

   int getNumberMembers(); // Total number of Members in the inventory

   Member& getLastMember();

    Member& getUserByNumber( int accountNum );

   int getSize();

   void seeAllMembers();

   void printAllInfo();

private:

   int capacity;
   int size;
   int numElements;
   Member *inventory;

};

#endif
