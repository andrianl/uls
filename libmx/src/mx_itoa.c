#include "libmx.h"

#define INT_DIGITS 19 /* enough for 64 bit integer */
#define UINT_DIGITS 20
#define BASE 10

char* mx_itoa(int num)
{
    char *str = mx_strnew(12);
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitly, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && BASE == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % BASE;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/BASE;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    //reverse(str, i);
    mx_str_reverse(str);
 
    return str;
}
