
#include <iostream>
#include <fstream>
#include <iomanip>    
#include <queue>
#include "Arquivo.hpp"
using namespace std;


// escalonamento fcfs = o primeiro  que chega é o primeiro a sair  
void FCFS(int processo [][2], int p){                                                            
        ordenaChegada(processo,p);
        float tempoRetornoMedio=0, tempoRespostaMedio=0, tempoEsperaMedio=0;
        int i=0, tempo_de_Execucao=0;   
            tempo_de_Execucao = processo[0][0];                                                   
            for (i=0; i < p; i++){
            if(processo[i][0] > tempo_de_Execucao)
            tempo_de_Execucao = processo[i][0];
            tempoRetornoMedio += tempo_de_Execucao + processo[i][1] - processo [i][0];              
            tempoRespostaMedio += tempo_de_Execucao - processo[i][0];                               
            tempoEsperaMedio += tempo_de_Execucao - processo[i][0];                                 
            tempo_de_Execucao += processo[i][1];
        }
        tempoRetornoMedio /= p;
        tempoRespostaMedio /= p;
        tempoEsperaMedio /= p; 
         cout<<"FCFS "<<std::fixed<<std::setprecision(1)<<tempoRetornoMedio<<" "<<tempoRespostaMedio<<" "<<tempoEsperaMedio<<endl;                     
    
}       

// escalonamento sjf = Mmenor programa primeiro 
void SJF(int processo [][2], int p){
    ordenaChegada(processo,p);
float tempoRetornoMedio=0, tempoRespostaMedio=0, tempoEsperaMedio=0;
        int i=0,tempo_de_Execucao=0;
        tempo_de_Execucao = processo[0][0];
        while ((i =menorProcessoSJF(processo,p,tempo_de_Execucao))!= -1) 
 {
        if(processo[i][0] > tempo_de_Execucao)
            tempo_de_Execucao = processo[i][0];
        tempoRetornoMedio += tempo_de_Execucao + processo[i][1] - processo[i][0];              
        tempoRespostaMedio += tempo_de_Execucao - processo[i][0];                               
        tempoEsperaMedio += tempo_de_Execucao - processo[i][0];                                 
        tempo_de_Execucao += processo[i][1];
        processo[i][1]=0;
       }
       tempoRetornoMedio /=p;
       tempoRespostaMedio /= p;
       tempoEsperaMedio /= p; 
       cout<<"SJF "<<std::fixed<<std::setprecision(1)<<tempoRetornoMedio<<" "<<tempoRespostaMedio<<" "<<tempoEsperaMedio<<endl;
      }

//escalonador RR =Round Robin com quantum 2
void RR(int processo [][2],int p){
   ordenaChegada(processo,p);
 int tempoRetorno[p]={0};
 int tempoResposta[p] = {0};
 int  tempoEspera[p] = {0};

 int quantum =2, tempo_de_Execucao;
 bool inicializado[p]={false};
 std::queue < int > fila;

 fila.push(0);
 tempo_de_Execucao = processo[0][0];

 while(Fprocessos(processo,p)){

     if(fila.empty()){
         for( int w = 0; w < p ; w++){
            if( processo[w][0] > tempo_de_Execucao ){
                fila.push(w);
                tempo_de_Execucao = processo[w][0];
                break;
            }
        }
     }

     int indice;
     indice = fila.front();
     fila.pop();
  
    
    if( !inicializado[indice] ){
        inicializado[indice] = true;
        tempoResposta[indice] = tempo_de_Execucao;
     
    }
    if (quantum > processo[indice][1]){
        tempo_de_Execucao += processo[indice][1];
        processo[indice][1] = 0 ;
    }
    else{
        tempo_de_Execucao += quantum;
        processo[indice][1]-= quantum;
    }
    if(processo[indice][1] == 0){
        tempoRetorno[indice] = tempo_de_Execucao;
    }
    for( int j = 0; j < p; j++){
        if((processo[j][0] <= tempo_de_Execucao) && (processo[j][1] != 0) && (!VerQueue(fila, j)) && (j != indice)){
            fila.push(j);
        } 
    }
     if(processo[indice][1] != 0){
            fila.push(indice);
        }
 }
 obterProcessos(processo);
    ordenaChegada(processo,p);
    float tempoRespostaMedio=0;
    float tempoEsperaMedio=0;
    float tempoRetornoMedio=0;

     for(int i=0;i<p;i++)
    {
      tempoRetorno[i]-=processo[i][0]; 
      tempoResposta[i]-=processo[i][0]; 
      tempoEspera[i]=tempoRetorno[i]-processo[i][1]; 
      tempoRetornoMedio+=tempoRetorno[i];
      tempoRespostaMedio+=tempoResposta[i];
      tempoEsperaMedio+=tempoEspera[i];
    }
    tempoEsperaMedio/=p;
    tempoRespostaMedio/=p;
    tempoRetornoMedio/=p;

    cout<<"RR "<<std::fixed<<std::setprecision(1)<<tempoRetornoMedio<<" "<<tempoRespostaMedio<<" "<<tempoEsperaMedio<<endl;
}

int main(void){
int P = obterLinhas();                                                                      
int processo[P][2];
obterProcessos(processo);
FCFS(processo,P);
obterProcessos(processo);
SJF(processo,P);
obterProcessos(processo);
RR(processo, P);
}