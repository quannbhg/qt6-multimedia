#ifndef APPINFOVIEWMODEL_H
#define APPINFOVIEWMODEL_H

#include <QObject>
#include <QString>

// ViewModel thu nghiem: dua ten app va mot "media mau" len QML.
class AppInfoViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString appTitle READ appTitle CONSTANT)
    Q_PROPERTY(QString sampleMedia READ sampleMedia CONSTANT)

public:
    explicit AppInfoViewModel(QObject *parent = nullptr);

    QString appTitle() const;
    QString sampleMedia() const;

private:
    QString m_appTitle;
    QString m_sampleMedia;
};

#endif // APPINFOVIEWMODEL_H