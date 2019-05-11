#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QColorDialog>
#include <QColor>
#include <QTextEdit>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pFileManager = new FileManager();
    pFontMain = new Font(ui->textEdit);

    ui->actionNew_file->setShortcut(QKeySequence(tr("Ctrl+N","New file")));
    ui->actionSave_file->setShortcut(QKeySequence(tr("Ctrl+S","Save file")));
    ui->actionCut->setShortcut(QKeySequence(tr("Ctrl+X","Cut")));
    ui->actionCopy->setShortcut(QKeySequence(tr("Ctrl+C","Copy")));
    ui->actionPaste->setShortcut(QKeySequence(tr("Ctrl+V","Paste")));
    ui->actionSelect_all->setShortcut(QKeySequence(tr("Ctrl+A","Select all")));
    ui->actionSave_file_as->setShortcut(QKeySequence("Ctrl+Shift+S"));

    connect(ui->actionOpen_file, &QAction::triggered, this, &MainWindow::on_openfile_pressed);
    connect(ui->actionNew_file, &QAction::triggered, this, &MainWindow::on_newfile_pressed);
    connect(ui->actionSave_file, &QAction::triggered, this, &MainWindow::on_savefile_pressed);
    connect(ui->actionBackground_colour, &QAction::triggered, this, &MainWindow::on_BgColour_pressed);
    connect(ui->actionTextBgColour, &QAction::triggered, this, &MainWindow::on_TextBgColour_pressed);
    connect(ui->actionFont_colour, &QAction::triggered, this, &MainWindow::on_FontColour_pressed);
    connect(ui->actionFont_size, &QAction::triggered, this, &MainWindow::on_FontSize_pressed);
    connect(ui->actionFont_style, &QAction::triggered, this, &MainWindow::on_FontStyle_pressed);
    connect(ui->actionSelection_colour, &QAction::triggered, this, &MainWindow::on_SelectionColour_pressed);
    connect(ui->actionSave_file_as, &QAction::triggered, this, &MainWindow::on_savefile_as_pressed);
    connect(ui->actionSynHL, &QAction::toggled, this, &MainWindow::SynHL);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openfile_pressed() {
    QString filepath = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                    "C:/qt_projects/documents",
                                               tr("Text files (*.txt *.docx *.cpp *.h *.c)"));
    if (filepath != ""){
        ui->textEdit->setText(pFileManager->openfile(filepath));
        current_filepath = filepath;
    }
}

void  MainWindow::on_savefile_pressed(){
    if(current_filepath != "")
    {
        QString text = ui->textEdit->toPlainText();
        pFileManager->savefile(current_filepath, text);
    }
}

void MainWindow::on_newfile_pressed() {
    QString path = QFileDialog::getSaveFileName(this, tr("Создать файл"), "sampleText");
    current_filepath = path;
    pFileManager->newfile(path);

}

void MainWindow::on_savefile_as_pressed(){

    QString text = ui->textEdit->toPlainText();
    QString filepath = QFileDialog::getSaveFileName(this, tr("Open file"),
                                                    "C:/qt_projects/documents",
                                               tr("Text files (*.txt *.docx *.cpp *.h *.c)"));
    if (filepath != ""){
        current_filepath = filepath;
        pFileManager->savefile(current_filepath, text);
    }
}

void MainWindow::on_TextBgColour_pressed(){
    QColor col = QColorDialog::getColor(ui->textEdit->textBackgroundColor(), this);
    if (col.isValid()) {
        ui->textEdit->setTextBackgroundColor(col);
    };
    ui->textEdit->show();
}

void MainWindow::on_BgColour_pressed()
{
    pFontMain->setBackgroundColor(QColorDialog::getColor(pFontMain->backgroundColor,this));
}

void MainWindow::on_FontSize_pressed()
{
    pFontMain->setFontSize(QInputDialog::getInt(this, "Изменить размер текста", "выф", pFontMain->fontSize, 1, 100));
}

void MainWindow::on_FontColour_pressed()
{
    pFontMain->setFontColor(QColorDialog::getColor(pFontMain->fontColor,this));
}

void MainWindow::on_FontStyle_pressed()
{
    pFontMain->setFontStyle(QFontDialog::getFont(nullptr, pFontMain->fontStyle, this));
}

void MainWindow::on_SelectionColour_pressed()
{
    pFontMain->setSelectColor(QColorDialog::getColor(pFontMain->selectColor,this));
}

void MainWindow::SynHL()
{
    pHighlight = new Highlight(pFontMain->pFont->document());

  if (ui->actionSynHL->isChecked() == true){
     pFontMain->setFontStyle(QFont("Courier New", 15, 10, false));
     pFontMain->setFontSize(25);
     pFontMain->setBackgroundColor(Qt::black);
     pFontMain->setFontColor(Qt::white);
     pFontMain->setSelectColor(Qt::blue);

  } else {
      pFontMain->setFontColor(Qt::black);
      delete pHighlight;
      pFontMain->setFontStyle(QFont("Times New Roman", 0, 75, false));
      pFontMain->setBackgroundColor(Qt::white);
      pFontMain->setSelectColor(defaultSelectColor);
  }
}
