//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define PACKET_SIZE       40

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(19200);
  SerialBT.begin("ESP32"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  // 리모컨 조종 없이 정지 상태에서 데이터 수신 받을 때만 사용
  // MFC 리시버 프로그램에서 통신 연결하고, 파일 생성해서 데이터 받을 준비를 하기 위한 시간을 10초 준다.
  delay( 10000 );
}

void loop() {
  int16_t receiveHead = 0x7ffd; // 수신 데이터 시작 지점
  int16_t receiveTail = 0x7ffe; // 수신 데이터 종료 지점
  int16_t receiveEnd  = 0x7fff; // 시리얼 통신 종료

  byte receivePacket[ PACKET_SIZE ];
  
  int16_t result;

  int recvSize;

  
  if ( Serial.available() > 0 )
  {
    recvSize = 0;
    while ( 1 )
    {
      recvSize += Serial.readBytes( &receivePacket[recvSize], 2 - recvSize );
      if ( recvSize >= 2 )
        break;
    }

    result = ( receivePacket[ 1 ] << 8 ) | receivePacket[ 0 ];

    if( result == receiveHead )
    {
      ;
    }
    else if( result == receiveTail )
    {
      SerialBT.print( '\n' );
    }
    else
    {
      SerialBT.print( result );
      SerialBT.print( " " );
    }
  }

  
//  if (SerialBT.available()) {
//    Serial.write(SerialBT.read());
//  }
//  delay(20);
}
