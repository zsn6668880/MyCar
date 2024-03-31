#include "CMD.h"

using namespace Cmd;
static unsigned char Cmd::_cmd1[8] = {0x19, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11};
static unsigned char Cmd::_cmd2[8] = {0x19, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11};
static unsigned char Cmd::_data1[8] = {0x29, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11};
static unsigned char Cmd::_data2[8] = {0x29, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11};

void Cmd::setPos(double pos){
  Cmd::setCmdB('A',ACC);
  Cmd::setCmdB('B', MAXSPEED);
  Cmd::setCmdB('C', DEC);

  Cmd::setCmdA('A',ACC);
  Cmd::setCmdA('B', MAXSPEED);
  Cmd::setCmdA('C', DEC);

  Cmd::setCmdA('a',ACC);
  Cmd::setCmdA('b', MAXSPEED);
  Cmd::setCmdA('c', DEC);

  Cmd::setCmdB('a',ACC);
  Cmd::setCmdB('b', MAXSPEED);
  Cmd::setCmdB('c', DEC);

  Cmd::setCmdA('G', pos * LAP_A);
  Cmd::setCmdB('G', -pos * LAP_B);
  Cmd::setCmdA('g', -pos * LAP_A);
  Cmd::setCmdB('g', pos * LAP_B);
}

void Cmd::setDis(double dis){
    Cmd::setCmdB('A',0.5 * ACC);
        Cmd::setCmdB('B',0.5 * MAXSPEED);
        Cmd::setCmdB('C',0.5 * DEC);

        Cmd::setCmdA('A',0.5 * ACC);
        Cmd::setCmdA('B',0.5 * MAXSPEED);
        Cmd::setCmdA('C',0.5 * DEC);

        Cmd::setCmdB('a',0.5 * ACC);
        Cmd::setCmdB('b',0.5 * MAXSPEED);
        Cmd::setCmdB('c',0.5 * DEC);

        Cmd::setCmdA('a',0.5 * ACC);
        Cmd::setCmdA('b',0.5 * MAXSPEED);
        Cmd::setCmdA('c',0.5 * DEC);

        Cmd::setCmdA('E',dis * LAP_A);
        Cmd::setCmdA('e',-dis * LAP_A);
        Cmd::setCmdB('E',-dis * LAP_B);
        Cmd::setCmdB('e', dis * LAP_B);
}


void Cmd::init(){
    SERIAL_A.begin(115200);
    SERIAL_B.begin(115200);

    // Cmd::setCmdA('R',0);
    // Cmd::setCmdB('R', 0);
    // delay(500);
    // Cmd::setCmdA('U',0);
    // Cmd::setCmdB('U', 0);

    // Cmd::setCmdA('P', 20);
    // Cmd::setCmdA('I', 10);
    // Cmd::setCmdA('D', 0);
    // Cmd::setCmdA('p', 20);
    // Cmd::setCmdA('i', 10);
    // Cmd::setCmdA('d', 0);

    // Cmd::setCmdB('P', 20);
    // Cmd::setCmdB('I', 10);
    // Cmd::setCmdB('D', 0);
    // Cmd::setCmdB('p', 20);
    // Cmd::setCmdB('i', 10);
    // Cmd::setCmdB('d', 0);
    
    // Cmd::setCmdA('F', 0);
    // Cmd::setCmdA('f', 0);
    // Cmd::setCmdB('F', 0);
    // Cmd::setCmdB('f', 0);

    // Cmd::setCmdA('J', 0);
    // Cmd::setCmdA('j', 0);
    // Cmd::setCmdB('J', 0);
    // Cmd::setCmdB('j', 0);
}

void Cmd::setCmdA(unsigned char cmdSend, long motorSpeed){
  // command 
  _cmd1[2] = cmdSend;
   
  // data
  // send MSB first
  _cmd1[3] = (unsigned char)(motorSpeed >> 24);
  _cmd1[4] = (unsigned char)(motorSpeed >> 16);
  _cmd1[5] = (unsigned char)(motorSpeed >> 8);
  _cmd1[6] = (unsigned char)(motorSpeed);
  
  // send command 
  SERIAL_A.write(_cmd1,8);
  
  return;
}

