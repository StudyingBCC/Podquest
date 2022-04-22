typedef struct keyWord {
  char keyWords[64];
  struct keyWord *next;
  struct keyWord *prev;

} KeyWord;

typedef struct keyWords {
  KeyWord *ini;
  KeyWord *end;

} KeyWords;

typedef struct podcast {
  char namePodcast[64];
  int idPodcast;
  
}Podcast;

typedef Podcast *Podquest;

typedef struct Episode {
  Podcast podcast;

  char nameEpisode[64];
  int numberEpisode;

} Episode;

typedef struct Celula {
  struct Celula * next;
  struct Celula * prev;

  Episode * episode;
} Celula;

typedef struct Head {
  Podcast podcasts[64];
  Celula * curr;
  Celula * ini;
  Celula * end;
  int shuffle;

} Head;
typedef Head * List;

void remove_newline_ch(char *line);

List startList();

void add(List list);

void playCurr(List list);

void playNext(List list, bool shuffle);

void remover(List list);

void showPodcasts(List list);

void resetList(List list);