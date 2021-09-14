#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "playfair.h"
#include <string.h>

int main()
{
	unsigned char *encrypt;
	char *decrypt;
	encrypt = bmp_encrypt("TUKE", "students");
	printf("bmp_encrypt: %s\n", encrypt);
	//size_t len = strlen(encrypt);
	for (size_t i = 0; encrypt[i]; i++)
	{
		printf("0x%x, ", encrypt[i]);
	}
	printf("\n");
	decrypt = bmp_decrypt("CoMPuTeR", encrypt);
	printf("bmp_decrypt: %s\n", decrypt);
	free(encrypt);
    free(decrypt);
	encrypt = NULL; 
	decrypt = NULL;
	///
	char *encrypted;
	char *decrypted;
	//char *key = "SeCReT";
	//char * text = "Hello world";
    // even length of string
    encrypted = playfair_encrypt("SeCReT", "Hello world");
    printf("%s\n", encrypted);
    // "Hello world" --> "HELXLOVORLDX"
    // IS JZ JQ XN TK JC
	decrypted = playfair_decrypt("SeCReT", "IS JZ JQ XN TK JC");
    printf("%s\n\n", decrypted);
    // HELXLOVORLDX
	//if (encrypted)
		free(encrypted);
	//if (decrypted)
		free(decrypted);
	encrypted = NULL;
	decrypted = NULL;

	//if (key)free(key);
	//if (text)free(text);
	//key = NULL;
	//text = NULL;
	/////*
	//char *encrypted1;
	//char *decrypted1;
 //   // odd length of string
 //   encrypted1 = playfair_encrypt("world", "Hello");
 //   printf("%s\n", encrypted1);
 //   // "Hello" --> "HELXLO"
 //   // JB RY DR
 //   decrypted1 = playfair_decrypt("world", encrypted1);
 //   printf("%s\n\n", decrypted1);
 //   // HELXLO
 //   free(encrypted1);
 //   free(decrypted1);
	//encrypted1 = NULL; 
	//decrypted1 = NULL;
 //   ///
	//char *encrypted2;
	//char *decrypted2;
 //   // letter 'X' in message
 //   encrypted2 = playfair_encrypt("Password", "Taxi please");
 //   printf("%s\n", encrypted2);
 //   // "Taxi please" --> "TAXIPLEASE"
 //   // UP YH AK DO OB
 //   decrypted2 = playfair_decrypt("Password", encrypted2);
 //   printf("%s\n\n", decrypted2);
 //   // TAXIPLEASE
 //   free(encrypted2);
 //   free(decrypted2);
	//encrypted2 = NULL; 
	//decrypted2 = NULL;
 //   ///
	//char *encrypted3;
	//char *decrypted3;
 //   // multi 'X's in message
 //   encrypted3 = playfair_encrypt("please", "Taxxxiii");
 //   printf("%s\n", encrypted3);
 //   // "Taxxxiii" --> "TAXXXIIXIX"
 //   // RS EE VJ JV JV
 //   decrypted3 = playfair_decrypt("please", encrypted3);
 //   printf("%s\n\n", decrypted3);
 //   // TAXXXIIXIX
 //   free(encrypted3);
 //   free(decrypted3);
	//encrypted3 = NULL; 
	//decrypted3 = NULL;
	return 0;
}
