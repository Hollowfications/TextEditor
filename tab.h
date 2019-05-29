#ifndef TAB_H
#define TAB_H
#include <QString>
#include "filemanager.h"
#include "syntaxhighlighting.h"
#include "font.h"

class Tab {
public:
    QString currentfilepath;
    Font* pFont;
    Highlight* pHighlight;
    FileManager* pFilemanager;
    Tab();
    ~Tab();


};

#endif // TAB_H
