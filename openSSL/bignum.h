#pragma once
#include<string>
#include<openssl/bn.h>
#include<iostream>
using namespace std;
string mod_exp(string a, string e, string m);
string mod_inverse(string a, string m);
