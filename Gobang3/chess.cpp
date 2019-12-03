#include"chess.h"
using namespace std;

//const int N = 15;//N为棋盘长宽;  
std::unordered_map<char,int> mp={{'A',0},{'B',1},{'C',2},{'D',3}, {'E',4}, {'F',5}, {'G',6}, {'H',7}, {'I',8}, {'J',9}, {'K',10}, {'L',11}, {'M',12}, {'N',13}, {'O',14}};

Chessboard::Chessboard()
{
}

Chessboard::~Chessboard()
{
}

void Chessboard::run(){
    while(1){
        initBoard();
        GameUI();
        system("CLS");
        std::cout<<"************************\n";
    }
}

void Chessboard::GameUI(){
    std::cout << "_____________Start Game Gobang_________" << '\n';
    std::cout << "                                       " << '\n';
    std::cout << "_________    1.enter game : E     _____" << '\n';
    std::cout << "_________    2.chose model: M     _____" << '\n';
    std::cout << "_________    3.quit game  : Q     ____" << '\n'; 
    std::cout << "_______________________________________" << '\n';
    std::cout << "Current Model: "<<'\n';
    if(getModel()==0){std::cout<<"Human vs Human \n";}
    else std::cout<<"Human vs Computer \n";
    std::cout << "_______________________________________" << '\n';
    std::cout << "Please input instruction:";
    char command,Model='C';mess=Correct_Input;
    cin>>command;
    if(command=='E'){
        system("CLS");
        if(0==model){
            std::cout<<"your are playing with human now ,two players!"<<'\n';
            std::cout<<"please set who go first(Player1:Human Player2:Human) 1 or 2"<<'\n';
        }else if(1==model)
        {
            std::cout<<"your are playing with computer now!"<<'\n';
            std::cout<<"please set who go first(Player1:Human Player2:Computer) 1 or 2"<<'\n';
        }
        int firsthand=0;//先手 1为player1执黑 2为player2执黑
        std::cin>>firsthand;
        flag=firsthand-1;
        initBoard();
        int firststep=1;//是该局第一步
        int x_last=5,y_last=5;//维护上一步的落子位置
        mess=Correct_Input;
        int try_num =0;//电脑尝试computermove次数
        int flag2=0;

        //该while循环为双人对战模式
        while(0==getModel()){   
            system("CLS");
            Boardpainter();
            if(flag==0){ //player1's move
                if(firsthand==1){
                    std::cout<<"\n----Player 1(Black)'s turn-----\n";
                }else
                {
                    std::cout<<"\n----Player 1(White)'s turn-----\n";
                }
            }else if (flag==1)//player2's move
            {
                if(firsthand==2){
                    std::cout<<"\n----Player 2(Black)'s turn-----\n";
                }else
                {
                    std::cout<<"\n----Player 2(White)'s turn-----\n";
                }
            }
            
            //if(flag!=0)
            if(mess==Invalid_Input){
                std::cout << "\n ----invalid coordinate!please input again!---"<<'\n';
            }else if (mess==Position_Occupy)
            {
                std::cout << "\n ----Position already have input!please input again!---"<<'\n';
            }else if (mess==Correct_Input)
            {
                std::cout<<"\n";
            }
            
            std::cout << "input coordinate:";

            int row;
            char col;

            cin.clear();
            string tmp;
            getline(cin,tmp);
            stringstream ss(tmp);
            ss>>col;
            ss>>row;
            if(tmp.length()==0) continue;

            //std::cin>>col>>row;
            int x=0,y=0;
            x=N-row;
            y=to_coordinate(col);
            //std::cin >> x >> y;
            if(check(x,y)!=1){
                //system("pause");
                //system("CLS");
                continue;
            }

            if(firststep!=1) Board[x_last][y_last]--;//上一步落子位置数值-1 变为圆形棋子
            x_last=x;
            y_last=y;//维护上一步的落子位置

            int cur=Board[x][y];
            Put(x, y,firsthand);
            if(Judge(x,y,firsthand)==1){ //该步走完，一方获胜
                system("CLS");
                Boardpainter();
                std::cout<<"Player: "<<(flag+1)<<" win!\n";
                score[flag]+=2;
                std::cout<<"Current scores(Player1 Player2): "<<score[0]<<" : "<<score[1]<<'\n';
                std::cout<<"-----Play again? Y or N -----\n";
                char choose;
                std::cin>>choose;
                if(choose=='Y'||choose=='y'){
                    initBoard();
                    //system("CLS");
                    firststep=1;
                    firsthand=(3-firsthand);
                    flag=(firsthand-1);
                    continue;
                }else{
                    break;
                }
            }else if(Judge(x,y,firsthand)==0){ //该步为禁手
                std::cout<<"Black player move is Forbiddened!Would you(white player) like to point out? Y or N\n";
                flag^=1;
                char choose2;
                std::cin>>choose2;
                if(choose2=='Y'||choose2=='y'){//白方申诉
                    std::cout<<"Player: "<<(flag+1)<<" win!\n";
                    score[flag]+=2;
                    std::cout<<"Current scores(Player1 Player2): "<<score[0]<<" : "<<score[1]<<'\n';
                    std::cout<<"-----Play again? Y or N -----\n";
                    char choose3;
                    std::cin>>choose3;
                    if(choose3=='Y'||choose3=='y'){
                        initBoard();
                        continue;
                    }else{
                        break;
                    }
                }else{ //白方不申诉，继续游戏
                    flag^=1;
                    continue;
                }
                // withdraw(x,y,cur); 
                // continue;
            }else if(Judge(x,y,firsthand)==-1){ //没有任何一方胜出
                firststep=0;
                flag^=1;
                continue;
            }else if(Judge(x,y,firsthand)==-2){ //平局
                std::cout<<"No player win! \n";
                score[0]++;score[1]++;
                std::cout<<"Current scores(Player1 Player2): "<<score[0]<<" : "<<score[1]<<'\n';
                std::cout<<"-----Play again? Y or N -----\n";
                char choose4;
                std::cin>>choose4;
                if(choose4=='Y'||choose4=='y'){
                    continue;
                }else{
                    break;
                }
            }
        }
        
        //TODO:
        //该while循环为人机对战模式
        while(1==getModel()){ 
            system("CLS");
            Boardpainter();
            if(flag==0){ //player's move
                if(firsthand==1){
                    std::cout<<"\n----Player (Black)'s turn-----\n";
                }else
                {
                    std::cout<<"\n----Player (White)'s turn-----\n";
                }
            }else if (flag==1)//Computer's move
            {   
                
                if(firsthand==2){
                    std::cout<<"\n----Computer(Black)'s turn-----\n";
                }else
                {
                    std::cout<<"\n----Computer(White)'s turn-----\n";
                }
            }
            
            
            int x=0,y=0;
            
            if(flag==0){//player回合
                int row;
                char col;

                if(mess==Invalid_Input){
                    std::cout << "\n ----invalid coordinate!please input again!---"<<'\n';
                }else if (mess==Position_Occupy)
                {
                    std::cout << "\n ----Position already have input!please input again!---"<<'\n';
                }else if (mess==Correct_Input)
                {
                    std::cout<<"\n";
                }

                std::cout << "input coordinate:";
                string tmp;
                getline(cin,tmp);
                stringstream ss(tmp);
                ss>>col;
                ss>>row;
                if(tmp.length()==0) continue;
                if(col>='a'&&col<='o'){col=toupper(col);}
                x=N-row;
                y=to_coordinate(col);
                //std::cin >> x >> y;
                if(check(x,y)!=1){
                    //system("pause");
                    //system("CLS");
                    continue;
                }
            }else{
                x=x_last;
                y=y_last;
                if(flag2==0) ComputerMove(x,y,firsthand,try_num);//传引用改变x,y
                else {x++;y++;}
                if(firststep==1){x=7;y=7;}
                if(check(x,y)==0){ //理论上此处不需要check合法性了 ai的落子应该一定合法
                    try_num++;
                    if(try_num>15){
                        x=(x_last+1)%15;
                        y=y_last;
                        try_num=0;
                        x_last=x;
                        y_last=y;
                    }else{
                        x=x_last;
                        y=y_last;
                    }
                    flag2=1;
                    continue;
                }else if(check(x,y)==-1){
                    x=x_last=1;
                    y=y_last=1;
                }else if(check(x,y)==1)
                {
                    flag2=0;
                }
                
            }
            
            if(firststep!=1) Board[x_last][y_last]--;//上一步落子位置数值-1 变为圆形棋子
            x_last=x;
            y_last=y;//维护上一步的落子位置

            int cur=Board[x][y];
            Put(x, y,firsthand);
            if(Judge(x,y,firsthand)==1){ //该步走完，一方获胜
                system("CLS");
                Boardpainter();
                if(flag==0){
                    std::cout<<"Player  "<<" win!\n";
                }else if(flag==1)
                {
                    std::cout<<"Computer "<<" win!\n";
                }
                score[flag]+=2;
                std::cout<<"Current scores(Player Computer): "<<score[0]<<" : "<<score[1]<<'\n';
                std::cout<<"-----Play again? Y or N -----\n";
                char choose;
                std::cin>>choose;
                
                if(choose=='Y'||choose=='y'){
                    initBoard();
                    //system("CLS");
                    firststep=1;
                    x_last=7;
                    y_last=7;
                    firsthand=(3-firsthand);
                    flag=(firsthand-1);
                    continue;
                }else{
                    break;
                }
            }else if(Judge(x,y,firsthand)==0){ //该步为禁手
                std::cout<<"Black player move is Forbiddened!Would you(white player) like to point out? Y or N\n";
                flag^=1;
                char choose2;
                std::cin>>choose2;
                if(choose2=='Y'||choose2=='y'){//白方申诉
                    if(flag==0){
                        std::cout<<"Player  "<<" win!\n";
                    }else if(flag==1)
                    {
                        std::cout<<"Computer "<<" win!\n";
                    }
                    score[flag]+=2;
                    std::cout<<"Current scores(Player Computer): "<<score[0]<<" : "<<score[1]<<'\n';
                    std::cout<<"-----Play again? Y or N -----\n";
                    char choose3;
                    std::cin>>choose3;
                    if(choose3=='Y'||choose3=='y'){
                        initBoard();
                        continue;
                    }else{
                        break;
                    }
                }else{ //白方不申诉，继续游戏
                    flag^=1;
                    continue;
                }
                // withdraw(x,y,cur); 
                // continue;
            }else if(Judge(x,y,firsthand)==-1){ //没有任何一方胜出
                firststep=0;
                flag^=1;
                continue;
            }else if(Judge(x,y,firsthand)==-2){ //平局
                std::cout<<"No player win! \n";
                score[0]++;score[1]++;
                std::cout<<"Current scores(Player Computer): "<<score[0]<<" : "<<score[1]<<'\n';
                std::cout<<"-----Play again? Y or N -----\n";
                char choose4;
                std::cin>>choose4;
                if(choose4=='Y'||choose4=='y'){
                    continue;
                }else{
                    break;
                }
            }
        }

    }else if(command=='Q'){
        exit(0);
    }else if(command=='M'){
        system("CLS");
        std::cout<< "chose play with Human or Computer... H or C" << '\n';
        while(cin>>Model){
            if (Model=='H') {setModel(0);}
            else if(Model=='C') {setModel(1);}
            else {std::cout<<"Invalid input!\n";continue;}
            std::cout<< "Now game model is: " ;
            if(getModel()==0){
                std::cout<<"Human vs Human \n";break;
            }else
            {
                std::cout<<"Human vs Computer \n";break;
            }
        }
    }else{
        // system("CLS");
        // cin.clear();
    }
}


