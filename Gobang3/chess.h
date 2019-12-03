#pragma once

#include<iostream>
#include<iomanip>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<sstream>
#include<unordered_map>
#define N 15
using namespace std;

//extern const int N;//N为棋盘长宽;  
extern unordered_map<char,int> mp;

class Chessboard
{
protected:
    int flag = 0;//下棋方 0为player1 1为player2
    int model = 1; //游戏模式 0为双人对战 1为人机对战
    int Board[N][N]={0};//用字符串二维数组表示纵横交界
    int scoreBoard[N][N]={0}; //电脑评分棋盘
    int score[2]={0};//player1、2的分数
    enum Message{Position_Occupy,Invalid_Input,Correct_Input} mess;
public:
    Chessboard();
    ~Chessboard();
    void run();

    void GameUI(); //游戏UI
    void initBoard(); //初始化棋盘 不显示
    void RenewBoard();//更新棋盘 并显示
    void painter(int sign);
    void Boardpainter(); //按照当前Board数组绘制棋盘 并显示
    void Put(int x,int y,int firsthand);
    int check(int x, int y);
    void ComputerMove(int &x,int &y,int firsthand,int try_num);//电脑落子
    void updatescore(int firsthand);//更新评分棋盘
    int to_coordinate(char row);
    void withdraw(int x, int y,int cur);//悔棋
    bool checkForbidden(int x,int y);//检查禁手
    int win_or_not(int x,int y,int flag,int firsthand);
    int win_or_not2(int x,int y,int flag,int firsthand);
    int CheckBoard(int i, int j, char flag);
    int Judge(int x,int y,int firsthand);
    inline void setflag(int f){flag=f;}
    inline int getflag(){return flag;};
    inline void setModel(int M){model=M;}
    inline int getModel(){return model;}
};