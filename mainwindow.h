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
    QString current_filepath;
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
    void SynHL();

private:
    Ui::MainWindow *ui;
    FileManager *pFileManager;
    Font *pFontMain;
    Highlight *pHighlight;

};

#endif // MAINWINDOW_H
