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
#include <QInputDialog>
#include <QTextCodec>
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->setTabsClosable(true);
    ui->tabWidget->setMovable(true);

    pFileManager = new FileManager();
    pFontMain1 = new Font(ui->textEdit);
    pFontMain2 = new Font(ui->textEdit_2);

    ui->actionNew_file->setShortcut(QKeySequence(tr("Ctrl+N","New file")));
    ui->actionSave_file->setShortcut(QKeySequence(tr("Ctrl+S","Save file")));
    ui->actionCut->setShortcut(QKeySequence(tr("Ctrl+X","Cut")));
    ui->actionCopy->setShortcut(QKeySequence(tr("Ctrl+C","Copy")));
    ui->actionPaste->setShortcut(QKeySequence(tr("Ctrl+V","Paste")));
    ui->actionSelect_all->setShortcut(QKeySequence(tr("Ctrl+A","Select all")));
    ui->actionSave_file_as->setShortcut(QKeySequence("Ctrl+Shift+S"));

    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(close_tab(int)));
    connect(ui->actionOpen_file, &QAction::triggered, this, &MainWindow::on_openfile_pressed);
    connect(ui->actionNew_file, &QAction::triggered, this, &MainWindow::on_newfile_pressed);
    connect(ui->actionSave_file, &QAction::triggered, this, &MainWindow::on_savefile_pressed);
    connect(ui->actionOpen_in_new, &QAction::triggered, this, &MainWindow::on_open_in_new_pressed);
    connect(ui->actionBackground_colour, &QAction::triggered, this, &MainWindow::on_BgColour_pressed);
    connect(ui->actionTextBgColour, &QAction::triggered, this, &MainWindow::on_TextBgColour_pressed);
    connect(ui->actionFont_colour, &QAction::triggered, this, &MainWindow::on_FontColour_pressed);
    connect(ui->actionFont_size, &QAction::triggered, this, &MainWindow::on_FontSize_pressed);
    connect(ui->actionFont_style, &QAction::triggered, this, &MainWindow::on_FontStyle_pressed);
    connect(ui->actionSelection_colour, &QAction::triggered, this, &MainWindow::on_SelectionColour_pressed);
    connect(ui->actionSave_file_as, &QAction::triggered, this, &MainWindow::on_savefile_as_pressed);
    connect(ui->actionSynHL, &QAction::toggled, this, &MainWindow::SynHL);
    connect(ui->actionUTF_8, &QAction::triggered, this, &MainWindow::code_UTF8);
    connect(ui->actionKOI_8, &QAction::triggered, this, &MainWindow::code_KOI8);
    connect(ui->actionWindows1251, &QAction::triggered, this, &MainWindow::code_Windows1251);
    connect(ui->actionMacintosh, &QAction::triggered, this, &MainWindow::code_Macintosh);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::close_tab(int index){
    if (ui->tabWidget->currentIndex() != 0){
        ui->tabWidget->removeTab(index);
    }
    else if (ui->tabWidget->currentIndex() == 0){
        return;
    }

}


void MainWindow::on_openfile_pressed() {
    if (ui->tabWidget->currentIndex() == 0){
        QString filepath = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                    "C:/qt_projects/documents",
                                               tr("Text files (*.txt *.docx *.cpp *.h *.c)"));
        if (filepath != ""){
            ui->textEdit->setText(pFileManager->openfile(filepath));
            current_filepath1 = filepath;
        }
    }
    if (ui->tabWidget->currentIndex() == 1){

        QString filepath = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                    "C:/qt_projects/documents",
                                               tr("Text files (*.txt *.docx *.cpp *.h *.c)"));
        if (filepath != ""){
            ui->textEdit_2->setText(pFileManager->openfile(filepath));
            current_filepath2 = filepath;
        }
    }
}

void MainWindow::on_open_in_new_pressed(){
    if (ui->tabWidget->currentIndex() == 0){
        QString filepath = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                        "C:/qt_projects/documents",
                                                   tr("Text files (*.txt *.docx *.cpp *.h *.c)"));
        if (filepath != ""){
            ui->textEdit->setText(pFileManager->openfile(filepath));
            current_filepath1 = filepath;
        }
    }
    if (ui->tabWidget->currentIndex() == 1){
        QString filepath = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                        "C:/qt_projects/documents",
                                                   tr("Text files (*.txt *.docx *.cpp *.h *.c)"));
        if (filepath != ""){
            ui->textEdit_2->setText(pFileManager->openfile(filepath));
            current_filepath2 = filepath;
        }
    }

}
void  MainWindow::on_savefile_pressed(){
    if (ui->tabWidget->currentIndex() == 0){
        if(current_filepath1 != "")
        {
            QString text = ui->textEdit->toPlainText();
            pFileManager->savefile(current_filepath1, text);
        }
    }
    if (ui->tabWidget->currentIndex() == 1) {
        if(current_filepath2 != "")
        {
            QString text = ui->textEdit->toPlainText();
            pFileManager->savefile(current_filepath2, text);
        }
    }
}

