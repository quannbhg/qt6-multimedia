#ifndef PLAYBACKSERVICE_H
#define PLAYBACKSERVICE_H

#include <QObject>
#include <QString>
#include "domain/iplaybackengine.h"

/* Playback logic: seek +-10s with clamping, volume, mute, speed.
Only knows IPlaybackEngine, not QMediaPlayer. */
class PlaybackService : public QObject {
    Q_OBJECT

    public:
        explicit PlaybackService(IPlaybackEngine *engine, QObject *parent = nullptr);

        void openFile(const QString &filePath);
        void play();
        void pause();
        void stop();
        void togglePlayPause();

        void seekTo(qint64 positionMs);
        void seekForward();
        void seekBackward();

        void setVolume(int percent);
        void toggleMute();
        void setPlaybackRate(double rate);

        int volume() const;
        bool isMuted() const;
        double playbackRate() const;
        qint64 position() const;
        qint64 duration() const;
        PlaybackState state() const;
        QString currentFilePath() const;

    signals:
        void positionChanged(qint64 positionMs);
        void durationChanged(qint64 durationMs);
        void stateChanged(PlaybackState state);
        void errorOccurred(const QString &message);
        void volumeChanged(int percent);
        void mutedChanged(bool muted);
        void playbackRateChanged(double rate);
        void fileChanged(const QString &filePath);

    private:
        static const qint64 SEEK_STEP_MS = 10000;

        IPlaybackEngine *m_engine;
        QString m_currentFilePath;
        int m_volume;
        bool m_muted;
        double m_playbackRate;
};

#endif /* PLAYBACKSERVICE_H */