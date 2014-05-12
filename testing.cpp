#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

class LogicError : public std::logic_error {
public:

    LogicError( ) : std::logic_error( "" ) {

    }

    virtual const char *what( ) const throw () {
        return m_message.c_str( );
    }

    virtual ~LogicError( ) throw () {

    }

protected:
    std::string m_message;
};

class OutOfRange : public LogicError {
public:

    OutOfRange( int argument, int beginOfRange, int endOfRange ) {
        std::string str_argument, str_beginOfRange, str_endOfRange;

        str_argument = intToString( argument );
        str_beginOfRange = intToString( beginOfRange );
        str_endOfRange = intToString( endOfRange );

        m_message = "Argument " + str_argument + " doesn't hit in the range [" +
                str_beginOfRange + ", " + str_endOfRange + "]";
    }

private:

    std::string intToString( int number ) {
        std::stringstream stream;
        stream << number;
        return stream.str( );
    }
};

class EmptyArgument : public LogicError {
public:

    EmptyArgument( ) {
        m_message = "Error: empty argument.";
    }
};

bool statistics( const std::vector<int> &inputArray, std::vector<int> &outOddArray, std::vector<int> &outEvenArray ) throw (EmptyArgument, OutOfRange);

TEST( test001, exceptionTest ) {
    std::vector<int> inputArray;
    std::vector<int> outOddArray;
    std::vector<int> outEvenArray;

    ASSERT_THROW({
        statistics( inputArray, outOddArray, outEvenArray );
    }, EmptyArgument );
}

TEST( test002, exceptionTest ) {
    std::vector<int> inputArray;
    std::vector<int> outOddArray;
    std::vector<int> outEvenArray;

    inputArray.push_back( 1 );

    ASSERT_NO_THROW({
        statistics( inputArray, outOddArray, outEvenArray );
    } );
}

TEST( test003, exceptionTest ) {
    std::vector<int> inputArray;
    std::vector<int> outOddArray;
    std::vector<int> outEvenArray;

    inputArray.push_back( 31 );

    ASSERT_NO_THROW({
        statistics( inputArray, outOddArray, outEvenArray );
    } );
}

TEST( test004, exceptionTest ) {
    std::vector<int> inputArray;
    std::vector<int> outOddArray;
    std::vector<int> outEvenArray;

    inputArray.push_back( 0 );

    ASSERT_THROW({
        statistics( inputArray, outOddArray, outEvenArray );
    }, OutOfRange );
}

TEST( test005, exceptionTest ) {
    std::vector<int> inputArray;
    std::vector<int> outOddArray;
    std::vector<int> outEvenArray;

    inputArray.push_back( 32 );

    ASSERT_THROW({
        statistics( inputArray, outOddArray, outEvenArray );
    }, OutOfRange );
}

TEST( test006, normalTest ) {
    std::vector<int> inputArray;
    std::vector<int> outOddArray;
    std::vector<int> outEvenArray;

    inputArray.push_back( 4 );
    inputArray.push_back( 16 );
    inputArray.push_back( 19 );
    inputArray.push_back( 31 );
    inputArray.push_back( 2 );

    bool actualAnswer;

    ASSERT_NO_THROW({
        actualAnswer = statistics( inputArray, outOddArray, outEvenArray );
    } );

    // Size of Odd
    std::size_t expectedSizeOfOdd = 2;
    std::size_t actualSizeOfOdd = outOddArray.size( );
    ASSERT_EQ( expectedSizeOfOdd, actualSizeOfOdd );

    // Size of Even
    std::size_t expectedSizeOfEven = 3;
    std::size_t actualSizeOfEven = outEvenArray.size( );
    ASSERT_EQ( expectedSizeOfEven, actualSizeOfEven );

    // Check Odd Array
    int expected = 19;
    int actual = outOddArray[0];
    ASSERT_EQ( expected, actual );

    expected = 31;
    actual = outOddArray[1];
    ASSERT_EQ( expected, actual );

    // Check Even Array
    expected = 4;
    actual = outEvenArray[0];
    ASSERT_EQ( expected, actual );

    expected = 16;
    actual = outEvenArray[1];
    ASSERT_EQ( expected, actual );

    expected = 2;
    actual = outEvenArray[2];
    ASSERT_EQ( expected, actual );

    // Check Answer
    bool expectedAnswer = true;
    ASSERT_EQ( expectedAnswer, actualAnswer );
}

TEST( test007, normalTest ) {
    std::vector<int> inputArray;
    std::vector<int> outOddArray;
    std::vector<int> outEvenArray;

    inputArray.push_back( 29 );
    inputArray.push_back( 4 );
    inputArray.push_back( 7 );
    inputArray.push_back( 12 );
    inputArray.push_back( 15 );
    inputArray.push_back( 17 );
    inputArray.push_back( 24 );
    inputArray.push_back( 1 );

    bool actualAnswer;

    ASSERT_NO_THROW({
        actualAnswer = statistics( inputArray, outOddArray, outEvenArray );
    } );

    // Size of Odd
    std::size_t expectedSizeOfOdd = 5;
    std::size_t actualSizeOfOdd = outOddArray.size( );
    ASSERT_EQ( expectedSizeOfOdd, actualSizeOfOdd );

    // Size of Even
    std::size_t expectedSizeOfEven = 3;
    std::size_t actualSizeOfEven = outEvenArray.size( );
    ASSERT_EQ( expectedSizeOfEven, actualSizeOfEven );

    // Check Odd Array
    int expected = 29;
    int actual = outOddArray[0];
    ASSERT_EQ( expected, actual );

    expected = 7;
    actual = outOddArray[1];
    ASSERT_EQ( expected, actual );

    expected = 15;
    actual = outOddArray[2];
    ASSERT_EQ( expected, actual );

    expected = 17;
    actual = outOddArray[3];
    ASSERT_EQ( expected, actual );

    expected = 1;
    actual = outOddArray[4];
    ASSERT_EQ( expected, actual );

    // Check Even Array
    expected = 4;
    actual = outEvenArray[0];
    ASSERT_EQ( expected, actual );

    expected = 12;
    actual = outEvenArray[1];
    ASSERT_EQ( expected, actual );

    expected = 24;
    actual = outEvenArray[2];
    ASSERT_EQ( expected, actual );

    // Check Answer
    bool expectedAnswer = false;
    ASSERT_EQ( expectedAnswer, actualAnswer );
}

int main( int argc, char *argv[] ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS( );
}
