#include <iostream>
#include "Hal.h"
#include "BasicMath.h"

int main() {
  Hal *hal = new Hal();
  hal->get_version();

  hal->~Hal();

  std::cout << " BasicMath Version is " << BasicMath::get_version() << std::endl;
  return 0;
}