//检查输入坐标合法性 返回-1超限 0已占 1合法
int Chessboard::check(int x, int y)
{   
    
    if (x >= N  || y >= N || x < 0 || y < 0)
    {   
        //std::cout << "\n ----invalid coordinate!please input again!---"<<'\n';
        mess=Invalid_Input;
        return -1;
    }
    if (Board[x][y]==11||Board[x][y]==12||Board[x][y]==13||Board[x][y]==10)
    {   
        //std::cout << "\n ----Position already input,dont input again!---" << '\n';
        mess=Position_Occupy;
        std::cout<<endl;
        return 0;
    }
    mess=Correct_Input;
    return 1;
}

void Chessboard::Put(int x,int y,int firsthand){
    if(flag==0){ //player1 落子x y
        if(firsthand==1){
            Board[x][y]=13;
        }else{
            Board[x][y]=11;
        }
    }else if(flag==1){//player2 落子x y
        if(firsthand==2){
            Board[x][y]=13;
        }else{
            Board[x][y]=11;
        }
    }
}



// 最关键的计算评分函数
void Chessboard::updatescore(int firsthand)
{   
    int playercode=0;
    int botcode=0;
    if(firsthand==1){
        playercode=12;
        botcode=10;
    }else if (firsthand==2)
    {
        playercode=10;
        botcode=12;
    }
    
    // 统计玩家或者电脑连成的子
    int personNum = 0; // 玩家连成子的个数
    int botNum = 0; // AI连成子的个数
    int emptyNum = 0; // 各方向空白位的个数
 
    // 置零 二维评分数组
    memset(scoreBoard,0,sizeof(scoreBoard));
 
    // 计分（此处是完全遍历，其实可以用bfs或者dfs加减枝降低复杂度，通过调整权重值，调整AI智能程度以及攻守风格）
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
        {   
            // 空白点就算
            if (row > 0 && col > 0 &&
                Board[row][col] == 0)
            {
                // 遍历周围八个方向
                for (int y = -1; y <= 1; y++)
                    for (int x = -1; x <= 1; x++)
                    {
                        // 重置
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;
 
                        // 原坐标不算
                        if (!(y == 0 && x == 0))
                        {
                            // 每个方向延伸4个子
 
                            // 对玩家白子评分（正反两个方向）
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y > 0 && row + i * y < N &&
                                    col + i * x > 0 && col + i * x < N &&
                                    Board[row + i * y][col + i * x] == playercode) // 玩家的子
                                {
                                    personNum++;
                                }
                                else if (row + i * y > 0 && row + i * y < N &&
                                         col + i * x > 0 && col + i * x < N &&
                                         Board[row + i * y][col + i * x] == 0) // 空白位
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
                                    Board[row - i * y][col - i * x] == playercode) // 玩家的子
                                {
                                    personNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < N &&
                                         col - i * x > 0 && col - i * x < N &&
                                         Board[row - i * y][col - i * x] == 0) // 空白位
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // 出边界
                                    break;
                            }
 
                            if (personNum == 1)                      // 杀二
                                scoreBoard[row][col] += 10;
                            else if (personNum == 2)                 // 杀三
                            {
                                if (emptyNum == 1)
                                    scoreBoard[row][col] += 30;
                                else if (emptyNum == 2)
                                    scoreBoard[row][col] += 40;
                            }
                            else if (personNum == 3)                 // 杀四
                            {
                                // 量变空位不一样，优先级不一样
                                if (emptyNum == 1)
                                    scoreBoard[row][col] += 60;
                                else if (emptyNum == 2)
                                    scoreBoard[row][col] += 110;
                            }
                            else if (personNum == 4)                 // 杀五
                                scoreBoard[row][col] += 10100;
 
                            // 进行一次清空
                            emptyNum = 0;
 
                            // 对AI黑子评分
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y > 0 && row + i * y < N &&
                                    col + i * x > 0 && col + i * x < N &&
                                    Board[row + i * y][col + i * x] == 1) // 玩家的子
                                {
                                    botNum++;
                                }
                                else if (row + i * y > 0 && row + i * y < N &&
                                         col + i * x > 0 && col + i * x < N &&
                                         Board[row +i * y][col + i * x] == 0) // 空白位
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
                                    Board[row - i * y][col - i * x] == botcode) // AI的子
                                {
                                    botNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < N &&
                                         col - i * x > 0 && col - i * x < N &&
                                         Board[row - i * y][col - i * x] == 0) // 空白位
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
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            if(Board[row][col]==(playercode+1)||Board[row][col]==playercode){
                if((row-1)>=0&&(row+1)<N-1){
                    scoreBoard[row-1][col]+=100;
                    scoreBoard[row+1][col]+=100;
                }
                if((col-1)>=0&&(col+1)<N-1){
                    scoreBoard[row][col-1]+=100;
                    scoreBoard[row][col+1]+=100;
                }
                scoreBoard[row][col]=0;
            }
        }
    }
}

    


