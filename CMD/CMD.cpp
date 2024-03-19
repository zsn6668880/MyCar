#include "CMD.h"
using namespace Cmd;
static unsigned char Cmd::_cmd1[8] = {0x19, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11};
static unsigned char Cmd::_cmd2[8] = {0x19, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11};
static unsigned char Cmd::_data1[8] = {0x29, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11};
static unsigned char Cmd::_data2[8] = {0x29, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11};


void Cmd::test(){
  Cmd::setCmdB('A',1000);
  Cmd::setCmdB('B', 3000);
  Cmd::setCmdB('C', 1000);
  Cmd::setCmdB('G',10000000);
}

void Cmd::init(){
    SERIAL_A.begin(115200);
    SERIAL_B.begin(115200);
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

char Cmd::readDataA(unsigned char cmdSend, long* data){
    long d;
  char in[4];

  *data = 0;
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


         return 4;
       }
       else
         return -1;
    }

  return 0;
}

char Cmd::readDataB(unsigned char cmdSend, long* data){
    long d;
  char in[4];

  *data = 0;
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