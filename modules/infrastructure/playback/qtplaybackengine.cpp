#include "infrastructure/qtplaybackengine.h"
#include <QUrl>

QtPlaybackEngine::QtPlaybackEngine(QObject *parent)
    : IPlaybackEngine(parent)
{
    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_player->setAudioOutput(m_audioOutput);

    /* Forward signals of QMediaPlayer to signals of IPlaybackEngine. */
    connect(m_player, &QMediaPlayer::positionChanged,
            this, &IPlaybackEngine::positionChanged);
    connect(m_player, &QMediaPlayer::durationChanged,
            this, &IPlaybackEngine::durationChanged);

    connect(m_player, &QMediaPlayer::playbackStateChanged,
            this, &QtPlaybackEngine::onPlayerStateChanged);
    connect(m_player, &QMediaPlayer::errorOccurred,
            this, &QtPlaybackEngine::onPlayerError);
}

void QtPlaybackEngine::setSource(const QString &filePath)
{
    m_player->setSource(QUrl::fromLocalFile(filePath));
}

void QtPlaybackEngine::play()
{
    m_player->play();
}

void QtPlaybackEngine::pause()
{
    m_player->pause();
}

void QtPlaybackEngine::stop()
{
    m_player->stop();
}

void QtPlaybackEngine::setPosition(qint64 positionMs)
{
    m_player->setPosition(positionMs);
}

void QtPlaybackEngine::setVolume(int percent)
{
    /* QAudioOutput uses 0.0 .. 1.0 */
    m_audioOutput->setVolume(percent / 100.0f);
}

void QtPlaybackEngine::setMuted(bool muted)
{
    m_audioOutput->setMuted(muted);
}

void QtPlaybackEngine::setPlaybackRate(double rate)
{
    m_player->setPlaybackRate(rate);
}

qint64 QtPlaybackEngine::position() const
{
    return m_player->position();
}

qint64 QtPlaybackEngine::duration() const
{
    return m_player->duration();
}

PlaybackState QtPlaybackEngine::state() const
{
    PlaybackState result = PlaybackStopped;

    switch (m_player->playbackState()) {
    case QMediaPlayer::PlayingState:
        result = PlaybackPlaying;
        break;
    case QMediaPlayer::PausedState:
        result = PlaybackPaused;
        break;
    case QMediaPlayer::StoppedState:
        result = PlaybackStopped;
        break;
    }
    return result;
}

void QtPlaybackEngine::onPlayerStateChanged()
{
    emit stateChanged(state());
}

void QtPlaybackEngine::onPlayerError(QMediaPlayer::Error error, const QString &errorString)
{
    Q_UNUSED(error);
    emit errorOccurred(errorString);
}