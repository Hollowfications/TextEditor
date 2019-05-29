#include "tab.h"
#include "syntaxhighlighting.h"
#include "filemanager.h"

Tab::Tab(){
    pFont = new Font(new QTextEdit());
    QString currentfilepath = "\n";
    pFilemanager = new FileManager();
}

Tab::~Tab(){
    delete pFont;
    delete pHighlight;
    delete pFilemanager;
}
