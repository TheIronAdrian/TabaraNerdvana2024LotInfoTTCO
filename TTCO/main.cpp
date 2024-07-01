#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include "Citire.h"
#include "Matrice.h"
#include "Time.h"
#include "PiesePosibile.h"
#define TIME 0
#define MOVE 1
#define PLAY 2
#define QUIT 3
//#define
using namespace std;

int main(){
  INPUT linie;

  Init();
  TimeInit();

  linie.val=-1;
  while(linie.val!=QUIT){
    linie=ReadLine();

    switch (linie.val){
      case TIME:
        if(start!=-1){
          cout << "= " << TimeLeft() << "\n";
        }else{
          TimeStart();
          cout << "= 0\n";
        }
      break;

      case MOVE:
        cout << "= move\n";
      break;

      case PLAY:
        Occupy(linie.text);
        cout << "=\n";
      break;
    }

    cout.flush();
    //cerr << linie.val;
  }

  for(int i=0;i<MAXSIZE;i++){
    for(int j=0;j<MAXSIZE;j++){
      printf("%d",matPiese[i][j]);
    }
    printf("\n");
  }

  return 0;
}
