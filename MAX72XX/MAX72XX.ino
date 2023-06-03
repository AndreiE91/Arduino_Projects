#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Time.h>

#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define MAX_DEVICES 4
#define DATA_PIN 11
#define CLK_PIN 13
#define CS_PIN 10
#define ROWS 8
#define COLS 32
#define MAX_FOOD 1

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

struct Point {
  byte x, y;
};

byte leftButtonState = 0;
byte rightButtonState = 0;
byte turnLeftButtonPin = 4;
byte turnRightButtonPin = 3;
byte buzzerPin = 2;
byte resetPin = 8;

Point food;
Point arr[ROWS][COLS];
Point snake[ROWS * COLS + 1];
int snakeLength;
int gameTick;
enum directions {
  UP,
  RIGHT,
  DOWN,
  LEFT
};
directions currentDir;

int randomNumber(int low, int high) {
    return(rand()%(high - low + 1) + low);
}

bool isInSnake() {
  for(int i = 0; i < snakeLength; ++i) {
    if(food.x == snake[i].x && food.y == snake[i].y) {
      return true;
    }
  }
  return false;
}

void createFood() {
  int newX{0};
  int newY{0};
  do{
    newX = random(0, ROWS - 1);
    newY = random(0, COLS - 1);
    food.x = newX;
    food.y = newY;
  }while(isInSnake());
}

void mapping() {
  int x;
  for (int i = 0; i < ROWS; i++) {
    x = 0;
    for (int j = 7; j >= 0; j--) {
      arr[i][x].x = i;
      arr[i][x++].y = j;
    }
  }

  for (int i = 0; i < ROWS; i++) {
    x = 8;
    for (int j = 15; j >= 8; j--) {
      arr[i][x].x = i;
      arr[i][x++].y = j;
    }
  }

  for (int i = 0; i < ROWS; i++) {
    x = 16;
    for (int j = 23; j >= 16; j--) {
      arr[i][x].x = i;
      arr[i][x++].y = j;
    }
  }

  for (int i = 0; i < ROWS; i++) {
    x = 24;
    for (int j = 31; j >= 24; j--) {
      arr[i][x].x = i;
      arr[i][x++].y = j;
    }
  }
}

void insertInSnake(int x, int y) {
  for (int i = snakeLength; i > 0; --i) {
    snake[i] = snake[i - 1];
  }
  snake[0].x = x;
  snake[0].y = y;
  ++snakeLength;
}

void move(bool turnLeft, bool turnRight) {
  switch (currentDir) {
    case UP:
      {
        if (turnLeft && !turnRight) {
          currentDir = LEFT;
          for (int i = snakeLength - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
          }
          if(snake[0].y - 1 < 0) {
            snake[0].y = COLS - 1;
          } else {
            snake[0].y--;
          }
        } else if (!turnLeft && turnRight) {
          currentDir = RIGHT;
          for (int i = snakeLength - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
          }
          if(snake[0].y + 1 >= COLS) {
            snake[0].y = 0;
          } else {
            snake[0].y++;
          }
        } else {
          for (int i = snakeLength - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
          }
          if(snake[0].x + 1 >= ROWS) {
            snake[0].x = 0;
          } else {
            snake[0].x++;
          }
        }
        break;
      }
    case RIGHT:
      {
        if (turnLeft && !turnRight) {
          currentDir = UP;
          for (int i = snakeLength - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
          }
          if(snake[0].x + 1 >= ROWS) {
            snake[0].x = 0;
          } else {
            snake[0].x++;
          }
        } else if (!turnLeft && turnRight) {
          currentDir = DOWN;
          for (int i = snakeLength - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
          }
          if(snake[0].x - 1 < 0) {
            snake[0].x = ROWS - 1;
          } else {
            snake[0].x--;
          }
        } else {
          for (int i = snakeLength - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
          }
          if(snake[0].y + 1 >= COLS) {
            snake[0].y = 0;
          } else {
            snake[0].y++;
          }
        }
        break;
      }
    case DOWN:
      {
        if (turnLeft && !turnRight) {
          currentDir = RIGHT;
          for (int i = snakeLength - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
          }
          if(snake[0].y + 1 >= COLS) {
            snake[0].y = 0;
          } else {
            snake[0].y++;
          }
        } else if (!turnLeft && turnRight) {
          currentDir = LEFT;
          for (int i = snakeLength - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
          }
          if(snake[0].y - 1 < 0) {
            snake[0].y = COLS - 1;
          } else {
            snake[0].y--;
          }
        } else {
          for (int i = snakeLength - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
          }
          if(snake[0].x - 1 < 0) {
            snake[0].x = ROWS - 1;
          } else {
            snake[0].x--;
          }
        }
        break;
      }
    case LEFT:
      {
        if (turnLeft && !turnRight) {
          currentDir = DOWN;
          for (int i = snakeLength - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
          }
          if(snake[0].x - 1 < 0) {
            snake[0].x = ROWS - 1;
          } else {
            snake[0].x--;
          }
        } else if (!turnLeft && turnRight) {
          currentDir = UP;
          for (int i = snakeLength - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
          }
          if(snake[0].x + 1 >= ROWS) {
            snake[0].x = 0;
          } else {
            snake[0].x++;
          }
        } else {
          for (int i = snakeLength - 1; i > 0; --i) {
            snake[i] = snake[i - 1];
          }
          if(snake[0].y - 1 < 0) {
            snake[0].y = COLS - 1;
          } else {
            snake[0].y--;
          }
        }
        break;
      }
  }
}

