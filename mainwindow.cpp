#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
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

    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(ui->actionNew_file, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionSave_file, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionSave_file_as, &QAction::triggered, this, &MainWindow::saveAs);
    connect(ui->actionOpen_file, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionOpen_second_tab, &QAction::triggered, this, &MainWindow::openInNew);
    connect(ui->actionBackground_colour, &QAction::triggered, this, &MainWindow::changeBgColour);
    connect(ui->actionTextBgColour, &QAction::triggered, this, &MainWindow::changeTextBgColour);
    connect(ui->actionFont_colour, &QAction::triggered, this, &MainWindow::changeFontColour);
    connect(ui->actionFont_size, &QAction::triggered, this, &MainWindow::changeFontSize);
    connect(ui->actionFont_style, &QAction::triggered, this, &MainWindow::changeFontStyle);
    connect(ui->actionSelection_colour, &QAction::triggered, this, &MainWindow::changeSelectionColour);
    connect(ui->actionSynHL, &QAction::toggled, this, &MainWindow::SynHL);
    connect(ui->actionUTF_8, &QAction::triggered, this, &MainWindow::codeUTF8);
    connect(ui->actionKOI_8, &QAction::triggered, this, &MainWindow::codeKOI8);
    connect(ui->actionWindows1251, &QAction::triggered, this, &MainWindow::codeWindows1251);
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeTab(int index){
    if (ui->tabWidget->currentIndex() != 0) {
        ui->tabWidget->removeTab(index);
    }
    else if (ui->tabWidget->currentIndex() == 0) {
        return;
    }
}


void MainWindow::openFile() {
    if (ui->tabWidget->currentIndex() == 0) {
        QString filepath = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                    "C:/qt_projects/documents",
                                               tr("Text files (*.txt *.docx *.cpp *.h *.c)"));
        if (filepath != "") {
            ui->textEdit->setText(pFileManager->open(filepath));
            currentFilepath1 = filepath;
        }
    }
    if (ui->tabWidget->currentIndex() == 1) {

        QString filepath = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                    "C:/qt_projects/documents",
                                               tr("Text files (*.txt *.docx *.cpp *.h *.c)"));
        if (filepath != ""){
            ui->textEdit_2->setText(pFileManager->open(filepath));
            currentFilepath2 = filepath;
        }
    }
}

void MainWindow::openInNew() {
    if (ui->tabWidget->currentIndex() == 0) {
    QString filepath = QFileDialog::getOpenFileName(this, tr("Open file"),
                                                    "C:/qt_projects/documents",
                                               tr("Text files (*.txt *.docx *.cpp *.h *.c)"));
    if (filepath != "") {
        ui->tabWidget->addTab(new QTextEdit(), QString("Tab 2").arg(ui->tabWidget->count() + 1));
        for(int i = ui->tabWidget->count() - 1; i < ui->tabWidget->count(); i++) {
            QTextEdit* textEdit = qobject_cast<QTextEdit*>(ui->tabWidget->widget(i));
            if(textEdit) {
                textEdit->setText(pFileManager->open(filepath));
            }
        }
     }
    }
}
void  MainWindow::saveFile() {
    if (ui->tabWidget->currentIndex() == 0) {
        if(currentFilepath1 != "") {
            QString text = ui->textEdit->toPlainText();
            pFileManager->save(currentFilepath1, text);
        }
    }
    if (ui->tabWidget->currentIndex() == 1) {
        if(currentFilepath2 != "") {
            QString text = ui->textEdit->toPlainText();
            pFileManager->save(currentFilepath2, text);
        }
    }
}

void MainWindow::newFile() {
    if (ui->tabWidget->currentIndex() == 0) {
        QString path = QFileDialog::getSaveFileName(this, tr("Создать файл"), "C:/qt_projects/documents", "sampleText");
        currentFilepath1 = path;
        pFileManager->newfile(path);
    }
    if (ui->tabWidget->currentIndex() == 1) {
        QString path = QFileDialog::getSaveFileName(this, tr("Создать файл"), "sampleText");
        currentFilepath2 = path;
        pFileManager->newfile(path);
    }
}

void MainWindow::saveAs() {
    if (ui->tabWidget->currentIndex() == 0) {
        QString text = ui->textEdit->toPlainText();
        QString filepath = QFileDialog::getSaveFileName(this, tr("Open file"),
                                                        "C:/qt_projects/documents",
                                                   tr("Text files (*.txt *.docx *.cpp *.h *.c)"));
        if (filepath != "") {
            currentFilepath1 = filepath;
            pFileManager->save(currentFilepath1, text);
        }
    }
    if (ui->tabWidget->currentIndex() == 1) {
        QString text = ui->textEdit_2->toPlainText();
        QString filepath = QFileDialog::getSaveFileName(this, tr("Open file"),
                                                        "C:/qt_projects/documents",
                                                   tr("Text files (*.txt *.docx *.cpp *.h *.c)"));
        if (filepath != "") {
            currentFilepath2 = filepath;
            pFileManager->save(currentFilepath2, text);
        }
    }
}

void MainWindow::changeTextBgColour() {
    if (ui->tabWidget->currentIndex() == 0) {
        QColor col = QColorDialog::getColor(ui->textEdit->textBackgroundColor(), this);
        if (col.isValid()) {
            ui->textEdit->setTextBackgroundColor(col);
        }
        ui->textEdit->show();
    }
    if (ui->tabWidget->currentIndex() == 1) {
        QColor col = QColorDialog::getColor(ui->textEdit->textBackgroundColor(), this);
        if (col.isValid()) {
            ui->textEdit_2->setTextBackgroundColor(col);
        }
        ui->textEdit_2->show();
    }
}

