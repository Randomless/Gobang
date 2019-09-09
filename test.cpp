#include<iostream>
#include<stdlib.h>
#include<iomanip>//格式化输出
using namespace std;

const int N = 9; //修饰N为常量
static int A=0, B=0;
char command;


class jiemian{
public:
    void Jiemainbuzhi();
    void initBoard();
    void Qijubuzhi();
    void Chesspainter(int x,int y);
    int check(int x, int y);
    int checkcommand(int x, int y);
    void chessicont(int x);
    int Checkzuobiao(int i, int j, char flag);
    int x, y;  //设置路障
protected:
    bool flag = 0; //下棋次数计数
    char chessBord[N + 1][N + 1];
};

void jiemian::chessicont(int x)
{
    if (x == 1) A++;
    if (x == 2) B++;
    std::cout<< "A : B -" << A << ":" << B << '\t';
}


void jiemian::Jiemainbuzhi()
{
    std::cout << "_____________start game_________" << endl;
    std::cout << "________________________________" << endl;
    std::cout << "_____________1.enter game  E_____________" << endl;
    std::cout << "_____________2.quit game 0 0_____________" << endl;
    std::cout << "_____________3.chose level  C_____________" << endl; 
    std::cout << "################################" << endl;
}


void jiemian::Qijubuzhi()
{
    std::cout << "plaese entry - x - y " << endl;
    std::cout << setw(3) << setfill(' ') << left << 0;
    for (int i = 1; i < N + 1; i++) 
    {
        std::cout << setw(6) << setfill(' ') << right << i;
    }
    std::cout << endl;
    std::cout << "   |";
    for (int i = 1; i < N + 1; i++) 
    {
        std::cout << "-----|";
    }
    std::cout << endl;
    for (int i = 1; i < N + 1; i++) 
    {
        for (int j = 0; j < N + 1; j++) 
        {
            if (j == 0) {
                std::cout << setw(3) << setfill(' ') << left << i << '|';
            }else {
                std::cout << "  " << chessBord[i][j] << "  |";
            }
        }
        std::cout << endl;
        std::cout << "  |";
        for (int i = 1; i < N + 1; i++) 
        {
            std::cout << "-----|";
        }
        std::cout << endl;
    }
}


void jiemian::initBoard()
{
    for (int i = 0; i < N + 1; i++)
        for (int j = 0; j < N + 1; j++)
        {
            chessBord[i][j] = ' '; //初始化
        }
}


void jiemian::Chesspainter(int x, int y) //下棋
{
    if (-1 == check(x, y))
    {
        std::cout << "invalid coordinate!please input again!"<<endl;
    }
    else if (0 == check(x, y))
    {
        std::cout << "already input x y ,dont input again!" << endl;
    }
    else
    {
        system("CLS");
        if (flag == 0)
        {
            chessBord[x][y] = 'x';
            std::cout << "Palyer " << "A with 'x' IS " << "X," << x << "Y," << y << endl;
            flag = 1;
        }
        else if (flag == 1)
        {
        chessBord[x][y] = 'o';
        std::cout << "Palyer " << "B with 'o' IS " << "X," << x << "Y," << y << endl;
        flag = 0;
        }
        Qijubuzhi();
    }
}


int  jiemian::checkcommand(int x,int y)  //缺少容错机制
{
    if(0==x&&0==y)
    {
        return 1;
    }
    else
        return 0;
}


int jiemian::check(int x, int y)
{
    if (x > N + 1 || y > N + 1 || x < 1 || y < 1)
    {
        return -1;
    }
    if (chessBord[x][y] != ' ')
    {
        return 0;
    }
    return 1;
}


