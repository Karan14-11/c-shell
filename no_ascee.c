#include "terminal.h"
#include "functions.h"

char notoas(int a)
{
    if (a == 0)
        return '0';
    if (a == 1)
        return '1';
    if (a == 2)
        return '2';
    if (a == 3)
        return '3';
    if (a == 4)
        return '4';
    if (a == 5)
        return '5';
    if (a == 6)
        return '6';
    if (a == 7)
        return '7';
    if (a == 8)
        return '8';
    if (a == 9)
        return '9';
    return '@';
}

int chartoint(char a)
{
    if (a == '0')
        return 0;
    if (a == '1')
        return 1;
    if (a == '2')
        return 2;
    if (a == '3')
        return 3;
    if (a == '4')
        return 4;
    if (a == '5')
        return 5;
    if (a == '6')
        return 6;
    if (a == '7')
        return 7;
    if (a == '8')
        return 8;
    if (a == '9')
        return 9;
    return -1;
}

int strtoint(char *a)
{
    int length = strlen(a);
    int j = 1;
    int ans = 0;
    for (int i = length - 1; i >= 0; i--)
    {
        ans += chartoint(a[i]) * j;
        j *= 10;
    }
    return ans;
}
long long int strtolong(char *a)
{
    long long int length = strlen(a);
    long long int j = 1;
    long long int ans = 0;
    for (long long int i = length - 1; i >= 0; i--)
    {
        ans += chartoint(a[i]) * j;
        j *= 10;
    }
    return ans;
}

char *inttostr(int a, char *ret)
{
    int b = a;
    int c = 0;
    while (b)
    {
        int rem = b % 10;
        ret[c++] = notoas(rem);
        b /= 10;
    }
    ret[c++] = '\0';
    c = strlen(ret);
    char *temp = malloc(c + 2);
    strcpy(temp, ret);
    for (int i = 0; i < c; i++)
        ret[i] = temp[i];
    ret[c] = '\0';
    free(temp);
    return ret;
}