#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "filemanager.h"
#include "font.h"
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
    QString current_filepath1;
    QString current_filepath2;
private slots:
    void on_openfile_pressed();
    void on_newfile_pressed();
    void on_savefile_pressed();
    void on_savefile_as_pressed();
    void on_BgColour_pressed();
    void on_TextBgColour_pressed();
    void on_FontColour_pressed();
    void on_FontSize_pressed();
    void on_FontStyle_pressed();
    void on_SelectionColour_pressed();
    void on_open_in_new_pressed();
    void SynHL();
    void code_Macintosh();
    void code_Windows1251();
    void code_KOI8();
    void code_UTF8();
    void close_tab(int index);

private:
    Ui::MainWindow *ui;
    FileManager *pFileManager;
    Font *pFontMain1;
    Font *pFontMain2;
    Highlight *pHighlight1;
    Highlight *pHighlight2;

};

#endif // MAINWINDOW_H