void MainWindow::on_newfile_pressed() {
    if (ui->tabWidget->currentIndex() == 0){
        QString path = QFileDialog::getSaveFileName(this, tr("Создать файл"), "sampleText");
        current_filepath1 = path;
        pFileManager->newfile(path);
    }
    if (ui->tabWidget->currentIndex() == 1){
        QString path = QFileDialog::getSaveFileName(this, tr("Создать файл"), "sampleText");
        current_filepath2 = path;
        pFileManager->newfile(path);
    }
}

void MainWindow::on_savefile_as_pressed(){

    if (ui->tabWidget->currentIndex() == 0){
        QString text = ui->textEdit->toPlainText();
        QString filepath = QFileDialog::getSaveFileName(this, tr("Open file"),
                                                        "C:/qt_projects/documents",
                                                   tr("Text files (*.txt *.docx *.cpp *.h *.c)"));
        if (filepath != ""){
            current_filepath1 = filepath;
            pFileManager->savefile(current_filepath1, text);
        }
    }
    if (ui->tabWidget->currentIndex() == 1){
        QString text = ui->textEdit_2->toPlainText();
        QString filepath = QFileDialog::getSaveFileName(this, tr("Open file"),
                                                        "C:/qt_projects/documents",
                                                   tr("Text files (*.txt *.docx *.cpp *.h *.c)"));
        if (filepath != ""){
            current_filepath2 = filepath;
            pFileManager->savefile(current_filepath2, text);
        }
    }

}

void MainWindow::on_TextBgColour_pressed(){
    if (ui->tabWidget->currentIndex() == 0){
        QColor col = QColorDialog::getColor(ui->textEdit->textBackgroundColor(), this);
        if (col.isValid()) {
            ui->textEdit->setTextBackgroundColor(col);
        };
        ui->textEdit->show();
    }
    if (ui->tabWidget->currentIndex() == 1){
        QColor col = QColorDialog::getColor(ui->textEdit->textBackgroundColor(), this);
        if (col.isValid()) {
            ui->textEdit_2->setTextBackgroundColor(col);
        };
        ui->textEdit_2->show();
    }

}

void MainWindow::on_BgColour_pressed()
{
    if (ui->tabWidget->currentIndex() == 0){

        pFontMain1->setBackgroundColor(QColorDialog::getColor(pFontMain1->backgroundColor, this));
    }
    if (ui->tabWidget->currentIndex() == 1){
        pFontMain2->setBackgroundColor(QColorDialog::getColor(pFontMain2->backgroundColor, this));

    }
}

void MainWindow::on_FontSize_pressed()
{
    if (ui->tabWidget->currentIndex() == 0){
        pFontMain1->setFontSize(QInputDialog::getInt(this, "Изменить размер текста", "", pFontMain1->fontSize, 1, 100));
    }
    if (ui->tabWidget->currentIndex() == 1){
        pFontMain2->setFontSize(QInputDialog::getInt(this, "Изменить размер текста", "", pFontMain2->fontSize, 1, 100));
    }
}

void MainWindow::on_FontColour_pressed()
{
    if (ui->tabWidget->currentIndex() == 0){
        pFontMain1->setFontColor(QColorDialog::getColor(pFontMain1->fontColor,this));
    }
    if (ui->tabWidget->currentIndex() == 1){
        pFontMain2->setFontColor(QColorDialog::getColor(pFontMain2->fontColor,this));

    }
}

void MainWindow::on_FontStyle_pressed()
{
    if (ui->tabWidget->currentIndex() == 0){
        pFontMain1->setFontStyle(QFontDialog::getFont(nullptr, pFontMain1->fontStyle, this));
    }
    if (ui->tabWidget->currentIndex() == 0){
        pFontMain2->setFontStyle(QFontDialog::getFont(nullptr, pFontMain2->fontStyle, this));

    }
}

