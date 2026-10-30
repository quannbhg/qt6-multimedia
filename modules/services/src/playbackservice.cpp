#include "services/playbackservice.h"

PlaybackService::PlaybackService(IPlaybackEngine *engine, QObject *parent)
    : QObject(parent)
    , m_engine(engine)
    , m_volume(30)
    , m_muted(false)
    , m_playbackRate(1.0)
{
    /* Forward signals of the engine to the upper layer. */
    connect(m_engine, &IPlaybackEngine::positionChanged,
            this, &PlaybackService::positionChanged);
    connect(m_engine, &IPlaybackEngine::durationChanged,
            this, &PlaybackService::durationChanged);
    connect(m_engine, &IPlaybackEngine::stateChanged,
            this, &PlaybackService::stateChanged);
    connect(m_engine, &IPlaybackEngine::errorOccurred,
            this, &PlaybackService::errorOccurred);

    /* Apply the default values to the engine. */
    m_engine->setVolume(m_volume);
    m_engine->setMuted(m_muted);
    m_engine->setPlaybackRate(m_playbackRate);
}

void PlaybackService::openFile(const QString &filePath)
{
    if (filePath == "") {
        return;
    }
    m_currentFilePath = filePath;
    m_engine->setSource(filePath);
    emit fileChanged(filePath);
}

void PlaybackService::play()
{
    m_engine->play();
}

void PlaybackService::pause()
{
    m_engine->pause();
}

void PlaybackService::stop()
{
    m_engine->stop();
}

void PlaybackService::togglePlayPause()
{
    if (m_engine->state() == PlaybackPlaying) {
        m_engine->pause();
    } else {
        m_engine->play();
    }
}

void PlaybackService::seekTo(qint64 positionMs)
{
    qint64 target = positionMs;

    if (target < 0) {
        target = 0;
    }
    if (target > m_engine->duration()) {
        target = m_engine->duration();
    }
    m_engine->setPosition(target);
}

void PlaybackService::seekForward()
{
    seekTo(m_engine->position() + SEEK_STEP_MS);
}

void PlaybackService::seekBackward()
{
    seekTo(m_engine->position() - SEEK_STEP_MS);
}

void PlaybackService::setVolume(int percent)
{
    int value = percent;

    if (value < 0) {
        value = 0;
    }
    if (value > 100) {
        value = 100;
    }
    if (value == m_volume) {
        return;
    }
    m_volume = value;
    m_engine->setVolume(m_volume);
    emit volumeChanged(m_volume);
}

void PlaybackService::toggleMute()
{
    m_muted = !m_muted;
    m_engine->setMuted(m_muted);
    emit mutedChanged(m_muted);
}

void PlaybackService::setPlaybackRate(double rate)
{
    if (rate <= 0.0) {
        return;
    }
    m_playbackRate = rate;
    m_engine->setPlaybackRate(m_playbackRate);
    emit playbackRateChanged(m_playbackRate);
}

int PlaybackService::volume() const
{
    return m_volume;
}

bool PlaybackService::isMuted() const
{
    return m_muted;
}

double PlaybackService::playbackRate() const
{
    return m_playbackRate;
}

qint64 PlaybackService::position() const
{
    return m_engine->position();
}

qint64 PlaybackService::duration() const
{
    return m_engine->duration();
}

PlaybackState PlaybackService::state() const
{
    return m_engine->state();
}

QString PlaybackService::currentFilePath() const
{
    return m_currentFilePath;
}