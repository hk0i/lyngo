#ifndef LYWORD_H
#define LYWORD_H

#include <QtCore>

class LyWord
{
    public:

        LyWord(void);
        LyWord(const QString&, const QChar&, const QString&);

        QString word(void) const;
        QString definition(void) const;
        QString partOfSpeech(void) const;
        QChar   pos(void) const;

        QStringList data(void) const;

        void setWord(const QString &);
        void setDefinition(const QString &);
        void setPos(const QChar&);

    private:

        QString _word;
        QChar   _pos;
        QString _definition;

};

#endif
