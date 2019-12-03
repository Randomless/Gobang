#include"chess.h"
using namespace std;

//const int N = 15;//NΪ���̳���;  
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
        int firsthand=0;//���� 1Ϊplayer1ִ�� 2Ϊplayer2ִ��
        std::cin>>firsthand;
        flag=firsthand-1;
        initBoard();
        int firststep=1;//�Ǹþֵ�һ��
        int x_last=5,y_last=5;//ά����һ��������λ��
        mess=Correct_Input;
        int try_num =0;//���Գ���computermove����
        int flag2=0;

        //��whileѭ��Ϊ˫�˶�սģʽ
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

            if(firststep!=1) Board[x_last][y_last]--;//��һ������λ����ֵ-1 ��ΪԲ������
            x_last=x;
            y_last=y;//ά����һ��������λ��

            int cur=Board[x][y];
            Put(x, y,firsthand);
            if(Judge(x,y,firsthand)==1){ //�ò����꣬һ����ʤ
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
            }else if(Judge(x,y,firsthand)==0){ //�ò�Ϊ����
                std::cout<<"Black player move is Forbiddened!Would you(white player) like to point out? Y or N\n";
                flag^=1;
                char choose2;
                std::cin>>choose2;
                if(choose2=='Y'||choose2=='y'){//�׷�����
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
                }else{ //�׷������ߣ�������Ϸ
                    flag^=1;
                    continue;
                }
                // withdraw(x,y,cur); 
                // continue;
            }else if(Judge(x,y,firsthand)==-1){ //û���κ�һ��ʤ��
                firststep=0;
                flag^=1;
                continue;
            }else if(Judge(x,y,firsthand)==-2){ //ƽ��
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
        //��whileѭ��Ϊ�˻���սģʽ
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
            
            if(flag==0){//player�غ�
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
                if(flag2==0) ComputerMove(x,y,firsthand,try_num);//�����øı�x,y
                else {x++;y++;}
                if(firststep==1){x=7;y=7;}
                if(check(x,y)==0){ //�����ϴ˴�����Ҫcheck�Ϸ����� ai������Ӧ��һ���Ϸ�
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
            
            if(firststep!=1) Board[x_last][y_last]--;//��һ������λ����ֵ-1 ��ΪԲ������
            x_last=x;
            y_last=y;//ά����һ��������λ��

            int cur=Board[x][y];
            Put(x, y,firsthand);
            if(Judge(x,y,firsthand)==1){ //�ò����꣬һ����ʤ
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
            }else if(Judge(x,y,firsthand)==0){ //�ò�Ϊ����
                std::cout<<"Black player move is Forbiddened!Would you(white player) like to point out? Y or N\n";
                flag^=1;
                char choose2;
                std::cin>>choose2;
                if(choose2=='Y'||choose2=='y'){//�׷�����
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
                }else{ //�׷������ߣ�������Ϸ
                    flag^=1;
                    continue;
                }
                // withdraw(x,y,cur); 
                // continue;
            }else if(Judge(x,y,firsthand)==-1){ //û���κ�һ��ʤ��
                firststep=0;
                flag^=1;
                continue;
            }else if(Judge(x,y,firsthand)==-2){ //ƽ��
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


//�����������Ϸ��� ����-1���� 0��ռ 1�Ϸ�
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
    if(flag==0){ //player1 ����x y
        if(firsthand==1){
            Board[x][y]=13;
        }else{
            Board[x][y]=11;
        }
    }else if(flag==1){//player2 ����x y
        if(firsthand==2){
            Board[x][y]=13;
        }else{
            Board[x][y]=11;
        }
    }
}



// ��ؼ��ļ������ֺ���
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
    
    // ͳ����һ��ߵ������ɵ���
    int personNum = 0; // ��������ӵĸ���
    int botNum = 0; // AI�����ӵĸ���
    int emptyNum = 0; // ������հ�λ�ĸ���
 
    // ���� ��ά��������
    memset(scoreBoard,0,sizeof(scoreBoard));
 
    // �Ʒ֣��˴�����ȫ��������ʵ������bfs����dfs�Ӽ�֦���͸��Ӷȣ�ͨ������Ȩ��ֵ������AI���̶ܳ��Լ����ط��
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
        {   
            // �հ׵����
            if (row > 0 && col > 0 &&
                Board[row][col] == 0)
            {
                // ������Χ�˸�����
                for (int y = -1; y <= 1; y++)
                    for (int x = -1; x <= 1; x++)
                    {
                        // ����
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;
 
                        // ԭ���겻��
                        if (!(y == 0 && x == 0))
                        {
                            // ÿ����������4����
 
                            // ����Ұ������֣�������������
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y > 0 && row + i * y < N &&
                                    col + i * x > 0 && col + i * x < N &&
                                    Board[row + i * y][col + i * x] == playercode) // ��ҵ���
                                {
                                    personNum++;
                                }
                                else if (row + i * y > 0 && row + i * y < N &&
                                         col + i * x > 0 && col + i * x < N &&
                                         Board[row + i * y][col + i * x] == 0) // �հ�λ
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // ���߽�
                                    break;
                            }
 
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row - i * y > 0 && row - i * y < N &&
                                    col - i * x > 0 && col - i * x < N &&
                                    Board[row - i * y][col - i * x] == playercode) // ��ҵ���
                                {
                                    personNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < N &&
                                         col - i * x > 0 && col - i * x < N &&
                                         Board[row - i * y][col - i * x] == 0) // �հ�λ
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // ���߽�
                                    break;
                            }
 
                            if (personNum == 1)                      // ɱ��
                                scoreBoard[row][col] += 10;
                            else if (personNum == 2)                 // ɱ��
                            {
                                if (emptyNum == 1)
                                    scoreBoard[row][col] += 30;
                                else if (emptyNum == 2)
                                    scoreBoard[row][col] += 40;
                            }
                            else if (personNum == 3)                 // ɱ��
                            {
                                // �����λ��һ�������ȼ���һ��
                                if (emptyNum == 1)
                                    scoreBoard[row][col] += 60;
                                else if (emptyNum == 2)
                                    scoreBoard[row][col] += 110;
                            }
                            else if (personNum == 4)                 // ɱ��
                                scoreBoard[row][col] += 10100;
 
                            // ����һ�����
                            emptyNum = 0;
 
                            // ��AI��������
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row + i * y > 0 && row + i * y < N &&
                                    col + i * x > 0 && col + i * x < N &&
                                    Board[row + i * y][col + i * x] == 1) // ��ҵ���
                                {
                                    botNum++;
                                }
                                else if (row + i * y > 0 && row + i * y < N &&
                                         col + i * x > 0 && col + i * x < N &&
                                         Board[row +i * y][col + i * x] == 0) // �հ�λ
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // ���߽�
                                    break;
                            }
 
                            for (int i = 1; i <= 4; i++)
                            {
                                if (row - i * y > 0 && row - i * y < N &&
                                    col - i * x > 0 && col - i * x < N &&
                                    Board[row - i * y][col - i * x] == botcode) // AI����
                                {
                                    botNum++;
                                }
                                else if (row - i * y > 0 && row - i * y < N &&
                                         col - i * x > 0 && col - i * x < N &&
                                         Board[row - i * y][col - i * x] == 0) // �հ�λ
                                {
                                    emptyNum++;
                                    break;
                                }
                                else            // ���߽�
                                    break;
                            }
 
                            if (botNum == 0)                      // ��ͨ����
                                scoreBoard[row][col] += 5;
                            else if (botNum == 1)                 // ���
                                scoreBoard[row][col] += 10;
                            else if (botNum == 2)
                            {
                                if (emptyNum == 1)                // ����
                                    scoreBoard[row][col] += 25;
                                else if (emptyNum == 2)
                                    scoreBoard[row][col] += 50;  // ����
                            }
                            else if (botNum == 3)
                            {
                                if (emptyNum == 1)                // ����
                                    scoreBoard[row][col] += 55;
                                else if (emptyNum == 2)
                                    scoreBoard[row][col] += 100; // ����
                            }
                            else if (botNum >= 4)
                                scoreBoard[row][col] += 10000;   // ����
 
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

    


//x,y��ʱΪ��һ���Է�����
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


//��鵱ǰ���º����Ƿ�Ϊ���� �ǽ����򷵻�true 
bool Chessboard::checkForbidden(int x,int y){
    if(Board[x-1][y-1]==12&&Board[x-1][y+1]==12&&Board[x+1][y-1]==12&&Board[x+1][y+1]==12){
        return true;
    }
    if(Board[x][y-1]==12&&Board[x][y-2]==12&&Board[x+2][y]==12&&Board[x+3][y]==12){
        return true;
    }
    return false;
}

//���Ӻ����� �жϵ�ǰ�Ƿ����˻�ʤ ���� 1һ����ʤ 0�ò����� -1���˻�ʤ -2ƽ��
int Chessboard::Judge(int x,int y,int firsthand){
    if(firsthand==(flag+1)){ //�������Ƿ���� ������������������
        if(checkForbidden(x,y)){
            return 0;
        }
    }
    //return win_or_not(x,y,flag,firsthand);
    return win_or_not2(x,y,flag,firsthand);

}


//�жϻ�ʤ��ƽ�� 1��ʤ -1���˻�ʤ -2ƽ��
int Chessboard::win_or_not2(int x,int y,int flag,int firsthand){
    int win=-1;
    int max=0;
    int tempXIndex = x;
    int tempYIndex = y;
    Board[x][y]--;
    int dir[4][2][2]={
        // dir[0][0][0] {-1,0} ���� x-1 y���� ����ǰ���ӵ����ϵķ������������������Ӽ��
        { { -1, 0 }, { 1, 0 } },
                // ����
        { { 0, -1 }, { 0, 1 } },
                // ��б
        { { -1, -1 }, { 1, 1 } },
                // ��б
        { { 1, -1 }, { -1, 1 } }
    };
    for (int i = 0; i < 4; i++) {
        int count = 1;
        //jΪ0,1�ֱ�Ϊ���ӵ����߷��򣬱�����ں����ʱ��j=0,��ʾ����λ�ӵ���ߣ�j=1��ʱ���ʾ�ұ�
        for (int j = 0; j < 2; j++) {
            bool result = true;
            /**
             while�����Ϊһֱ��ĳһ���������
                ����ͬ��ɫ�����ӵ�ʱ��Count++
                ������resultΪfalse�������ø÷���ı���
                **/
            while (result) {
                tempXIndex = tempXIndex + dir[i][j][0];
                tempYIndex = tempYIndex + dir[i][j][1];

                //����������̴�С���ж�
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

    bool full=true;//�ж���������
    for (int l = 0; l < N; l++) 
    {
        for (int c = 0; c < N; c++)
        {
            if (Board[l][c] ==0||Board[l][c] ==1||Board[l][c] ==2||Board[l][c] ==3||Board[l][c] ==4||Board[l][c] ==5||Board[l][c] ==6||Board[l][c] ==7||Board[l][c] ==8)
            {   
                full=false; //˵�������л��пո�
            }
        }
    }
    if(!full){ //���̲��� ����win==1or-1 ��ʤ����Ϸ����
        Board[x][y]++;
        return win;
    }else{ //������
        if(win==1){ //�����һ��ǡ�û�ʤ������win==1 ��ʤ
            Board[x][y]++;
            return win;
        }else{  //�����һ��Ҳ���˻�ʤ������win==-2 ƽ��
            win=-2;
            return win;
        }
    }
}


//�жϻ�ʤ��ƽ�� 1��ʤ -1���˻�ʤ -2ƽ��
int Chessboard::win_or_not(int i,int j,int flag,int firsthand){
    if (flag==0){ //player1 ����
        if(firsthand==1){ //player1ִ������
            flag=12;
        }else{
            flag=10;
        }
    }else if (flag==1) //player2����
    {
        if(firsthand==2){ //player2ִ������
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

    //�ж����Ƿ���������
    (i - 4) > 0 ? begin = i - 4 : begin = 0; //�Ѿ����м�4 ���ߴӱ߽���
    (i + 4) < N ? end = N-1 : end = (i + 4);
    for (j, i = begin; i + 4 <= end; i++)
    {
        if (Board[i][j] == flag&&Board[i + 1][j] == flag&&Board[i + 2][j] == flag&&Board[i + 3][j] == flag&&Board[i + 4][j] == flag)
        {   
            Board[i][j]++;
            return 1;
        }
    }

    //�ж����Ƿ���������
    i = x, j = y;
    (j - 4) > 0 ? begin = j - 4 : begin = 0; //�Ѿ����������4
    (j + 4) < N ? end = N-1 : end = (j + 4); //���ĩβ����N�򣬴�N�����һ��
    for (i, j = begin; j + 4 <= end; j++)
    {
        if (Board[i][j] == flag&&Board[i][j + 1] == flag&&Board[i][j + 2] == flag&&Board[i][j + 3] == flag&&Board[i][j + 4] == flag)
        {   
            Board[i][j]++;
            return 1;
        }
    }

    //�ж����Խ����Ƿ�����
    int len = 0;
    i = x, j = y;
    i >j ? len = j - 1 : len = i - 1; //�ж�i>j�����ã�������߾�С�����������ʼֵ
    if (len > 4)    len = 4;
    begin = i - len; //���������ʼλ��
    begin1 = j - len; //�����꣬��Ϊ����б����������Ҫ����ͬ��

    i > j ? len = (N - i) : len = (N - j); //��������ҲҪ���վ���߽���ĵ�ȥ��
    if (len>4)  len = 4;
    end= i + len; //������Ľ���λ��
    end1 = j + len;  //������Ľ���λ��

    for (int i = begin, j = begin1; (i + 4 < end) && (j + 4 < end1); i++, j++)
    {
        if (Board[i][j] == flag&&Board[i + 1][j + 1] == flag&&Board[i + 2][j + 2] == flag&&Board[i + 3][j + 3] == flag&&Board[i + 4][j + 4] == flag)
        {   
            Board[i][j]++;
            return 1;
        }
    }

    //�жϸ��Խ����Ƿ�����
    i = x, j = y;
    (i - 1) >(N - j) ? len = (N - j) : len = i - 1;//�жϸ��Խ��������λ���Ƿ������¼�С�ľ���
    if (len > 4)    len = 4;
    begin = i - len; //���������ʼλ��
    begin1 = j + len; //���������ʼλ��

    (N - i) > (j - 1) ? len = (j - 1) : len = (N - i);
    if (len>4)  len = 4;
    end = i + len; //������Ľ���λ��
    end1 = j - len; //������Ľ���λ��

    for (int i = begin, j = begin1; (i + 4 < end) && (j - 4 > end1); i++, j--)
    {
        if (Board[i][j] == flag&&Board[i + 1][j - 1] == flag&&Board[i + 2][j - 2] == flag&&Board[i + 3][j - 3] == flag&&Board[i + 4][j - 4] == flag)
        {   
            Board[i][j]++;
            return 1;
        }
    }

    //�ж������Ƿ����� ����Board[][]
    for (int l = 0; l < N; l++) //������û������
    {
        for (int c = 0; c < N; c++)
        {
            if (Board[l][c] ==0||Board[l][c] ==1||Board[l][c] ==2||Board[l][c] ==3||Board[l][c] ==4||Board[l][c] ==5||Board[l][c] ==6||Board[l][c] ==7||Board[l][c] ==8)
            {   
                Board[i][j]++;
                return -1; //˵�������л��пո�
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
    {   // �� �� �� 
        case 0: std::cout<<" �� ";break;
        case 1: std::cout<<" �� ";break;
        case 2: std::cout<<" �� ";break;
        case 3: std::cout<<" �� ";break;
        case 4: std::cout<<" �� ";break;
        case 5: std::cout<<" �� ";break;
        case 6: std::cout<<" �� ";break;
        case 7: std::cout<<" �� ";break;
        case 8: std::cout<<" �� ";break;
        case 9: std::cout<<" ";break;
        // case 10: std::cout<<"a";break;
        // case 11: std::cout<<"A";break;
        // case 12: std::cout<<"b";break;
        // case 13: std::cout<<"B";break;
        case 10: std::cout<<" ��";break;
        case 11: std::cout<<" ��";break;
        case 12: std::cout<<" ��";break;
        case 13: std::cout<<" ��";break;
    }

}

void Chessboard::initBoard(){ //��ʼ������ ����ʾ
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

//���յ�ǰBoard�����������
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