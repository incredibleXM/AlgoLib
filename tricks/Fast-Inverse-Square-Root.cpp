#include <bits/stdc++.h>
using namespace std;
float FastInvSqrt(float x) //?????????????
{
    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f-(xhalf*x*x));
    return x;
}
int main()
{
    float input;
    printf("please input a decimal number: ");
    scanf("%f", &input);
    printf("ans of FIS is %f", FastInvSqrt(input));
    return 0;
}
