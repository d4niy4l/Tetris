/*name: daniyal ahmed
roll no: 22i-1032
section: b
PF FINAL PROJECT*/
/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include "utilis.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
using namespace std;
int main(){
    srand(time(0));
    RenderWindow window(VideoMode(360, 560), title);
    Texture obj1, obj2, obj3, obj4, bombimg; 
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    bombimg.loadFromFile("img/bomb.png");
    Font open_sans,tet;
    open_sans.loadFromFile("img/newsans.ttf");
    tet.loadFromFile("img/Tetris.ttf");
    Text score;
    score.setFont(open_sans);
    score.setString("SCORE");
    score.setCharacterSize(40);
    score.setPosition(250,50);
    score.setFillColor(Color::Black);
    Text levels;
    levels.setFont(open_sans);
    levels.setString("LEVEL");
    levels.setCharacterSize(40);
    levels.setPosition(260,370);
    levels.setFillColor(Color::Black);
    Text over;
    over.setFont(open_sans);
    over.setString("GAME OVER");
    over.setPosition(31,150);
    over.setCharacterSize(60);
    over.setFillColor(Color::Black);
    Text pausing;
    pausing.setFont(open_sans);
    pausing.setString("PAUSED");
    pausing.setPosition(80,20);
    pausing.setCharacterSize(50);
    pausing.setFillColor(Color::Black);
    Text tetris;
    tetris.setFont(tet);
    tetris.setString("TETRIS");
    tetris.setPosition(65,20);
    tetris.setCharacterSize(60);
    tetris.setFillColor(Color::Black);
    Text scorewas;
    scorewas.setFont(open_sans);
    scorewas.setString("YOUR SCORE WAS: ");
    scorewas.setPosition(36,250);
    scorewas.setCharacterSize(30);
    scorewas.setFillColor(Color::Black);
    Text back;
    back.setFillColor(Color::Black);
    back.setFont(open_sans);
    back.setPosition(40,400);
    back.setString("PRESS M FOR THE MENU \nPRESS R TO RESTART");
    back.setCharacterSize(30);
    Text Start;
    Start.setFont(open_sans);
    Start.setString("START (S)");
    Start.setPosition(110,100);
    Start.setFillColor(Color::Black);
    Start.setCharacterSize(30);
    Text exit;
    exit.setFont(open_sans);
    exit.setString("EXIT (ESC)");
    exit.setPosition(110,450);
    exit.setFillColor(Color::Black);
    exit.setCharacterSize(30);
    Text Help;
    Help.setFont(open_sans);
    Help.setString("HELP (H)");
    Help.setPosition(110,250);
    Help.setFillColor(Color::Black);
    Help.setCharacterSize(30);
    Text inst;
    inst.setFont(tet);
    inst.setString("CONTROLS");
    inst.setPosition(90,30);
    inst.setFillColor(Color::Black);
    inst.setCharacterSize(30);
    Text cont;
    cont.setFont(open_sans);
    cont.setString("UP KEY - ROTATES THE BLOCK \nDOWN KEY - ACCELERATES BLOCK \nLEFT KEY - LEFT MOVE \nRIGHT KEY - RIGHT MOVE \nSPACEBAR - TELEPORT \nP KEY - PAUSE \n R KEY - RESTART");
    cont.setCharacterSize(25);
    cont.setPosition(30,100);
    cont.setFillColor(Color::Black);
    Text pauseMenu;
    pauseMenu.setFont(open_sans);
    pauseMenu.setPosition(30,150);
    pauseMenu.setCharacterSize(35);
    pauseMenu.setFillColor(Color::Black);
    pauseMenu.setString("PRESS R TO RESTART \nPRESS S TO RESUME \nPRESS M FOR THE MENU");
    Text next;
    next.setFont(open_sans);
    next.setCharacterSize(40);
    next.setFillColor(Color::Black);
    next.setPosition(260,200);
    next.setString("NEXT");
    Music music;
    music.openFromFile("img/music.wav");
    music.setLoop(true);
    music.play();
    Sound effect1,effect2,effect3,effect4,effect5;
    SoundBuffer buffer1,buffer2,buffer3,buffer4,buffer5;
    buffer1.loadFromFile("img/effect1.wav"); //loading music
    buffer2.loadFromFile("img/effect2.wav");
    buffer3.loadFromFile("img/effect3.wav");
    buffer4.loadFromFile("img/effect4.wav");
    buffer5.loadFromFile("img/effect5.wav");
    effect1.setBuffer(buffer1);
    effect2.setBuffer(buffer2);
    effect3.setBuffer(buffer3);
    effect4.setBuffer(buffer4);
    effect5.setBuffer(buffer5);
    effect5.setVolume(100);
    effect1.setVolume(100);
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
    Sprite sprite(obj1), background(obj2), frame(obj3) ,shadow(obj4), block(obj1),bomb(bombimg),block2(obj1);
    int delta_x=5, colorNum=1 + rand()%7, number=0,point_3[4][2],levelNo=1;
    int comingBlock[4][2],Bomb[2]={0},delta2_x=4,comingBlock2[4][2];
    float timer=0, delay=0.35,timer2=0,delay2=0.5,timer3=0,temp,temp1,temp2,timer4=0,temp3;
    bool rotate=0,flag=0,stop=0,l=0,re=0,downwards=0,bombfall=0,menu=1,begin=1,help=0,go=0;
    Clock clock,clock2;
    int colorNum2=rand()%7,chance;
	int next1=rand()%7,next2=rand()%7;
    bool play1=0,play2=0,play3=0,play4=0,play5=0;
    int n=rand()%7,color=1 + rand()%7,color2=1 + rand()%7;
    for(int i=0;i<4;i++){  //initlaizing all the blocks, if not done then the single block will come as it will have no meaningful values
	    point_1[i][0] = BLOCKS[n][i] % 2;
        point_1[i][1] = BLOCKS[n][i] / 2;
    }
	for(int i=0;i<4;i++){
        comingBlock[i][0]= BLOCKS[next1][i] %2;
        comingBlock[i][1]=BLOCKS[next1][i] / 2;
    }
	for(int i=0;i<4;i++){
        comingBlock2[i][0]= BLOCKS[next2][i] %2;
        comingBlock2[i][1]= BLOCKS[next2][i] / 2;
    }
    /*begin--startup menu-menu pop ups  stop - pause menu pops up re=restarts games */
    while (window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        if(!begin && !help && !menu){
            timer3+=time;  //timer for levels
            timer2+=time;  //timer for bomb
            timer+=time;   //timer for block
            go=true;
        }
		if(begin && !help){
			animationClear(menu,begin);
		}
            //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up){            //Check if the other key pressed is UP key
                    rotate = true;
                    play3=1;
                }                         //Rotation gets on
                else if (e.key.code == Keyboard::Left){     //Check if the other key pressed is LEFT key
                    delta_x = -1;
                    play1=1;
                }
                                            //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right){    //Check if the other key pressed is RIGHT key
                    delta_x = 1;
                    std ::cout << "poop";
                    play1=1;                           //Change in X-Axis - Positive
                }
                else if(!begin && !menu){
                    if(e.key.code == Keyboard::Space){
                        while(!check()){
                            for(int i=0;i<4;i++){
                                point_1[i][1] += 1;
                                timer=0;
                            }
                        }
                    }
                }
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
        if(Keyboard::isKeyPressed(Keyboard::P)){
            temp=timer;
            temp1=timer2;
            temp2=timer3;
            stop=1;
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            stop=0;
        }
        if(Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();
        if(play1){
            effect1.play();
            play1=0;
        }
        if(play3){
            effect3.play();
            play3=0;
        }
        if(stop && !menu){
            if(Keyboard::isKeyPressed(Keyboard::R)){
                re=1;
                stop=0;
            }   
        }
        if(stop && !menu){
            if(Keyboard::isKeyPressed(Keyboard::M)){
                menu=1;
                help=0;
                re=1;
                begin=1;
                stop=0;
            }
        }
        if(!menu && !help){
            if(Keyboard::isKeyPressed(Keyboard::Return)){
                begin=0;
            }
        }
        if(menu){
            if(Keyboard::isKeyPressed(Keyboard::H)){
                help=1;
                menu=0;
            }
        }
        if(!menu && help){
            if(Keyboard::isKeyPressed(Keyboard::BackSpace)){
                help=0;
                menu=1;
            }
        }
        if(menu && !help){
            if(Keyboard::isKeyPressed(Keyboard::S))
                menu=0;  
        }
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        if(timer>delay){
            for(int i=0;i<4;i++){
                point_2[i][0]=point_1[i][0];

            }
        }
		if(begin){
            animation();
        }
        
        if(!begin && !stop && go){
            fallingPiece(timer, delay, colorNum, delta_x, comingBlock,next1,next2,comingBlock2,color,color2);
            if(bombfall)
                fallingPiecev2(timer2,Bomb,delay2,delta2_x,colorNum2,bombfall);              //Example: fallingPiece() function is called here
            bombAnomoly(Bomb);
            bombDestruction(Bomb,colorNum,colorNum2,delta2_x,bombfall,play4);
            regenBomb(chance,bombfall);
            move(delta_x);
            rotation(rotate);
            duplicate(point_3);
            shadows(point_3);
            checkDup(point_3);
            pause(stop,timer,delta_x,rotate,temp,timer2,temp1,timer3,temp2);
            endRow(number,play2);
            rowDown();
            lev(timer3,delay,l,levelNo);
            gameOver(delay,delta_x,timer,flag,bombfall,timer2,play5,delta_x);
            restart(number,flag,levelNo,re,rotate,delta_x,bombfall,timer3);
        }
        window.clear(Color::White);
        window.draw(background);
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////
        std::string string_levelsNo=to_string(levelNo);
        Text levelsNo(string_levelsNo,open_sans);
        levelsNo.setCharacterSize(40);
        levelsNo.setFillColor(Color::Black);
        levelsNo.setPosition(290,400);
        std::string string_points=to_string(number);
        Text points(string_points,open_sans);
        points.setCharacterSize(40);
        points.setFillColor(Color::Black); //cahnging score (int) to string
        points.setPosition(284,80);
        Text displaypoint(string_points,open_sans);
        displaypoint.setFillColor(Color::Black);
        displaypoint.setPosition(260,250);
        displaypoint.setCharacterSize(30);
        if(play2){
            effect2.play();
            play2=0;
        }
        if(play4){
            effect4.play();
            play4=0;
        }

		if(help){
            window.draw(inst);
            window.draw(cont);
        }
		if(!menu && stop){
           	window.draw(pausing);
            window.draw(pauseMenu);
        }
        if(!menu && !help && !stop){
            for (int i=0; i<M; i++){
                for (int j=0; j<N; j++){
                    if (gameGrid[i][j]==0)
                        continue;
                    sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                    sprite.setPosition(j*18,i*18);
                    sprite.move(28,31); //offset
                    window.draw(sprite);
                }
            }
            for (int i=0; i<4; i++){
                sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
                sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
                sprite.move(28,31);
                window.draw(sprite);
            }
            for (int i=0; i<4; i++){
                shadow.setTextureRect(IntRect(colorNum*18,0,18,18));
                shadow.setPosition(point_3[i][0]*18,point_3[i][1]*18);
                shadow.move(28,31);
                shadow.setColor(Color(0,0,0,70));  //uisng RGBA values
                window.draw(shadow);
            }
            for(int i=0;i<4;i++){
                block.setTextureRect(IntRect(color2*18,0,18,18));
                block.setPosition(comingBlock[i][0]*18,comingBlock[i][1]*18);
                block.move(260,270);
                window.draw(block);
            }
            if(levelNo==1){
			    for(int i=0;i<4;i++){
                    block2.setTextureRect(IntRect(color*18,0,18,18));
                    block2.setPosition(comingBlock2[i][0]*18,comingBlock2[i][1]*18);
                    block2.move(310,270);
                    window.draw(block2);
                }
            }
        }
        if(!menu && !begin && !help && !stop){
            bomb.setScale(0.09,0.09);
            bomb.setPosition(Bomb[0]*18,Bomb[1]*18);
            bomb.move(28,31);
            switch(colorNum2){
                case 1:
                    bomb.setColor(Color::Red);
                    break;
                case 2:
                    bomb.setColor(Color(0,250,0));
                    break;
                case 3:
                    bomb.setColor(Color(255,20,148));
                    break;
                case 4:
                    bomb.setColor(Color(255,140,0));
                    break;
                case 5:
                    bomb.setColor(Color::Cyan);
                    break;
                case 6:
                    bomb.setColor(Color(0,0,250));
                    break;
                case 7:        //num2 has random values which change and gives the bomb a color
                    bomb.setColor(Color::Yellow);
                    break;
                }
	            
            if(bombfall)
                window.draw(bomb);
        }

            //---The Final on Which Everything is Drawn Over is Loaded---//
            if(flag){
                window.clear(Color::White);
                window.draw(background);
                window.draw(over);
                window.draw(scorewas);
                window.draw(displaypoint);
                window.draw(back);
                if(play5){
                    effect5.play();
                    play5=0;
                }
                if(Keyboard::isKeyPressed(Keyboard::R)){
                    re=1;
                    flag=0;
                }
                if(Keyboard::isKeyPressed(Keyboard::M)){
                    menu=1;
                    re=1;
                    begin=1;
                    flag=0;
                }

            }
			//window.draw(background);  
        if(!menu && !help && !stop){
            if(!flag){
                window.draw(frame);
                window.draw(score);
                window.draw(points);
                window.draw(levelsNo);
                window.draw(levels);
                window.draw(next);
            }
        }
		if(menu){
            window.draw(tetris);
            window.draw(Start);
            window.draw(exit);
            window.draw(Help);
            }
            //---The Window that now Contains the Frame is Displayed---//
            window.display();
        }
        
    return 0;
}
