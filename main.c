/*
  @author : Ylony
  @date : 26/09/2016
  @name : Pendu
  @description : Jeu du pendu
  @LastEdit : 04/10/2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 

const char WordList[] = "liste.txt";
const int mincount = 1;
int max_try = 10;

int p_random(int mincount , int wordcount){
	return rand()%(wordcount-mincount) +mincount;
}

void addword(){

}

void delword(){

}

int my_strlen(char *word){
	int i = 0;
	while(word[i] != 0){
		i++;
	}
	return i;
}

void PickAWord(char *word, int rand){
  FILE* list = NULL;
  list = fopen(WordList, "r");
  int i = 0;
  if(list != NULL){
 	while(i < rand){
 		fgets(word, 20, list);
 		i++;
 	}
 	printf("%s\n", word);
    fclose(list);
  }
  else{
    printf("Can't open the wordlist");
  }
}

int CountWord(){
  FILE* list = NULL;
  int i = 0;
  char lign[20];
  list = fopen(WordList, "r");
  if(list != NULL)
  {
    while(fgets(lign, 20, list) != NULL){
    	i++;
    }
    fclose(list);
    return i;
  }
  else{
    printf("Can't open the wordlist");
    return 0;
  } 
}

void build(char char_g, char *word, char guess[]){
	if (char_g == ' '){

	}
	else{
		int i = 0;
		while(word[i] != 0){
			if(word[i] == ' '){
				guess[i] = word[i];
			}
			if(word[i] != char_g){
				i++;
			}
			else{
				guess[i] = word[i];
				i++;
			}
		}
	}
}

void fill(char *guess, char c, int nb){
	int i = 0;
	while(i<nb-1){
		guess[i] = c;
		i++;
	}
	guess[i] = '\0';
}

int check(char guess[], char word[], char c, int count){
	int i = 0;
	while(i<count){
		if(guess[i] == c)
			return -1;
		i++;
	}
	return 0;
}

void hint(char guess[], char word[], int count){
	int random;
	char tobuild;
	random = p_random(mincount, 5);
	tobuild = word[random];
	build(tobuild, word, guess);
	printf("%s\n", guess);
}

void IntGame(char *KeepGame){
  char word[20] = {0};
  char *guess = NULL;
  char char_g;
  int nb_char;
  int check2;
  PickAWord(word, p_random(mincount, CountWord()));
  nb_char = my_strlen(word);
  guess = malloc(nb_char * sizeof(char));
  fill(guess, '*', nb_char);
  hint(guess, word, my_strlen(word));
  while(max_try != 0)
 	{
  		printf("Donner une lettre : \n");
  		scanf("%c%*c", &char_g);
  		build(toupper(char_g), word, guess);
  		printf("%s\n", guess);
  		max_try--;
  		check2 = check(guess, word, '*', my_strlen(word));
  		if(check2 == 0){
  			printf("Bien joué !\n");
  			break;
  		}
  		if(max_try == 0){
  			printf("Perdu !\n");
  		}
  		else{
  			printf("Il vous reste %d coups ! \n", max_try);
  		}
	}
  printf("Le mot était %s\n", word);
  printf("Voulez vous continuer à jouer ? (O/N) \n");
  max_try = 10;
  scanf("%c%*c", KeepGame);
}

int main(){
  char KeepGame = 'O';
  while (KeepGame == 'O'){
    IntGame(&KeepGame);
  }
  return 0;
}