//x,y此时为上一步对方所走
void Chessboard::ComputerMove(int &x,int &y,int firsthand,int try_num){
    updatescore(firsthand);

    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         std::cout<<scoreBoard[i][j];
    //     }
    //     std::cout<<'\n';
    // }
    int max_val=0,x_max,y_max;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
           if(scoreBoard[i][j]>max_val){
               max_val=scoreBoard[i][j];
               x_max=i;
               y_max=j;
           }
        }
    }
    x=x_max;
    y=y_max;
    if(try_num<=5){
        std::cout<<"##########\n";
    }else{
        std::cout<<"----------\n";
        //x=(x+1)%15;
        y=(y+1)%15;
    }
    // do{
    //     srand(time(NULL));
    //     x_tmp= x+rand()%5;
    //     y_tmp= y+rand()%5;
    // }while(Board[x1][y1]!=0);
    // for(int i = 0; i < 15; i ++){
    //     for(int j = 0; j < 15; j ++){
    //         if(Board[i][j] != 0){
    //             continue;
    //         }
    //     }
    // }
    
}


//检查当前所下黑棋是否为禁手 是禁手则返回true 
bool Chessboard::checkForbidden(int x,int y){
    if(Board[x-1][y-1]==12&&Board[x-1][y+1]==12&&Board[x+1][y-1]==12&&Board[x+1][y+1]==12){
        return true;
    }
    if(Board[x][y-1]==12&&Board[x][y-2]==12&&Board[x+2][y]==12&&Board[x+3][y]==12){
        return true;
    }
    return false;
}

