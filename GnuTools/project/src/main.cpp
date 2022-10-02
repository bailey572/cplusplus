#include <iostream>
#include "Hal.h"
#include "BasicMath.h"
#include "dataObject.h"

int main() {
  // Silly hal program
  Hal *hal = new Hal();
  hal->get_version();
  hal->~Hal();

  // Print version of BasicMath
  std::cout << " BasicMath Version is " << BasicMath::get_version() << std::endl;

  // Simple recursion algorithm to give us some run time
  for (int ii=10000;ii>0;ii--) {
    recursiveFactorial(ii);
    // std::cout << "Recursive length is " << recur << std::endl;
  }
  // example template usage for some gprof variety
  int ii = maximum(9,5,3);
	double dd = maximum(0.3,9.8,5.4);
	char letter = maximum('b','d','A');
  std::cout << "Max value for ints " << ii << std::endl;
  std::cout << "Max value for doubles " << dd << std::endl;
  std::cout << "Max value for characters " << letter<< std::endl;

  return 0;
}