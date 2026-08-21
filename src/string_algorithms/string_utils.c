#include "string_utils.h"
#include <string.h>

bool is_palindrome(const char* str)
{
    if (str == NULL)
    {
        return false;
    }

    int left = 0;
    int right = strlen(str) - 1;

    while (left < right)
    {
        if (str[left] != str[right])
        {
            return false;
        }
        left++;
        right--;
    }

    return true;
}

bool is_anagram(const char* str1, const char* str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        return false;
    }

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 != len2)
    {
        return false;
    }

    int freq[256] = {0};

    for (int i = 0; i < len1; i++)
    {
        freq[(unsigned char)str1[i]]++;
        freq[(unsigned char)str2[i]]--;
    }

    for (int i = 0; i < 256; i++)
    {
        if (freq[i] != 0)
        {
            return false;
        }
    }

    return true;
}