//落子后运行 判断当前是否有人获胜 返回 1一方获胜 0该步禁手 -1无人获胜 -2平局
int Chessboard::Judge(int x,int y,int firsthand){
    if(firsthand==(flag+1)){ //检查黑棋是否禁手 仅做了两个三三禁手
        if(checkForbidden(x,y)){
            return 0;
        }
    }
    //return win_or_not(x,y,flag,firsthand);
    return win_or_not2(x,y,flag,firsthand);

}


//判断获胜和平局 1获胜 -1无人获胜 -2平局
int Chessboard::win_or_not2(int x,int y,int flag,int firsthand){
    int win=-1;
    int max=0;
    int tempXIndex = x;
    int tempYIndex = y;
    Board[x][y]--;
    int dir[4][2][2]={
        // dir[0][0][0] {-1,0} 代表 x-1 y不变 即当前落子点向上的方向搜索从上往下落子检查
        { { -1, 0 }, { 1, 0 } },
                // 竖着
        { { 0, -1 }, { 0, 1 } },
                // 左斜
        { { -1, -1 }, { 1, 1 } },
                // 右斜
        { { 1, -1 }, { -1, 1 } }
    };
    for (int i = 0; i < 4; i++) {
        int count = 1;
        //j为0,1分别为棋子的两边方向，比如对于横向的时候，j=0,表示下棋位子的左边，j=1的时候表示右边
        for (int j = 0; j < 2; j++) {
            bool result = true;
            /**
             while语句中为一直向某一个方向遍历
                有相同颜色的棋子的时候，Count++
                否则置result为false，结束该该方向的遍历
                **/
            while (result) {
                tempXIndex = tempXIndex + dir[i][j][0];
                tempYIndex = tempYIndex + dir[i][j][1];

                //这里加上棋盘大小的判断
                if (tempXIndex >= 0 && tempXIndex <= 14 && tempYIndex >= 0 && tempYIndex <= 14) {
                    if ((Board[tempXIndex][tempYIndex] == Board[x][y])) {
                        count++;
                    }else{
                        result = false;
                    }
                }else{
                    result = false;
                }
                
            }
            tempXIndex = x;
            tempYIndex = y;
        }

        if (count >= 5) {
            //max = 1;
            win=1;
            break;
        } // else
            //max = 0;
    }

    bool full=true;//判断棋盘下满
    for (int l = 0; l < N; l++) 
    {
        for (int c = 0; c < N; c++)
        {
            if (Board[l][c] ==0||Board[l][c] ==1||Board[l][c] ==2||Board[l][c] ==3||Board[l][c] ==4||Board[l][c] ==5||Board[l][c] ==6||Board[l][c] ==7||Board[l][c] ==8)
            {   
                full=false; //说明棋盘中还有空格
            }
        }
    }
    if(!full){ //棋盘不满 返回win==1or-1 获胜或游戏继续
        Board[x][y]++;
        return win;
    }else{ //棋盘满
        if(win==1){ //若最后一步恰好获胜，返回win==1 获胜
            Board[x][y]++;
            return win;
        }else{  //若最后一步也无人获胜，返回win==-2 平局
            win=-2;
            return win;
        }
    }
}


