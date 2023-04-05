#ifndef _VAD_H
#define _VAD_H
#include <stdio.h>

/* TODO: add the needed states */
typedef enum
{
   ST_UNDEF = 0,
   ST_SILENCE,
   ST_VOICE,
   ST_INIT,
   ST_MV,
   ST_MS
} VAD_STATE;

/* Return a string label associated to each state */
const char *state2str(VAD_STATE st);

/* TODO: add the variables needed to control the VAD 
   (counts, thresholds, etc.) */

typedef struct
{
   VAD_STATE state;
   float sampling_rate;
   unsigned int frame_length;
   float last_feature; /* for debuggin purposes */
   float p1, alpha1, alpha2, k0, k1, k2;
   unsigned int counter_init, counter_N, min_back_voice_counter, frames_mv, frames_ms, fr_und;
} VAD_DATA;

/* Call this function before using VAD: 
   It should return allocated and initialized values of vad_data
   sampling_rate: ... the sampling rate */
   
VAD_DATA *vad_open(float sampling_rate, int number_init, float alpha1, float alpha2, int frames_mv, int frames_ms);

/* vad works frame by frame.
   This function returns the frame size so that the program knows how
   many samples have to be provided */
unsigned int vad_frame_size(VAD_DATA *);

/* Main function. For each 'time', compute the new state 
   It returns:
    ST_UNDEF   (0) : undefined; it needs more frames to take decission
    ST_SILENCE (1) : silence
    ST_VOICE   (2) : voice
    x: input frame
       It is assumed the length is frame_length */
VAD_STATE vad(VAD_DATA *vad_data, float *x);

/* Free memory
   Returns the state of the last (undecided) states. */
VAD_STATE vad_close(VAD_DATA *vad_data, VAD_STATE state);

/* Print actual state of vad, for debug purposes */
void vad_show_state(const VAD_DATA *, FILE *);

#endif