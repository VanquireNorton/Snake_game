#include<iostream>
#include<conio.h> //for e direction
#include<windows.h> // for kbhit and set console
using namespace std;
bool game_over;
const int width=20;
const int height=20;
int head_x,head_y;
int fruit_x,fruit_y,score;
int tail_x[100],tail_y[100];
int n_tail;
enum eDirection{ STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
void setup()
{
    game_over=false;
    dir=STOP;
    head_x=width/2;
    head_y=height/2;
    fruit_x=rand()%width;
    fruit_y=rand()%height;
    score=0;
}
void draw()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0}); /// it takes cursor to first word of top line and starts to overwrite the text so the flickering just stops
    for(int i=0;i<width+2;i++)
    cout<<"#";
    cout<<endl;

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(j==0)
            cout<<"#";
            if(i==head_y && j==head_x)
            cout<<"O";
            else if(i==fruit_y && j==fruit_x)
            cout<<"F";
            else
            {
                bool print=false;
                for(int k=0;k<n_tail;k++)
                {
                    
                    if(tail_x[k]==j && tail_y[k]==i)
                    {
                        cout<<"o";
                        print =true;
                    }
                }
                if(!print)
                cout<<" ";
            }
            if(j==width-1)
            cout<<"#";        
        }
        cout<<endl;
    }
    for(int i=0;i<width+2;i++)
    cout<<"#";
    cout<<endl;
    cout<<"Score:"<<score<<endl;
}
void input()
{
    if(_kbhit())   //returns 1 if any key from keyboard is pressed else returns 0
    {
        switch(_getch()) //returns the ascii value of character input
        {
            case 'a':
                dir=LEFT;
                break;
            case 'd':
                dir=RIGHT;
                break;
            case 'w':
                dir=UP;
                break;
            case 's':
                dir=DOWN;
                break;
            case 'x':
                game_over=true;
                break;
        }
    }
}
void logic()
{
    int prev_x=tail_x[0];
    int prev_y=tail_y[0];
    int prev2x,prev2y;
    tail_x[0]=head_x;
    tail_y[0]=head_y;
    for(int i=1;i<n_tail;i++)
    {
        prev2x=tail_x[i];
        prev2y=tail_y[i];
        tail_x[i]=prev_x;
        tail_y[i]=prev_y;
        prev_x=prev2x;
        prev_y=prev2y;
    }
    switch(dir)
    {
        case LEFT:
            head_x--;
            break;
        case RIGHT:
            head_x++;
            break;
        case UP:
            head_y--;
            break;
        case DOWN:
            head_y++;
            break;
        default:
            break;
    }
    /*if(head_x>width || head_x<0 || head_y>height || head_y<0)
    {
        game_over=true;
    }*/
    if(head_x>=width)
    head_x=0;
    else if(head_x<0)
    head_x=width-1;
    if(head_y>=height)
    head_y=0;
    else if(head_y<0)
    head_y=height-1;
    for(int i=0;i<n_tail;i++)
    {
        if(tail_x[i]==head_x && tail_y[i]==head_y)
        {
            game_over=true;
        }
    }
    if(head_x==fruit_x && head_y==fruit_y )
    {
        score+=10;
        fruit_x=rand()%width;
        fruit_y=rand()%height;
        n_tail++;
    }
}
int main()
{
    setup();
    while(!game_over)
    {
        draw();
        input();
        logic();
        Sleep(40);
        //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    }
    return 0;
}