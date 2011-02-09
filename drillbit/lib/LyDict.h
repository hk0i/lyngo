#ifndef LYDICT_H
#define LYDICT_H

#include <QtCore>
#include "LyWord.h"

#define DEBUGMODE

#ifdef DEBUGMODE
#include <iostream>
#define DEBUG_PRINT(x) std::cout << x << std::endl
#else
#define DEBUG_PRINT(x)
#endif

/**
 * @brief
 *  A list (dictionary) of @ref LyWord "LyWords" that is capable of file
 *  loading and saving.
 * @author Gregory McQuillan
 */
class LyDict
{
    public:

        LyDict(void);
        // ~LyDict(void);

        void load(const QString&);
        void save(const QString&);

        // Mutators
        void setName(const QString&);

        void add(const LyWord&);

        void add(const QString &,
                 const QChar&,
                 const QString &);

        void add(const QString &,
                 const char&,
                 const QString &);

        void removeAt(const int&);

        // Accessors
        QString name(void);
        LyWord *itemAt(const int&);
        const int count(void) const;

        // Misc
        static QString posFromAbbr(QChar);
        static QChar   posFromName(QString);

    private:

        void load_file(const QString&); /** brains behind the public load() function */
        void parse_line(QString); /** parses lines in the file load() function */

        QString _name;             /** the name of the dictionary */

        QList<LyWord> _words;
};

#endif
