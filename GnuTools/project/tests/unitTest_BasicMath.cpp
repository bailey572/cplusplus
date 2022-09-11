#define BOOST_TEST_MODULE BasicMath
// #include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>
#include "BasicMath.h"

/* Test known version */
BOOST_AUTO_TEST_CASE( get_version  )
{
    BOOST_CHECK_EQUAL (BasicMath::get_version(), 0.1);
}

BOOST_AUTO_TEST_CASE( addInts )
{
    BOOST_CHECK_EQUAL( BasicMath::add(1,1),1+1 );
    BOOST_CHECK_EQUAL( BasicMath::add(5,1),5+1 );
    BOOST_CHECK_EQUAL( BasicMath::add(5,5),5+5 );
    BOOST_CHECK_EQUAL( BasicMath::add(10,10),10+10 );
    BOOST_CHECK_EQUAL( BasicMath::add(25,25),25+25 );
    BOOST_CHECK_EQUAL( BasicMath::add(50,50),50+50 );
    BOOST_CHECK_EQUAL( BasicMath::add(100,100),100+100 );
    BOOST_CHECK_EQUAL( BasicMath::add(123,456),456+123 );
    BOOST_CHECK_EQUAL( BasicMath::add(500,500),500+500 );
    BOOST_CHECK_EQUAL( BasicMath::add(1000,1000),1000+1000 );
}

BOOST_AUTO_TEST_CASE( addDoubles )
{
    BOOST_CHECK_EQUAL( BasicMath::add(1.1,1.2),1.1+1.2 );
    BOOST_CHECK_EQUAL( BasicMath::add(5.3,1.3),5.3+1.3 );
    BOOST_CHECK_EQUAL( BasicMath::add(5.7,5.7),5.7+5.7 );
    BOOST_CHECK_EQUAL( BasicMath::add(10.123,10.345),10.123+10.345 );
    BOOST_CHECK_EQUAL( BasicMath::add(25.7,25.8),25.7+25.8 );
    BOOST_CHECK_EQUAL( BasicMath::add(50.5,50.3),50.3+50.5 );
    BOOST_CHECK_EQUAL( BasicMath::add(100.432,100.234),100.234+100.432 );
    BOOST_CHECK_EQUAL( BasicMath::add(123.654, 456.45), 456.45 + 123.654);
    BOOST_CHECK_EQUAL( BasicMath::add(123.654, 456.45), 123.654 + 456.45);
    BOOST_CHECK_EQUAL( BasicMath::add(500.21,500.12),500.12+500.21 );
    BOOST_CHECK_EQUAL( BasicMath::add(1000.1,1000.2),1000.2+1000.1 );
}

BOOST_AUTO_TEST_CASE( MultiplyInts )
{
    BOOST_CHECK_EQUAL( BasicMath::multiply(1,1),1*1 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(5,1),5*1 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(5,5),5*5 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(10,10),10*10 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(25,25),25*25 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(50,50),50*50 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(100,100),100*100 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(123,456),456*123 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(500,500),500*500 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(1000,1000),1000*1000 );
}
BOOST_AUTO_TEST_CASE( multiplyDoubles )
{
    BOOST_CHECK_EQUAL( BasicMath::multiply(1.1,1.2),1.1*1.2 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(5.3,1.3),5.3*1.3 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(5.7,5.7),5.7*5.7 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(10.123,10.345),10.123*10.345 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(25.7,25.8),25.7*25.8 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(50.5,50.3),50.3*50.5 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(100.432,100.234),100.2340*100.4320 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(123.654, 456.45), 123.654 * 456.45);
    BOOST_CHECK_EQUAL( BasicMath::multiply(123.654, 456.45), 456.45 * 123.654);
    BOOST_CHECK_EQUAL( BasicMath::multiply(500.21,500.12),500.12*500.21 );
    BOOST_CHECK_EQUAL( BasicMath::multiply(1000.1,1000.2),1000.2*1000.1 );
}