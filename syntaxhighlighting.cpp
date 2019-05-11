#include "syntaxhighlighting.h"

Highlight::Highlight(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    SyntaxHighlightingRule rule;

    normalTextFormat.setForeground(Qt::white);
    rule.pattern = QRegExp("\\b[A-Za-z]+\\b");
    rule.format = normalTextFormat;
    highlightingRules.append(rule);

    keywordFormat.setForeground(Qt::lightGray);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }



    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkCyan);
    rule.pattern = QRegExp("\\bclass+ [A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    ifFormat.setFontWeight(QFont::Bold);
    ifFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\bif\\b|\\belse\\b|\\bfor\\b|\\bwhile\\b|\\bdo\\b|\\bswitch\\b|\\bcase\\b");
    rule.format = ifFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::darkGreen);

    quotationFormat.setForeground(Qt::darkYellow);
    rule.pattern = QRegExp("\".*\"|'.*'");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    numbersFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\b[0-9]+\\b");
    rule.format = numbersFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::gray);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    includeFormat.setForeground(Qt::magenta);
    rule.pattern = QRegExp("^#include");
    rule.format = includeFormat;
    highlightingRules.append(rule);

    includeBracketsFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("<.*>");
    rule.format = includeBracketsFormat;
    highlightingRules.append(rule);


    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

Highlight::~Highlight(){}

void Highlight::highlightBlock(const QString &text)
{
    foreach (const SyntaxHighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
