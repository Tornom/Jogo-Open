#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#define per 19
#define epc 32
#define fimx 78
#define fimy 22
#define pare 219
#define mazep 254
#define pry 3
#define prx 1

COORD coord={0,0};

clock_t start_t, end_t, total_t;

int x,y,p,coliX,coliY,flag,totP,P,fx,nivel,kbp,linha,mjogo,ar,xant,yant,tbit,toff,contatempo;

char snivel;

float score;

int matrixy[300][80];

void gotoxy(int u,int v);

void controle ();

void controle2();

void mover ();

void apagar ();

void ia();

void maze ();

void maze2(int obx, int oby);

void ini ();

void ini2(int obx,int oby);

void retornaprog();

void tempoponto();

void dificuldade ();

void cria_paredes ();

void mojogo();

void block (int bloco);

 int main (){
    ini();
    while(P<totP){
        controle();
        ia();
        mover();
        tempoponto();
    }
    retornaprog();
    return 0;
}

void limpa_rastro(){
    system("@cls||clear"); //limpa tela

    int k,l;                //limpa objeto
    int m= fimy;
    int n= fimx;
    for (k=pry+1;k<m;k++){
        for(l=3;l<n;l++){
            matrixy[l][k]=0;
        }
    }

    gotoxy(0,0);    //   zera paramentros
    totP=0;
    P=0;
    kbp=0;
    linha=0;
    mjogo=0;
    ar=0;
}

void ini(){
    limpa_rastro();
    printf("Comandos Cima:u Direita:k Esquerda:h Baixo:j Recomecar:x\n");
    cria_paredes ();
    start_t = clock();
    CONSOLE_FONT_INFO (cursor) = {1,FALSE};                 //desliga o cursor do terminal
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
    mojogo();
}

void retornaprog(){
if (mjogo=='1'){
    gotoxy(30,2);
    kbp=kbp/totP;
    score=((((totP+nivel/2)/(total_t)*333.3))-(((-nivel*30)+(kbp*(kbp/(40*nivel))))+sin(nivel)*(total_t*nivel)))/10-(nivel/linha)-kbp*2-total_t*total_t/nivel;  //funçao para o score (louca néh?)
    if (score<0){
        printf("Zerou X.X");
    }
    else{
    printf("Pontuacao final:%.2f",score);
    }
}


    while(1){  //aguarda o pressionar do X para recomeçar
    if(kbhit()){
        int tecla;
        tecla = getch();
        if (tecla =='x'){
            main();
        }
    }
   }
}

void mover (){
   // if (flag!=0){
    gotoxy(x,y);
    printf("%c",per);
  //  }
}

void ia (){
    if (y==pry+1){
        coliY=1;
    }
        else if(y==fimy-1){
            coliY=2;
        }
            else{
                coliY=0;
            }
    if (x==prx+1){
        coliX=1;
    }
        else if(x==fimx){
            coliX=2;
        }
            else{
                coliX=0;
            }


    if (mjogo=='1'){
    if (matrixy[x][y]==1){
        P++;
        printf("%c",07);
        matrixy[x][y]=0;
    }
    /*flag=0;
    gotoxy(x,y);             modulo para nao destruir objetos
    printf("%c",mazep);
    gotoxy(x,y);
    }
    else {
        flag=1;
    }
*/
}
else{
    if (y==fimy-1){
        ar=0;
    }
    if (matrixy[x][y+1]==1){
        ar=0;
    }
    else if (y!=fimy-1) {
        ar=1;
    }
    if (matrixy[x][y]==1){
        if (y<yant){
        gotoxy(x,y);
        printf("%c",mazep);
        y++;
        mover();
        ar=1;
        }
    }

}

}

void apagar (){
  //  if (flag!=0){
    gotoxy(x,y);
    printf("%c",epc);
//}
}

void controle(){
int tecla;
        if (kbhit()){
        apagar(x,y);
        tecla = getch();
        if (tecla =='u'&& coliY!=1){
                kbp++;
                y--;
        }
        else if (tecla=='j'&& coliY!=2){
                   y++;
                    kbp++;
            }
            else if ( tecla== 'h' && coliX!=1){
                       x--;
                       kbp++;
                }
                else if (tecla == 'k' && coliX!=2){
                           x++;
                           kbp++;
                           }
                            else if (tecla == 'x'){
                           ini();
                           }

    }
return;
}

void maze (){
    dificuldade();     //estabelece a dificuldade do jogo
    int m,n,k,l;
    m= fimy;
    n= fimx;
    srand( (unsigned)time(NULL) );
    for (k=pry+1;k<m;k=(k+(rand()%nivel+1))){   //gera objetos aleatorios baseado na dificuldade do jogo
            linha++;
        for(l=3;l<n;l=l+(rand())%nivel+1){
            totP++;                             // conta o valor max de objetos
            matrixy[l][k]=1;
         gotoxy(l,k);
         printf("%c",mazep);
        }
    }
}

