/*
 * main.c
 *
 * Created: 3/8/2023 11:54:52 PM
 *  Author: Awara
 */ 

#include <xc.h>
#include "mbed.h"
#include "MFRC522.h" //MFRC522 RfChip (SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS, MF_RESET);
MFRC522 RFID (D4, D5, D6, D7, D8);
int main(void) {
	printf("Touch a RFID card...\r\n");// Init. RC522 Chip	
	RFID.PCD_Init();
	while (true) {
		if ( ! RFID.PICC_IsNewCardPresent()){
			wait_ms(500);
			continue;
		}		
		if ( ! RFID.PICC_ReadCardSerial()){ // Select one of the cards
			wait_ms(500);
			continue;
		}		
		printf("Card UID: "); // Print Card UID
		for (uint8_t i = 0; i < RFID.uid.size; i++){
			printf(" %d", RFID.uid.uidByte[i]);
		}
		printf("\n\r"); // Print Card type		
		uint8_t piccType = RFID.PICC_GetType(RFID.uid.sak);
		printf("PICC Type: %s \n\r", RFID.PICC_GetTypeName(piccType));
		wait_ms(500);
	}
}