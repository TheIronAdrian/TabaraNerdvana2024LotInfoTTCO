#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <assert.h>
using namespace std;

clock_t start;

void TimeInit(){
  start = -1;
}

double TimeLeft(){
  return double(clock()-start)/double(CLOCKS_PER_SEC);
}

void TimeStart(){
  start=clock();
}
