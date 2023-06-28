#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


char*read_line(FILE *file){
	int size = 0;
	int capacity = 16;
	char *buffer = malloc(capacity);
	char c;

	while((c = fgetc(file)) != EOF && c != '\n'){
		if(size == capacity){
			size *= 2;
			char *temp = realloc(buffer, size + 2);
			if(!temp){
				free(buffer);
				return "dopici";
			}
			buffer = temp;
		}
		buffer[size++] = c;
	}
	buffer[size] = '\0';
	return buffer;
}
bool contains(char *haystack, char needle){
	for(int i = 0; i < 5; i++){
		if(haystack[i] == needle){
			return true;
		}
	}
	return false;
}
bool is_candidate(char green[5], char yellow[5], char black[20], char *line){
	for (int i = 0; i < 5; i++){
		if (green[i] != '-' && line[i] != green[i]){
			return false;
		}
		if (yellow[i] != '-' && !contains(line, yellow[i])){
			return false;
		}
		if (black[i] != '-' && contains(line, black[i])){
			return false;
		}
	}
	return true;
}

void solve(char green[5], char yellow[5], char black[20]){
	FILE *all_words = fopen("all_wordle_words.txt", "r");
	FILE *output = fopen("solution.txt", "w");

	if(!all_words || !output){
		printf("fail\n");
		return;
	}
	char *line = NULL;

	while(!feof(all_words)){
		line = read_line(all_words);
        if (!is_candidate(green, yellow, black, line)){
            free(line);
            continue;
        }
		fwrite(line, strlen(line), 1, output);
		fwrite("\n", 1, 1, output);
		free(line);
	}
	fclose(all_words);
	fclose(output);
	printf("Solution generated in solution.txt\n");
}

int main(void){
	char green[5];
	char c;
	int inputed = 0;
	printf("Input known letter or '-':");
	while(inputed != 5){
		if((c = getchar()) != '\n'){
			green[inputed] = c;
			inputed++;
		}
	}
	char yellow[5];
	inputed = 0;
	printf("\n\nInput yellow letters or '-' to end prompt:");
	while(inputed != 5){
		if((c = getchar()) != '\n'){
			yellow[inputed] = c;
			inputed++;
		}
		if (c == '-'){
			break;
		}
	}
	while (inputed != 5){
		yellow[inputed] = '-';
		inputed++;
	}
	char black[20];
	inputed = 0;
	printf("\n\nInput black letters or '-' to end prompt:");
	while ((c = getchar() != '-')){
		black[inputed] = c;
		inputed++;
	}
	while (inputed != 20){
		black[inputed] = '-';
		inputed++;
	}
	while((c = getchar()) != 'n'){
		printf("\n\nDo you wish to continue? If so input *y*, if no input *n*\n");
		if(c == 'y'){
			printf("Solving..\n");
			solve(green, yellow, black);
			return 0;
		}
	}
	return 1;
}
