#ifndef QTPLAYBACKENGINE_H
#define QTPLAYBACKENGINE_H

#include <QMediaPlayer>
#include <QAudioOutput>
#include "domain/iplaybackengine.h"


class QtPlaybackEngine : public IPlaybackEngine {
    Q_OBJECT

    public:
        explicit QtPlaybackEngine(QObject *parent = nullptr);

        void setSource(const QString &filePath) override;
        void play() override;
        void pause() override;
        void stop() override;
        void setPosition(qint64 positionMs) override;
        void setVolume(int percent) override;
        void setMuted(bool muted) override;
        void setPlaybackRate(double rate) override;

        qint64 position() const override;
        qint64 duration() const override;
        PlaybackState state() const override;
    
    private slots:
        void onPlayerStateChanged();
        void onPlayerError(QMediaPlayer::Error error, const QString &errorString);
    
    private:
        QMediaPlayer *m_player;
        QAudioOutput *m_audioOutput;

};
#endif /* QTPLAYBACKENGINE_H */