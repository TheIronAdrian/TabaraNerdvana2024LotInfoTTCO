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
#define FIRSTMOVEX 5
#define FIRSTMOVEY 10
#define SECONMOVEX 10
#define SECONMOVEY 5
#define EU 0
#define OPPON 1

struct RASPPIESA{
  int x,y,piesa,rot;
};

string PlaceAPiece(RASPPIESA transfer){
  int i,j,n,m,x,y,piesa,rot,s;
  string aux;
  bitset <MAXSIZE*MAXSIZE> rasp(0);


  x=transfer.x;
  y=transfer.y;
  piesa=transfer.piesa;
  rot=transfer.rot;

  playerPc[piesa][EU]=0;

  n=pc[piesa][rot].n;
  m=pc[piesa][rot].m;

  for(i=0;i<n;i++){
    for(j=0;j<m;j++){
      rasp[i*MAXSIZE+j]=pc[piesa][rot].mat[i*MAXSIZE+j];
    }
  }


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

bitset <MAXSIZE*MAXSIZE> Transformer(RASPPIESA transfer){
  int piesa,rot,n,m,i,j;
  bitset <MAXSIZE*MAXSIZE> aux(0);

  piesa=transfer.piesa;
  rot=transfer.rot;
  n=pc[piesa][rot].n;
  m=pc[piesa][rot].m;
  for(i=0;i<n;i++){
    for(j=0;j<m;j++){
      aux[i*MAXSIZE+j]=pc[piesa][rot].mat[i*MAXSIZE+j];
    }
  }

  return aux;
}

bool CheckPosition(int player,RASPPIESA transfer,bitset <MAXSIZE*MAXSIZE> aux){
  int x,y;
  bitset <MAXSIZE*MAXSIZE> rasp;

  x=transfer.x;
  y=transfer.y;

  aux=aux<<(x*MAXSIZE+y);

  rasp=(matPiese[0]|matPiese[1]|BORDARE)&aux;

  if(rasp!=0){
    return false;
  }

  rasp=((matPiese[player]<<16)|
        (matPiese[player]<<1)|
        (matPiese[player]>>16)|
        (matPiese[player]>>1))&aux;

  if(rasp!=0){
    return false;
  }

  if(matPiese[player]==0){
    if(matPiese[1-player]==0){
      rasp=0;
      rasp[(FIRSTMOVEX)*MAXSIZE+FIRSTMOVEY]=1;
      rasp=rasp&aux;
    }else{
      rasp=0;
      rasp[(SECONMOVEX)*MAXSIZE+SECONMOVEY]=1;
      rasp=rasp&aux;
    }
  }else{
    rasp=((matPiese[player]<<17)|
          (matPiese[player]<<15)|
          (matPiese[player]>>17)|
          (matPiese[player]>>15))&aux;
  }

  if(rasp!=0){
    return true;
  }
  return false;
}

RASPPIESA FindPiece(int player){
  int z,c,x,y,i,j,n,m;
  bitset <MAXSIZE*MAXSIZE> colt(0);
  bitset <MAXSIZE*MAXSIZE> piesa(0);

  if(matPiese[player]==0){
    if(matPiese[1-player]==0){
      colt[FIRSTMOVEX*MAXSIZE+FIRSTMOVEY]=1;
    }else{
      colt[SECONMOVEX*MAXSIZE+SECONMOVEY]=1;
    }
  }else{
    colt=  ((matPiese[player]<<17)|
            (matPiese[player]<<15)|
            (matPiese[player]>>17)|
            (matPiese[player]>>15))^(BORDARE | matPiese[0] | matPiese[1]);
  }

  while(1==1){
    z=rand()%NRPIECE;
    if(playerPc[z][0]==1){
      c=rand()%pc[z].size();
      piesa=Transformer({-1,-1,z,c});
      n=pc[z][c].n;
      m=pc[z][c].m;

      i=rand()%n;
      j=rand()%m;
      for(x=i+1;x<=PLAYAREA;x++){
        for(y=j+1;y<=PLAYAREA;y++){
          if(CheckPosition(player,{x,y,z,c},piesa)){
            return {x,y,z,c};
          }
        }
      }
    }
  }

  /*for(z=0;z<NRPIECE;z++){
    if(playerPc[z][0]==1){
      for(c=0;c<pc[z].size();c++){
        piesa=Transformer({-1,-1,z,c});

        n=pc[z][c].n;
        m=pc[z][c].m;
        for(i=0;i<n;i++){
          for(j=0;j<m;j++){
            for(x=i+1;x<=PLAYAREA;x++){
              for(y=j+1;y<=PLAYAREA;y++){
                if(CheckPosition(player,{x,y,z,c},piesa)){
                  return {x,y,z,c};
                }
              }
            }
          }
        }
      }
    }
  }*/


  assert(1==1 && "EstiProstNuAiGasitPiesa");
}