void setup() {
  digitalWrite(resetPin, HIGH);
  Serial.begin(9600); //for debugging
  gameTick = 500; //default value
  pinMode(turnLeftButtonPin, INPUT);
  pinMode(turnRightButtonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  snakeLength = 0;
  currentDir = RIGHT;
  mx.begin();
  mapping();
  mx.clear();
  snake[0].x = 3;
  snake[0].y = 11;
  ++snakeLength;
  insertInSnake(3, 12);
  insertInSnake(3, 13);
  insertInSnake(3, 14);
  createFood();
}

void checkDeath() {
  for(int i=1; i<snakeLength; i++){
    if(snake[0].x==snake[i].x && snake[0].y==snake[i].y){
      tone(buzzerPin, 90);
      delay(200);
      noTone(buzzerPin);
      digitalWrite(resetPin, LOW);
    }
  }
}

void loop() {
  gameTick = analogRead(A5) / 2 + 100;
  //int random = randomNumber(1, 809);
  //int buttonValue = analogRead(A4);
  //Serial.println(gameTick);
  //Serial.println(buttonValue);
  //Serial.println(random);
  //delay(50);
  //tone(buzzerPin, 90);
  leftButtonState = digitalRead(turnLeftButtonPin);
  rightButtonState = digitalRead(turnRightButtonPin);
  static byte isPressed = 0;

  static int i = 0;
  static int j = 0;
  static unsigned long timer{ 0 };

  if(leftButtonState != LOW && rightButtonState == LOW) {
    isPressed = 1;
  }

  if(rightButtonState != LOW && leftButtonState == LOW) {
    isPressed = 2;
  }

  if(leftButtonState != LOW && rightButtonState != LOW) {
    isPressed = 0;
  }

  if (millis() - timer > gameTick) { //code inside this structure will run once every gameTick(milliseconds value)
        Point lastTailPosition;
        lastTailPosition.x = snake[snakeLength-1].x;
        
        lastTailPosition.y = snake[snakeLength-1].y;

        if(isInSnake()){ //checks whether food touched snake or not
        tone(buzzerPin, 400);
        delay(50);
        noTone(buzzerPin);
        snake[snakeLength].x = lastTailPosition.x;
        snake[snakeLength].y = lastTailPosition.y;
        snakeLength++;
        createFood();
      } else {
          tone(buzzerPin, 10);
          delay(25);
          noTone(buzzerPin);
      }
        if(isPressed==0 || leftButtonState !=LOW || rightButtonState !=LOW) {
          move(false, false);
        }
        else{
          if(leftButtonState == LOW && rightButtonState == LOW && isPressed == 1) {
            move(true, false);
          }
          
          if(leftButtonState == LOW && rightButtonState == LOW && isPressed == 2) {
            move(false, true);
          }
      }
      
      mx.clear();
      


      for (int i = 0; i < snakeLength; ++i) {
        mx.setPoint(arr[snake[i].x][snake[i].y].x, arr[snake[i].x][snake[i].y].y, true);
      }
      mx.setPoint(arr[food.x][food.y].x, arr[food.x][food.y].y, true);
      checkDeath();
      timer = millis();
      isPressed = 0;
    }
}