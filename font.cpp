#include "font.h"

Font::Font(QTextEdit* text)
{
    pFont = text;
    fontStyle = defaultFontStyle;
    fontSize = defaultFontSize;
    fontColor = defaultColor;
    backgroundColor = defaultBackgroundColor;
    selectColor = defaultSelectColor;
}

Font::~Font() {}

void Font::setFontStyle(const QFont inputfontStyle)
{
  this->fontStyle = inputfontStyle;
  pFont->setFont(this->fontStyle);

}

void Font::setFontColor(const QColor inputfontColor)
{
  this->fontColor = inputfontColor;
  pFont->setTextColor(this->fontColor);
}

void Font::setFontSize(int inputfontSize)
{
  this->fontSize = inputfontSize;
  pFont->setFontPointSize(this->fontSize);

}

void Font::setBackgroundColor(const QColor inputbackgroundColor)
{
  QPalette color = pFont->palette();
  color.setColor(QPalette::Base,inputbackgroundColor);
  pFont->setPalette(color);
}


void Font::setSelectColor(const QColor selectColor)
{
  QPalette p = pFont->palette();
  p.setColor(QPalette::Highlight, QColor(selectColor));
  p.setColor(QPalette::HighlightedText, QColor(defaultBackgroundColor));
  pFont->setPalette(p);
}
