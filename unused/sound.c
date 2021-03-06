#include "../headers/sound.h"


//static Record* records;
//int currentRecordID;

static RecordArray recordsArray;

void audioCallback(void* userdata, Uint8* stream, int len){
    Record* curRecord = getCurrentRecord(recordsArray);
    if (curRecord->recordLen == 0){
        return;
    }
    Uint32 audioLen = (curRecord->recordLen - curRecord->recordPos > len ? len : curRecord->recordLen - curRecord->recordPos);
    memcpy(stream, curRecord->recordData + curRecord->recordPos, audioLen);
    //printf("%u\n",audioLen);
    curRecord->recordPos += audioLen;
}


SDL_AudioSpec defaultSpec(){
    SDL_AudioSpec spec;

    spec.freq = 44100;
    spec.format = AUDIO_S16;
    spec.callback = &audioCallback;
    spec.channels = 2;
    spec.samples = 1024;
    spec.userdata = NULL;

    return spec;
}

Record defaultRecord(){
    Record rec;
    rec.recordData = NULL;
    rec.recordLen = 0;
    rec.recordPos = 0;
    return rec;
}

void defaultRecords(){
    recordsArray.records = (Record*)malloc(sizeof(Record)*NB_RECORDS);
    unsigned int i;
    for (i = 0;i<NB_RECORDS;i++){
        recordsArray.records[i] = defaultRecord();
    }
}

Record loadRecord(const char* path, SDL_AudioSpec spec){
    Record rec;
    rec = defaultRecord();
    SDL_AudioSpec fileSpec;
    SDL_AudioCVT cvt;
    if (!SDL_LoadWAV(path, &fileSpec, &rec.recordData, &rec.recordLen)){
        printf("Error: at loadRecord: Could not load audio record \"%s\": %s",path,SDL_GetError());
        return defaultRecord();
    }
    if (SDL_BuildAudioCVT(&cvt,fileSpec.format,fileSpec.channels,fileSpec.freq,spec.format,spec.channels,spec.freq) < 0){
        printf("Error: at loadRecord: Could not create audio converter: %s",SDL_GetError());
        return defaultRecord();
    }

    cvt.buf = malloc(rec.recordLen * cvt.len_mult);
    cvt.len = rec.recordLen;
    memcpy(cvt.buf, rec.recordData, rec.recordLen);

    SDL_FreeWAV(rec.recordData);

    if (SDL_ConvertAudio(&cvt) < 0){
        printf("Error: at loadRecord: Could convert record: %s",SDL_GetError());
        return defaultRecord();
    }

    rec.recordLen = cvt.len_cvt;
    rec.recordData = malloc(cvt.len_cvt);
    memcpy(rec.recordData, cvt.buf, rec.recordLen);
    free(cvt.buf);

    return rec;
}

void loadRecords(){
    SDL_AudioSpec spec;
    spec = initSpec();
    recordsArray.currentRecordID = 0;
    defaultRecords();
}

SDL_AudioSpec initSpec(){
    SDL_AudioSpec wantedAudioSpec, audioSpec;
    wantedAudioSpec = defaultSpec();
    if (SDL_OpenAudio(&wantedAudioSpec,&audioSpec) < 0){
        return defaultSpec();
    }
    return audioSpec;
}

void playRecord(int recordName){
    if (!recordsArray.records){
        printf("Error: at playRecord: Undefined records\n");
        return;
    }
    recordsArray.currentRecordID = recordName-1;
    getCurrentRecord(recordsArray)->recordPos = 0;
    SDL_PauseAudio(0);
}

void updateAudio(){
    if (!recordsArray.records){
        printf("Error: at updatedAudio: Undefined records\n");
        return;
    }
    if (getCurrentRecord(recordsArray)->recordPos >= getCurrentRecord(recordsArray)->recordLen){
        SDL_PauseAudio(1);
    }
}

Record* getCurrentRecord(RecordArray array){
    if (!array.records){
        printf("Error: at getCurrentRecord: Undefined records\n");
        return NULL;
    }
    return &array.records[array.currentRecordID];
}

void freeRecords(){
    SDL_PauseAudio(1);
    unsigned int i;
    if (!recordsArray.records){
        return;
    }
    for (i = 0; i<NB_RECORDS;i++){
        freeRecord(&recordsArray.records[i]);
    }
    free(recordsArray.records);
    recordsArray.records = NULL;
}

void freeRecord(Record* rec){
    if (!rec){
        return;
    }
    SDL_FreeWAV(rec->recordData);
}

void quitAudio(){
    SDL_PauseAudio(1);
    freeRecords();
    SDL_CloseAudio();
}

