#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int valueArrayLen = 10;

char isNumber(char *str)
{
	for (int i = 0;str[i] != '\0';i++){
		if (48 > str[i] ||  57 < str[i] || str[i] == '-')
		{
			return 0;
		}
	}
	return 1;
}

// get strings lenght
int strLen(char* str)
{
	int len = 0;
	while(str[len]){len++;}
	return len;
}

// check if strings are equal
char strEq(char *word1,char *word2)
{
	int len1 = 0;
	int len2 = 0;
	while (word1[len1] != '\0'){
		len1++;
	}
	while (word2[len2] != '\0'){
		len2++;
	}
	if (len1 != len2){
		return 0;
	}
	for (int i = 0;i < len1;i++){
		if (word1[i] != word2[i]){
			return 0;
		}
	}
	
	return 1;
}

void updateIntArrayValue(int *values, int *positions, int pos,int newValue)
{
	int num;
	for (int i = 0; i < valueArrayLen; i++ )
	{
		if (positions[i] == pos)
		{
			values[i] = newValue;
		}
	}
}

int strToInt(char* str)
{
	int i = 0;
	int num = 0;
	char isNeg = 0;
	if (str[i] == '-'){
		i++;
		isNeg = 1;
	}
	for (i;str[i];i++){
		if (48 > str[i] ||  57 < str[i])
		{
			return 0;
		}
	}

	for (int j = i-1; j >= isNeg ;j--)
	{
		int exp = 1;
		for (int k = 0; k < i-j-1;k++){exp *= 10;}
		num += (str[j]-48)*exp;
	}
	if (isNeg){
		return -num;
	}else{
		return num;
	}
}

int fromIntArray(int intValue[valueArrayLen], int intPosition[valueArrayLen], int pos)
{
	int num;
	for (int i = 0; i < valueArrayLen; i++ )
	{
		if (intPosition[i] == pos)
		{
			num = intValue[i];
		}
	}
	return num;
}

// get strings nTh word
char* nThWord(unsigned char *originalWord, int word)
{
	char *parsedWord;
	char isOther = 0;
	int spaceCount = 0;
	int count = 0;
	int isQuote = 0;
		
	parsedWord = (char *)malloc(sizeof(char));
	
	for (int i = 0;originalWord[i] != '\0';i++)
	{
		if (isOther && word == spaceCount){
			while (originalWord[i] != '\0' && (originalWord[i] != ' ' || isQuote))
			{
				if (originalWord[i] == '"'){
					if (isQuote){
						isQuote = 0;
					}else{
						isQuote = 1;
					}
				}
				parsedWord[count] = originalWord[i];
				i++;
				count++;
			}
			return parsedWord;
		}
		if (isOther && originalWord[i] == ' ') spaceCount++;
		if (!isOther && originalWord[i] != '\t' && originalWord[i] != ' '){
			isOther = 1;
			i--;
		}
	}
	return "";
}

void print(char *firstWord, char *line, int *intValue, int *intPosition){
	char *secondWord = nThWord(line,1);
	if (secondWord[0] == '"'){
		printf("%s", secondWord);
	}
	else if (strEq(secondWord, "int")){
		printf("%d", fromIntArray(intValue, intPosition, strToInt(nThWord(line,2)) ));

	}

	if (strEq(firstWord, "printl"))
	{
		printf("\n");
	}
}

void update(char *line, int *intValue, int *intPosition){
	char *secondWord = nThWord(line,1);
	if (strEq(secondWord, "int"))
	{
		char *fifthWord = nThWord(line,4);
		char *fourthWord = nThWord(line,3);
		char *thirdWord = nThWord(line,2);
			
		if (strEq(fifthWord, ""))
		{
			updateIntArrayValue(intValue, intPosition, strToInt(thirdWord), strToInt(fourthWord));
		}
		else if (strEq(fourthWord, "int"))
		{
			int num1 = fromIntArray(intValue, intPosition, strToInt(nThWord(line,4)));
			int num2 = 0;
			if (strEq(nThWord(line,5), "+")){
				if (strEq(nThWord(line,6), "int")){
					num2 = fromIntArray(intValue, intPosition, strToInt(nThWord(line,7)));
				}
				else
				{
					num2 = strToInt(nThWord(line,6));
				}
				updateIntArrayValue(intValue, intPosition, strToInt(thirdWord), num1 + num2);
			}
			else if (strEq(nThWord(line,5), "-")){
				if (strEq(nThWord(line,6), "int")){
					num2 = fromIntArray(intValue, intPosition, strToInt(nThWord(line,7)));
				}
				else
				{
					num2 = strToInt(nThWord(line,6));
				}
				updateIntArrayValue(intValue, intPosition, strToInt(thirdWord), num1 - num2);
			}
			else if (strEq(nThWord(line,5), "*")){
		if (strEq(nThWord(line,6), "int")){
			num2 = fromIntArray(intValue, intPosition, strToInt(nThWord(line,7)));
		}
		else
		{
			num2 = strToInt(nThWord(line,6));
		}
				updateIntArrayValue(intValue, intPosition, strToInt(thirdWord), num1 * num2);
			}
			else if (strEq(nThWord(line,5), "/")){
				if (strEq(nThWord(line,6), "int")){
					num2 = fromIntArray(intValue, intPosition, strToInt(nThWord(line,7)));
				}
				else
				{
					num2 = strToInt(nThWord(line,6));
				}
				updateIntArrayValue(intValue, intPosition, strToInt(thirdWord), num1 / num2);
			}
		}
	}
}