void Cmd::setCmdB(unsigned char cmdSend, long motorSpeed){
  // command
  _cmd2[2] = cmdSend;

  // send command
  _cmd2[3] = (unsigned char)(motorSpeed >> 24);
  _cmd2[4] = (unsigned char)(motorSpeed >> 16);
  _cmd2[5] = (unsigned char)(motorSpeed >> 8);
  _cmd2[6] = (unsigned char)(motorSpeed);
  SERIAL_B.write(_cmd2, 8);

  return;
}

char Cmd::readDataA(unsigned char cmdSend,  short* data){
  char in[4];
  // command
  _data1[2] = cmdSend;

  // send command
  SERIAL_A.write(_data1, 8);

  if((cmdSend == 'S')||(cmdSend == 's')||(cmdSend == 'T')||(cmdSend == 't'))     // Target
    {
       //read data
       SERIAL_A.readBytes(in, 4);

       if((in[0] == cmdSend)&&(in[3] == 'L'))
       {
         //MSB first
         *data = *(unsigned char*)(in + 1) << 8;
         *data = *data | *(unsigned char*)(in + 2);
         if(*data < 0){
          *data = ~*data;
         }
         return 4;
       }
       else
         return -1;
    }

  return 0;
}

char Cmd::readDataB(unsigned char cmdSend, short* data){
  char in[4];

  *data = 0;
  // long* data1 = 0;
  // command
  _data2[2] = cmdSend;

  // send command
  SERIAL_B.write(_data2, 8);

  if((cmdSend == 'S')||(cmdSend == 's')||(cmdSend == 'T')||(cmdSend == 't'))     // Target
    {
       //read data
       SERIAL_B.readBytes(in, 4);

       if((in[0] == cmdSend)&&(in[3] == 'L'))
       {
         //MSB first
         *data = *(unsigned char*)(in + 1) << 8;
         *data = *data | *(unsigned char*)(in + 2);
         if(*data < 0){
          *data = ~*data;
          
         }
           
        // *data1 = *(signed char*)in[1];
        //  *data1 = *data << 8;
        //  *data1 |= *(unsigned char*)in[2];
        //  *data += *data1;

         return 4;
       }
       else
         return -1;
    }

  return 0;
}

char Cmd::readPosA(unsigned char cmdSend, long* data){
    long d;
  char in[8];
  
  *data = 0;
  // command 
  _data1[2] = cmdSend;
   
  // data
  d = -2;
  // send MSB first
  _data1[3] = (unsigned char)(d >> 24);
  _data1[4] = (unsigned char)(d >> 16);
  _data1[5] = (unsigned char)(d >> 8);
  _data1[6] = (unsigned char)(d);
  
  // send command 
  SERIAL_A.write(_data1,8);
  
  if((cmdSend == 'O')||(cmdSend == 'o'))     // Target
    {
       //read data
       SERIAL_A.readBytes(in, 8); 
       
       if((in[0] == cmdSend - 2)&&(in[3] == 'L')&&(in[4] == cmdSend)&&(in[7] == 'L'))
       {
         //MSB first
         *data = *(unsigned char*)(in + 1) << 24;
         *data = *data | ((*(unsigned char*)(in + 2))<<16);
         *data = *data | ((*(unsigned char*)(in + 5))<<8);
         *data = *data | (*(unsigned char*)(in + 6));
        
         return 8;
       }
       else
         return -1;
    }
  
  return 0;
}

char Cmd::readPosB(unsigned char cmdSend, long* data){
    long d;
  char in[8];

  *data = 0;
  // command
  _data2[2] = cmdSend;

  // data
  d = -2;
  // send MSB first
  _data2[3] = (unsigned char)(d >> 24);
  _data2[4] = (unsigned char)(d >> 16);
  _data2[5] = (unsigned char)(d >> 8);
  _data2[6] = (unsigned char)(d);

  // send command
  SERIAL_B.write(_data2, 8);

  if((cmdSend == 'O')||(cmdSend == 'o'))     // Target
    {
       //read data
       SERIAL_B.readBytes(in, 8);

       if((in[0] == cmdSend - 2)&&(in[3] == 'L')&&(in[4] == cmdSend)&&(in[7] == 'L'))
       {
         //MSB first
         *data = *(unsigned char*)(in + 1) << 24;
         *data = *data | ((*(unsigned char*)(in + 2))<<16);
         *data = *data | ((*(unsigned char*)(in + 5))<<8);
         *data = *data | (*(unsigned char*)(in + 6));
        
         return 8;
       }
       else
         return -1;
    }
  
  return 0;
}