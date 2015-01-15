// http://www.reddit.com/r/dailyprogrammer/comments/2s7ezp/20150112_challenge_197_easy_isbn_validator/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

bool isDash(char c)
{
    return c == '-';
}

bool isISBN(std::string text)
{
    // The return from remove_if, is an iterator to the element that follows the last element not removed.
    // The range between first and this iterator includes all the elements in the sequence for which predicate does not return true.
    text.erase( std::remove_if(text.begin(), text.end(), isDash), text.end() );

    if (text.length() != 10)
    {
        return false;
    }

    int multiplier = 10;
    int sum = 0;
    int val = 0;

    for (std::string::iterator it = text.begin(); it != text.end(); ++it, multiplier--)
    {
        if ((it == text.end() - 1) && (*it == 'X'))
        {
            val = 10;
        }
        else
        {
            val = *it - '0';
        }

        sum = sum + ( multiplier*val );
    }

    return sum%11 == 0;
}

void checkISBN(std::string potentialISBN)
{
    std::cout << "\t" << potentialISBN << "\tisISBN: " << isISBN(potentialISBN) << std::endl;
}

int main()
{
    checkISBN("0-7475-3269-9"); // true
    checkISBN("1-5688-1111-X"); // true
    checkISBN("0321334876");    // Effective C++
    checkISBN("1-5688-111-X");  // false
    checkISBN("1-5688-1131-X"); // false

    return 0;
}