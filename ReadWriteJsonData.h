#ifndef READWRITEJSONDATA_H
#define READWRITEJSONDATA_H
#include <QDebug>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QDomDocument>
#include <QDir>

class ReadWriteJsonData: public QObject
{
    Q_OBJECT
public:
    ReadWriteJsonData();
    bool m_CheckDataType(QByteArray RawData);
    void m_ReadJSON_byQJsonObject(QJsonObject jsonObj);
    void m_Iterator(QJsonObject jsonObj, QString TagName);
    QMap<QString,QString> Map_FData;
    QList<QMap<QString,QString> > ListMap_FData;

};

#endif // READWRITEJSONDATA_H
