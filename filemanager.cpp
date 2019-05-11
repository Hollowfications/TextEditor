#include "filemanager.h"
#include <QString>
#include <QMessageBox>


FileManager::FileManager(){};
FileManager::~FileManager(){};


QString FileManager::openfile(QString filepath)
{
    QFile file(filepath);
    QTextStream fstream(&file);
    file.open(QIODevice::ReadOnly);
    QString text = fstream.readAll();
    file.close();
    return text;
}

void FileManager::newfile( QString &filepath)
{
    QFile file(filepath);
    file.open(QIODevice::WriteOnly);

    file.close();
}

void FileManager::savefile(QString &filepath, QString& text)
{
    QFile file (filepath);
    QTextStream fstream(&file);
    file.open(QIODevice::WriteOnly);
    fstream << text;
    file.flush();
    file.close();
}

