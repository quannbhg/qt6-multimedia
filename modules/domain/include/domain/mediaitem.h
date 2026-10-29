#ifndef MEDIAITEM_H
#define MEDIAITEM_H

#include <QString>
#include <QDateTime>

/* A media file (music, video, image). 
Contains only data; no logic. */
typedef struct
{
    int id = 0;
    QString title;
    QString path;
    QString type;          /* "Audio", "Video", "Image" */
    qint64 sizeBytes = 0;
    qint64 durationMs = 0;
    QDateTime createdAt;
} MediaItem;

#endif /* MEDIAITEM_H */