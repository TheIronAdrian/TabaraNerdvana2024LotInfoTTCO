#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <assert.h>
using namespace std;

struct INPUT{
  int val;
  string text;
};

INPUT ReadLine(){
  string text;

  cin >> text;

  if(text == "set_game"){
    cin >> text;
    cin >> text;
    return {-1,""};
  }

  if(text == "clear_board"){
    return {-1,""};
  }

  if(text == "cputime"){
    return {0,""};
  }

  if(text == "genmove"){
    cin >> text;
    return {1,""};
  }
  if(text == "quit"){
    return {3,""};
  }

  assert(text == "play" && "Citire Gresita");


  cin >> text;
  cin >> text;

  return {2,text};
}




