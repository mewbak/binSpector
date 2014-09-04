#ifndef LLVM_HIGHLIGHTER_H
#define LLVM_HIGHLIGHTER_H

/*
 *
 * largely copied from: http://doc.qt.digia.com/qq/qq21-syntaxhighlighter.html
 *
 */

#include <QSyntaxHighlighter>

namespace control
{
namespace syntax
{
class llvmHighlighter: public QSyntaxHighlighter
{
    Q_OBJECT
public:
    llvmHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};
} // syntax_highlighter
} // control

#endif // LLVM_HIGHLIGHTER_H