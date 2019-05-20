#ifndef FONT_H
#define FONT_H

#include <QTextEdit>
#include <QColor>
#include <QPalette>
#include <QFontDialog>
#include <QFont>
#include <QRegularExpression>


const int defaultFontSize = 20;
const QFont defaultFontStyle("Times New Roman");
const QColor defaultColor = Qt::black;
const QColor defaultBackgroundColor = Qt::white;
const QColor defaultSelectColor = QColor::fromRgb(0, 120, 215, 255);

class Font
{
public:
    Font(QTextEdit* text);
    ~Font();
    void setFontStyle(const QFont fontStyle);
    void setFontColor(const QColor fontColor);
    void setFontSize(int size);
    void setBackgroundColor(const QColor backgroundColor);
    void setSelectColor(const QColor selectColor);

    QColor fontColor;
    QColor backgroundColor;
    QFont fontStyle;
    int fontSize;
    QColor selectColor;
    QTextEdit *pFont;
};

#endif // FONT_H
