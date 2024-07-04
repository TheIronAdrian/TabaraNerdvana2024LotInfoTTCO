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
#define ADAN 3
#define EU 0
#define OPPON 1

int NumberOfSearched;
int NumberOfGoInDepth;
int NumberOfEvaluate;

struct RASPPIESA{
  int x,y,piesa,rot;
};

struct XYZ{
  int x,y;
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
  rasp=pc[piesa][rot].mat;

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

bitset <MAXSIZE*MAXSIZE> CalcColt(int player,bitset <MAXSIZE*MAXSIZE> colt){
  bitset <MAXSIZE*MAXSIZE> lat;


  //cout << colt << "\n";
  if(matPiese[player]==0){
    if(matPiese[1-player]==0){
      colt[FIRSTMOVEX*MAXSIZE+FIRSTMOVEY]=1;
    }else{
      colt[SECONMOVEX*MAXSIZE+SECONMOVEY]=1;
    }
  }else{
    lat =  ((matPiese[player]<<16)|
            (matPiese[player]<<1)|
            (matPiese[player]>>16)|
            (matPiese[player]>>1)|
            (BORDARE | matPiese[0] | matPiese[1])
          )^(BORDARE | matPiese[0] | matPiese[1]);


    colt=  ((matPiese[player]<<17)|
            (matPiese[player]<<15)|
            (matPiese[player]>>17)|
            (matPiese[player]>>15)|
            (BORDARE | matPiese[0] | matPiese[1] | lat)
          )^(BORDARE | matPiese[0] | matPiese[1] | lat);


  }

  return colt;
}

int Eval(int player){
  int x,colt[2],block[2],used[2];
  bitset <MAXSIZE*MAXSIZE> eval;


  for(x=0;x<2;x++){
    eval=  ((matPiese[x]<<16)|
            (matPiese[x]<<1)|
            (matPiese[x]>>16)|
            (matPiese[x]>>1)|
            (BORDARE | matPiese[0] | matPiese[1])
           )^(BORDARE | matPiese[0] | matPiese[1]);

    block[x]=eval.count();

    eval=  ((matPiese[x]<<17)|
            (matPiese[x]<<15)|
            (matPiese[x]>>17)|
            (matPiese[x]>>15)|
            (BORDARE | matPiese[0] | matPiese[1] | eval)
           )^(BORDARE | matPiese[0] | matPiese[1] | eval);

    colt[x]=eval.count();


    used[x]=matPiese[x].count();
  }

  return colt[player]*4+
         used[player]*3+
         block[1-player]*1

       -(colt[1-player]*4+
         used[1-player]*3+
         block[player]*1);
}

int EvalFinal(int player){
  return 1000*(matPiese[player].count()-matPiese[1-player].count());
}

void Undo(RASPPIESA transfer,int player){
  int x,y,piesa,rot;

  x=transfer.x;
  y=transfer.y;
  piesa=transfer.piesa;
  rot=transfer.rot;

  playerPc[piesa][player]=1-playerPc[piesa][player];

  matPiese[player]^=((pc[piesa][rot].mat<<(x*MAXSIZE))<<y);
}

void PrintMat(){
  int x,i,j;

  if(DEBUG>5){
    for(x=0;x<2;x++){
      for(i=1;i<MAXSIZE;i++){
        for(j=1;j<MAXSIZE;j++){
          cout << matPiese[x][i*MAXSIZE+j];
        }
        cout << "\n";
      }
      cout << "--------------\n";
    }
    cout << "################\n";
  }

}

int NegaMax(int adan,int player,int alpha,int beta,int fin){
  int p,poz,i,j,z,rot,last,aux,ma;
  vector <XYZ> pozi;
  bitset <MAXSIZE*MAXSIZE> colt(0);

  if(fin==2){
    return EvalFinal(player);
  }

  if(adan==ADAN){
    NumberOfEvaluate++;
    return Eval(player);
  }

  colt=CalcColt(player,colt);
  //cout << colt << "\n";
  last=0;
  while((colt>>last).count()>0){
    p=256;
    poz=last+1;
    while(p>0){
      if((colt>>(p+poz)).count()==(colt>>last).count()){
        poz+=p;
      }
      p>>=1;
    }

    pozi.push_back({poz/MAXSIZE,poz%MAXSIZE});
    last=poz+1;
  }

  ma=-INFI;

  for(z=0;z<NRPIECE;z++){
    if(DEBUG>4){
      cerr << "Piesa " << z << ": " << playerPc[z][player] << "\n";
    }
    if(playerPc[z][player]==1){
      for(rot=0;rot<pc[z].size();rot++){
        for(XYZ cord : pozi){
          for(i=0;i<pc[z][rot].n && i<cord.x;i++){
            for(j=0;j<pc[z][rot].m && j<cord.y;j++){
              NumberOfSearched++;
              if(CheckPosition(player,{cord.x-i,cord.y-j,z,rot},pc[z][rot].mat)){
                NumberOfGoInDepth++;
                Undo({cord.x-i,cord.y-j,z,rot},player);
                if(DEBUG>4){
                  cerr << cord.x << " ";
                  cerr << cord.y << " ";
                  cerr << z << " ";
                  cerr << rot << "\n";
                }
                aux=-NegaMax(adan+1,1-player,-beta,-alpha,fin);

                ma=max(ma,aux);
                alpha=max(alpha,aux);

                Undo({cord.x-i,cord.y-j,z,rot},player);

                if(alpha>=beta){
                  return ma;
                }
              }
            }
          }
        }
      }
    }
  }

  if(ma==-INFI){
    return -NegaMax(adan+1,1-player,-beta,-alpha,fin);
  }

  return ma;
}

void PrintTesting(bitset <MAXSIZE*MAXSIZE> colt,vector <XYZ> pozi){
  int c;

  //if(DEBUG>9){
    c=0;

    for(int i=0;i<MAXSIZE; i++) {
      for(int j=0;j<MAXSIZE; j++) {
        if(colt[i*MAXSIZE+j] == 1){
          cerr << "\e[102m  \e[49m\e[39m";
          if(matPiese[0][i*MAXSIZE+j] == 1 || matPiese[1][i*MAXSIZE+j] == 1){
            assert(1==1 && "You override corners");
          }
          c++;
        }else{
          if(matPiese[0][i*MAXSIZE+j] == 1) {
            cerr << "\e[105m  \e[49m\e[39m";
          }else{
            if(matPiese[1][i*MAXSIZE+j] == 1){
              cerr << "\e[43m  \e[49m\e[39m";
            }else{
              cerr << "  ";
            }
          }
        }
      }
      cerr << "\n";
    }

    if(c!=pozi.size()){
      assert(1==1 && "Numar gresit de colturi");
    }

    for(XYZ cord : pozi){
      if(colt[cord.x*MAXSIZE+cord.y]==0){
        assert(1==1 && "Colt pus gresit");
      }
    }
  //}
}

RASPPIESA FindPiece(int player){
  int p,poz,i,j,z,rot,last,ma,aux;
  RASPPIESA ans;
  vector <XYZ> pozi;
  bitset <MAXSIZE*MAXSIZE> colt(0);

  //NumberOfSearched=0;
  //NumberOfGoInDepth=0;
  //NumberOfEvaluate=0;

  colt=CalcColt(player,colt);
  //PrintMat();
  last=0;
  while((colt>>last).count()>0){
    p=256;
    poz=last+1;
    while(p>0){
      if((colt>>(p+poz)).count()==(colt>>last).count()){
        poz+=p;
      }
      p>>=1;
    }

    pozi.push_back({poz/MAXSIZE,poz%MAXSIZE});
    last=poz+1;
  }

  PrintTesting(colt,pozi);
  ma=-INFI-1;

  for(z=0;z<NRPIECE;z++){
    //if(DEBUG>4){
      //cerr << "Piesa " << z << ": " << playerPc[z][player] << "\n";
    //}
    if(playerPc[z][player]==1){
      for(rot=0;rot<pc[z].size();rot++){
        for(XYZ cord : pozi){
          for(i=0;i<pc[z][rot].n && i<cord.x;i++){
            for(j=0;j<pc[z][rot].m && j<cord.y;j++){
              NumberOfSearched++;
              if(CheckPosition(player,{cord.x-i,cord.y-j,z,rot},pc[z][rot].mat)){
                NumberOfGoInDepth++;
                //cerr << "Exista Mutarea " << z << " " << rot << "\n";
                Undo({cord.x-i,cord.y-j,z,rot},player);
                if(DEBUG>4){
                  cerr << cord.x << " ";
                  cerr << cord.y << " ";
                  cerr << z << " ";
                  cerr << rot << "\n";
                }
                //PrintMat();
                aux=-NegaMax(1,1-player,-INFI,-ma,0);
                if(aux>ma){
                  ma=aux;
                  ans={cord.x-i,cord.y-j,z,rot};
                }
                //PrintMat();
                Undo({cord.x-i,cord.y-j,z,rot},player);
              }
            }
          }
        }
      }
    }
  }

  cerr << ma << "\n";
  cerr << NumberOfSearched << " " << NumberOfGoInDepth << " " << NumberOfEvaluate << "\n";


  //assert(1==1 && "Test" );
  //assert(ma!=-INFI && "EstiProstNuAiGasitPiesa");

  return ans;
}

