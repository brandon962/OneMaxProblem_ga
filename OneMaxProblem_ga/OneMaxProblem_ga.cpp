#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#include <iostream>
#include <string>
#include "ga.h"

using namespace std;

int main()
{
    Ga ga = Ga(1,1000,100,20,1,0.005, 0.9);
    ga.run();
}
