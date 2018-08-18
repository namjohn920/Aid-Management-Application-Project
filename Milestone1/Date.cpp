// Final Project Milestone 1
//
// Version 1.0
// Date 2018/07/13
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
#include "Date.h"

namespace AMA {

  // number of days in month mon_ and year year_
  //
  int Date::mdays(int mon, int year)const {
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int month = mon >= 1 && mon <= 12 ? mon : 13;
    month--;
    return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
  }


  void Date::errCode(int errorCode) {

	  state = errorCode;
  }


  //CONSTRUCTORS
  Date::Date() {
	  year = 0;
	  month = 0;
	  day = 0;
	  comp = 0;
	  //state = NO_ERROR;
	  errCode(NO_ERROR);
  }
    
  Date::Date(int y, int m, int d) {
	  int a = mdays(m, y);
	  bool valid=true;

	  if (y < min_year || y > max_year) {
		  //state = YEAR_ERROR;
		  errCode(YEAR_ERROR);
		  year = 0;
		  month = 0;
		  day = 0;
		  comp = 0;
		  valid = !(bad());
	  }
	  
	  if (m < 1 || m > 12) {
		  //state = MON_ERROR;
		  errCode(MON_ERROR);
		  year = 0;
		  month = 0;
		  day = 0;
		  comp = 0;
		  valid = !(bad());
	  }

	  if (d<1 || d > a) {
		  //state = DAY_ERROR;
		  errCode(DAY_ERROR);
		  year = 0;
		  month = 0;
		  day = 0;
		  comp = 0;
		  valid = !(bad());
	  }
	  
	  if (valid) {
		  //state = NO_ERROR;
		  errCode(NO_ERROR);
		  year = y;
		  month = m;
		  day = d;
		  comp = (year * 372 + month * 13 + day);
	  }
	  

  }

  //OPERATORS

  bool Date::operator==(const Date& rhs) const {
	  if (this == nullptr || &rhs == nullptr) {
		  return false;
	  }
	  
	  if (this->comp == rhs.comp) {
		  return true;
	  }
	  else return false;
  }

  bool Date::operator!=(const Date& rhs) const {
	  if (this == nullptr || &rhs == nullptr) {
		  return false;
	  }

	  if (this->comp == rhs.comp) {
		  return false;
	  }
	  else return true;
  }
  bool Date::operator<(const Date& rhs) const {
	  if (this == nullptr || &rhs == nullptr) {
		  return false;
	  }

	  if (this->comp < rhs.comp) {
		  return true;
	  }
	  else return false;
  }
  bool Date::operator>(const Date& rhs) const {
	  if (this == nullptr || &rhs == nullptr) {
		  return false;
	  }

	  if (this->comp > rhs.comp) {
		  return true;
	  }
	  else return false;
  }
  bool Date::operator<=(const Date& rhs) const {
	  if (this == nullptr || &rhs == nullptr) {
		  return false;
	  }

	  if (this->comp == rhs.comp) {
		  return true;
	  }
	  else return false;
  }
  bool Date::operator>=(const Date& rhs) const {
	  if (this == nullptr || &rhs == nullptr) {
		  return false;
	  }

	  if (this->comp >= rhs.comp) {
		  return true;
	  }
	  else return false;
  }

  //Queries and Modifiers
  int Date::errCode() const {
	  return state;
  }

  bool Date::bad() const {
	  int a = errCode();
	  if (a != 0) {
		  return true;
	  }
	  else return false;
  }

  std::istream& Date::read(std::istream& istr) {
	  char slash_dummy;
	  int y;
	  int m;
	  int d;
	
	  istr >> y >> slash_dummy >> m >> slash_dummy >> d;

	  if (istr.fail()) errCode(CIN_FAILED);
	  else if (min_year > y || max_year < y) errCode(YEAR_ERROR);
	  else if (1 > m || 12 < m) errCode(MON_ERROR);
	  else if (1 > d || mdays(m, y) < d) errCode(DAY_ERROR);
	  else {
		  year = y;
		  month = m;
		  day = d;
	  }
	  return istr;
	 
  }
  std::istream& operator >>(std::istream& is, Date& date) {

	  date.read(is);
	  
	  return is;
  }
  std::ostream& Date::write(std::ostream& ostr) const {
	  ostr.fill('0');

	 
	  ostr << year << "/";

	  ostr.width(2);
	  ostr << month << "/";

	  ostr.width(2);
	  ostr << day;

	  return ostr;

  }
  

  std::ostream& operator <<(std::ostream& os, const Date& date) {

	  date.write(os);

	  return os;

  }
  





}
