#include <U8glib.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
float x1 = 128;
float x2 = 178;
float circley = 30;
int randomlengh = random(10, 50);
int randomlengh2 = random(10, 50);
int a = 0;
int score = 0;
bool finish = false;
int emptyplace = 20;
int pillarturn = 1;


int boardX = 55;
float ballx = 20;
float bally = 20;
float ballspeedx = 0.3;
float ballspeedy = 0.3;
bool finishballgame = false;
int ballscore = 0;

int game = 10;


void draw() {
  x1 = x1 - 0.3;
  x2 = x2 - 0.3;
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(10, 20);
  u8g.print(score);


  u8g.drawBox(x1, 0, 8, randomlengh);
  u8g.drawBox(x1, randomlengh + emptyplace, 8, 100);

  u8g.drawBox(x2, 0, 8, randomlengh2);
  u8g.drawBox(x2, randomlengh2 + emptyplace, 8, 100);

  u8g.drawCircle(20, circley, 3);
  u8g.setColorIndex(1);
  if (x1 < 2) {
    x1 = 128;
    score++;
    randomlengh = random(10, 50);
    pillarturn = 2;

  }
  if (x2 < 2) {
    x2 = 128;
    randomlengh2 = random(10, 50);
    pillarturn = 1;

  }


  int btn = digitalRead(7);
  if (btn == 1) {
    circley = circley + 0.3;

  } else if (btn == 0) {
    circley = circley - 0.6;
  }
  //위쪽 기둥에 닿았을때
  if (pillarturn == 1) {

    if (circley - 3 < randomlengh) {

      if (x1 <= 20 && 20 <= x1 + 8) {
        Serial.println("touch");
        finish = true;
      }
    }
    //아래쪽 기둥에 닿았을때
    if (circley + 3 > randomlengh + emptyplace) {
      if (x1 <= 20 && 20 <= x1 + 8) {
        Serial.println("touch");
        finish = true;
      }
    }
  } else if (pillarturn == 2) {

    if (circley - 3 < randomlengh2) {
      Serial.println(randomlengh2);


      if (x2 <= 20 && 20 <= x2 + 8) {
        Serial.println("touch");
        finish = true;
      }
    }
    //아래쪽 기둥에 닿았을때
    if (circley + 3 > randomlengh2 + emptyplace) {

      if (x2 <= 20 && 20 <= x2 + 8) {
        Serial.println("touch");
        finish = true;
      }
    }
  }


  if (circley - 3 <= 0 || circley + 3 >= 64) {
    finish = true;
  }
}

void drawb() {
  int joystickX = analogRead(A1);
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(10, 20);
  u8g.print(ballscore);
  if (joystickX < 300) {
    boardX--;
  } else if (joystickX > 600) {
    boardX++;
  }
  ballx = ballx + ballspeedx;
  bally = bally + ballspeedy;
  Serial.println(bally);

  //판에 닿았을때
  if (bally + 4 >= 55) {
    if (ballx >= boardX && ballx <= boardX + 30) {
      ballspeedy = -ballspeedy;
      ballscore++;
      if (ballscore % 10 == 0) {
        if (ballspeedx > 0) {
          ballspeedx = ballspeedx + 0.1;
        } else {
          ballspeedx = ballspeedx - 0.1;
        }
        if (ballspeedy > 0) {
          ballspeedy = ballspeedy + 0.1;
        } else {
          ballspeedy = ballspeedy - 0.1;
        }
      }
    }
  }


  //위쪽에 닿았을때
  else if (bally - 4 <= 0) {
    ballspeedy = -ballspeedy;
  }
  //왼쪽에 닿았을때
  else if (ballx - 4 <= 0) {
    Serial.println("left touch");
    ballspeedx = -ballspeedx;
  }
  //오른쪽에 닿았을때
  else if (ballx + 4 >= 128) {
    ballspeedx = -ballspeedx;

    Serial.println("right touch");
  }
  if (bally + 4 >= 64) {
    Serial.println("finsih");
    finishballgame = true;
  }
  u8g.drawCircle(ballx, bally, 4);
  u8g.drawBox(boardX, 55, 30, 5);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(8) == LOW) {
    Serial.println("8");
  }
  if (digitalRead(9) == LOW) {
    Serial.println("9");
  }
  if (digitalRead(10) == LOW) {
    Serial.println("10");
  }
  if (digitalRead(8) == HIGH && digitalRead(9) == LOW && digitalRead(10) == LOW) {
    game = 1;
  } else if (digitalRead(8) == LOW && digitalRead(9) == LOW && digitalRead(10) == HIGH) {
    game = 0;
  } else {
    game = 10;
  }

  u8g.firstPage();
  do {

    if (game == 0) {
      if (!finishballgame) {
        drawb();
      } else {
        u8g.setFont(u8g_font_osb18);
        u8g.drawStr(30, 40, "Finish");
        u8g.setFont(u8g_font_unifont);
        u8g.setPrintPos(35, 60);
        u8g.print("score:");
        u8g.setFont(u8g_font_unifont);
        u8g.setPrintPos(85, 60);
        u8g.print(ballscore);
      }
    } else if (game == 1) {
      if (finish == false) {
        draw();
      } else {
        u8g.setFont(u8g_font_osb18);
        u8g.drawStr(30, 40, "Finish");
        u8g.setFont(u8g_font_unifont);
        u8g.setPrintPos(35, 60);
        u8g.print("score:");
        u8g.setFont(u8g_font_unifont);
        u8g.setPrintPos(85, 60);
        u8g.print(score);
      }
    } else {
      u8g.setFont(u8g_font_courB08);
      u8g.drawStr(10, 40, "Chip not recognized");
    }





  } while (u8g.nextPage());
}
