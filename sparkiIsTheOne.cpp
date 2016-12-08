/*******************************************
 Sparki Line-following example
 
 Threshold is the value that helps you 
 determine what's black and white. Sparki's 
 infrared reflectance sensors indicate white 
 as close to 900, and black as around 200.
 This example uses a threshold of 500 for 
 the example, but if you have a narrow line, 
 or perhaps a lighter black, you may need to 
 adjust.
********************************************/

/* Remote Codes */
// /------^-----
// |            |
// | 69  70  71 |
// | 68  64  67 |
// |  7  21   9 |
// | 22  25  13 |
// | 12  24  94 |
// |  8  28  90 |
// | 66  82  74 |
// ____________/

#include <Sparki.h> // include the sparki library

/* state sparki is in */
int STATE = 0;

/* 2D array representing the tic-tac-toe board
   0 is empty, 1 is user, 2 is sparki */
int board[3][3];
int rows = {0,0,0,1,1,1,2,2,2};
int cols = {0,1,2,0,1,2,0,1,2};

void setup() 
{
    // fill board with zeros
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            board[i][j] = 0;
        }
    }
}

void loop () {
    sparki.clearLCD(); // clear LCD in case we print to it

    /* starts by sparki getting a piece (described below)
      user goes first
      wait for user to say where they have gone
      fill that spot in the array
      generate random number 1-9
        check if that space in the array is filled
        if it is, go around array until find an empty one
        or generate another random number?
      go to the selected space
      drop piece
      follow line back to beginning marker
      continue past marker to get another piece
      close arms around piece
      turn around
      follow line to beginning marker
      stop and wait for user input
    */

    switch(STATE) {
        int userMove;
        int sparkiMove;
        /* at beginning marker, already has piece
           get user input, choose sparki's next move */
        case 0:
            int remoteInput = readIR();
            if(remoteInput == -1){
                break;
            }
            switch(remoteInput) {
                case 12:
                    userMove = 1;
                    break;
                case 24:
                    userMove = 2;
                    break;
                case 94:
                    userMove = 3;
                    break;
                case 8:
                    userMove = 4;
                    break;
                case 28:
                    userMove = 5;
                    break;
                case 90:
                    userMove = 6;
                    break;
                case 66:
                    userMove = 7;
                    break;
                case 82:
                    userMove = 8;
                    break;
                case 74:
                    userMove = 9;
                    break;
            }
            board[rows[userMove-1]][cols[userMove-1]] = 1; // update the board

            // get sparki's next move
            if(userMove < 5){
                for(int i = 0; i < 9; i++){
                    if(i != 5 && board[rows[i]][cols[j]]){
                        sparkiMove = i + 1;
                    }
                }
            }else{
                for(int i = 8; i >= 0; i--){
                    if(i != 5 && board[rows[i]][cols[j]]){
                        sparkiMove = i + 1;
                    }
                }
            }
            STATE = 1; // go to next state
            break;
        case 1:
            break;
    }
}

/* line follow code adapted from Arduino line-following tutorial */
void line_following() {
  int threshold = 500;
  
  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor

  if ( lineLeft < threshold ) // if line is below left line sensor
  {  
    sparki.moveLeft(); // turn left
  }

  if ( lineRight < threshold ) // if line is below right line sensor
  {  
    sparki.moveRight(); // turn right
  }

  // if the center line sensor is the only one reading a line
  if ( (lineCenter < threshold) && (lineLeft > threshold) && (lineRight > threshold) )
  {
    sparki.moveForward(); // move forward
  }

  // if all three line sensors read a line
  if ( (lineCenter < threshold) && (lineLeft < threshold) && (lineRight < threshold)) {
    // FOUND A MARKER - need a way to keep track of which one
    // depends on which state sparki is in
    delay(100); // filler
  }

  sparki.clearLCD(); // wipe the screen
  
  sparki.print("Line Left: "); // show left line sensor on screen
  sparki.println(lineLeft);
  
  sparki.print("Line Center: "); // show center line sensor on screen
  sparki.println(lineCenter);
  
  sparki.print("Line Right: "); // show right line sensor on screen
  sparki.println(lineRight);
  
  sparki.updateLCD(); // display all of the information written to the screen

  delay(100); // wait 0.1 seconds
}