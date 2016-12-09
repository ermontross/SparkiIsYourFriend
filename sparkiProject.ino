#include <Sparki.h>

#define LOSS -1
#define WIN 99
#define TIE 27
#define PLAYERINPUT 0
#define THINK 1
#define GRABCUP 2
#define GET_TO_LINE 3
#define PLACE_CUP 4
#define THRESHOLD 700



/* Tic Tac Toe
 *
 * Board Spaces:
 *    1  2  3
 *    0  8  4
 *    7  6  5
 *
 * Board Initialization
 *
 *  0  -- Empty
 *  1  -- Sparki (X? Doesn't really matter)
 *  -1 -- Human (Shit, still doesn't matter)
 *
 */

int state;
int board[9];
int counter;
int right;
int myMove;
int numMoves;
int cup = 0;
int code = -1;
int oldcode = -1;

void humanInput()
{
  // | 12  24  94 |
  // |  8  28  90 |
  // | 66  82  74 |
  while(code == oldcode){
    code = sparki.readIR();
  }
  while(code == -1){
    code = sparki.readIR();
    delay(10);
  }
  if(code != -1)
  {
    sparki.print("Received code: ");
    sparki.println(code);
    sparki.updateLCD();
    oldcode = code;
    delay(1000);
  }
  switch(code)
  { 
    // Movement buttons
    case 8:  board[0] = -1; break;
    case 12: board[1] = -1; break;
    case 24: board[2] = -1; break;
    case 94: board[3] = -1; break;
    case 90: board[4] = -1; break;
    case 74: board[5] = -1; break;
    case 82: board[6] = -1; break;
    case 66: board[7] = -1; break;
    case 28: board[8] = -1; break;
    default:
      break;
  }
}
/* Tic Tac Toe
 *
 * Board Spaces:
 *    1  2  3
 *    0  8  4
 *    7  6  5
 *
 * Board Initialization
 *
 *  0  -- Empty
 *  1  -- Sparki (X? Doesn't really matter)
 *  -1 -- Human (Shit, still doesn't matter)
 *
 */
int checkForWin(){
  int win;
  win = board[1] + board[2] + board[3];
  if(win == -3){
    return -1;
  }
  else if (win == 3){
    return 99;
  }
  win = board[0] + board[8] + board[4];
  if(win == -3){
    return -1;
  }
  else if (win == 3){
    return 99;
  }
  win = board[7] + board[6] + board[5];
  if(win == -3){
    return -1;
  }
  else if (win == 3){
    return 99;
  }
  win = board[1] + board[0] + board[7];
  if(win == -3){
    return -1;
  }
  else if (win == 3){
    return 99;
  }
  win = board[2] + board[8] + board[6];
  if(win == -3){
    return -1;
  }
  else if (win == 3){
    return 99;
  }
  win = board[3] + board[4] + board[5];
  if(win == -3){
    return -1;
  }
  else if (win == 3){
    return 99;
  }
  win = board[7] + board[8] + board[3];
  if(win == -3){
    return -1;
  }
  else if (win == 3){
    return 99;
  }
  win = board[1] + board[8] + board[5];
  if(win == -3){
    return -1;
  }
  else if (win == 3){
    return 99;
  }
  return 0;
}


