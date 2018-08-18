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
#include <iostream>
#include "Date.h"

namespace AMA 
{
  // number of days in month mon_ and year year_
  //
  int Date::comparetor() const
   {

      return m_year * 372 + m_month * 13 + m_day;

   }

  bool Date::valid()
   {

      int checker = 1;

      if (m_year < min_year || m_year > max_year) 
      {
         m_check = YEAR_ERROR;
         checker = 0;
      }

      if (checker != 0) 
      {
         if (m_month < 1 || m_month > 12)
         {
            m_check = MON_ERROR;
            checker = 0;
         }
      }

      if (checker != 0) 
      {
         if (m_day < 1 || m_day > mdays(m_month, m_year))
         {
            m_check = DAY_ERROR;
            checker = 0;
         }
      }

      return checker;

   }


  int Date::mdays(int mon, int year)const 
  {

    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int month = mon >= 1 && mon <= 12 ? mon : 13;
    month--;
    return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));

  }


  void Date::errCode(int errorCode) 
  {

     m_check = errorCode;

  }


  Date::Date()
  {

     m_year = 0;
     m_month = 0;
     m_day = 0;
     m_check = NO_ERROR;

  }

  Date::Date(int year, int month, int day)
  {

     m_year = year;
     m_month = month;
     m_day = day;

     if (valid()) 
     {
        m_check = NO_ERROR;

     } else {

        *this = Date();

     }

  }

  bool Date::operator==(const Date& rhs) const
  {

     return this->comparetor() == rhs.comparetor();

  }


  bool Date::operator!=(const Date& rhs) const
  {

     return this->comparetor() != rhs.comparetor();


  }


  bool Date::operator<(const Date& rhs) const
  {

     return this->comparetor() < rhs.comparetor();

  }


  bool Date::operator>(const Date& rhs) const
  {

     return this->comparetor() > rhs.comparetor();


  }


  bool Date::operator<=(const Date& rhs) const
  {

     return this->comparetor() <= rhs.comparetor();

  }


  bool Date::operator>=(const Date& rhs) const
  {

     return this->comparetor() >= rhs.comparetor();

  }


  int Date::errCode() const
  {

     return m_check;

  }


  bool Date::bad() const
  {

     return errCode() != NO_ERROR;

  }


  std::istream& Date::read(std::istream& istr)
  {
     int i;
     char j;
     *this = Date();

     if (istr >> i && !istr.fail()) 
     {

        m_year = i;

     } else {

        *this = Date();
        errCode(CIN_FAILED);

     }

     if (istr >> j && istr.fail()) 
     {
        *this = Date();
        errCode(CIN_FAILED);

     }

     if (istr >> i && !istr.fail()) 
     {

        m_month = i;

     } else {

        *this = Date();
        errCode(CIN_FAILED);

     } 

     if (istr >> j && istr.fail()) 
     {

        *this = Date();
        errCode(CIN_FAILED);


     }

     if (istr >> i && !istr.fail()) 
     {
        m_day = i;

     } else {
        *this = Date();
        errCode(CIN_FAILED);
     }


     if (!bad()) {

        if (valid()) 
        {
           m_check = NO_ERROR; 

        } else {

           m_year = 0;
           m_month = 0;
           m_day = 0;
        }
     }

     return istr;
  }

  std::ostream& Date::write(std::ostream& ostr) const
  {
     ostr << m_year << "/";
     if (m_month < 10)
     {
        ostr << "0" << m_month << "/";

     } else {
        ostr << m_month << "/";

     }

     if (m_day < 10)
     {
        ostr << "0" << m_day;

     } else {
        ostr << m_day;

     }

     return ostr;
  }


  std::ostream& operator<<(std::ostream& out, const Date& ar)
  {

     return ar.write(out);

  }
  std::istream& operator>>(std::istream& in, Date& ar)
  {

     return ar.read(in);

  }

}
