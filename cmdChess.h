#pragma once

#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;

extern const int N = 12;//N为棋盘长宽;  
extern int A,B;
extern char Model;

class GameBoard{
public:
    GameBoard(){};
    ~GameBoard(){};
    void GameStart();
    void initchessBoard();
    void RenewBoard();
    void Chesspainter(int x,int y);
    int check(int x, int y);
    void WinnerCount(int x);
    int CheckBoard(int i, int j, char flag);
    void setflag(int f){flag=f;} //设置当前下棋方
    int x, y;  //设置路障
    int getflag(){return flag;};
    void calculateScore(); // 计算评分
    void actionByComputer(int &Row, int &Col); // 机器执行下棋
protected:
    int flag = 0; //下棋方
    char chessBoard[N + 1][N + 1];//用字符串二维数组表示全部棋子
    int scoreBoard[N+1][N+1]={0};
};