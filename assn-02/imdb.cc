using namespace std;
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "imdb.h"

const char *const imdb::kActorFileName = "actordata";
const char *const imdb::kMovieFileName = "moviedata";

imdb::imdb(const string& directory)
{
  const string actorFileName = directory + "/" + kActorFileName;
  const string movieFileName = directory + "/" + kMovieFileName;
  
  actorFile = acquireFileMap(actorFileName, actorInfo);
  movieFile = acquireFileMap(movieFileName, movieInfo);
}

bool imdb::good() const
{
  return !( (actorInfo.fd == -1) || 
	    (movieInfo.fd == -1) ); 
}

// you should be implementing these two methods right here... 
bool imdb::getCredits(const string& player, vector<film>& films) const {
  int numActors = *(int*) actorFile; 
  int firstOffset = 0;
  int lastOffset = numActors - 1; 
  int middle = 0;
  int offset = 0;
  while (firstOffset <= lastOffset) {
    middle = (firstOffset + lastOffset) / 2;
    offset = *(int*)((char*)actorFile + sizeof(int) + middle * sizeof(int)); 
    char* curName = (char*)actorFile + offset;
    if (curName < player) {
      firstOffset = middle + 1; 
    } 
    else if (curName > player) {
      lastOffset = middle - 1; 
    } 
    else break; 
  }
  if (firstOffset > lastOffset) return false;
  int actorLength = player.size();
  if(player.size() % 2 == 0){
     actorLength += 2;
  }
  else actorLength += 1;
  short numMovies = *(short *)((char * ) actorFile + offset + actorLength);
  int moviesOffsets = actorLength;
  if((actorLength + 2) % 4 != 0) moviesOffsets += 2;
  for (int i = 0; i < numMovies; i++) {
    int curOffset = *(int*)((char*)actorFile + offset + moviesOffsets + 2 + i * sizeof(int));
    string movie = (char * ) (movieFile) + curOffset;
    char y = *(char *)((char *) movieFile + curOffset + movie.size() + 1);
    int year = (int) y;
    year += 1900;
    film f;
    f.title = movie;
    f.year = year;
    films.push_back(f);
  }
  return true;
}

bool imdb::getCast(const film& movie, vector<string>& players) const {
  int numMovies = *(int *) movieFile;
  int firstOffset = 0;
  int lastOffset = numMovies - 1; 
  int middle = 0;
  int offset = 0;
  while(firstOffset <= lastOffset) {
    middle = (firstOffset + lastOffset) / 2;
    offset = *(int *)((char *)movieFile + sizeof(int) + middle * sizeof(int));
    char* s = (char*) movieFile + offset; 
    string curMovieTitle = s;
    char year = *(char *)((char *)movieFile + offset + curMovieTitle.size() + 1);
    film curMovie;
    curMovie.title = curMovieTitle;
    curMovie.year = (int)year + 1900;
    if(curMovie < movie){
      firstOffset = middle + 1;
    }
    else if(movie < curMovie){
      lastOffset = middle - 1;
    }
    else break;
  }
  if(firstOffset > lastOffset)  return false;
  
  int numActorOffset = movie.title.size() + 2;
  if(numActorOffset % 2 != 0) numActorOffset += 1;
  short nActors = *(short *) ((char*) movieFile + offset + numActorOffset);
  numActorOffset += 2;
  if((numActorOffset) % 4 != 0) numActorOffset += 2;
  for(int i = 0; i < nActors; i++){
    int curActorOffset = *(int *)((char *) movieFile + offset + numActorOffset + i * sizeof(int)); 
    string name = (char * ) (actorFile) + curActorOffset;
    players.push_back(name);
  }
  return true;
}

imdb::~imdb()
{
  releaseFileMap(actorInfo);
  releaseFileMap(movieInfo);
}

// ignore everything below... it's all UNIXy stuff in place to make a file look like
// an array of bytes in RAM.. 
const void *imdb::acquireFileMap(const string& fileName, struct fileInfo& info)
{
  struct stat stats;
  stat(fileName.c_str(), &stats);
  info.fileSize = stats.st_size;
  info.fd = open(fileName.c_str(), O_RDONLY);
  return info.fileMap = mmap(0, info.fileSize, PROT_READ, MAP_SHARED, info.fd, 0);
}

void imdb::releaseFileMap(struct fileInfo& info)
{
  if (info.fileMap != NULL) munmap((char *) info.fileMap, info.fileSize);
  if (info.fd != -1) close(info.fd);
}
