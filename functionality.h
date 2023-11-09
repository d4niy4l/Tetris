/*name: daniyal ahmed
roll no: 22i-1032
section: b
PF FINAL PROJECT*/
/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//
void checkAnamoly(int point_1[][2],int point_2[][2]){
    if(!anamoly()){     //checks for anamoly ie crossing the grid, if it does then point 1's cordinates are switched back to point 2 
        for(int i=0;i<4;i++){
            point_1[i][0]=point_2[i][0];
        }
    }    
}
void upcomingPiece(int n,int comingBlock[4][2]);
bool bombAnomoly(int bomb[]);
void fallingPiece(float& timer, float& delay,int &colorNum,int &delta_x,int comingBlock[][2],int &next,int &next2,int comingBlock2[][2],int &color,int &color2){
        //delta_x = 5;
    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;            //How much units downward
        }
        if (!anamoly()){           
            for(int i=0;i<4;i++){
                gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
            }
            color=1+rand()%7;
            color=1+rand()%7;
            int n=rand() % 7;
            int temp,temp2; //initializing temp variables
            //--- Un-Comment this Part When You Make BLOCKS array---/
            temp2=color;
            for (int i=0;i<4;i++){
                delay=0.5;
                comingBlock2[i][0]=BLOCKS[n][i] % 2; //random n in next next block
                comingBlock2[i][1]=BLOCKS[n][i] / 2;
                comingBlock[i][0]=BLOCKS[next2][i] % 2;
                comingBlock[i][1]=BLOCKS[next2][i] / 2;
                point_1[i][0] = BLOCKS[next][i] % 2;
                point_1[i][1] = BLOCKS[next][i] / 2;
            }
            temp2=color2;
            color2=color;
            colorNum=temp2;
            color=rand()%7 + 1;
            temp=next2;             
            next2=n;        //next2 becomes n
            next=temp;      //and next becomes next
            delta_x=5;      //so that next block comes from centre
        }

        delay=0.35;
        timer=0;
    }
}
////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
void fallingPiecev2(float &timer,int Bomb[2],float &delay,int &delta_x,int &colorNum,bool &flag){    
    if(timer>delay){
        Bomb[1]+=1;
        if(!bombAnomoly(Bomb)){
            colorNum=1+rand()%7;   //randomzing color no of bomb
            Bomb[1]=-1;        //incase of anomaly ie hiting block bomb goes back to og position
            Bomb[0]=delta_x;   //random spawn position
            flag=0;            //after anomly the boolean variable responsible for apearance of bomb resets
        }
        delta_x=rand()%10;    //randomizng spawn x coordinate
        timer=0;    //resetting timer of bomb
    }   

}
bool bombAnomoly(int Bomb[]){
    if(Bomb[0]<0 || Bomb[0]>=N || Bomb[1]>=M){  //anamoly function like the point 1 anomoly 
        return 0;                             //for the bomb whgich checks it stays in grid and does not overlap bomb
    }
    else if(gameGrid[Bomb[1]][Bomb[0]]){
        return 0;     //checks if bomb is overlapping a block
    }
    return 1;
}
void bombDestruction(int Bomb[],int &colorNum,int &colorNum2,int &delta_x,bool &flag,bool &flag1){
    if(Bomb[1]!=M-1){
        if(gameGrid[Bomb[1] +1][Bomb[0]]==colorNum2){   //if the color of block under bomb is equal to its color
            for(int i=0;i<M;i++){
                for(int j=0;j<N;j++){
                    gameGrid[i][j]=0;
                }                               //whole grid becomes zero
            }
            Bomb[1]=-1;          //bomb resets
            Bomb[0]=delta_x;
            colorNum2=1 + rand()%7;                        
            delta_x=rand()%10;
            flag=0;
            flag1=1;
            for(int i=0;i<4;i++){
                point_1[i][0]=point_2[i][0];
                point_1[i][1]=point_2[i][1];
            }
        }
        else if(gameGrid[Bomb[1]+1][Bomb[0]]>0 ){  //checks if its any other color other than its color
            for(int i=1;i<=2;i++){
                for(int j=0;j<2;j++){ 
                    gameGrid[Bomb[1]+i][Bomb[0]+j]=0;  //removes block in a square radius
                }
            }
            Bomb[1]=-1;
            Bomb[0]=delta_x;
            colorNum2=1+rand()%7;
            delta_x=rand()%10;    //bomb resets
            flag=0;
            flag1=1;
            for(int i=0;i<4;i++){
                point_1[i][0]=point_2[i][0];
                point_1[i][1]=point_2[i][1];
            }
        }
    }
}

