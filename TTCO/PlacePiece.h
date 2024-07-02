#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <bitset>
#include <queue>
#define MAXSIZE 16
#define MATRICESIZE MAXSIZE*MAXSIZE
#define NRPIECE 21
#define EU 0
#define OPPON 1

struct RASPPIESA{
  int x,y,piesa,rot;
};

string PlacedPiece(RASPPIESA transfer){
  int i,j,n,m,x,y,piesa,rot,s;
  string aux;
  bitset <MAXSIZE*MAXSIZE> rasp(0);


  x=transfer.x;
  y=transfer.y;
  piesa=transfer.piesa;
  rot=transfer.rot;

  playerPc[piesa][EU]=0;

  for(i=0;i<5;i++){
    for(j=0;j<MAXSIZE;j++){
      rasp[i*MAXSIZE+j]=pc[piesa][rot].mat[i*MAXSIZE+j];
    }
  }

  n=pc[piesa][rot].n;
  m=pc[piesa][rot].m;

  matPiese[EU]|=((rasp<<(x*MAXSIZE))<<y);

  aux="";

  s=0;

  for(i=0;i<n;i++){
    for(j=0;j<m;j++){
      if(pc[piesa][rot].mat[i*MAXSIZE+j]==1){

        if(s==0){
          s=1;
        }else{
          aux+=(char)',';
        }

        aux+=((char)'a'+i-1+x);
        if(j+y>=10){
          aux+=((char)(j+y)/10+'0');
        }
        aux+=((char)(j+y)%10+'0');
        //cout << aux << "---";
      }
    }
  }


  return aux;
}
