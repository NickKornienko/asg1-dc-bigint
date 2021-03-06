// $Id: bigint.cpp,v 1.2 2021-12-28 14:11:26-08 - - $
//James Garrett jaagarre
//Nick Kornienko nkornien

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"

bigint::bigint(long that) : uvalue(ubigint(that)), is_negative(that < 0)
{
}

bigint::bigint(const ubigint &uvalue_, bool is_negative_) :
 uvalue(uvalue_), is_negative(is_negative_)
{
}

bigint::bigint(const string &that)
{
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint(that.substr(is_negative ? 1 : 0));
}

bigint bigint::operator+() const
{
   return *this;
}

bigint bigint::operator-() const
{
   return {uvalue, not is_negative};
}

bigint bigint::operator+(const bigint &that) const
{
   bigint result;

   if (this->is_negative == that.is_negative)
   {
      result.uvalue = uvalue + that.uvalue;
      result.is_negative = this->is_negative;
   }
   else
   {
      if (this->uvalue < that.uvalue)
      {
         result.uvalue = that.uvalue - this->uvalue;
         result.is_negative = that.is_negative;
      }
      else
      {
         result.uvalue = this->uvalue - that.uvalue;
         result.is_negative = this->is_negative;
      } 
   }

   bigint neg_zero (0);
   neg_zero.is_negative = true;
   
   if(result == neg_zero)
       result.is_negative = false;

   return result;
}

bigint bigint::operator-(const bigint &that) const
{
   bigint result;
   if (this->is_negative != that.is_negative)
   {
      result.uvalue = this->uvalue + that.uvalue;
      result.is_negative = this->is_negative;
   }
   else
   {
      if (this->uvalue < that.uvalue)
      {
         result.uvalue = that.uvalue - this->uvalue;
         result.is_negative = !that.is_negative;
      }
      else
      {
         result.uvalue = this->uvalue - that.uvalue;
         result.is_negative = this->is_negative;
      } 
   }

   bigint neg_zero (0);
   neg_zero.is_negative = true;
   
   if(result == neg_zero)
       result.is_negative = false;

   return result;
}

bigint bigint::operator*(const bigint &that) const
{
   bigint result;
   
   if (this->is_negative == that.is_negative)
   {
      result.is_negative = false;
   }
   else
   {
      result.is_negative = true;
   }

   result.uvalue = this->uvalue * that.uvalue;  

   bigint neg_zero (0);
   neg_zero.is_negative = true;
   
   if(result == neg_zero)
       result.is_negative = false;

   return result;
}

bigint bigint::operator/(const bigint &that) const
{
   bigint result;
   result.uvalue = this->uvalue / that.uvalue; 

   if (this->is_negative == that.is_negative)
   {
      result.is_negative = false;
   }
   else
   {
      result.is_negative = true;
   }

   bigint neg_zero (0);
   neg_zero.is_negative = true;
   
   if(result == neg_zero)
       result.is_negative = false;

   return result;
}

bigint bigint::operator%(const bigint &that) const
{
   bigint result{uvalue % that.uvalue};

   bigint neg_zero (0);
   neg_zero.is_negative = true;
   
   if(result == neg_zero)
       result.is_negative = false;

   return result;
}

bool bigint::operator==(const bigint &that) const
{
   return is_negative == that.is_negative and uvalue == that.uvalue;
}

bool bigint::operator<(const bigint &that) const
{
   if (is_negative != that.is_negative)
      return is_negative;
   
   if(is_negative)
   {
      return this->uvalue > that.uvalue;
   }
   return this->uvalue < that.uvalue;
}

void bigint::print() const
{
   DEBUGF('p', this << " -> " << *this);
   if (is_negative)
      cout << "-";
   uvalue.print();
}

ostream &operator<<(ostream &out, const bigint &that)
{
   return out << "bigint(" << (that.is_negative ? "-" : "+")
              << "," << that.uvalue << ")";
}

