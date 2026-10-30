#ifndef IPLAYBACKENGINE_H
#define IPLAYBACKENGINE_H

#include <QObject>
#include <QString>
#include "domain/playbackstate.h"

/* Interface of a player. Services only know this class,
not QMediaPlayer. All times are in milliseconds. */
class IPlaybackEngine : public QObject {
    Q_OBJECT

    public:
        explicit IPlaybackEngine(QObject *parent = nullptr) : QObject(parent) {}
        virtual ~IPlaybackEngine() {}

        virtual void setSource(const QString &filePath) = 0;
        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;
        virtual void setPosition(qint64 positionMs) = 0;
        virtual void setVolume(int percent) = 0;          /* 0..100 */
        virtual void setMuted(bool muted) = 0;
        virtual void setPlaybackRate(double rate) = 0;    /* 1.0 = normal */

        virtual qint64 position() const = 0;
        virtual qint64 duration() const = 0;
        virtual PlaybackState state() const = 0;

    signals:
        void positionChanged(qint64 positionMs);
        void durationChanged(qint64 durationMs);
        void stateChanged(PlaybackState state);
        void errorOccurred(const QString& message);
};

#endif /* IPLAYBACKENGINE_H */