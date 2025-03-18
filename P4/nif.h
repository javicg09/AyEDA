#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime> 

class nif {
 public:
  nif();
  nif(long value) : value_(value) {}

  bool operator==(const nif& other) const {return value_ == other.value_;}
  bool operator!=(const nif& other) const {return !(*this == other);}
	bool operator<(const nif& other) const {return value_ < other.value_;}
	bool operator>(const nif& other) const {return value_ > other.value_;}
  bool operator>(long int value) const {return value_ > value;}
	bool operator<=(const nif& other) const {return !(*this > other);}
	bool operator>=(const nif& other) const {return !(*this < other);}
  operator long() const {return value_;}
  nif& operator/=(int divisor);

  friend std::istream& operator>>(std::istream& input, nif& n);

 private:
  long value_; 
};