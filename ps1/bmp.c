#include "bmp.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* reverse(const char* text)
{
	if (text)
	{
		size_t len = strlen(text);
		char* tmp = (char*)calloc((len + 1), sizeof(char));
		for (int i = 0; i < len; i++)
		{
			tmp[i] = toupper(text[len - 1 - i]);
		}
		tmp[len] = '\0';
		return tmp;
	}
	return NULL;
}

int chek_key(const char* key)
{
	if (key)
	{
		size_t len_key = strlen(key);
		for (int i = 0; i < len_key; i++)
		{
			if (toupper(key[i]) < 'A' || toupper(key[i]) > 'Z')
			{
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

char* vigenere_encrypt(const char* key, const char* text)
{
	if (key && text)
	{
		if (chek_key(key))
		{
			size_t len = strlen(text);
			size_t len_key = strlen(key);
			char* encrypted = (char*)calloc((len + 1), sizeof(char));
			if (chek_key(key))
				for (int i = 0, j = 0; i < len + 1; i++)
				{
					if (toupper(text[i]) >= 'A' && toupper(text[i]) <= 'Z')
					{
						if (toupper(key[j % len_key] >= 'A' && toupper(key[j % len_key]) <= 'Z'))
						{
							encrypted[i] = 'A' + ((toupper(text[i]) + toupper(key[j++ % len_key])) % 26);
						}
						else
						{
							free(encrypted);
							return NULL;
						}
					}
					else
					{
						encrypted[i] = text[i];
					}
				}
			encrypted[len] = '\0';
			return encrypted;
		}
	}
	return NULL;
}

char* vigenere_decrypt(const char* key, const char* text)
{
	if (key && text)
	{
		if (chek_key(key))
		{
			size_t len = strlen(text);
			size_t len_key = strlen(key);
			char* encrypted = (char*)calloc((len + 1), sizeof(char));
			for (int i = 0, j = 0; i < len + 1; i++)
			{
				if (toupper(text[i]) >= 'A' && toupper(text[i]) <= 'Z')
				{
					if (toupper(key[j % len_key] >= 'A' && toupper(key[j % len_key]) <= 'Z'))
					{
						encrypted[i] = 'A' + (toupper(text[i]) + 26 - toupper(key[j++ % len_key])) % 26;
					}
					else
					{
						free(encrypted);
						return NULL;
					}
				}
				else
				{
					encrypted[i] = text[i];
				}
			}
			encrypted[len] = '\0';
			return encrypted;
		}
	}
	return NULL;
}

int switchbit(const int value, const int position)
{
	return value ^ (1 << position);
}

int checkbit(const int value, const int position)
{
	return value & (1 << position);
}

int swapbit(const unsigned char value, const int firstbit, const int secondbit)
{
	if (firstbit >= 0 && secondbit >= 0)
	{
		unsigned char tmp = value;
		if ((!checkbit(tmp, firstbit) && checkbit(tmp, secondbit)) || (checkbit(tmp, firstbit) && !checkbit(tmp, secondbit)))
		{
			tmp = switchbit(tmp, firstbit);
			tmp = switchbit(tmp, secondbit);
		}
		return tmp;
	}
	return 0;
}

int bitcpy(unsigned char* source, const int number_starbit_source, const unsigned char destination, const int number_starbit_destination, const int amountbit)
{
	if (source && number_starbit_source >= 0 && number_starbit_destination >= 0)
	{
		for (int i = 0; i < amountbit; i++)
		{
			if (checkbit(destination, number_starbit_destination + i) != checkbit(*source, number_starbit_source + i))
			{
				*source = switchbit(*source, i - number_starbit_destination);
			}
		}
		return 1;
	}
	return 0;
}

unsigned char* bit_encrypt(const char* text)
{
	if (text)
	{
		size_t len = strlen(text) + 1;
		unsigned char* tmp = (unsigned char*)calloc(len, sizeof(unsigned char));
		for (int i = 0; i < len - 1; i++)
		{
			tmp[i] = text[i];
			unsigned char a = 0x0;
			unsigned char b = 0x0;
			// 1
			tmp[i] = swapbit(tmp[i], 4, 5);
			tmp[i] = swapbit(tmp[i], 6, 7);
			//2
			bitcpy(&a, 0, tmp[i], 0, 4);
			bitcpy(&b, 0, tmp[i], 4, 4);
			//3
			a ^= b; //XOR
			//4
			bitcpy(tmp + i, 0, a, 0, 4);
			bitcpy(tmp + i, 4, b, 0, 4);
		}
		tmp[len - 1] = '\0';
		return tmp;
	}
	return NULL;
}

char* bit_decrypt(const unsigned char* text)
{
	if (text)
	{
		size_t len;
		for (len = 0; text[len]; len++);
		len++;
		char* tmp = (char*)calloc(len, sizeof(char));
		for (int i = 0; i < len - 1; i++)
		{
			tmp[i] = text[i];
			unsigned char a = 0x0;
			unsigned char b = 0x0;
			//1
			bitcpy(&a, 0, tmp[i], 0, 4);
			bitcpy(&b, 0, tmp[i], 4, 4);
			//2
			a ^= b; //XOR
			//3
			bitcpy((unsigned char*)(tmp + i), 0, a, 0, 4);
			bitcpy((unsigned char*)(tmp + i), 4, b, 0, 4);
			//4
			tmp[i] = swapbit(tmp[i], 4, 5);
			tmp[i] = swapbit(tmp[i], 6, 7);
		}
		tmp[len - 1] = '\0';
		return tmp;
	}
	return NULL;
}

unsigned char* bmp_encrypt(const char* key, const char* text)
{
	char* rev = reverse(text);
	char* vig_enc = vigenere_encrypt(key, rev);
	unsigned char* b_enc = bit_encrypt(vig_enc);
	free(rev);
	free(vig_enc);
	return b_enc;
}

char* bmp_decrypt(const char* key, const unsigned char* text)
{
	char* b_dec = bit_decrypt(text);
	char* vig_dec = vigenere_decrypt(key, b_dec);
	char* rev = reverse(vig_dec);
	free(b_dec);
	free(vig_dec);
	return rev;
}

//unsigned char* bmp_encrypt(const char* key, const char* text)
//{
//	return bit_encrypt(vigenere_encrypt(key, reverse(text)));
//}
//
//char* bmp_decrypt(const char* key, const unsigned char* text)
//{
//	return reverse(vigenere_decrypt(key, bit_decrypt(text)));
//}