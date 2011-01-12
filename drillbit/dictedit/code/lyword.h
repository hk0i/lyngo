#ifndef LYWORD_H
#define LYWORD_H

#include <QtCore>

/**
 * @brief
 *  Represents a word with its associated definition and part of speech.
 * @author Gregory McQuillan
 */
class LyWord
{
    public:

        LyWord(void);
        LyWord(const QString&, const QChar&, const QString&);

        QString word(void) const;
        QString definition(void) const;
        QString partOfSpeech(void) const;
        QChar   pos(void) const;

        QStringList data(bool fileOutput = true) const;

        void setWord(const QString &);
        void setDefinition(const QString &);
        void setPos(const QChar&);

    private:

        QString _word;
        QChar   _pos;
        QString _definition;

};

#endif