int jiemian::Checkzuobiao(int i,int j ,char flag)//入参坐标和选手的旗子
{
    int x = i, y = j;
    int begin = 0;
    int end = 0;

    int begin1 = 0;
    int end1 = 0;

    //判断列是否满足条件  hao
    (i - 4) > 0 ? begin = i - 4 : begin = 1; //已经将列减4 或者从边界算
    (i + 4) < N ? end = N : end = (i + 4);


    for (j, i = begin; i + 4 <= end; i++)
    {
        if (chessBord[i][j] == flag&&chessBord[i + 1][j] == flag&&chessBord[i + 2][j] == flag&&chessBord[i + 3][j] == flag&&chessBord[i + 4][j] == flag)
        {
        return 1;
        }
    }

    //判断行是否满足条件 hao
    i = x, j = y;
    (j - 4) > 0 ? begin = j - 4 : begin = 1; //已经将横坐标减4
    (j + 4) < N ? end = N : end = (j + 4); //如果末尾大于N则，从N算最后一个


    for (i, j = begin; j + 4 <= end; j++)
    {
        if (chessBord[i][j] == flag&&chessBord[i][j + 1] == flag&&chessBord[i][j + 2] == flag&&chessBord[i][j + 3] == flag&&chessBord[i][j + 4] == flag)
        {
        return 1;
        }
    }

    //判断正对角线是否满足 HAO
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
        if (chessBord[i][j] == flag&&chessBord[i + 1][j + 1] == flag&&chessBord[i + 2][j + 2] == flag&&chessBord[i + 3][j + 3] == flag&&chessBord[i + 4][j + 4] == flag)
        {
            return 1;
        }
    }


    //判断负对角线是否满足 HAO
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
        if (chessBord[i][j] == flag&&chessBord[i + 1][j - 1] == flag&&chessBord[i + 2][j - 2] == flag&&chessBord[i + 3][j - 3] == flag&&chessBord[i + 4][j - 4] == flag)
        {
            return 1;
        }
    }

    //判断棋盘是否下满 .ZUIHOU
    for (int z = 1; z < N + 1; z++) //棋盘有没有下满
    {
        for (int l = 1; l < N + 1; l++)
        {
            if (chessBord[z][l] == ' ')
            return -1; //说明棋盘中还有空格
        }
    }

    return 0;
}






int main()
{
    jiemian obj;
    obj.Jiemainbuzhi();
    while(1)
    {
        int x=0, y=0;
        char flager;
        std::cout << "input instruction:";
        cin >> command;
        if ('E' == command)
        {
            system("CLS");
            obj.initBoard();
            obj.Qijubuzhi();
            while ('E' == command)
            {
                std::cout << "input coordinate:";
                cin >> x >> y;
                if (1 == obj.checkcommand(x, y))
                {
                    break;
                }
                obj.Chesspainter(x, y);

                if (0 == obj.Checkzuobiao(x, y, ' ')) //判断棋盘是否下满HAO
                {
                    std::cout << "draw:againt ?  Y  OR  N  " << endl;
                    cin >> flager;
                    if (flager == 'N')
                    {
                        break;
                    }
                    else
                    {
                    system("CLS");
                    obj.initBoard();
                    }
                }

                if (1== obj.Checkzuobiao(x, y,'x')|| 1== obj.Checkzuobiao(x, y, 'o'))
                {
                    if (1 == obj.Checkzuobiao(x, y, 'x'))
                    {
                        obj.chessicont(1); //显示比分
                        std::cout << "Player A win!" << endl;
                    }
                    if (1 == obj.Checkzuobiao(x, y, 'o'))
                    {
                        obj.chessicont(2);
                        std::cout << "Player B win!" << endl;
                    }
                    std::cout << "play again? Y or N " << endl;
                    cin >> flager;
                    if (flager == 'N')
                    {
                        break;
                    }
                    else
                    {
                        obj.initBoard();
                    }
                }
            }
        }
        else if ('C' == command)
        {
            system("CLS");
            std::cout<< "please waitting..." << endl;
        }
        else
        {
            system("CLS");
            std::cout<< "invalid command,please input again!" << endl;
            obj.Jiemainbuzhi();
        }
    }
}