#include<iostream>
#include<iomanip>
using namespace std;

extern const int N = 12;//N为棋盘长宽
extern int A=0, B=0;//int A B为玩家胜利次数
extern char Model='C';


class GameBoard{
public:
    void GameStart();
    void initchessBoard();
    void RenewBoard();
    void Chesspainter(int x,int y);
    int check(int x, int y);
    void WinnerCount(int x);
    int CheckBoard(int i, int j, char flag);
    void setflag(int f){flag=f;}
    int x, y;  //设置路障
protected:
    int flag = 0; //下棋方
    char chessBoard[N + 1][N + 1];//用字符串二维数组表示全部棋子
};

//cmd显示胜利者及 A B胜利次数
void GameBoard::WinnerCount(int x)
{
    if (x == 1) {
        A++;
        std::cout << "*****  Player A win!  *****" << '\n';
    }
    if (x == 2) {
        B++;
        std::cout << "*****  Player B win!  *****" << '\n';
    }
    std::cout<< "Win Time Counts |  A : B   " << A << ":" << B << '\t';
}

//cmd显示游戏开始界面
void GameBoard::GameStart()
{
    std::cout << "_____________Start Game Gobang_________" << '\n';
    std::cout << "_______________________________________" << '\n';
    std::cout << "_____________1.enter game  E___________" << '\n';
    std::cout << "_____________2.quit game   Q___________" << '\n';
    std::cout << "_____________3.chose model M__________" << '\n'; 
    std::cout << "#######################################" << '\n';
}

//更新棋盘
void GameBoard::RenewBoard()
{
    std::cout << "plaese entry - x - y " << '\n';
    
    for (int i = 1; i < N + 1; i++) 
    {
        std::cout << setw(6) << setfill(' ') << right << i;
    }
    std::cout << '\n';
    std::cout << "  |";
    for (int i = 1; i < N + 1; i++) { std::cout << "-----|";  }//输出第一行
    std::cout << '\n';
    for (int i = 1; i < N + 1; i++) 
    {
        for (int j = 0; j < N + 1; j++) 
        {
            if (j == 0) {
                std::cout << setw(2) << setfill(' ') << left << i << '|';
            }else {
                std::cout << "  " << chessBoard[i][j] << "  |";
            }
        }
        std::cout << '\n';
        std::cout << "  |";
        for (int i = 1; i < N + 1; i++) { std::cout << "-----|";} //输出最后一行
        std::cout << '\n';
    }
}

//初始化chessBoard为全' '字符串数组
void GameBoard::initchessBoard()
{
    for (int i = 0; i < N + 1; i++)
        for (int j = 0; j < N + 1; j++)
        {
            chessBoard[i][j] = ' '; 
        }
}


void GameBoard::Chesspainter(int x, int y) //下棋
{
    if (-1 == check(x, y))
    {
        std::cout << "invalid coordinate!please input again!"<<'\n';
    }
    else if (0 == check(x, y))
    {
        std::cout << "already input x y ,dont input again!" << '\n';
    }
    else
    {
        system("CLS");
        if (flag == 0)
        {
            chessBoard[x][y] = 'x';
            std::cout << "Palyer " << "Last action by Player A with 'x' is:   " << "X: " << x << " Y: " << y << '\n';
            flag = 1;
        }
        else if (flag == 1)
        {
            chessBoard[x][y] = 'o';
            std::cout << "Palyer " << "Last action by Player B with 'o' is:   " << "X: " << x << " Y: " << y << '\n';
            flag = 0;
        }
        RenewBoard();
    }
}

/*
 * 检查输入坐标合法性
 * @para:  int x,y
 * @return:int -1超限 0已占 1合法
 */
int GameBoard::check(int x, int y)
{
    if (x > N + 1 || y > N + 1 || x < 1 || y < 1)
    {
        return -1;
    }
    if (chessBoard[x][y] != ' ')
    {
        return 0;
    }
    return 1;
}

/*
 * 判断获胜和棋盘下满
 * @para：int i,j char flag
 * @return: int 1获胜 -1棋盘未满 0棋盘满
 */
