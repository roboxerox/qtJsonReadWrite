#include <QCoreApplication>
#include <ReadWriteJsonData.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ReadWriteJsonData *rwJsonData =  new ReadWriteJsonData;
    Q_UNUSED(rwJsonData)
    return a.exec();
}