void move(int &delta_x){
    for(int i=0;i<4;i++){       //stores blocks x and y cordinates in point2(will be used in case of anamolies) 
        point_2[i][0]=point_1[i][0];
        point_1[i][0]+=delta_x;         //adds delta x to the x cordinate of block
    }
    delta_x=0;              //resets delta x back so it may be used again(if not it will continously move +1 or -1 units)
    checkAnamoly(point_1,point_2);
}
void regenBomb(int &chance,bool& flag){
    chance=rand()%10000;    //rolls dice for bomb if it is 5 then bomb falls
    if(chance==5){
        flag=1;
    }
}
void endRow(int &score,bool &flag){
    bool flag1=1;           
    int rowCount=0;    //counts no of rows being removed for scoring
    for(int i=0;i<M;i++){
        flag1=1;
        for(int j=0;j<N;j++){
            switch(gameGrid[i][j]){
                case 0:       //if any col in a row is zero then flag becomes one otherwuse it stays zero
                flag1=0;
            }
        }
        if(flag1==1){
            for(int j=0;j<N;j++){
                gameGrid[i][j]=0;   //sets that whole row zerp
                flag=1;  
            }
            rowCount++;  //increases row count everytime a row is set to zero
        }
    }
	switch(rowCount){
        case 1:
        score+=10;       //increases score according to rubrics
        break;
        case 2:
        score+=30;
        break;
        case 3:
        score+=60;
        break;
        case 4:
        score+=100;
        break;
    }
    rowCount=0;   //sets row count back to zero for the next iteration
}
/*Detects if there is any empty row b/w rows and then replaces the empty row with the row above it*/
void rowDown(){
    bool flag=1;
    for(int i=0;i<M;i++){           
        flag=1;
        for(int j=0;j<N;j++){
            switch(gameGrid[i][j]){
            case 1:           //1-7 showcolor blocks and 0 shows empty space in gameGrid
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                flag=0;             //if any block in the row then flag becomes zero
                break;
            }                           
        }
        if (flag){              //if flag ==1 then it means one of the rows is empty
            for(int j=0;j<N;j++){
                gameGrid[i][j]=gameGrid[i-1][j];  //replaces row below with row above
                gameGrid[i-1][j]=0;
            }
        }
    }
}
void rotation(bool &rotate){
    int transX,transY;
    if(rotate){    
        for(int i=0;i<4;i++){   //as origin is trasnlating sp we find coordiantes wrt trasnlated origin
            transX=point_1[i][0]-point_1[1][0]; //X=x-h  X Y is translated coordinates x y is orignal and h k is translated orign coordinates
            transY=point_1[i][1]-point_1[1][1]; //Y=y-k
            point_2[i][0]=point_1[i][0];   //x*=Xcos-Ysin  y*=Ycos+Xsim  put theetha=90
            point_2[i][1]=point_1[i][1];    //x*=-Y       y*=X
            point_1[i][0]=transY+point_1[1][0];  //adding the pivot point as rotation is aroiund that poiunt not the gamegrids origin
            point_1[i][1]=-transX+point_1[1][1];   
        }
    }    
    rotate=false;
    if(!anamoly()){
        for(int i=0;i<4;i++){
            point_1[i][0]=point_2[i][0];  //stores x and y coroinate of point 1 in point 2 for anomoly
            point_1[i][1]=point_2[i][1];
			if(point_1[i][0]==N-1 || point_1[i][0]==N-2){   
                point_1[i][0]-=1;        //wallkicks ie wallpushes against bnlock incase its hampering its rotation
                 rotate=1;
            }
            else if(point_1[i][0] == 0 || point_1[i][0] == 1 ){
                point_1[i][0]+=1;
                    rotate=1;
            }
        }

    }
}
void gameOver(float& delay, int& delta_x, float& timer, bool& f, bool& flag1, float& timer2, bool& flag2, int& delta_X ) {
    bool flag=0;
    for(int i=0;i<N;i++){
        if(gameGrid[0][i]){   //if top row of grid becomes one then game ends 
            delay=100000;
            flag=1;     //all timers are set to zero as no more blocks will fall
            f=1;
            flag1=0;
            timer2=0;
            flag2=1;
            delta_x = 5;
            break;   //loop breaks as no need to check again
        }
    }
    if(flag){
        for(int i=0;i<4;i++){
          point_1[i][1]=0;
          point_1[i][0]=5;   //resertting poiunt 1
        }
        delta_x=5;
    }
}
void pause(bool &flag, float &timer, int &delta_x,bool &rotate,float &temp,float &timer2,float &temp1,float &timer3,float& temp2){
    if(flag){
        timer=temp;
        rotate=false;
        delta_x=0;        //setting all timers to a contasnt equal to the time when the p key is pressed
        timer2=temp1;
        timer3=temp2;
    }
}
void lev(float timer3,float &delay,bool &flag,int &level){
    if(timer3>300){       //if level timer is greater than 300 then speed increases
        flag=true;
        delay=0.25;
        level= 2;
    }
}
void restart(int &score,bool &flag1,int &level,bool &flag2,bool &rotate,int& delta_x,bool &flag3,float &timer3){
    if(flag2){
        delta_x=5;
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                gameGrid[i][j] = 0;  //r key pressed game grid empties
            }
        }
        score=0;
        level=1;      //every menu and animation flag becomes zero                             
        flag2=0;
        flag1=0;
        flag3=0;
        timer3=0;
        int n=rand()%7;
        for(int i=0;i<4;i++){
            point_1[i][0]=BLOCKS[n][i] % 2 + 5;
            point_1[i][1]=BLOCKS[n][i] / 2;   //assigns random value back to point one for next run
        }
        
    }
}
bool check(){
    int i=0;
    while(i<4){
        if (point_1[i][1]>M || gameGrid[point_1[i][1] + 1][point_1[i][0]]){
            return 1;                                //checks if block under point 1
        }
        i++;
    }
    return 0;
}
bool checkDup(int point_3[][2]){
    for(int i=0;i<4;i++){
        if(point_3[i][1]>=M-1 || gameGrid[point_3[i][1] + 1][point_3[i][0]] ){
            return 0;     //checks if theres a block under the shadow sprte
        }
    }
    return 1;
}
void duplicate(int point_3[][2]){
    for(int i=0;i<4;i++){
        point_3[i][0]=point_1[i][0];   //point 3 is for shadows and everychange in point 1 is happeining in shadows
        point_3[i][1]=point_1[i][1];   //duplicates shape of point 1 in point 3
    }
}
void shadows(int point_3[][2]){
    for(;checkDup(point_3);){  //checks if there is a block under the shadow
        int i=0;   //works on the principal of hard drop but instead of the block the shadow falls down
        while(i<4){
            point_3[i][1]+=1;
		    gameGrid[point_3[i][1]][point_3[i][0]];
            i++;
        }
    }
}

void animation(){
    for(int i=0;i<M;i++){
        for(int j=0;j<N;j++){
            gameGrid[i][j]=rand() % 7;
        }             //just a basic function for animation (random block animation)
    }
}   
void animationClear(bool& flag1,bool& flag2){
    if(!(flag1) || !(flag2)){
        for(int i=0;i<M;i++){
            for(int j=0;j<N;j++){
                gameGrid[i][j]=0;          
            }   //clears animation when enter is pressed
        }
    }
}
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
