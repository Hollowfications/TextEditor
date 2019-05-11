#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QFile>
#include <QTextStream>

class FileManager {
public:
   FileManager();
   void newfile(QString &filepath);
   void savefile(QString &filepath, QString &text);
   QString openfile(QString filepath);
   ~FileManager();
};


#endif // FILEMANAGER_H
