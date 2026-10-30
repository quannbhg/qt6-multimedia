#ifndef PLAYERVIEWMODEL_H
#define PLAYERVIEWMODEL_H

#include <QObject>
#include <QString>
#include <QUrl>
#include "services/playbackservice.h"

/* ViewModel of the player page. QML reads properties and calls Q_INVOKABLE functions. */
class PlayerViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged)
    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(QString positionText READ positionText NOTIFY positionChanged)
    Q_PROPERTY(QString durationText READ durationText NOTIFY durationChanged)
    Q_PROPERTY(bool playing READ isPlaying NOTIFY playingChanged)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(bool muted READ isMuted NOTIFY mutedChanged)
    Q_PROPERTY(double playbackRate READ playbackRate WRITE setPlaybackRate NOTIFY playbackRateChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged)

public:
    explicit PlayerViewModel(PlaybackService *service, QObject *parent = nullptr);

    QString fileName() const;
    qint64 position() const;
    qint64 duration() const;
    QString positionText() const;
    QString durationText() const;
    bool isPlaying() const;
    int volume() const;
    bool isMuted() const;
    double playbackRate() const;
    QString errorMessage() const;

    void setVolume(int percent);
    void setPlaybackRate(double rate);

    Q_INVOKABLE void openFile(const QUrl &fileUrl);
    Q_INVOKABLE void togglePlayPause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void seek(qint64 positionMs);
    Q_INVOKABLE void seekForward();
    Q_INVOKABLE void seekBackward();
    Q_INVOKABLE void toggleMute();

signals:
    void fileNameChanged();
    void positionChanged();
    void durationChanged();
    void playingChanged();
    void volumeChanged();
    void mutedChanged();
    void playbackRateChanged();
    void errorMessageChanged();

private slots:
    void onStateChanged();
    void onError(const QString &message);

private:
    QString formatTime(qint64 milliseconds) const;

    PlaybackService *m_service;
    QString m_fileName;
    QString m_errorMessage;
};

#endif /* PLAYERVIEWMODEL_H */