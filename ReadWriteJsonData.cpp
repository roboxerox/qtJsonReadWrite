#include "ReadWriteJsonData.h"

ReadWriteJsonData::ReadWriteJsonData()
{
    QFile file("Sample1.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonData = file.readAll();
    file.close();
    qDebug()<<"Read "<< m_CheckDataType(jsonData);
}

bool ReadWriteJsonData::m_CheckDataType(QByteArray RawData)
{
    QJsonParseError error;
    QJsonDocument json_doc = QJsonDocument::fromJson(RawData, &error);

    if (json_doc.isNull())
    {
        qDebug() << "Failed to create JSON doc." << error.errorString();
        QDomDocument *doc = new QDomDocument;
        RawData.replace("&lt;","<");
        RawData.replace("&gt;",">");
        if (!doc->setContent(RawData))
        {
            qDebug() <<"QByteArray not set to content. Xml data content has error.";
            qDebug()<< "This is neither JSON nor XML data .";
            return false;
        }
        else
        {
            qDebug() <<"This is XML data. ";
            return true;
        }
    }
    else
    {
        qDebug() <<"This is JSON data. ";
        m_ReadJSON_byQJsonObject(json_doc.object());
        return true;
    }

    return false;
}

void ReadWriteJsonData::m_ReadJSON_byQJsonObject(QJsonObject jsonObj)
{
    QString strModuleName;
    if (jsonObj.isEmpty()) {
        qDebug() << "JSON object is empty." ;
    }
    else
    {
        strModuleName = jsonObj["MODULE_NAME"].toString();
        QString fID = jsonObj["FUNCTION_ID"].toString();
        m_Iterator(jsonObj, "FDATA");
        qDebug()<<strModuleName <<fID <<"\n MAPPED_DATA "<<Map_FData<<"\n LIST_OF_MAPPED_DATA "<<ListMap_FData;
    }
}

void ReadWriteJsonData::m_Iterator(QJsonObject jsonObj, QString TagName)
{
    if(jsonObj[TagName].isArray())
    {
        QJsonArray fdata = jsonObj[TagName].toArray();
        ListMap_FData.clear();
        QVariantList list = fdata.toVariantList();
        for(int i = 0; i<list.size(); i ++)
        {
            QMap<QString,QVariant> vMap = list.at(i).toMap();
            QMap<QString,QString> mapData;
            for(QMap<QString,QVariant>::Iterator iter = vMap.begin(); iter != vMap.end(); ++iter)
                mapData.insert(iter.key(), iter.value().value<QString>());
            ListMap_FData << mapData;
        }
    }
    else
    {
       QJsonObject fdata_obj=  jsonObj[TagName].toObject();
       QVariantMap vMap = fdata_obj.toVariantMap();
       Map_FData.clear();
       for(QVariantMap::const_iterator iter = vMap.begin(); iter != vMap.end(); ++iter)
       {
           if(iter.value().userType() == QMetaType::QString)
               Map_FData.insert(iter.key(),iter.value().value<QString>());
           else
           {
               QJsonObject obj = QJsonObject::fromVariantMap(vMap);
               m_Iterator(obj, iter.key());
           }
       }
       //qDebug()<<TagName <<Map_FData;
    }
}


void ReadWriteJsonData::m_ListMap_DataWrite(QString mName, int fId, QList<QMap<QString,QString> > lMap)
{
    QJsonObject docObject;
    docObject.insert("MODULE_NAME", QJsonValue::fromVariant(mName));
    docObject.insert("FUNCTION_ID", QJsonValue::fromVariant(QString::number(fId).rightJustified(2,'0')));

    QJsonArray listArray;
    for(int i=0; i<lMap.size(); i++)
    {
        QMap<QString, QString> tempMap = lMap[i];
        QJsonObject tempObject;
        for (QMap<QString, QString>::iterator iter = tempMap.begin(); iter != tempMap.end(); ++iter)
            tempObject.insert(iter.key(), iter.value());
        listArray.push_back(tempObject);
    }

    docObject.insert("FDATA", listArray);

    QFile file("Sample10.json");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonDocument doc(docObject);
        qint64 bytes = file.write(doc.toJson());
        qDebug()<<"Write bytes "<<bytes;
    }
    else
        qDebug()<<"unable to write";

}


void ReadWriteJsonData::m_Map_DataWrite(QString mName, int fId, QMap<QString,QString>  tempMap)
{
    QJsonObject docObject;
    docObject.insert("MODULE_NAME", QJsonValue::fromVariant(mName));
    docObject.insert("FUNCTION_ID", QJsonValue::fromVariant(QString::number(fId).rightJustified(2,'0')));
    QJsonObject tempObject;
    for (QMap<QString, QString>::iterator iter = tempMap.begin(); iter != tempMap.end(); ++iter)
        tempObject.insert(iter.key(), iter.value());

    docObject.insert("FDATA", tempObject);

    QFile file("Sample11.json");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QJsonDocument doc(docObject);
        qint64 bytes = file.write(doc.toJson());
        qDebug()<<"Write bytes "<<bytes;
    }
    else
        qDebug()<<"unable to write";

}
