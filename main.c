#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "linkedlist.h"

int main(void){
  printf("\n\tWelcome to our Podquest");

  int option;
  bool shuffle = false;
  List list = startList();

 do{
    printf("\n\n Your options are:\n\n 0 - Leave\n 1 - Play\n 2 - Play Next Episode\n 3 - Add Podcast\n 4 - Shuffe\n 5 - Remove\n 6 - Show Podcasts\n\n Choose one: ");
    
    scanf("%d", &option);
  switch(option){
    case 0:
      printf("\n See You Later, Alligator!\n After A While, Crocodile!\n THX!! BYEE!!!");
      return 0;
      break;
    
    //Play
    case 1: 
      playCurr(list);
      break;

    //Play next
    case 2:
      playNext(list, shuffle);
      break;

    //Add
    case 3:
      add(list);
      break;

    //Shuffle
    case 4: 
      if (shuffle) {
          printf("\nShuffle off!\n");
          shuffle = false;
        } else {
          printf("\nShuffle on!\n");
          shuffle = true;
        }
      break; 

    //Remove
    case 5:
      remover(list);
      break;
    
    //ShowPodcast
    case 6:
      showPodcasts(list);
      break;
    
    default:
      if(option != 0)
        printf("\t\nThis option doesn't exist, sorry!\n Please try again...");
    }
  } while(option != 0);
    free(list);
  return 0;
}
