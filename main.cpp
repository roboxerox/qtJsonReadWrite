#include <QCoreApplication>
#include <ReadWriteJsonData.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ReadWriteJsonData *rwJsonData =  new ReadWriteJsonData;

    QList<QMap<QString,QString> > lmap;

    QMap<QString,QString> map;
    map.insert("one","1");
    map.insert("two","2");
    map.insert("three","3");
    lmap <<map;
    map.clear();
    map.insert("one","11");
    map.insert("two","22");
    map.insert("three","33");
    lmap <<map;
    map.clear();
    map.insert("one","111");
    map.insert("two","222");
    map.insert("three","333");
    lmap <<map;

    rwJsonData->m_ListMap_DataWrite("USER00",3,lmap);
    rwJsonData->m_Map_DataWrite("Admin00",10, map);
    return a.exec();
}