void gotocup_GrabCup()
{
  while(1)
  {
    int distance;
    distance = sparki.ping();
//     sparki.clearLCD();
//    sparki.println(distance);
//    sparki.updateLCD();
    if (distance <= 5 && distance > -1 && cup == 0)
    {
      sparki.moveStop();
      sparki.gripperClose();
      delay(3500);
      sparki.gripperStop();
      sparki.moveRight(90);
      sparki.moveStop();
      while (!(sparki.lineLeft() < THRESHOLD))
      {
        sparki.moveRight();
      }
      sparki.moveStop();
      cup = 1;
    }

    int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
    int lineCenter = sparki.lineCenter(); // measure the center IR sensor
    int lineRight  = sparki.lineRight();  // measure the right IR sensor
    if ( lineLeft < THRESHOLD ) // if line is below left line sensor
    {
      sparki.moveLeft(); // turn left
    }
    if ( lineRight < THRESHOLD ) // if line is below left line sensor
    {
      sparki.moveRight(); // move forward
    }
  if ( (lineCenter < THRESHOLD) && (lineLeft > THRESHOLD) && (lineRight > THRESHOLD) )
  {
    sparki.moveForward(); // move forward
  }
  if(cup == 1){
      if ((lineCenter > THRESHOLD) && (lineLeft > THRESHOLD) && (lineRight > THRESHOLD)){
        break;
        return;
      }
      else
      {
          if ( lineLeft < THRESHOLD ){ // if line is below left line sensor
          
             sparki.moveLeft(); // turn left
           }
          if ( lineRight < THRESHOLD ){ // if line is below left line sensor
              sparki.moveForward(); // move forward
           }
           if ( (lineCenter < THRESHOLD) && (lineLeft > THRESHOLD) && (lineRight > THRESHOLD) ) {
              sparki.moveForward(); // move forward
              }
       }
  }
  
  
    

    sparki.clearLCD(); // wipe the screen

    sparki.print("Line Left: "); // show left line sensor on screen
    sparki.println(lineLeft);

    sparki.print("Line Center: "); // show center line sensor on screen
    sparki.println(lineCenter);

    sparki.print("Line Right: "); // show right line sensor on screen
    sparki.println(lineRight);

    sparki.print("cup: ");
    sparki.println(cup);
    sparki.updateLCD(); // display all of the information written to the screen

    delay(100); // wait 0.1 seconds
  }

}

void place_cup() {
  while(1){

  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor

  if ( lineLeft < THRESHOLD ) // if line is below left line sensor
  {
    sparki.moveLeft(); // turn left
  }

  if ( lineRight < THRESHOLD ) // if line is below right line sensor
  {
    sparki.moveRight(); // turn right
  }

  // if the center line sensor is the only one reading a line
  if ( (lineCenter < THRESHOLD) && (lineLeft > THRESHOLD) && (lineRight > THRESHOLD) )
  {
    sparki.moveForward(); // move forward
  }

  // if all three line sensors read a line
  if ( (lineCenter < THRESHOLD) && (lineLeft < THRESHOLD) && (lineRight < THRESHOLD)) {
    // FOUND A MARKER - need a way to keep track of which one
    // depends on which state sparki is in
    if(counter > 0){
      counter = counter -1;
      sparki.moveForward(2);
    }
    else{
      if(right == 0){
        sparki.moveForward(2);
        sparki.moveLeft(90);
        sparki.moveForward(4);
        sparki.gripperOpen();
        delay(4000);
        sparki.gripperStop();
        sparki.moveBackward(5);
        sparki.moveLeft(90);
        while(lineCenter > THRESHOLD){
          sparki.moveLeft();
        }
        moveToStart();
        return;
      }
      else{
        sparki.moveForward(2);
        sparki.moveRight(90);
        sparki.moveForward(4);
        sparki.gripperOpen();
        delay(4000);
        sparki.gripperStop();
        sparki.moveBackward(5);
        sparki.moveRight(90);
        while(lineCenter > THRESHOLD){
          sparki.moveRight();
        }
        moveToStart();
        return;
      }
    }
    delay(100); // filler
  }
}
}
void moveToStart() {
  while(1){

  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor

  if ( lineLeft < THRESHOLD ) // if line is below left line sensor
  {
    sparki.moveLeft(); // turn left
  }

  if ( lineRight < THRESHOLD ) // if line is below right line sensor
  {
    sparki.moveRight(); // turn right
  }

  // if the center line sensor is the only one reading a line
  if ( (lineCenter < THRESHOLD) && (lineLeft > THRESHOLD) && (lineRight > THRESHOLD) )
  {
    sparki.moveForward(); // move forward
  }
  //if no line on censor
  if ( (lineCenter > THRESHOLD + 50) && (lineLeft > THRESHOLD + 50) && (lineRight > THRESHOLD + 50) )
  {
    if(right){
      sparki.moveForward(1);
      sparki.moveRight(90);
      sparki.moveForward(4);
      return;
    }
    else{
      sparki.moveForward(5);
    return;
  }
  return;
  }
}
}

