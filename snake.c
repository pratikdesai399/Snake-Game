#include<stdio.h>
#include<windows.h>
#include <conio.h>
#include <stdlib.h>
#include<time.h>

#define R 20
#define C 40

int i,j,Field[R][C],x,y,Gy,Head,Tail,Game,Frogs,a,b,v,direction,score,Highscore;

FILE *fp;

void snakeBody(){
    fp = fopen("Highscore.txt","r");
    fscanf(fp,"%d",&Highscore);
    fclose(fp);

     for(i=0; i < R;i++){
         for(j=0; j<C; j++){
             Field[i][j]=0;
         }
     }

     // x and y are coordinated of the snake
     // Set them to centre

     x = R/2;  //10
     y = C/2;  //20
     Gy=y;  //20

     //Initial head and tail values of the snake

     Head = 5;
     Tail = 1;
     Game =0;
     Frogs = 0;
     direction = 'd';
     

     for(i=0;i<Head;i++){
         Gy++;
         Field[x][Gy-Head] = i+1;
     }
}

void fieldinit(){
    for(i = 0; i <= C+1;i++){
		if(i==0){
			printf("%c",201);
		}else if(i == C+1){
            printf("%c",187);
        }else{
            printf("%c",205);
        }
	}

    printf("YOUR SCORE : %d    HIGHSCORE : %d",score,Highscore);
    
    printf("\n");

    for(i=0;i<R;i++){
        printf("%c",186);
        for(j=0;j<C;j++){
            if(Field[i][j]==0){
                printf(" ");
            }

            // Snake Body
            if(Field[i][j] >0 && Field[i][j]!=Head){
                printf("%c",176);
            }
            // Snake Head
            if(Field[i][j] ==Head){
                printf("%c",178);
            }
            // Frogs
            if(Field[i][j] == -1){
                printf("%c", 254);
            }

            


            if(j==C-1){
                printf("%c\n",186);
            }
        }
        
    }
    for(i=0;i<=C+1;i++){
        if(i==0){
            printf("%c",200);
        }else if(i==C+1){
            printf("%c",188);
        }else{
            printf("%c",205);
        }
    }
}

void resetScreen(){
    HANDLE hout;  // To handle the screen
    COORD Position;  // Coordinates

    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hout,Position); 
}

void Random(){
    srand(time(0));
    a = 1 + rand()%17;
    b = 1 + rand()%37;

    if(Frogs == 0 && Field[a][b] == 0){
        Field[a][b] = -1;
        Frogs = 1;
    }
}

int  getchar(){
    if(_kbhit()){
        return _getch();     // If keyboard is hit return ascci ofthat char
    }else{
        return -1;     
    }
}

void movement(){
    v = getchar();
        

    if(((v == 'a' || v == 's' )|| (v == 'd'|| v == 'w') ) && abs(direction-v)>5){
        direction = v;
    }

    if(direction == 'd'){
        y++;

        if(Field[x][y]!=0 && Field[x][y]!=-1){
            GameOver();
        }
        if(y==C-1){
            y=0;
        }

        if(Field[x][y]==-1){
            Frogs = 0;
            score += 10;
            Tail = Tail - 2;
        }
        Head++;
        Field[x][y] = Head;
    }

    if(direction == 'a'){
        y--;
        if(Field[x][y]!=0 && Field[x][y]!=-1){
            GameOver();
        }
        if(y==0){
            y=C-1;
        }
        if(Field[x][y]==-1){
            Frogs = 0;
            score += 10;
            Tail = Tail - 2;
        }
        Head++;
        Field[x][y] = Head;
    }

    if(direction == 'w'){
        x--;
        if(Field[x][y]!=0 && Field[x][y]!=-1){
            GameOver();
        }
        if(x==-1){
            x=R-1;
        }
        if(Field[x][y]==-1){
            Frogs = 0;
            score += 10;
            Tail = Tail - 2;
        }
        Head++;
        Field[x][y] = Head;
    }

    if(direction == 's'){
        x++;
        if(Field[x][y]!=0 && Field[x][y]!=-1){
            GameOver();
        }
        if(x==R-1){
            x=0;
        }
        if(Field[x][y]==-1){
            Frogs = 0;
            score+=10;
            Tail = Tail - 2;
        }
        Head++;
        Field[x][y] = Head;
    }
}

void TailUpdate(){
      for(i=0;i<R;i++){
          for(j=0;j<C;j++){
              if(Field[i][j]==Tail){
                  Field[i][j] = 0;
              }
          }
      }
      Tail++;
}

void GameOver(){
    
    printf("OOPS YOU BITE YOURSLESS  \a");
    Sleep(3000); //Time delay so that the user can read the message

    // Clear the screen
    system("Cls");
    if(score > Highscore){
        printf("CONGRATS!! YOU GOT A NEW HIGHSCORE : %d\n\n",Highscore);
        system("pause");
        fp = fopen("Highscore.txt","w");
        fprintf(fp,"%d",score);
        fclose(fp);
        Highscore = score;
    }
    system("Cls");

    printf("\n\nGAME OVER!!\n");
    printf("SCORE : %d\n\n",score);

    Game = 1;   // So that the loop stops
}

void main(){
    snakeBody();

    while(Game == 0){
         fieldinit();
         resetScreen();
         Random();
         movement();
         TailUpdate();
         Sleep(99);
         
    }



    
}