void MainWindow::changeBgColour() {
    if (ui->tabWidget->currentIndex() == 0) {

        pFontMain1->setBackgroundColor(QColorDialog::getColor(pFontMain1->backgroundColor, this));
    }
    if (ui->tabWidget->currentIndex() == 1) {
        pFontMain2->setBackgroundColor(QColorDialog::getColor(pFontMain2->backgroundColor, this));

    }
}

void MainWindow::changeFontSize() {
    if (ui->tabWidget->currentIndex() == 0) {
        pFontMain1->setFontSize(QInputDialog::getInt(this, "Изменить размер текста", "", pFontMain1->fontSize, 1, 100));
    }
    if (ui->tabWidget->currentIndex() == 1) {
        pFontMain2->setFontSize(QInputDialog::getInt(this, "Изменить размер текста", "", pFontMain2->fontSize, 1, 100));
    }
}

void MainWindow::changeFontColour() {
    if (ui->tabWidget->currentIndex() == 0) {
        pFontMain1->setFontColor(QColorDialog::getColor(pFontMain1->fontColor,this));
    }
    if (ui->tabWidget->currentIndex() == 1) {
        pFontMain2->setFontColor(QColorDialog::getColor(pFontMain2->fontColor,this));
    }
}

void MainWindow::changeFontStyle() {
    if (ui->tabWidget->currentIndex() == 0) {
        pFontMain1->setFontStyle(QFontDialog::getFont(nullptr, pFontMain1->fontStyle, this));
    }
    if (ui->tabWidget->currentIndex() == 1) {
        pFontMain2->setFontStyle(QFontDialog::getFont(nullptr, pFontMain2->fontStyle, this));
    }
}

void MainWindow::changeSelectionColour() {
    if (ui->tabWidget->currentIndex() == 0) {
        pFontMain1->setSelectColor(QColorDialog::getColor(pFontMain1->selectColor,this));
    }
    if (ui->tabWidget->currentIndex() == 1) {
        pFontMain2->setSelectColor(QColorDialog::getColor(pFontMain2->selectColor,this));

    }
}

void MainWindow::SynHL(){
   if (ui->tabWidget->currentIndex() == 0) {
        pHighlight1 = new Highlight(pFontMain1->pFont->document());
    if (ui->actionSynHL->isChecked() == true){
        pFontMain1->setFontStyle(QFont("Courier New", 15, 10, false));
        pFontMain1->setFontSize(25);
        pFontMain1->setBackgroundColor(Qt::black);
        pFontMain1->setFontColor(Qt::white);
        pFontMain1->setSelectColor(Qt::blue);

     } else {
        delete pHighlight1;
        pFontMain1->setFontColor(defaultFontColor);
        pFontMain1->setFontStyle(defaultFontStyle);
        pFontMain1->setBackgroundColor(defaultBackgroundColor);
        pFontMain1->setSelectColor(defaultSelectColor);
    }

   }
   if (ui->tabWidget->currentIndex() == 1) {
        pHighlight2 = new Highlight(pFontMain2->pFont->document());
    if (ui->actionSynHL->isChecked() == true){
        pFontMain2->setFontStyle(QFont("Courier New", 15, 10, false));
        pFontMain2->setFontSize(25);
        pFontMain2->setBackgroundColor(Qt::black);
        pFontMain2->setFontColor(Qt::white);
        pFontMain2->setSelectColor(Qt::blue);

     } else {
        delete pHighlight2;
        pFontMain2->setFontColor(defaultFontColor);
        pFontMain2->setFontStyle(defaultFontStyle);
        pFontMain2->setBackgroundColor(defaultBackgroundColor);
        pFontMain2->setSelectColor(defaultSelectColor);
    }

   }
}

void MainWindow::codeUTF8() {
    if (ui->tabWidget->currentIndex() == 0) {
        QString text = ui->textEdit->toPlainText();
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::ReadOnly);
        in >> byteArray;
        byteArray = codec->fromUnicode(text);
        text = byteArray;
        ui->textEdit->setPlainText(text);
    }
    if (ui->tabWidget->currentIndex() == 1) {
        QString text = ui->textEdit_2->toPlainText();
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::ReadOnly);
        in >> byteArray;
        byteArray = codec->fromUnicode(text);
        text = byteArray;
        ui->textEdit->setPlainText(text);
    }
}

void MainWindow::codeKOI8() {
    if (ui->tabWidget->currentIndex() == 0) {
        QString text = ui->textEdit->toPlainText();
        QTextCodec *codec = QTextCodec::codecForName("KOI8-R");
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::ReadOnly);
        in >> byteArray;
        byteArray = codec->fromUnicode(text);
        text = byteArray;
        ui->textEdit->setPlainText(text);
    }
    if (ui->tabWidget->currentIndex() == 1) {
        QString text = ui->textEdit->toPlainText();
        QTextCodec *codec = QTextCodec::codecForName("KOI8-R");
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::ReadOnly);
        in >> byteArray;
        byteArray = codec->fromUnicode(text);
        text = byteArray;
        ui->textEdit_2->setPlainText(text);
    }
}

void MainWindow::codeWindows1251() {
    if (ui->tabWidget->currentIndex() == 0) {
        QString text = ui->textEdit->toPlainText();
        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::ReadOnly);
        in >> byteArray;
        byteArray = codec->fromUnicode(text);
        text = byteArray;
        ui->textEdit->setPlainText(text);
    }
    if (ui->tabWidget->currentIndex() == 1) {
        QString text = ui->textEdit_2->toPlainText();
        QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
        QByteArray byteArray;
        QDataStream in(&byteArray, QIODevice::ReadOnly);
        in >> byteArray;
        byteArray = codec->fromUnicode(text);
        text = byteArray;
        ui->textEdit->setPlainText(text);
    }
}
