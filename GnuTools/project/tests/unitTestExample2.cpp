#define BOOST_TEST_MODULE Example Two
// #include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>
//____________________________________________________________________________//

// most frequently you implement test cases as a free functions with automatic registration
BOOST_AUTO_TEST_CASE( exampleTwo_1  )
{
    // reports 'error in "example1": test 2 == 1 failed'
    BOOST_CHECK_NE( 2 ,1 );
}

//____________________________________________________________________________//

// // each test file may contain any number of test cases; each test case has to have unique name
BOOST_AUTO_TEST_CASE( exampleTwo_2 )
{
    int i = 0;
    BOOST_CHECK_EQUAL( i, 0 );
   // reports 'error in "example2": check i == 2 failed [0 != 2]'
    BOOST_CHECK_EQUAL( i, 2 );
}

BOOST_AUTO_TEST_CASE(exampleTwo_3)
{
  int i = 1;
  BOOST_TEST(i); 
  BOOST_TEST(i != 2); 
}