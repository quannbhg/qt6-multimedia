#ifndef PLAYBACKSTATE_H
#define PLAYBACKSTATE_H

/* State of the player */
typedef enum {
    PlaybackStopped = 0,
    PlaybackPlaying,
    PlaybackPaused
} PlaybackState;

#endif /* PLAYBACKSTATE_H */