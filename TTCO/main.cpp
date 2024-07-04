#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#define TIME 0
#define MOVE 1
#define PLAY 2
#define QUIT 3
#define INFI 1000000000
#define DEBUG 0
#define PLAYAREA 14
#include "Citire.h"
#include "PiesePosibile.h"
#include "Matrice.h"
#include "Time.h"
#include "PlacePiece.h"
using namespace std;

int main(){
  INPUT linie;

  Init();
  InitPiese();
  TimeInit();

  linie.val=-1;
  while(linie.val!=QUIT){
    linie=ReadLine();

    switch (linie.val){
      case -1:
        cout << "= \n\n";
      break ;
      case TIME:
        if(start!=-1){
          cout << "= " << TimeLeft() << "\n\n";
        }else{
          TimeStart();
          cout << "= 0\n\n";
        }
      break;

      case MOVE:
        cout << "= "<<PlaceAPiece(FindPiece(0)) <<"\n\n";
      break;

      case PLAY:
        Occupy(linie.text);
        cout << "= \n\n";
      break;
    }

    cout.flush();
    //cerr << linie.val;
  }
  cout << "= \n\n";

  if(DEBUG>1){
    for(int i=0;i<MAXSIZE;i++){
      printf("%c:",i+'a'-1);
      for(int j=0;j<MAXSIZE;j++){
        cerr << (matPiese[EU][(i*MAXSIZE+j)]);
      }
      printf("\n");
    }
    printf("--------------\n");
    for(int i=0;i<MAXSIZE;i++){
      printf("%c:",i+'a'-1);
      for(int j=0;j<MAXSIZE;j++){
        cerr << (matPiese[OPPON][(i*MAXSIZE+j)]);
      }
      printf("\n");
    }
    printf("--------------\n");
    for(int i=0;i<MAXSIZE;i++){
      for(int j=0;j<MAXSIZE;j++){
        cerr << (BORDARE[(i*MAXSIZE+j)]);
      }
      printf("\n");
    }

    printf("\n       ");
    for(int i=0;i<NRPIECE;i++){
      printf("%3d",i);
    }

    printf("\nOPSI : ");
    for(int i=0;i<NRPIECE;i++){
      printf("%3d",playerPc[i][OPPON]);
    }
    printf("\nEU   : ");
    for(int i=0;i<NRPIECE;i++){
      printf("%3d",playerPc[i][EU]);
    }
  }

  cerr << "--------Rezultat Final >"<< EvalFinal(0)/1000 << "<--------\n";
  cerr << "--------FinishGame--------\n\n";

  return 0;
}
