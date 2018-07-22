#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#define up(i,a,b) for(int i=a;i<=b;i++)
#define down(i,a,b) for(int i=a;i>=b;i--)
#define rep(i,a,b) for(int i=a;i<b;i++)
#define repd(i,a,b) for(int i=a-1;i>=b;i--)

using namespace std;

inline void Gotoxy(short x,short y){COORD co = {x,y};SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),co);}
inline void textcolor(short x){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);}
inline void clrscr(){system("cls");}

const int Ox=13,Oy=2;
const int minx=13; const int maxx=77;
const int miny=3;  const int maxy=23;

char a[79][24];

namespace GetWinner{
    inline bool Check_Vertical(char player,int x,int y){
        bool victory=true;
        while(a[x][y]==player) y--;
        up(i,1,5) if(a[x][y+i]!=player) victory=false;
        if(victory) return true;
        return false;
    }

    inline bool Check_Horizontal(char player,int x,int y){
        bool victory=true;
        while(a[x][y]==player) x--;
        up(i,1,5) if(a[x+i][y]!=player) victory=false;
        if(victory) return true;
        return false;
    }

    inline bool Check_Main_Diagonal(char player,int x,int y){
        bool victory=true;
        while(a[x][y]==player) x--,y--;
        up(i,1,5) if(a[x+i][y+i]!=player) victory=false;
        if(victory) return true;
        return false;
    }

    inline bool Check_Anti_Diagonal(char player,int x,int y){
        bool victory=true;
        while(a[x][y]==player) x++,y--;
        up(i,1,5) if(a[x-i][y+i]!=player) victory=false;
        if(victory) return true;
        return false;
    }

    inline bool Check_X_Win(int x,int y){
        if(Check_Horizontal('X',x,y)) return true;
        if(Check_Vertical('X',x,y)) return true;
        if(Check_Main_Diagonal('X',x,y)) return true;
        if(Check_Anti_Diagonal('X',x,y)) return true;
        return false;
    }

    inline bool Check_O_Win(int x,int y){
        if(Check_Horizontal('O',x,y)) return true;
        if(Check_Vertical('O',x,y)) return true;
        if(Check_Main_Diagonal('O',x,y)) return true;
        if(Check_Anti_Diagonal('O',x,y)) return true;
        return false;
    }

    inline bool Check_Draw(){
        up(i,minx,maxx) up(j,miny,maxy) if(!a[i][j]) return false;
        return true;
    }

    inline int Check_Winner(int x,int y){
        if(Check_X_Win(x,y)) return 1;
        if(Check_O_Win(x,y)) return 2;
        if(Check_Draw()) return 0;
        return -1;
    }
}

namespace Info{
    inline void PrintPlayer(int turn){
        Gotoxy(0,5);
        cout<<"Player: ";
        if(turn&1) textcolor(11),cout<<'O';
        else textcolor(12),cout<<'X';
        textcolor(7);
    }

    inline void PrintTurn(int turn){
        Gotoxy(0,7);
        cout<<"Turn: "<<turn;
    }

    inline void PrintCoord(int turn,int x,int y){
        Gotoxy(0,0);
        cout<<"Coordinate: ("<<x<<','<<y<<')';
        cout<<"\nPress Q to go to Menu";
        PrintPlayer(turn);
        PrintTurn(turn);
        Gotoxy(x,y);
    }
}

namespace TwoPlayers{
    inline void DrawBoard(){
        memset(a,0,sizeof(a));
        Gotoxy(minx-1,miny-1);
        up(i,1,maxx-minx+3) cout<<'-',Sleep(5);
        rep(i,0,maxy) Gotoxy(minx-1,i+2),cout<<'|',Sleep(5);
        Gotoxy(minx-1,maxy+1);
        up(i,1,maxx-minx+3) cout<<'-',Sleep(5);
        rep(i,0,maxy-1) Gotoxy(maxx+1,i+2),cout<<'|',Sleep(5);
    }

    inline char OX(int turn){
        return (turn&1)? 'O' : 'X';
    }

    inline void drawplayer(int x,int y,int &turn){
        if(a[x][y]) return;
        if(turn&1) textcolor(11);
        else textcolor(12);
        a[x][y]=OX(turn); cout<<a[x][y]; turn++;
        textcolor(7);
    }

    inline void goup(int x,int &y){
        y=max(miny,--y);
    }

    inline void godown(int x,int &y){
        y=min(++y,maxy);
    }

    inline void goleft(int &x,int y){
        x=max(minx,--x);
    }

