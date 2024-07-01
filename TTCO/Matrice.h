#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <assert.h>
#define MAXSIZE 14
#define NRPIECE 21
using namespace std;

int matPiese[MAXSIZE][MAXSIZE];
int playerPc[NRPIECE][2];

void Init(){
  int i,j;

  for(i=0;i<MAXSIZE;i++){
    for(j=0;j<MAXSIZE;j++){
      matPiese[i][j]=0;
    }
  }

  for(i=0;i<NRPIECE;i++){
    playerPc[i][0]=1;
    playerPc[i][1]=1;
  }
}

void Occupy(string text){
  int i,j;

  while(!text.empty()){
    if(text[0]==','){
      text.erase(0,1);
    }
    i=text[0]-'a';
    j=text[1]-'0';
    text.erase(0,2);
    if(!text.empty() && isdigit(text[0])){
      j=j*10+text[0]-'0';
      text.erase(0,1);
    }

    j--;
    matPiese[i][j]=1;
  }
}
