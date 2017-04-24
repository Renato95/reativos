void setup() {
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,OUTPUT);
}
short btnPress[2];
short btnState[2];

unsigned long timestamp;
unsigned long lastBlink;

unsigned long pressTime[2];
unsigned long releaseTime[2];
unsigned long blockTime[2];

short velocidade = 1000;
short bounceSpeed = 50;

bool blocked = false;
bool led;

void loop() {
  // lendo estados
  timestamp = millis();
  btnPress[0] = digitalRead(2);
  btnPress[1] = digitalRead(3);

  if(lastBlink+velocidade<timestamp&&!blocked){// blink desde q nao bloqueado
    digitalWrite(4,led);led=!led;
    lastBlink = timestamp;
  }

  BtnPress(0);// muda a vel caso necessario
  BtnPress(1);// tb grava qual foi a ultima vez q o btn foi apertado
  long interval = pressTime[0]-pressTime[1];// intervalo entre os presses
  
  if(abs(interval)<500&&pressTime[0]&&pressTime[1]&&blockTime[0]!=pressTime[0]&&blockTime[1]!=pressTime[1]){
    // bloqueia se estiver dentro do intervalo, os botes sendo apertados ao menos uma vez e em um tempo diferente do ultimo bloqueio
    blockTime[0] = pressTime[0];
    blockTime[1] = pressTime[1];
    blocked = !blocked;
    //while(1);//caso seja pra bloquear direto
  }

  if(velocidade<0)velocidade = 0;// limite inferior da velocidade
}

void BtnPress(int btn){
  if(btnPress[btn] && !btnState[btn] && releaseTime[btn]+bounceSpeed<timestamp){ //rising sem bounce
    if(!blocked){// nao mudo velocidade caso bloqueado
      velocidade+=50*((btn*2)-1);
    }
    pressTime[btn]=timestamp;releaseTime[btn]=0;
  }
  if(!btnPress[btn] && btnState[btn]){ //falling
    pressTime[btn]=0;releaseTime[btn]=timestamp;
  }
  btnState[btn]=btnPress[btn];
}

