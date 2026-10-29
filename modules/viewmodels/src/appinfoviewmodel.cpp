#include "viewmodels/appinfoviewmodel.h"
#include "domain/mediaitem.h"

AppInfoViewModel::AppInfoViewModel(QObject *parent)
    : QObject(parent)
{
    m_appTitle = "Multimedia App";

    MediaItem item;
    item.id = 1;
    item.title = "Bai hat mau";
    item.type = "audio";
    m_sampleMedia = item.title + " (" + item.type + ")";
}

QString AppInfoViewModel::appTitle() const
{
    return m_appTitle;
}

QString AppInfoViewModel::sampleMedia() const
{
    return m_sampleMedia;
}