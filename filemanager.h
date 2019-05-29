#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QFile>
#include <QTextStream>

class FileManager {
public:
   FileManager();
   void newfile(QString &filepath);
   void save(QString &filepath, QString &text);
   QString open(QString filepath);
   ~FileManager();
};


#endif // FILEMANAGER_H
