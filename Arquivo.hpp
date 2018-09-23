#include <iostream>
#include <fstream>
#include <queue>

// lê os processos do arquivo do arquivo
 int obterLinhas(void){                                    
    std::ifstream arquivo("Processos entrada.txt");
    std::string obter_linhas;
    int linhas=0, i;
    for (i=0; std::getline(arquivo, obter_linhas); ++i)
    linhas++;
    return linhas;
}

// pega os processos do arquivo
 void obterProcessos(int processo[][2]){               
    int aux=0, linha=0, dados;
    std::ifstream arquivo("Processos entrada.txt");
    while(arquivo >> dados){
        aux++;
        if((aux%2)==0){
            processo[linha][1]=dados;
            linha++;
    } else {
            processo[linha][0]=dados;
       }
    }  
}
// função que vê quantos processos faltam
 bool Fprocessos (int processo[][2], int p){
    int i;
    for(i=0; i<p; i++){
        if(processo[i][1] != 0)
            return true;
}
    return false;
}
// funcao que ordena os processos por ordem de chegada
void ordenaChegada(int processo[][2], int p){
      int aux, temp[2], k, j;                                                                                                   
        for(k=0; k <p; k++){
               aux = k;
               for(j = k+1; j < p; j++) {
                   if(processo[j][0] < processo[aux][0])
                   aux=j;
     }                                
               temp[0]=processo[k][0];                                                        
               temp[1]= processo[k][1];                                
               processo[k][0]= processo[aux][0];                                                        
               processo[k][1]= processo[aux][1];
               processo[aux][0] = temp[0];
               processo[aux][1] = temp[1];
       } 
}

//procurar processo na fila
bool VerQueue(std::queue <int> fila,int value){
  int aux;
  while(!fila.empty())
  {
    aux=fila.front();
    fila.pop();
    if(aux == value)
      return true;
  }
  return false;
}

// funcao que pega o menor processo proximo
int menorProcessoSJF(int processo[][2], int p, int temp){
    int idMenorduracao = -1, i;
    if(Fprocessos(processo, p)){
        for(i=0; i < p; i++)
{
    if((processo[i][0] <= temp) && (processo[i][1]!=0)){
             if(idMenorduracao == -1)
                idMenorduracao = i;
             else if(processo[i][1] < processo[idMenorduracao][1])
                idMenorduracao = i;
            }
            }
             if(idMenorduracao == -1){
             for(int i=0; i <p; i++)
             {
            if((processo[i][0] > temp) &&(processo[i][1] != 0))
            {
             temp = processo[i][0];
             idMenorduracao = i;
             break;
            }
            }
            for(int i = idMenorduracao; i <p; i++)
            {
            if((processo[i][0] == temp) && (processo[i][1] != 0))
             {
             if(processo[i][1] < processo[idMenorduracao][1])
             idMenorduracao = i;
             }
             }   
             }

        }
          return idMenorduracao;                      
    }

        

