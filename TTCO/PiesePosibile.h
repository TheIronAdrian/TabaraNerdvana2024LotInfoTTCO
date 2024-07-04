#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <bitset>
#include <vector>
#include <string>
#include <queue>
#define MAXSIZE 16
#define MATRICESIZE MAXSIZE*MAXSIZE
#define NRPIECE 21
#define EU 0
#define OPPON 1
using namespace std;

struct PIECE{
  int n,m;
  bitset <MAXSIZE*MAXSIZE> mat;
};

vector <PIECE> pc[NRPIECE];
string matInitiala[NRPIECE][MAXSIZE]={
  {
  {".#."},
  {"###"},
  {".#."}
  },
  {
  {"#.."},
  {"###"},
  {".#."}
  },
  {
  {"#.."},
  {"##."},
  {".##"}
  },
  {
  {"#."},
  {"##"},
  {"##"}
  },
  {
  {"##"},
  {"#."},
  {"##"}
  },
  {
  {"#."},
  {"##"},
  {"#."},
  {"#."}
  },
  {
  {"#"},
  {"#"},
  {"#"},
  {"#"},
  {"#"}
  },
  {
  {"##"},
  {"#."},
  {"#."},
  {"#."}
  },
  {
  {"#.."},
  {"#.."},
  {"###"}
  },
  {
  {"###"},
  {".#."},
  {".#."}
  },
  {
  {"#."},
  {"##"},
  {".#"},
  {".#"}
  },
  {
  {".##"},
  {".#."},
  {"##."}
  },
  {
  {"##"},
  {"#."},
  {"#."}
  },
  {
  {"#."},
  {"##"},
  {".#"}
  },
  {
  {"#."},
  {"##"},
  {"#."}
  },
  {
  {"##"},
  {"##"}
  },
  {
  {"##"},
  {"#."}
  },
  {
  {"#"},
  {"#"},
  {"#"},
  {"#"}
  },
  {
  {"#"},
  {"#"},
  {"#"}
  },
  {
  {"#"},
  {"#"}
  },
  {
  {"#"}
  }
};

PIECE Normal(string linie[NRPIECE]){
  int n,m,i,j;
  bitset <MAXSIZE*MAXSIZE> val(0);

  m=linie[0].size();
  n=0;
  while(!linie[n].empty()){
    n++;
  }

  for(i=0;i<n;i++){
    for(j=0;j<m;j++){
      if(linie[i][j]=='#'){
        val[(i*MAXSIZE+j)]=1;
      }else{
        val[(i*MAXSIZE+j)]=0;
      }
    }
  }

  return {n,m,val};
}

PIECE Jos(PIECE val){
  int n,m,i,j,aux;

  n=val.n;
  m=val.m;

  for(i=0;i<n/2;i++){
    for(j=0;j<m;j++){
      aux=val.mat[i*MAXSIZE+j];
      val.mat[i*MAXSIZE+j]=val.mat[(n-1-i)*MAXSIZE+j];
      val.mat[(n-1-i)*MAXSIZE+j]=aux;
    }
  }

  return val;
}

PIECE Left(PIECE val){
  int n,m,i,j,aux;

  n=val.n;
  m=val.m;

  for(i=0;i<n;i++){
    for(j=0;j<m/2;j++){
      aux=val.mat[i*MAXSIZE+j];
      val.mat[i*MAXSIZE+j]=val.mat[i*MAXSIZE+m-1-j];
      val.mat[i*MAXSIZE+m-1-j]=aux;
    }
  }

  return val;
}

PIECE Rotate(PIECE val){
  int n,m,i,j;

  bitset <MAXSIZE*MAXSIZE> aux;

  n=val.m;
  m=val.n;

  for(i=0;i<val.n;i++){
    for(j=0;j<val.m;j++){
      aux[j*MAXSIZE+i]=val.mat[i*MAXSIZE+j];
    }
  }

  return {n,m,aux};
}

bool EgalPiece(PIECE a,PIECE b){
  int i,j;
  //queue

  if(a.n!=b.n || a.m!=b.m){
    return false;
  }

  for(i=0;i<a.n;i++){
    for(j=0;j<a.m;j++){
      if(a.mat[i*MAXSIZE+j]!=b.mat[i*MAXSIZE+j]){
        return false;
      }
    }
  }

  return true;
}

void InitPiese(){
  int x,cont,i,j;

  cont=0;

  for(x=0;x<NRPIECE;x++){
    pc[x].push_back(Normal(matInitiala[x]));
    pc[x].push_back(Jos(Normal(matInitiala[x])));
    pc[x].push_back(Left(Normal(matInitiala[x])));
    pc[x].push_back(Left(Jos(Normal(matInitiala[x]))));

    pc[x].push_back(Rotate(Normal(matInitiala[x])));
    pc[x].push_back(Rotate(Jos(Normal(matInitiala[x]))));
    pc[x].push_back(Rotate(Left(Normal(matInitiala[x]))));
    pc[x].push_back(Rotate(Left(Jos(Normal(matInitiala[x])))));

    cont+=8;
  }

  for(x=0;x<NRPIECE;x++){
    for(i=0;i<pc[x].size();i++){
      for(j=i+1;j<pc[x].size();j++){
        if(EgalPiece(pc[x][i],pc[x][j])){
          pc[x].erase(pc[x].begin()+j);
          cont--;
          j--;
        }
      }
    }
  }

  if(DEBUG > 4){
    /*for(x=0;x<NRPIECE;x++){
      for(PIECE aux : pc[x]){
        //cout << aux.mat;
        for(int i=0;i<aux.n;i++){
          for(int j=0;j<aux.m;j++){
            cerr << aux.mat[(i*MAXSIZE+j)];
          }
          printf("\n");
        }
        printf("-------\n");
      }
      printf("----NEW ELEMENT---\n");
    }

    printf("\nCONT : %3d\n",cont);*/
  }
}

