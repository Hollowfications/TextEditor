#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "filemanager.h"
#include "font.h"
#include "tab.h"
#include "syntaxhighlighting.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //std::vector<Tab> tabs;
    QString currentFilepath1;
    QString currentFilepath2;

private slots:
    void openFile();
    void newFile();
    void saveFile();
    void saveAs();
    void changeBgColour();
    void changeTextBgColour();
    void changeFontColour();
    void changeFontSize();
    void changeFontStyle();
    void changeSelectionColour();
    void SynHL();
    void codeWindows1251();
    void codeKOI8();
    void codeUTF8();
    //void closeTab(int index);
    //void openInNew();

private:
    Ui::MainWindow *ui;
    Font* pFontMain1;
    Font* pFontMain2;
    Highlight* pHighlight1;
    Highlight* pHighlight2;
    FileManager* pFileManager;



};

#endif // MAINWINDOW_H