int GameBoard::CheckBoard(int i,int j ,char flag)
{
    int x = i, y = j;
    int begin = 0;
    int end = 0;

    int begin1 = 0;
    int end1 = 0;

    //判断列是否满足条件
    (i - 4) > 0 ? begin = i - 4 : begin = 1; //已经将列减4 或者从边界算
    (i + 4) < N ? end = N : end = (i + 4);
    for (j, i = begin; i + 4 <= end; i++)
    {
        if (chessBoard[i][j] == flag&&chessBoard[i + 1][j] == flag&&chessBoard[i + 2][j] == flag&&chessBoard[i + 3][j] == flag&&chessBoard[i + 4][j] == flag)
        {
        return 1;
        }
    }

    //判断行是否满足条件
    i = x, j = y;
    (j - 4) > 0 ? begin = j - 4 : begin = 1; //已经将横坐标减4
    (j + 4) < N ? end = N : end = (j + 4); //如果末尾大于N则，从N算最后一个
    for (i, j = begin; j + 4 <= end; j++)
    {
        if (chessBoard[i][j] == flag&&chessBoard[i][j + 1] == flag&&chessBoard[i][j + 2] == flag&&chessBoard[i][j + 3] == flag&&chessBoard[i][j + 4] == flag)
        {
        return 1;
        }
    }

    //判断正对角线是否满足
    int len = 0;
    i = x, j = y;
    i >j ? len = j - 1 : len = i - 1; //判断i>j的作用，按照离边距小的坐标减做初始值
    if (len > 4)    len = 4;
    begin = i - len; //横坐标的起始位置
    begin1 = j - len; //纵坐标，，因为是正斜边所以两边要减相同数

    i > j ? len = (N - i) : len = (N - j); //结束坐标也要按照距离边界近的点去减
    if (len>4)  len = 4;
    end= i + len; //横坐标的结束位置
    end1 = j + len;  //纵坐标的结束位置

    for (int i = begin, j = begin1; (i + 4 < end) && (j + 4 < end1); i++, j++)
    {
        if (chessBoard[i][j] == flag&&chessBoard[i + 1][j + 1] == flag&&chessBoard[i + 2][j + 2] == flag&&chessBoard[i + 3][j + 3] == flag&&chessBoard[i + 4][j + 4] == flag)
        {
            return 1;
        }
    }

    //判断负对角线是否满足
    i = x, j = y;
    (i - 1) >(N - j) ? len = (N - j) : len = i - 1;//判断负对角线坐标的位置是否在上下减小的距离
    if (len > 4)    len = 4;
    begin = i - len; //横坐标的起始位置
    begin1 = j + len; //纵坐标的起始位置

    (N - i) > (j - 1) ? len = (j - 1) : len = (N - i);
    if (len>4)  len = 4;
    end = i + len; //横坐标的结束位置
    end1 = j - len; //纵坐标的结束位置

    for (int i = begin, j = begin1; (i + 4 < end) && (j - 4 > end1); i++, j--)
    {
        if (chessBoard[i][j] == flag&&chessBoard[i + 1][j - 1] == flag&&chessBoard[i + 2][j - 2] == flag&&chessBoard[i + 3][j - 3] == flag&&chessBoard[i + 4][j - 4] == flag)
        {
            return 1;
        }
    }

    //判断棋盘是否下满 遍历chessBoard[][]
    for (int l = 1; l < N + 1; l++) //棋盘有没有下满
    {
        for (int c = 1; c < N + 1; c++)
        {
            if (chessBoard[l][c] == ' ')
            return -1; //说明棋盘中还有空格
        }
    }

    return 0;
}

/*
 *返回落子结果
 * 
 */
int ShowResult(GameBoard &obj,int x,int y,char flager){
    if (1== obj.CheckBoard(x, y,'x')|| 1== obj.CheckBoard(x, y, 'o'))
    {
        if (1 == obj.CheckBoard(x, y, 'x'))
        {
            obj.WinnerCount(1); 
        }        
        if (1 == obj.CheckBoard(x, y, 'o'))
        {
            obj.WinnerCount(2);
        }
        std::cout << '\n' <<"play again? Y or N " << '\n';
        cin >> flager;
        if (flager == 'N'||flager=='n')
        {
            return -1;
        }
        else
        {
            obj.initchessBoard();
            obj.RenewBoard();
            obj.setflag(0);
            return 0;//这句没运行????!!
        }
    }

     //判断无人获胜的情况
    if (0 == obj.CheckBoard(x, y, ' ')) //判断棋盘是否下满
    {
        std::cout << "Board is full...No on wins..play againt ?  Y  OR  N  " << '\n';
        cin >> flager;
        if (flager == 'N'||flager=='n')
        {
            return -1;
        }
        else
        {
            system("CLS");
            obj.initchessBoard();
            obj.RenewBoard();
            return 0;
        }
    }

    return 1;
}