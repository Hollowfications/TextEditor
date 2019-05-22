#ifndef SYNTAXHIGHLIGHTING_H
#define SYNTAXHIGHLIGHTING_H
#include <QtCore/QRegExp>
#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>

class QTextDocument;

class Highlight : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlight(QTextDocument *parent = nullptr);
    ~Highlight();
    void highlightBlock(const QString &text);
private:
    struct SyntaxHighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<SyntaxHighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat normalTextFormat;
    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat ifFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat numbersFormat;
    QTextCharFormat includeFormat;
    QTextCharFormat includeBracketsFormat;
    QTextCharFormat bracesStartFormat;
    QTextCharFormat bracesEndFormat;
    QTextCharFormat signsFormat;
};
#endif // SYNTAXHIGHLIGHTING_H
