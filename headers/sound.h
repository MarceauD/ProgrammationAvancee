#ifndef SOUND_H
#define SOUND_H

#include "SDL.h"

#define AUDIO_FREQ_DEFAULT 22050
#define AUDIO_CHANNELS_STEREO 2
#define AUDIO_SAMPLES_DEFAULT 4096
#define RECORD_START_POS 0
#define NB_RECORDS 1

enum Sound{
    SOUND_NONE = 0,
};

struct Record{
    Uint8* recordData;
    Uint32 recordLen;
    Uint32 recordPos;
};

typedef struct Record Record
struct RecordArray{
    Record* records;
    int currentRecordID;
};
typedef struct RecordArray RecordArray


/*Return the default desired audio configuration*/
extern SDL_AudioSpec defaultSpec();

/* Create an empty record*/
extern Record defaultRecord();

/*Create the empty array of NB_RECORDS Record freeRecords has to be called once for every call of this*/
extern void defaultRecords();

/*Load a single sound based on the path and the desired specifications*/

extern Record loadRecord(const char* path, SDL_AudioSpec spec);
/* Load all the Record of the game and initiate the audio specification*/
extern void loadRecords();

/*Initiate the desired specification based on the default specification and the computer*/
extern SDL_AudioSpec initSpec();

/*Play a record using the record name*/
extern void playRecord(int recordID);

/*Update the audio:Pause the audio at the end of a record*/
extern void updateAudio();

extern Record* getCurrentRecord(RecordArray array);

extern void quitAudio();
extern void freeRecord(Record* rec);
extern void freeRecords();
#endif //SOUND_H
