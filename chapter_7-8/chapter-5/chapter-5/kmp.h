#pragma once
#include <iostream>
#include <vector>
using namespace std;

vector<int> getNext(string pattern)
{
    int j = 0, m = pattern.length();
    vector<int> next(m);
    int t = -1;
    next[0] = -1;
    while (j < m - 1)
    {
        if (t < 0 || pattern[t] == pattern[j])
        {
            t++;
            j++;
            next[j] = t;
        }
        else
        {
            t = next[t];
        }
    }
    return next;
}

int kmp_algo(string mainString, string pattern)
{
    int n = mainString.length();
    int m = pattern.length();
    vector<int> next = getNext(pattern);
    int i = 0, j = 0;
    while (i < n && j < m)
    {
        if (j < 0 || mainString[i] == pattern[j])
        {
            i++;
            j++;
            if (j == m)
                return i - j;
        }
        else
        {
            j = next[j];
        }
    }
    return -1;
}