void MainWindow::on_SelectionColour_pressed()
{
    if (ui->tabWidget->currentIndex() == 0){
        pFontMain1->setSelectColor(QColorDialog::getColor(pFontMain1->selectColor,this));
    }
    if (ui->tabWidget->currentIndex() == 1){
        pFontMain2->setSelectColor(QColorDialog::getColor(pFontMain2->selectColor,this));

    }
}

void MainWindow::SynHL(){
   if (ui->tabWidget->currentIndex() == 0){

        pHighlight = new Highlight(pFontMain1->pFont->document());

    if (ui->actionSynHL->isChecked() == true){
        pFontMain1->setFontStyle(QFont("Courier New", 15, 10, false));
        pFontMain1->setFontSize(25);
        pFontMain1->setBackgroundColor(Qt::black);
        pFontMain1->setFontColor(Qt::white);
        pFontMain1->setSelectColor(Qt::blue);

     } else {
        delete pHighlight;
        pFontMain1->setFontColor(defaultFontColor);
        pFontMain1->setFontStyle(defaultFontStyle);
        pFontMain1->setBackgroundColor(defaultBackgroundColor);
        pFontMain1->setSelectColor(defaultSelectColor);
    }

   }
   if (ui->tabWidget->currentIndex() == 1){

        pHighlight = new Highlight(pFontMain1->pFont->document());

    if (ui->actionSynHL->isChecked() == true){
        pFontMain1->setFontStyle(QFont("Courier New", 15, 10, false));
        pFontMain1->setFontSize(25);
        pFontMain1->setBackgroundColor(Qt::black);
        pFontMain1->setFontColor(Qt::white);
        pFontMain1->setSelectColor(Qt::blue);

     } else {
        delete pHighlight;
        pFontMain1->setFontColor(defaultFontColor);
        pFontMain1->setFontStyle(defaultFontStyle);
        pFontMain1->setBackgroundColor(defaultBackgroundColor);
        pFontMain1->setSelectColor(defaultSelectColor);
    }

   }


}

void MainWindow::code_UTF8()
{
    if (ui->tabWidget->currentIndex() == 0){
        QString text = ui->textEdit->toPlainText();
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::WriteOnly);
        in << text;
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        text = codec->toUnicode(byteArray);
        ui->textEdit->setPlainText(text);
    }
    if (ui->tabWidget->currentIndex() == 1){
        QString text = ui->textEdit_2->toPlainText();
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::WriteOnly);
        in << text;
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        text = codec->toUnicode(byteArray);
        ui->textEdit_2->setPlainText(text);
    }

}

void MainWindow::code_KOI8()
{
    if (ui->tabWidget->currentIndex() == 0){
        QString text = ui->textEdit->toPlainText();
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::WriteOnly);
        in << text;
        QTextCodec *codec = QTextCodec::codecForName("KOI-8-R");
        text = codec->toUnicode(byteArray);
        ui->textEdit->setPlainText(text);
    }
    if (ui->tabWidget->currentIndex() == 1){
        QString text = ui->textEdit_2->toPlainText();
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::WriteOnly);
        in << text;
        QTextCodec *codec = QTextCodec::codecForName("KOI-8-R");
        text = codec->toUnicode(byteArray);
        ui->textEdit_2->setPlainText(text);
    }
}

void MainWindow::code_Macintosh()
{
    if (ui->tabWidget->currentIndex() == 0){
        QString text = ui->textEdit->toPlainText();
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::WriteOnly);
        in << text;
        QTextCodec *codec = QTextCodec::codecForName("Macintosh");
        text = codec->toUnicode(byteArray);
        ui->textEdit->setPlainText(text);
    }
    if (ui->tabWidget->currentIndex() == 1){
        QString text = ui->textEdit_2->toPlainText();
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::WriteOnly);
        in << text;
        QTextCodec *codec = QTextCodec::codecForName("Macintosh");
        text = codec->toUnicode(byteArray);
        ui->textEdit_2->setPlainText(text);
    }
}

void MainWindow::code_Windows1251()
{
    if (ui->tabWidget->currentIndex() == 0){
        QString text = ui->textEdit->toPlainText();
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::WriteOnly);
        in << text;
        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        text = codec->toUnicode(byteArray);
        ui->textEdit->setPlainText(text);
    }
    if (ui->tabWidget->currentIndex() == 1){
        QString text = ui->textEdit_2->toPlainText();
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::WriteOnly);
        in << text;
        QTextCodec *codec = QTextCodec::codecForName("Windows-1252");
        text = codec->toUnicode(byteArray);
        ui->textEdit_2->setPlainText(text);
    }
}
