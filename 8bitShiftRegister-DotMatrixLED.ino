//    1 QA QB QC QD QE QF QG QH
//  2   13 03 04 10 06 11 15 16
// QA 09 ○  ○  ○  ○  ○  ○  ○  ○
// QB 14 ○  ○  ○  ○  ○  ○  ○  ○
// QC 08 ○  ○  ○  ○  ○  ○  ○  ○
// QD 12 ○  ○  ○  ○  ○  ○  ○  ○
// QE 01 ○  ○  ○  ○  ○  ○  ○  ○
// QF 07 ○  ○  ○  ○  ○  ○  ○  ○
// QG 02 ○  ○  ○  ○  ○  ○  ○  ○
// QH 05 ○  ○  ○  ○  ○  ○  ○  ○

#define SRCLK 22  
#define RCLK  32
#define SER   27
#define ROW_N 8

int seq = 0;
void setup(){
  pinMode(SRCLK, OUTPUT); digitalWrite(SRCLK, LOW);
  pinMode(RCLK, OUTPUT);  digitalWrite(RCLK, LOW);
  pinMode(SER, OUTPUT);   digitalWrite(SER, HIGH);

  Serial.begin(9600);
}

byte ledArray[1][8] = {
  {
    0b00000000,
    0b00011000,
    0b00100100,
    0b10011001,
    0b00100100,
    0b00011000,
    0b00000000,
    0b00000000
  }
};

void loop(){
  for(int no = 0; no < 1; no++){
    int stTime = millis();
    while(millis() - stTime < 1000){
      for(int i = 0; i < ROW_N; i++){ 
        // カソード側
        for(int j = 0; j < ROW_N; j++){
          if(i == (7-j))  digitalWrite(SER, LOW);    // ダイナミックな行のみLOWにする。
          else            digitalWrite(SER, HIGH);
          digitalWrite(SRCLK, HIGH);  // 立ち上がりでSERがレジスタに入る
          digitalWrite(SRCLK, LOW);   // レジスタに送ったらLOWにする
        }
      
        // アノード側
        for(int j = 0; j < ROW_N; j++){
          if(ledArray[no][i] & ( 0b00000001 << j))  digitalWrite(SER, HIGH);
          else                                  digitalWrite(SER, LOW);
          digitalWrite(SRCLK, HIGH);  // 立ち上がりでSERがレジスタに入る
          digitalWrite(SRCLK, LOW);   // レジスタに送ったらLOWにする
        }
        
        digitalWrite(RCLK, HIGH);   // 出力
        digitalWrite(RCLK, LOW);
      }
    }
  }
}
