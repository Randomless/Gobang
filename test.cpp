#include<iostream>
#include<stdlib.h>
#include"cmdChess.h"
using namespace std;

extern const int N ; //修饰N为常量
extern int A,B;


int main()
{
    
    jiemian obj;
    obj.Jiemainbuzhi();
    while(1)
    {
        int x=0, y=0;
        char flager;
        std::cout << "input instruction:";
        char command;
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