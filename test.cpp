#include<iostream>
#include<stdlib.h>
#include"cmdChess.h"
using namespace std;

extern const int N ;  
extern int A,B;
extern char Model;


int main()
{
    
    GameBoard obj;
    
    while(1)
    {
        int x=0, y=0;
        char flager=' ';
        obj.GameStart();
        std::cout << "input instruction:";
        char command;
        cin >> command;
        if ('E' == command)
        {
            system("CLS");
            int step=0;
            if('H'==Model){
                std::cout<<"your are playing with human now ,two players!"<<'\n';
            }else if('C'==Model)
            {
                std::cout<<"your are playing with computer now!"<<'\n';
                std::cout<<"please set who is first?Human or Computer? H or C"<<'\n';
                char first='H';
                
                std::cin>>first;
                
                if('H'==first){
                    obj.setflag(0);
                    std::cout<<"Human first! Computer is player B note with 'x' !"<<'\n';
                    step=0;
                }else{
                    obj.setflag(1);
                    std::cout<<"Computer first! Computer is player A note with 'o' !"<<'\n';
                    step=1;
                }
            }
            obj.initchessBoard();
            obj.RenewBoard();
            
            //双人对战模式  每局不交换先手
            while ('E' == command && 'H'==Model)
            {   
                std::cout << "input coordinate:";
                cin >> x >> y;
                obj.Chesspainter(x, y);
                
                if(ShowResult(obj,x,y,flager)==-1){
                    break;
                }else if(ShowResult(obj,x,y,flager)==0){
                    obj.initchessBoard();
                    obj.RenewBoard();
                    obj.setflag(0);
                }
                
                // //判断输赢方并输出统计，询问再来
                // if (1== obj.CheckBoard(x, y,'x')|| 1== obj.CheckBoard(x, y, 'o'))
                // {
                //     //system("CLS");
                //     if (1 == obj.CheckBoard(x, y, 'x'))
                //     {
                //         obj.WinnerCount(1); 
                //     }
                //     if (1 == obj.CheckBoard(x, y, 'o'))
                //     {
                //         obj.WinnerCount(2);
                //     }
                //     std::cout << '\n' <<"play again? Y or N " << '\n';
                //     cin >> flager;
                //     if (flager == 'N')
                //     {
                //         break;
                //     }
                //     else
                //     {
                //         obj.initchessBoard();
                //         obj.RenewBoard();
                //     }
                // }

                // //判断无人获胜的情况
                // if (0 == obj.CheckBoard(x, y, ' ')) //判断棋盘是否下满
                // {
                //     std::cout << "Board is full...No on wins..play againt ?  Y  OR  N  " << '\n';
                //     cin >> flager;
                //     if (flager == 'N')
                //     {
                //         break;
                //     }
                //     else
                //     {
                //         system("CLS");
                //         obj.initchessBoard();
                //         obj.RenewBoard();
                //     }
                // }
            }

            //机器对战模式  交换先手了！cmdChess.h 256 Line :return 0没有运行的原因！
            while ('E' == command && 'C'==Model){
                step=obj.getflag();
                //step 0为人类回合，1为机器回合
                if(step==0){
                    std::cout << "input coordinate:";
                    cin >> x >> y;
                    obj.Chesspainter(x, y);
                    //copy双人模式代码，判断获胜和无人获胜结果。
                    if(ShowResult(obj,x,y,flager)==-1){
                        break;
                    }
                    else if(ShowResult(obj,x,y,flager) == 0)
                    {
                        step=0;
                    }
                    else if(ShowResult(obj,x,y,flager) == 1){
                        step=1;
                    }
                    //可封装成函数 
                    //成员函数 void GameResult() 删去代码中obj.即可
                    //非成员函数  void ShowResult(GameBoard &obj)
                    
                }else if(step==1){
                    
                    obj.actionByComputer(x,y);
                    obj.Chesspainter(x, y);
                    
                    if(ShowResult(obj,x,y,flager)==-1){
                        break;
                    }else if(ShowResult(obj,x,y,flager)==0){
                        step=0;
                    }
                    else if(ShowResult(obj,x,y,flager) == 1){
                        step=0;
                    }
                    //step=0;
                }

            }
        }
        else if ('M' == command)
        {
            system("CLS");
            std::cout<< "chose play with Human or Computer... H or C" << '\n';
            std::cin>>Model;
        }
        else if('Q'==command){
            break;
        }
        else
        {
            system("CLS");
            std::cout<< "invalid command,please input again!" << '\n';
            obj.GameStart();
        }
    }
}