int main(int argc, char **argv)
{
	unsigned char *data;
	FILE *fileR = fopen(argv[1], "rb");

	if (fileR == NULL)
	{
		printf("Cannot open file \033[31m%s\033[0m\n", argv[1]);
		return 0;
	}
	fseek(fileR, 0, SEEK_END);
	unsigned long length = ftell(fileR);
	fseek(fileR, 0, SEEK_SET);
	data = (char *)malloc(length*sizeof(data)+1);
	int fileReturn = fread(data, 1, length, fileR);

	int intCount = 0;
	int intValue[valueArrayLen];
	int intPosition[valueArrayLen];

	unsigned char lines[500][100];
	int pos = 0;
	int lineCount = 0;

	unsigned long num = 0;
	for (unsigned long i = 0; i < length;i++)
	{
		if (data[i] == '\n' && data[i+1] != '\n' && data[i + 1] != '\0')
		{
			num++;
		}
	}
	num++;

	for (unsigned long i = 0; i < length;i++)
	{
		pos++;
		if (data[i] != '\n')
		{
		  	lines[lineCount][pos-1] = data[i];
		}else{
		 	pos = 0;
			if (!(lineCount != 0 && data[i-1] == '\n')){
		 		lineCount++;
			}
		}
	}

	for (int i = 0; i < lineCount;i++)
	{
		char *firstWord = nThWord(lines[i],0);

		// Printing
		if (strEq(firstWord, "print") || strEq(firstWord, "printl"))
		{
			print(firstWord, lines[i], intValue, intPosition);
		}

		// Making new variable
		else if (strEq(firstWord, "new"))
		{
			char *secondWord = nThWord(lines[i],1);
			if (strEq(secondWord, "int"))
			{
				intPosition[intCount] = strToInt(nThWord(lines[i],2));
				intValue[intCount] = strToInt(nThWord(lines[i],3));
				intCount++;
			}
		}

		// Updating old variables
		else if (strEq(firstWord, "update"))
		{
			update(lines[i], intValue, intPosition);

		}

		// If statemenet
		else if (strEq(firstWord, "if"))
		{
			char *secondWord = nThWord(lines[i],1);
			char *thirdWord = nThWord(lines[i],2);
			if (strEq(secondWord, "int"))
			{
				if (fromIntArray(intValue, intPosition, strToInt(thirdWord)) == 0)
				{
					int howManyIf = 1;
					i++;

					while ((i < lineCount) && (howManyIf > 0))
					{
						if (strEq(nThWord(lines[i],0),"if")){howManyIf++;};
						if (strEq(nThWord(lines[i],0),"endif")){howManyIf--;};
						//printf("i: %d, %d, %d, %s\n",i,lineCount,howManyIf,lines[i]);
						i++;
					}
					i--;
				}
			}
			else
			{
				if (strToInt(secondWord) == 0)
				{
					int howManyIf = 1;
					i++;

					while ((i < lineCount) && (howManyIf > 0))
					{
						if (strEq(nThWord(lines[i],0),"if")){howManyIf++;};
						if (strEq(nThWord(lines[i],0),"endif")){howManyIf--;};
						i++;
					}
					i--;
				}

			}
		}
		else if (strEq(firstWord, "endif")){
		}
		else
		{
			printf("Unknown keyword: \"%s\" at line %d\n", firstWord, i+1);
		}
	}
}