//判断获胜和平局 1获胜 -1无人获胜 -2平局
int Chessboard::win_or_not(int i,int j,int flag,int firsthand){
    if (flag==0){ //player1 落子
        if(firsthand==1){ //player1执黑先走
            flag=12;
        }else{
            flag=10;
        }
    }else if (flag==1) //player2落子
    {
        if(firsthand==2){ //player2执黑先走
            flag=12;
        }else{
            flag=10;
        }
    }
    Board[i][j]--;
    int x = i, y = j;
    int begin = 0;
    int end = 0;

    int begin1 = 0;
    int end1 = 0;

    //判断列是否满足条件
    (i - 4) > 0 ? begin = i - 4 : begin = 0; //已经将列减4 或者从边界算
    (i + 4) < N ? end = N-1 : end = (i + 4);
    for (j, i = begin; i + 4 <= end; i++)
    {
        if (Board[i][j] == flag&&Board[i + 1][j] == flag&&Board[i + 2][j] == flag&&Board[i + 3][j] == flag&&Board[i + 4][j] == flag)
        {   
            Board[i][j]++;
            return 1;
        }
    }

    //判断行是否满足条件
    i = x, j = y;
    (j - 4) > 0 ? begin = j - 4 : begin = 0; //已经将横坐标减4
    (j + 4) < N ? end = N-1 : end = (j + 4); //如果末尾大于N则，从N算最后一个
    for (i, j = begin; j + 4 <= end; j++)
    {
        if (Board[i][j] == flag&&Board[i][j + 1] == flag&&Board[i][j + 2] == flag&&Board[i][j + 3] == flag&&Board[i][j + 4] == flag)
        {   
            Board[i][j]++;
            return 1;
        }
    }

    //判断正对角线是否满足
    int len = 0;
    i = x, j = y;
    i >j ? len = j - 1 : len = i - 1; //判断i>j的作用，按照离边距小的坐标减做初始值
    if (len > 4)    len = 4;
    begin = i - len; //横坐标的起始位置
    begin1 = j - len; //纵坐标，因为是正斜边所以两边要减相同数

    i > j ? len = (N - i) : len = (N - j); //结束坐标也要按照距离边界近的点去减
    if (len>4)  len = 4;
    end= i + len; //横坐标的结束位置
    end1 = j + len;  //纵坐标的结束位置

    for (int i = begin, j = begin1; (i + 4 < end) && (j + 4 < end1); i++, j++)
    {
        if (Board[i][j] == flag&&Board[i + 1][j + 1] == flag&&Board[i + 2][j + 2] == flag&&Board[i + 3][j + 3] == flag&&Board[i + 4][j + 4] == flag)
        {   
            Board[i][j]++;
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
        if (Board[i][j] == flag&&Board[i + 1][j - 1] == flag&&Board[i + 2][j - 2] == flag&&Board[i + 3][j - 3] == flag&&Board[i + 4][j - 4] == flag)
        {   
            Board[i][j]++;
            return 1;
        }
    }

    //判断棋盘是否下满 遍历Board[][]
    for (int l = 0; l < N; l++) //棋盘有没有下满
    {
        for (int c = 0; c < N; c++)
        {
            if (Board[l][c] ==0||Board[l][c] ==1||Board[l][c] ==2||Board[l][c] ==3||Board[l][c] ==4||Board[l][c] ==5||Board[l][c] ==6||Board[l][c] ==7||Board[l][c] ==8)
            {   
                Board[i][j]++;
                return -1; //说明棋盘中还有空格
            }
        }
    }

    Board[i][j]++;
    return -2;
}


void Chessboard::withdraw(int x,int y,int cur){
    Board[x][y]=cur;
}

int Chessboard::to_coordinate(char row){
    if(row<='O'&&row>='A') return mp[row];
    else return -1;
}

void Chessboard::painter(int sign){
    switch (sign)
    {   // ┿ ╂ ╋ 
        case 0: std::cout<<" ┼ ";break;
        case 1: std::cout<<" ┌ ";break;
        case 2: std::cout<<" ┐ ";break;
        case 3: std::cout<<" └ ";break;
        case 4: std::cout<<" ┘ ";break;
        case 5: std::cout<<" ┬ ";break;
        case 6: std::cout<<" ├ ";break;
        case 7: std::cout<<" ┴ ";break;
        case 8: std::cout<<" ┤ ";break;
        case 9: std::cout<<" ";break;
        // case 10: std::cout<<"a";break;
        // case 11: std::cout<<"A";break;
        // case 12: std::cout<<"b";break;
        // case 13: std::cout<<"B";break;
        case 10: std::cout<<" ●";break;
        case 11: std::cout<<" ▲";break;
        case 12: std::cout<<" ○";break;
        case 13: std::cout<<" △";break;
    }

}

void Chessboard::initBoard(){ //初始化棋盘 并显示
    Board[0][0]=1;
    Board[0][N-1]=2;
    Board[N-1][0]=3;
    Board[N-1][N-1]=4;
    for (int i = 1; i < N-1; i++)
    {
        Board[0][i]=5;
        Board[N-1][i]=7;
        Board[i][0]=6;
        Board[i][N-1]=8;
    }
    for (int i = 1; i < N-1; i++)
    {
        for (int j = 1; j < N-1; j++)
        {
            Board[i][j]=0;
        }
    }
}

//按照当前Board数组绘制棋盘
void Chessboard::Boardpainter(){
    for (int i = 0; i < N; i++)
    {   
        std::cout<<std::right<<setw(3)<<N-i;
        for (int j = 0; j < N; j++)
        {   
            painter(Board[i][j]);
        }
        std::cout<<'\n';
    }
    std::cout<<"    A  B  C  D  E  F  G  H  I  J  K  L  M  N  O"<<'\n';
}