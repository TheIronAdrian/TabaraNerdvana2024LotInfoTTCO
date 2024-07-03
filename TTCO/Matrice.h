#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <bitset>
#include <time.h>
#include <queue>
#define MAXSIZE 16
#define MATRICESIZE MAXSIZE*MAXSIZE
#define NRPIECE 21
#define EU 0
#define OPPON 1
using namespace std;

bitset <MATRICESIZE> matPiese[2];
bitset <MATRICESIZE> BORDARE;
int playerPc[NRPIECE][2];

void Init(){
  int i,j;

  srand ( time(NULL) );
  matPiese[0]=0;
  matPiese[1]=0;

  for(i=0;i<MAXSIZE;i++){
    for(j=0;j<MAXSIZE;j++){
      BORDARE[i*MAXSIZE+j]=(((i==0)||(i==MAXSIZE-1))||((j==0)||(j==MAXSIZE-1)));
    }
  }

  for(i=0;i<NRPIECE;i++){
    playerPc[i][0]=1;
    playerPc[i][1]=1;
  }
}

void Occupy(string text){
  int i,j,miX,maX,miY,maY,n,m,s;
  queue <int> quePozPuse[2];
  bitset <5*MAXSIZE> val(0);

  maX=maY=0;
  miX=miY=100;

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
    i++;

    maX=max(maX,i);
    miX=min(miX,i);

    maY=max(maY,j);
    miY=min(miY,j);

    quePozPuse[0].push(i);
    quePozPuse[1].push(j);

    matPiese[OPPON][(i*MAXSIZE+j)]=1;
  }

  n=maX-miX+1;
  m=maY-miY+1;

  while(!quePozPuse[0].empty()){
    i=quePozPuse[0].front();
    j=quePozPuse[1].front();
    quePozPuse[0].pop();
    quePozPuse[1].pop();

    val[(i-miX)*MAXSIZE+(j-miY)]=1;
  }

  i=0;
  s=0;
  while(i<NRPIECE && s==0){
    for(auto aux : pc[i]){
      if(EgalPiece(aux,{n,m,val})){
        s=1;
      }
    }
    if(s==1){
      playerPc[i][OPPON]=0;
    }
    i++;
  }
}
