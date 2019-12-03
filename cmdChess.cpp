#include"cmdChess.h"



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
    std::cout << "                                       " << '\n';
    std::cout << "_________    1.enter game : E     _____" << '\n';
    std::cout << "_________    2.quit game  : Q     _____" << '\n';
    std::cout << "_________    3.chose model: M     ____" << '\n'; 
    std::cout << "Model:Human or Computer | Default Config:Computer"<<'\n';
    std::cout << "_______________________________________" << '\n';
    std::cout << "Please input instruction:" << '\n';
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
 * @return: int 
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


void GameBoard::calculateScore(){
    int personNum = 0; // 玩家连成子的个数
    int botNum = 0; // AI连成子的个数
    int emptyNum = 0; // 各方向空白位的个数

    scoreBoard[N+1][N+1]={0};
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++){

            if (row > 0 && col > 0 &&
                chessBoard[row][col] == ' ')
            {
                for (int y = -1; y <= 1; y++)
                    for (int x = -1; x <= 1; x++)
                    {
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;
                        if (!(y == 0 && x == 0))
                        {
                            // 每个方向延伸4个子
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y > 0 && row + i * y < N &&
                                    col + i * x > 0 && col + i * x < N &&
                                    chessBoard[row + i * y][col + i * x] == 'x') 
                                {
                                    personNum++;
                                }else if (row + i * y > 0 && row + i * y < N &&
                                         col + i * x > 0 && col + i * x < N &&
                                         chessBoard[row + i * y][col + i * x] == ' ')
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                {
                                    break;
                                }
                                
                            }

                            for (int i = 1; i <= 4; i++)
                            {
                                if (row - i * y > 0 && row - i * y < N &&
                                    col - i * x > 0 && col - i * x < N &&
                                    chessBoard[row - i * y][col - i * x] == 'x') 
                                {personNum++;}
                                else if(row - i * y > 0 && row - i * y < N &&
                                         col - i * x > 0 && col - i * x < N &&
                                         chessBoard[row - i * y][col - i * x] == ' ')
                                {
                                    emptyNum++;
                                    break;
                                }
                                else
                                {
                                    break;
                                }  
                            }
                            switch (personNum)
                            {
                                case 1:
                                    scoreBoard[row][col]+=10; break;
                                case 2:
                                    if (emptyNum == 1)
                                        scoreBoard[row][col] += 30;
                                    else if (emptyNum == 2)
                                        scoreBoard[row][col] += 40;
                                    break;
                                case 3:
                                    if (emptyNum == 1)
                                        scoreBoard[row][col] += 60;
                                    else if (emptyNum == 2)
                                        scoreBoard[row][col] += 110;
                                    break;
                                case 4:
                                    scoreBoard[row][col]+=10100; break;
                                default:
                                    break;
                            } 
                            emptyNum=0;

                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y > 0 && row + i * y < N &&
                                    col + i * x > 0 && col + i * x < N &&
                                    chessBoard[row + i * y][col + i * x] == 'x') // 玩家的子
                                {
                                    botNum++;
                                }
                                else if (row + i * y > 0 && row + i * y < N &&
                                         col + i * x > 0 && col + i * x < N &&
                                         chessBoard[row +i * y][col + i * x] == ' ') // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            for (int i = 1; i <= 4; i++)
                            {
                                if (row - i * y > 0 && row - i * y < N &&
                                    col - i * x > 0 && col - i * x < N &&
                                    chessBoard[row - i * y][col - i * x] == ' ') // AI的子
                                {
                                    botNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < N &&
                                         col - i * x > 0 && col - i * x < N &&
                                         chessBoard[row - i * y][col - i * x] == ' ') // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }

                            if (botNum == 0)                      // 普通下子
                                scoreBoard[row][col] += 5;
                            else if (botNum == 1)                 // 活二
                                scoreBoard[row][col] += 10;
                            else if (botNum == 2)
                            {
                                if (emptyNum == 1)                // 死三
                                    scoreBoard[row][col] += 25;
                                else if (emptyNum == 2)
                                    scoreBoard[row][col] += 50;  // 活三
                            }
                            else if (botNum == 3)
                            {
                                if (emptyNum == 1)                // 死四
                                    scoreBoard[row][col] += 55;
                                else if (emptyNum == 2)
                                    scoreBoard[row][col] += 100; // 活四
                            }
                            else if (botNum >= 4)
                                scoreBoard[row][col] += 10000;   // 活五
                            
                        }
                    }

            }
        }
}
void GameBoard::actionByComputer(int &row,int &col){
    calculateScore();
 
    // 从评分中找出最大分数的位置
    int maxScore = 0;
    std::vector<std::pair<int, int>> maxPoints;

    for (int row = 1; row < N; row++)
        for (int col = 1; col < N; col++)
        {
            // 前提是这个坐标是空的
            if (chessBoard[row][col] == ' ')
            {
                if (scoreBoard[row][col] > maxScore)          // 找最大的数和坐标
                {
                    maxPoints.clear();
                    maxScore = scoreBoard[row][col];
                    maxPoints.push_back(std::make_pair(row, col));
                }
                else if (scoreBoard[row][col] == maxScore)     // 如果有多个最大的数，都存起来
                    maxPoints.push_back(std::make_pair(row, col));
            }
        }
    // 随机落子，如果有多个点的话
    // srand((unsigned)time(0));
    // int index = rand() % maxPoints.size();
    int pi=maxPoints.size();
    int index=pi/2;
 
    std::pair<int, int> pointPair = maxPoints.at(index);
    row = pointPair.first; // 记录落子点
    col = pointPair.second;
    
}