void tempoponto(){
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    gotoxy(58,0);
    printf("tempo total gasto:%d    Objetivo atual:%d    Objetivos totais:%d  movimento no jogo:%d",total_t,P,totP,kbp);
}

void gotoxy (int x, int y){
coord.X=x;
coord.Y=y;// imprime parede superior
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void dificuldade(){
    gotoxy(20,10);
    printf("Selecione a Dificuldade(F,M,D):");
    scanf("%c",&snivel);
    gotoxy(20,10);
    printf("                                       ");
    srand( (unsigned)time(NULL) );
    if (snivel=='f'){
        nivel=26;
    }
        else if (snivel=='m'){
                 nivel=16;
        }
            else if (snivel=='d'){
                 nivel=8;
            }
            else dificuldade();
}

void cria_paredes (){
 gotoxy(0,pry);
    for(int a=0;a<=fimx;a++){   // imprime parede superior
        printf("_");
    }

    for (int j=0;j<2;j++){      // imprime paredes laterais
        for(int i=pry+1;i<(fimy+1);i++){
            gotoxy(j*(fimx+1),i);
            printf("%c",pare);
        }
    }
     gotoxy(0,fimy);
    for(int a=0;a<=fimx;a++){      // imprime parede inferior
        printf("_");
    }

}

void mojogo (){
    gotoxy(20,10);
    printf("Selecione o jogo(1 ou 2):");
        if (kbhit){
        mjogo=getchar();
            if (mjogo == '1'){
                x=prx+1; //ponto de inicio do personagem
                y=pry+1;
                maze();   // cria os objetivos do jogo
            }
            else if (mjogo=='2'){
                game2(6,pry+1);
                return;
            }
            else mojogo();
            }
else mojogo();
}

void game2(int obx,int oby){
    ini2(obx,oby);
    while(x!= obx || y!= oby){
    controle2();
    ia();
    mover();
    gravidade();
    Sleep(70);
    }
    retornaprog();
}

void maze2(int obx,int oby){
    int m,n,k,l,h;
    m= fimy;
    n= fimx;

   // block(rand()%12);
    srand( (unsigned)time(NULL) );
    for (k=pry+1;k<m;k=(k+(rand()%1+1))){   //gera objetos aleatorios
        for(l=3;l<n;l=l+(rand())%15+1){
            matrixy[l][k]=1;
         gotoxy(l,k);
         printf("%c",mazep);
        }
    }
    h=1;
    for (k=0;k<7;k++){
    h++;
    gotoxy(obx+k,oby+h);
    matrixy[obx+k][oby+h]=1;
    printf("%c",mazep);
    }
    gotoxy(obx,oby-2);
    for (k=oby-2;k<oby;k++){
        for (l=obx;l<obx+5;l++){
            matrixy[obx+k][oby+1]=0;
            printf("%c",epc);
        }
    }
}

void controle2(){
int tecla;
        if (kbhit()){
        apagar(x,y);
        tecla = getch();
        xant = x;
        yant = y;
        if (tecla == 'u' && coliY!=1 && ar==0){
                start_t = clock();
                contatempo=0;
                if (matrixy[x][y-2]==1 || y-2==pry){
                y=y-1;
                ar=1;
                }
                else if (matrixy[x][y-1]==1){}
                    else {
                        y=y-2;
                        ar=1;
                    }
        }
            else if ( tecla== 'h' && coliX!=1){
                    if (matrixy[x-1][y]==0) x--;
                }
                else if (tecla == 'k' && coliX!=2){
                            if (matrixy[x+1][y]==0) x++;
                           }
                            else if (tecla == 'x'){
                           ini();
                           }
    }
return;
}

void gravidade (){
    end_t=clock();
    total_t = (double)(end_t - start_t)/ ((clock_t)(150));
    if (total_t%5==2 || total_t%5==4 ) toff=1;
    if ((total_t%5==1 || total_t%5==3 || total_t%5==0)&&toff==1){
        tbit=1;
        toff=0;
        contatempo++;
    }
    if(y<fimy-1 && tbit==1 && ar==1 && contatempo>1){
        apagar();
        y++;
        mover();
        tbit=0;
    }
}

void ini2 (int obx,int oby){
    x=fimx-2;
    y=fimy-1;
    gotoxy(obx,oby);
    printf("%c",157);
    gotoxy(20,10);
    for(int a=0;a<30;a++){
    printf(" ");
    }
    maze2(obx,oby);
}
