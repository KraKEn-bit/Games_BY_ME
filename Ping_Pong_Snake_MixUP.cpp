// #include<raylib.h>

// int main(){
//     InitWindow(1000,800,"My first Raylib Project");
//     int ballX=500,ballY=500;
//     SetTargetFPS(80);
//     Color green={20,160,133,255};
//     float radius=25;
//     int slices=50;
//     int rings=70;
//     while(WindowShouldClose()==false){
//         //Event Handling

//         //Position changing
//         if(IsKeyDown(KEY_RIGHT)){
//             ballX+=2;
//         }
//         else if(IsKeyDown(KEY_LEFT)){
//             ballX-=2;
//         }
//         else if(IsKeyDown(KEY_UP)){
//             ballY-=2;
//         }
//         else if(IsKeyDown(KEY_DOWN)){
//             ballY+=2;
//         }
//         //Drawing Object
//         BeginDrawing();
//         ClearBackground(green);
//         DrawCircle(ballX,ballY,20,WHITE);
//         EndDrawing();
//     }
//     CloseWindow();
//     return 0;
// }


#include<raylib.h>

int main(){
    InitWindow(1000,800,"Ping_Pong Game");
    Color green={20,160,133,255};
    SetTargetFPS(60);
    
    //Circular Ball:
    float ballX=500;
    float ballY=400;
    int ball_radius=25;
    int dx=5.0f; //speed at x direction
    int dy=5.0f; //speed at y direction

    //Stage_1:
    int posX=65,posY=320;
    int width=40,height=170;

    //Stage_2:
    int posX2=1000-posX,posY2=320;
    int width2=40,height2=170;

    //Mid_Line:
    float start_posX=500,start_posY=0,end_posX=500,end_posY=800;

    //Mid_Circle:
    int mid_circleX=500,mid_circleY=400;
    int mid_radius=200;


    //CPU_Work:
    float cpu_speed=4.0f;
    bool ballHitPlatform1 = false;
    bool ballHitPlatform2 = false;
    bool cpuControl = false;

    int playerhit1=0,playerhit2=0,winner=0,framesSinceWin=0;

    while(WindowShouldClose()==false){
        //event handling

        //position changing
        ballX+=dx;
        ballY+=dy;

        if((ballX-ball_radius<=0) || (ballX+ball_radius)>=GetScreenWidth()){
            dx*=-1;
        }
        if((ballY-ball_radius<=0) || (ballY+ball_radius)>=GetScreenHeight()){
            dy*=-1;
        }

        if(IsKeyDown(KEY_UP)){
            if(posY>0){
                posY-=4;
            }
        }
        else if(IsKeyDown(KEY_DOWN)){
            if(posY + height <= GetScreenHeight()){
                posY+=4;
            }
        }

    char forward='W',backward='S';
   if (!cpuControl) {
    if (IsKeyDown(forward) && posY2 > 0) {
        posY2 -= 4;
    }
    if (IsKeyDown(backward) && posY2 + height2 <= GetScreenHeight()) {
        posY2 += 4;
    }
} else {
    if (ballY < posY2 + height2 / 2) {
        posY2 -= cpu_speed;
    } else if (ballY > posY2 + height2 / 2) {
        posY2 += cpu_speed;
    }

    // Clamp the paddle
    if (posY2 < 0) posY2 = 0;
    if (posY2 + height2 > GetScreenHeight()){
        posY2 = GetScreenHeight() - height2;
    }
}

        //Collision Setup:
        Rectangle platform1 = { (float)posX, (float)posY, (float)width, (float)height };
        Rectangle platform2 = { (float)posX2, (float)posY2, (float)width2, (float)height2 };

    if (winner == 0) {
    if (CheckCollisionCircleRec((Vector2){ballX, ballY}, ball_radius, platform1)) {
        if (!ballHitPlatform1) {
            dx *= -1;
            playerhit1++;
            ballHitPlatform1 = true;
            if (playerhit1 == 5) {
                winner = 1;
            }
        }
    } else {
        ballHitPlatform1 = false; 
    }
    if (CheckCollisionCircleRec((Vector2){ballX, ballY}, ball_radius, platform2)) {
        if (!ballHitPlatform2) {
            dx *= -1;
            playerhit2++;
            ballHitPlatform2 = true;
            if (playerhit2 >= 5) {
                cpuControl = true; 
            }
            if (playerhit2 == 5) {
                winner = 2; 
            }
        }
    } else {
        ballHitPlatform2 = false;
    }
} else {
    framesSinceWin++;
    if (framesSinceWin > 180) {
        playerhit1 = 0;
        playerhit2 = 0;
        winner = 0;
        framesSinceWin = 0;
        //cpuControl = false; 
    }
}  

    if (winner == 1) {
        DrawText("Player-1: Has WON!! TORE CHUDI", 250, 150, 30, YELLOW);
    } else if (winner == 2) {
        //DrawText("Player-2: Has WON!! TORE CHUDI", 200, 150, 30, YELLOW);
        if(ballY<posY2+height2/2){
            posY2-=cpu_speed;
        }
        else if(ballY>posY2+height2/2){
            posY2+=cpu_speed;
        }
    } else {
        DrawText(TextFormat("Player-1: %d", playerhit1), 200, 100, 30, YELLOW);
        DrawText(TextFormat("Player-2: %d", playerhit2), 700, 100, 30, YELLOW);
    }

        //Drawing Object
        BeginDrawing();
        ClearBackground(green);
        DrawCircle(ballX,ballY,ball_radius,WHITE);
        DrawRectangle(posX,posY,width,height,BLACK);
        DrawRectangle(posX2,posY2,width2,height2,BLACK);
       DrawLineEx((Vector2){start_posX, start_posY}, (Vector2){end_posX, end_posY}, 5.0f, BLACK);
        
        
       int thickness=5;
       for(int i=0;i<thickness;i++){
            DrawCircleLines(mid_circleX,mid_circleY,mid_radius-i,BLACK);
       }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}