#include "viewmodels/playerviewmodel.h"
#include <QFileInfo>

PlayerViewModel::PlayerViewModel(PlaybackService *service, QObject *parent)
    : QObject(parent)
    , m_service(service)
{
    /* Signals that carry no data: just tell QML "something changed". */
    connect(m_service, &PlaybackService::positionChanged,
            this, &PlayerViewModel::positionChanged);
    connect(m_service, &PlaybackService::durationChanged,
            this, &PlayerViewModel::durationChanged);
    connect(m_service, &PlaybackService::volumeChanged,
            this, &PlayerViewModel::volumeChanged);
    connect(m_service, &PlaybackService::mutedChanged,
            this, &PlayerViewModel::mutedChanged);
    connect(m_service, &PlaybackService::playbackRateChanged,
            this, &PlayerViewModel::playbackRateChanged);

    /* Signals that need extra work in a slot. */
    connect(m_service, &PlaybackService::stateChanged,
            this, &PlayerViewModel::onStateChanged);
    connect(m_service, &PlaybackService::errorOccurred,
            this, &PlayerViewModel::onError);
}

QString PlayerViewModel::fileName() const
{
    return m_fileName;
}

qint64 PlayerViewModel::position() const
{
    return m_service->position();
}

qint64 PlayerViewModel::duration() const
{
    return m_service->duration();
}

QString PlayerViewModel::positionText() const
{
    return formatTime(m_service->position());
}

QString PlayerViewModel::durationText() const
{
    return formatTime(m_service->duration());
}

bool PlayerViewModel::isPlaying() const
{
    return m_service->state() == PlaybackPlaying;
}

int PlayerViewModel::volume() const
{
    return m_service->volume();
}

bool PlayerViewModel::isMuted() const
{
    return m_service->isMuted();
}

double PlayerViewModel::playbackRate() const
{
    return m_service->playbackRate();
}

QString PlayerViewModel::errorMessage() const
{
    return m_errorMessage;
}

void PlayerViewModel::setVolume(int percent)
{
    m_service->setVolume(percent);
}

void PlayerViewModel::setPlaybackRate(double rate)
{
    m_service->setPlaybackRate(rate);
}

void PlayerViewModel::openFile(const QUrl &fileUrl)
{
    /* QML gives a URL like file:///D:/a.mp3; convert it to D:/a.mp3 */
    QString path = fileUrl.toLocalFile();

    if (path == "") {
        return;
    }

    m_errorMessage = "";
    emit errorMessageChanged();

    m_service->openFile(path);

    QFileInfo info(path);
    m_fileName = info.fileName();
    emit fileNameChanged();

    m_service->play();
}

void PlayerViewModel::togglePlayPause()
{
    m_service->togglePlayPause();
}

void PlayerViewModel::stop()
{
    m_service->stop();
}

void PlayerViewModel::seek(qint64 positionMs)
{
    m_service->seekTo(positionMs);
}

void PlayerViewModel::seekForward()
{
    m_service->seekForward();
}

void PlayerViewModel::seekBackward()
{
    m_service->seekBackward();
}

void PlayerViewModel::toggleMute()
{
    m_service->toggleMute();
}

void PlayerViewModel::onStateChanged()
{
    emit playingChanged();
}

void PlayerViewModel::onError(const QString &message)
{
    m_errorMessage = message;
    emit errorMessageChanged();
}

QString PlayerViewModel::formatTime(qint64 milliseconds) const
{
    qint64 totalSeconds = milliseconds / 1000;
    qint64 hours = totalSeconds / 3600;
    qint64 minutes = (totalSeconds % 3600) / 60;
    qint64 seconds = totalSeconds % 60;

    QString text;

    if (hours > 0) {
        text = QString("%1:%2:%3")
                   .arg(hours)
                   .arg(minutes, 2, 10, QChar('0'))
                   .arg(seconds, 2, 10, QChar('0'));
    } else {
        text = QString("%1:%2")
                   .arg(minutes, 2, 10, QChar('0'))
                   .arg(seconds, 2, 10, QChar('0'));
    }
    return text;
}