void resetBoard()
{
  for (int i = 0; i < 9; i++)
  {
    board[i] = 0;
  }
}

void printBoard()
{
  sparki.clearLCD();
  sparki.print("Board: ");
  for (int i = 0; i < 9; i++)
  {
     sparki.print(board[i]); sparki.print(", ");
  }
  sparki.updateLCD();
  delay(3000);
}

void setup() {
  // put your setup code here, to run once:
  resetBoard();
  sparki.RGB(10,0,0);
  // Start with state 0
  sparki.clearLCD();
  sparki.println("Whats up? -Sparki");
  sparki.updateLCD();
  sparki.servo(SERVO_CENTER); // Center the Servo
  sparki.gripperOpen();
  delay(5000);
//  sparki.gripperStop();
//  sparki.moveForward(8);
//  sparki.moveLeft(75);
//  sparki.moveForward(5);
  sparki.gripperStop();
  numMoves = 0;
  myMove = 0;
  state = PLAYERINPUT;
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(state)
  {
    case PLAYERINPUT:
        sparki.clearLCD(); sparki.println("State: PLAYERINPUT"); sparki.updateLCD();
        humanInput();
        numMoves = numMoves + 1;
        if (checkForWin() == -1){
          state = LOSS;
        }
        else{
          state = THINK;
        }
        break;
    case THINK:
        sparki.clearLCD(); sparki.println("State: THINK"); sparki.updateLCD();
        for(int i = 0; i < 9; i++){
          if(board[i] == 0){
            //if unoccupied space, set that to sparki's move
            myMove = i;
            state = GRABCUP;
            break;
          }
          if(i == 8){
            state = LOSS;
            break;
          }
        }
        sparki.clearLCD(); sparki.print("Move: "); sparki.println(myMove); sparki.updateLCD();
        delay(3000);
        state = GRABCUP;
        break;
    case GRABCUP:
        sparki.clearLCD(); sparki.println("State: GRABCUP"); sparki.updateLCD();
        //this ends with sparki holding a cup at the null spot (no lines =  start spot)
        gotocup_GrabCup();
        cup = 0;
        state = GET_TO_LINE;
        break;
    case GET_TO_LINE:
        sparki.clearLCD(); sparki.println("State: GET_TO_LINE"); sparki.updateLCD();
        if(myMove < 4){
          right = 1;
          counter = myMove;
          sparki.moveForward(10);
          sparki.moveLeft(75);
          sparki.moveForward(5);
        }
        else{
          right = 0;
          counter = 7 - myMove;
          sparki.moveForward(5);
        }
        state = PLACE_CUP;
        break;
    case PLACE_CUP:
        //code = -1;
        sparki.clearLCD(); sparki.println("State: PLACE_CUP"); sparki.print("Move: "); sparki.println(myMove); sparki.updateLCD();
        place_cup();
        board[myMove] = 1;
        numMoves = numMoves + 1;
        printBoard();
        if(checkForWin() == 99){
          state = WIN;
        }
        else{
          state = PLAYERINPUT;
          delay(100);
          break;
          delay(100);
        }
        break;
    case LOSS:
        sparki.clearLCD(); sparki.println("State: LOSS"); sparki.updateLCD();
        break;
    case WIN:
        sparki.clearLCD(); sparki.println("State: WIN"); sparki.updateLCD();
        break;
    case TIE:
        sparki.clearLCD(); sparki.println("State: TIE"); sparki.updateLCD();
        break;
  }
}

