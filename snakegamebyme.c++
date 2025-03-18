#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<windows.h> 

using namespace std;
bool gamestop;
int width=30,height=30,foodX,foodY,snake_x=0,snake_y=0,score=0;
enum directions{stop,Forward,Left,Right,Backward};
directions dir;
void setup(){
    srand(time(0));
     gamestop=false;
    snake_x=height/2;
    snake_y=width/2;
    foodX=rand()%height;
    foodY=rand()%width;
}
void map(){
    system("cls");
        for(int h=0;h<height;h++){
            cout<<" ";
            for(int w=0;w<width;w++){
               if(h==0 || h==height-1){
                cout<<"-";
               }
               else if(w==0 || w==width-1){
                cout<<"|";
               }     
               else if(h==snake_x && w==snake_y){
                cout<<"@";
              }
              else if(h==foodX && w==foodY){
                cout<<"*";
              }
               else{
                cout<<" ";
               }
            }
            cout<<endl;
        }
        cout<<"Your score is: "<<score<<endl;
}
void gameLogic(){
 dir=Forward;
 char key=getch();
if(key=='w' || key=='W'){
    dir=Forward;
    snake_x--;
}
else if(key=='s' || key=='S'){
    dir=Backward;
    snake_x++;
}
else if(key=='a'||key=='A'){
    dir=Left;
    snake_y--;
}
else if(key=='d'||key=='D'){
    dir=Right;
    snake_y++;
}

 if(snake_x==foodX && snake_y==foodY){
    score+=5;
    foodX=rand()%height;
    foodY=rand()%width;
}
if(snake_x>=height-1 ||snake_x<=0 || snake_y>=width-1 || snake_y<=0){
    gamestop=true;
}
}
int main(){
setup();
    while(!gamestop){
        map();
        gameLogic();
        Sleep(100);
    }
    cout<<"It's Game over ";
    return 0;
}