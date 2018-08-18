// Final Project Milestone 1
//
// Version 1.0
//  Date 2018/07/13
// Author HyunKyu Nam (141031161)
// Description
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef AMA_DATE_H
#define AMA_DATE_H
#include<iostream>

namespace AMA {
	const int min_year = 2000;
	const int max_year = 2030;
	const int NO_ERROR = 0;
	const int CIN_FAILED = 1;
	const int YEAR_ERROR = 2;
	const int MON_ERROR = 3;
	const int DAY_ERROR = 4;

  class Date {
	

	  //values
	  int year;
	  int month;
	  int day; //has something to do with mday function
	  int state;
	  int comp;
	 

	  //functions 
	  int mdays(int, int)const;
	  void errCode(int errorCode);
 
  public:
	  //constructors
	  Date();
	  Date(int, int, int);

	  //operators

	  bool operator==(const Date& rhs) const;
	  bool operator!=(const Date& rhs) const;
	  bool operator<(const Date& rhs) const;
	  bool operator>(const Date& rhs) const;
	  bool operator<=(const Date& rhs) const;
	  bool operator>=(const Date& rhs) const;

	  //Queries and Modifiers
	  int errCode() const;
	  bool bad() const;
	  std::istream& read(std::istream& istr);
	  std::ostream& write(std::ostream& ostr) const;

 
  };

  std::ostream& operator <<(std::ostream& os, const Date& date);
  std::istream& operator >>(std::istream& is, Date& date);




}
#endif