    inline void goright(int &x,int y){
        x=min(++x,maxx);
    }

    inline void enter(int &x,int &y,int &turn,bool &back_menu){
        char k=getch();
        if(k=='a' || k=='A' || k==75) goleft(x,y);
        if(k=='s' || k=='S' || k==80) godown(x,y);
        if(k=='d' || k=='D' || k==77) goright(x,y);
        if(k=='w' || k=='W' || k==72) goup(x,y);
        if(k==13) drawplayer(x,y,turn);
        if(k=='Q' || k=='q') back_menu=true;
    }
}

namespace MENU{

    inline void Two_Player();
    inline void EndGame(int winner);
    inline void Against_BOT();
    inline void How_To_Play();
    inline void Credit();
    inline void Exit();

    string s[5]={"1. Two Players",
                 "2. Play against BOT",
                 "3. How to play",
                 "4. Credit",
                 "5. Exit"};
    bool c[6];
    inline void menu(){
        clrscr();
        SetConsoleTitle("ADaPT - TIC TAC TOE");

        fill(c,c+6,false);
        c[1]=true;
        Gotoxy(30,5);textcolor(15); cout<<"Tic Tac Toe"; textcolor(7);
        up(i,1,5){
            Gotoxy(25,6+i);
            if(c[i]) textcolor(10), cout<<s[i-1], textcolor(7);
            else cout<<s[i-1];
        }
        int k=0;
        int choose=1;
        while(1+1==2){
            k=getch();
            if(k==80) c[choose]=false,choose++;
            if(k==72) c[choose]=false,choose--;
            if(k==13){
                if(choose==1) Two_Player();
                if(choose==2) Against_BOT();
                if(choose==3) How_To_Play();
                if(choose==4) Credit();
                if(choose==5) exit(0);
            }
            if(choose>5) choose=1;
            if(choose<1) choose=5;
            c[choose]=true;
            Gotoxy(30,5);textcolor(15); cout<<"Tic Tac Toe"; textcolor(7);
            up(i,1,5){
                Gotoxy(25,6+i);
                if(c[i]) textcolor(10), cout<<s[i-1];
                else textcolor(7),cout<<s[i-1];
            }
        }
    }

    inline void Two_Player(){
        clrscr();
        TwoPlayers::DrawBoard();
        int x=35,y=10,turn=0;
        bool back_menu=false;
        while(!back_menu){
            Gotoxy(x,y);
            Info::PrintCoord(turn,x,y);
            TwoPlayers::enter(x,y,turn,back_menu);
            int winner=GetWinner::Check_Winner(x,y);
            EndGame(winner);
        }
        menu();
    }

    inline void Against_BOT(){
        clrscr();
        Gotoxy(5,5); textcolor(7);
        cout<<"This mode is currently being built, come again when this mode is open";
        Gotoxy(15,15); cout<<"Press any key to go back to menu...";
        getch();
        menu();
    }

    inline void How_To_Play(){
        clrscr();
        textcolor(47);
        Gotoxy(30,1);
        cout<<"HOW TO PLAY\n";
        textcolor(15);
        Gotoxy(3,3);cout<<"Use W,A,S,D or arrow keys to move";
        Gotoxy(3,4);cout<<"The player who makes 5 in a row, or 5 in a column, or 5 in a diagonal wins";
        Gotoxy(3,5);cout<<"Have a great day!\n";
        Gotoxy(15,15); cout<<"Press any key to go back to menu...";
        getch();
        menu();
    }

    inline void Credit(){
        clrscr();
        textcolor(47);
        Gotoxy(35,1);
        cout<<"CREDIT";
        textcolor(15);
        Gotoxy(5,3); cout<<"This game was made by Kamisama";
        Gotoxy(5,4); cout<<"Facebook: https://www.facebook.com/profile.php?id=100006345313150";
        Gotoxy(15,15); cout<<"Press any key to go back to menu...";
        getch();
        menu();
    }

    inline void EndGame(int winner){
        if(winner==-1) return;
        clrscr();
        Gotoxy(35,5);
        if(!winner){
            textcolor(7);
            cout<<"DRAW!";
        }
        if(winner==1){
            textcolor(12);
            cout<<"X wins!";
        }
        if(winner==2){
            textcolor(11);
            cout<<"O wins!";
        }
        textcolor(15);
        Gotoxy(15,15); cout<<"Press any key to go back to menu...";
        getch(); menu();
    }
}

int main(){
    MENU::menu();
    return 0;
}
