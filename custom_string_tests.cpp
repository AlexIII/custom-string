/*
 *      Custom String test
 *      Author: AlexIII
 *      Description: Testing against std::string
 */

#define BOOST_TEST_MODULE custom_string
#include <boost/test/included/unit_test.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "custom_string.h"

using namespace std;

string getRandomString(size_t length) {
    string str;
    for (size_t i = 0; i < length; i++) {
        str += rand() % 80 + '0';
    }
    return str;
}

BOOST_AUTO_TEST_CASE( AssignmentLength ) {
    // Prepare
    const auto std_str1 = getRandomString(20);
    const auto std_str2 = getRandomString(20);
    BOOST_TEST( std_str1 != std_str2 );
    Custom::String str1(std_str1.c_str());
    Custom::String str2(std_str2.c_str());
    
    // Test length
    BOOST_TEST( str1.length() == std_str1.length() );
    BOOST_TEST( str2.length() == std_str2.length() );
    BOOST_TEST( !str1.empty() );
    Custom::String empty;
    BOOST_TEST( empty.empty() );
    // Test assignment
    BOOST_TEST( str1 != str2 );
    str1 = str2;
    BOOST_TEST( str1 == str2 );
}

BOOST_AUTO_TEST_CASE( operatorPlus ) {
    // Prepare
    const auto std_str1 = getRandomString(20);
    const auto std_str2 = getRandomString(20);
    BOOST_TEST( std_str1 != std_str2 );
    Custom::String str1(std_str1.c_str());
    Custom::String str2(std_str2.c_str());
    
    // Test
    BOOST_TEST( (str1 + str2).c_str() == std_str1 + std_str2 );
    BOOST_TEST( (str1 + str1).c_str() == std_str1 + std_str1 );
    str1 += str2;
    BOOST_TEST( str1.c_str() == std_str1 + std_str2 );
}

BOOST_AUTO_TEST_CASE( operatorElementAccess ) {
    // Prepare
    const auto std_str1 = getRandomString(20);
    const auto std_str2 = getRandomString(20);
    BOOST_TEST( std_str1 != std_str2 );
    Custom::String str1(std_str1.c_str());
    
    // Test const char&
    for(size_t i = 0; i < std_str1.size(); i++) {
        const char& c = str1[i];
        BOOST_TEST( c == std_str1[i] );
    }
    BOOST_TEST(str1.front() == std_str1.front());
    BOOST_TEST(str1.back() == std_str1.back());

    // Test char&
    for(size_t i = 0; i < std_str1.size(); i++) {
        char& c = str1[i];
        c = std_str2[i];
    }
    BOOST_TEST( str1.c_str() == std_str2 );
    {
        char& c = str1.front();
        BOOST_TEST(str1.front() == std_str2.front());
        c = std_str1.front();
        BOOST_TEST(str1.front() == std_str1.front());
    }
    {
        char& c = str1.back();
        BOOST_TEST(str1.back() == std_str2.back());
        c = std_str1.back();
        BOOST_TEST(str1.back() == std_str1.back());
    }
}

BOOST_AUTO_TEST_CASE( Comparison ) {
    // Prepare
    const auto std_str1 = getRandomString(20);
    const auto std_str2 = getRandomString(20);
    BOOST_TEST( std_str1 != std_str2 );
    Custom::String str1(std_str1.c_str());
    Custom::String str2(std_str2.c_str());
    
    // Test
    BOOST_TEST( str1 == Custom::String(std_str1.c_str()) );
    const auto c1 = str1.compare(str2);
    const auto c2 = std_str1.compare(std_str2);
    BOOST_TEST( (c1 < 0? -1 : c1 > 0? 1 : 0) == (c2 < 0? -1 : c2 > 0? 1 : 0) );
}

BOOST_AUTO_TEST_CASE( ToLower_ToUpper ) {
    // Prepare
    auto std_str1 = getRandomString(20);
    auto std_str2 = getRandomString(20);
    BOOST_TEST( std_str1 != std_str2 );
    Custom::String str1(std_str1.c_str());
    Custom::String str2(std_str2.c_str());

    std::transform(
        std_str1.begin(), std_str1.end(), std_str1.begin(),
        [](unsigned char c){ return std::tolower(c); }
    );
    BOOST_TEST( std_str1 != string(str1.c_str()) );
    std::transform(
        std_str2.begin(), std_str2.end(), std_str2.begin(),
        [](unsigned char c){ return std::toupper(c); }
    );
    BOOST_TEST( std_str2 != string(str2.c_str()) );
    
    // Test
    BOOST_TEST( str1 != Custom::String(std_str1.c_str()) );
    BOOST_TEST( str1.asLower() == Custom::String(std_str1.c_str()) );
    str1.toLower();
    BOOST_TEST( str1 == Custom::String(std_str1.c_str()) );

    BOOST_TEST( str2 != Custom::String(std_str2.c_str()) );
    BOOST_TEST( str2.asUpper() == Custom::String(std_str2.c_str()) );
    str2.toUpper();
    BOOST_TEST( str2 == Custom::String(std_str2.c_str()) );
}

BOOST_AUTO_TEST_CASE( OperatorStreamOut ) {
    // Prepare
    auto std_str1 = getRandomString(20);
    Custom::String str1(std_str1.c_str());
    stringstream ss;

    // Test
    ss << str1;
    ss << str1;
    BOOST_TEST( ss.str() == std_str1 + std_str1 );
}

BOOST_AUTO_TEST_CASE( OperatorStreamIn ) {
    // Prepare
    const auto std_str1 = getRandomString(20) + "\n";
    const auto std_str2 = getRandomString(0) + "\n";
    const auto std_str3 = getRandomString(2 * BUFSIZ + 5) + "\n";
    const auto std_str4 = getRandomString(20);
    stringstream ss(std_str1 + std_str2 + std_str3 + std_str4);
    Custom::String str;

    // Test
    ss >> str;
    BOOST_TEST( str.c_str() == std_str1 );
    ss >> str;
    BOOST_TEST( str.c_str() == std_str2 );
    ss >> str;
    BOOST_TEST( str.c_str() == std_str3 );
    ss >> str;
    BOOST_TEST( str.c_str() == std_str4 );
    stringstream() >> str;
    BOOST_TEST( str.c_str() == string("") );

    BOOST_TEST( bool(ss) == false );
}
