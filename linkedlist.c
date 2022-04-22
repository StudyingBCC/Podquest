#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#include "linkedlist.h"

void remove_newline_ch(char *line)
{
    int new_line = strlen(line) -1;
    if (line[new_line] == '\n')
        line[new_line] = '\0';
}

static int idPodcast = 1;

List startList() {
  List list = malloc(sizeof(List));

  list->curr = NULL;
  list->ini = NULL;
  list->end = NULL;
  list->shuffle = 0;
  
  for(int i = 0; i < sizeof(list->podcasts) / sizeof(Podcast); i++) {
    Podcast pdc;
    pdc.idPodcast = -1;
    list->podcasts[i] = pdc;
  }

  return list;
}

void resetList(List list) {
  list->curr = NULL;
  list->ini = NULL;
  list->end = NULL;
}

void resetCelula(Celula * celula) {
  celula->next = NULL;
  celula->prev = NULL;
}

Podcast * searchPodcast(List list, Podcast * podcast) {
  int compare; 
  for(Celula * aux = list->ini; aux != NULL; aux = aux->next) {
    compare = strcmp(aux->episode->podcast.namePodcast, podcast->namePodcast);
    if(strcmp(aux->episode->podcast.namePodcast, podcast->namePodcast) == 0) {
      return podcast;
    }
  }
  return NULL;
}

Celula * createCelula() {
  Episode * newEp = malloc(sizeof(Episode));
  Celula * newCelula = malloc(sizeof(Celula));
  Podcast podcast;

  printf("\n What is the Podcast ID: ");
  scanf("%d", &podcast.idPodcast);
  getchar();  
  
  printf("\n What is the Podcast Name: ");
  fgets(podcast.namePodcast, 64, stdin);
  remove_newline_ch(podcast.namePodcast);
  
  
  printf("\n What is the Episode Number: ");
  scanf("%d", &newEp->numberEpisode);
  getchar();
  
  printf("\n What is the Episode Name: ");
  fgets(newEp->nameEpisode, 64, stdin);
  remove_newline_ch(newEp->nameEpisode);

  
  newCelula->episode = newEp;
  podcast.idPodcast = idPodcast;
  newEp->podcast = podcast;
  
  return newCelula;
}

void add(List list) {  
  Celula * newCelula = createCelula();
  Podcast * resultSearch = searchPodcast(list, &newCelula->episode->podcast);
  
  if(resultSearch != NULL) {
    newCelula->episode->podcast = *resultSearch;
  }
  else {
    idPodcast++;
  }
  
  if(list->ini == NULL) {  
    
    list->curr = newCelula;
    list->ini = newCelula;
    list->end = newCelula;

    newCelula->prev = NULL;
    newCelula->next = NULL;


  } else {
    newCelula->prev = list->end;
    newCelula->next = NULL;
    list->end->next = newCelula;
    list->end = newCelula;
  }
  printf("\n YAYY, you add a new Episode :)\n");
}

void playCurr(List list) {

  if(list->curr != NULL) {
    printf("\n I'm in episode %s from podcast %s\n THX FOR ASKING :)", list->curr->episode->nameEpisode, list->curr->episode->podcast.namePodcast);
    
  }
  else {
    printf("\n Attention, there's no podcasts here!");
  }
}

void playNext(List list, bool shuffle) {
  
  if (list->ini != NULL) {
    if (shuffle) {
      while (true) {
        srand(time(NULL));
        int aux = rand() % sizeof(list) + 1;
           list->end->next = list->ini;
          Celula * ep = list->curr;

        for (int i = 0; i < aux; i++) {
          list->curr = list->curr->next;
        }

        if (ep != list->curr) {
          
          playCurr(list);
          return;
        }
      }
    } else {
      if (list->curr->next != NULL) {
        list->curr = list->curr->next;

        if (list->curr == list->end) {
          printf("\nIt's over darling :( We're going back to start...\n");
        }
        
        playCurr(list);
        
      } else {
        printf("\nIt's over darling :( We're going back to start...\n");

        list->curr = list->ini;

        playCurr(list);
      }
    }
    
  } else {
    printf("\n Attention, there's no podcasts here! :(");
  }
}

void showPodcasts(List list) {
  if(list->ini != NULL) {
    for(Celula * aux = list->ini; aux != NULL; aux=aux->next) {
      Episode * ep = aux->episode;
      Episode * epCurr = list->curr->episode;

      if(ep->numberEpisode == epCurr->numberEpisode && ep->podcast.idPodcast == epCurr->podcast.idPodcast) {
      printf("\n Episódio número: %d - %s, do podcast %d - %s, it's playing now\n", ep->numberEpisode, ep->nameEpisode, ep->podcast.idPodcast, ep->podcast.namePodcast);
      }
      else {
      printf("\n Episódio número: %d - %s, do podcast %d - %s\n", ep->numberEpisode, ep->nameEpisode, ep->podcast.idPodcast, ep->podcast.namePodcast);
      }
    }
  } 
  else {
    printf("\n Attention, there's no podcasts here! :(");
 } 
  
}

void remover(List list) {
 if(list) {
    
    int numberEpisode, idPodcast;
    Celula * removed;
    printf("\n What is the Episode number?: ");
    scanf("%d", &numberEpisode);
    getchar();
    printf("\n Tell me the ID of your Podcast: ");
    scanf("%d", &idPodcast);
    getchar();

    
      if(list->ini->next == NULL) {
        if(list->ini->episode->numberEpisode == numberEpisode && list->ini->episode->podcast.idPodcast) {
          removed = list->ini;
          resetList(list);
          printf("\n Episode %d from %s removed!", removed->episode->numberEpisode, removed->episode->podcast.namePodcast);
          return;
        }
      }
      else {
        for(Celula * aux = list->ini; aux != NULL; aux = aux->next){
          if(list->ini->episode->numberEpisode == numberEpisode && list->ini->episode->podcast.idPodcast == idPodcast) {
              removed = list->ini;
              list->ini = list->ini->next;
            if(list->curr->episode->numberEpisode == numberEpisode && list->curr->episode->podcast.idPodcast == idPodcast ) {
              list->curr= list->curr->next;
            }
              printf("\n Episode %d from podcast %s removed!", removed->episode->numberEpisode, removed->episode->podcast.namePodcast);
              resetCelula(removed);
            }
            
          else if(aux->next->episode->numberEpisode == numberEpisode && aux->next->episode->podcast.idPodcast == idPodcast) {
            removed= aux->next;
            aux->next = aux->next->next;
            resetCelula(removed);
            
            if(list->curr->episode->numberEpisode == numberEpisode && list->curr->episode->podcast.idPodcast == idPodcast ) {
              list->curr = list->curr->next;
            }
            printf("\n Episode %d from podcast %s removed!", removed->episode->numberEpisode, removed->episode->podcast.namePodcast);
            resetCelula(removed);
            return;
          }
        }
      }
    free(removed);
    }
  else {
    printf("\n Attention, there's no podcasts here!");
  }
}