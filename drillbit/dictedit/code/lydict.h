#ifndef LYDICT_H
#define LYDICT_H

#include <QtCore>

#define DEBUGMODE

#ifdef DEBUGMODE
#include <iostream>
#define DEBUG_PRINT(x) std::cout << x << std::endl
#else
#define DEBUG_PRINT(x)
#endif

class LyDict
{
    public:

        LyDict(void);
        // ~LyDict(void);

        void load(const QString&); /** loads a dictionary from file */
        void save(const QString&); /** saves a dictionary to a file */

        // Mutators
        void setName(const QString&);

        void add(const QString &,   /** add a word to the dictionary */
                 const QChar&,
                 const QString &);

        void add(const QString &,   /** add a word to the dictionary */
                 const char&,
                 const QString &);

        void removeAt(const int&);

        // Accessors
        QString name(void);
        QStringList itemAt(const int&); /** retrieve a QStringList of an item at position i */
        const int count(void) const; /** retrieves the number of words in dictionary **/

        // Misc
        static QString posFromAbbr(QChar);
        static QChar   posFromName(QString);

    private:

        void load_file(const QString&); /** brains behind the public load() function */
        void parse_line(QString); /** parses lines in the file load() function */

        int _count;                 /** size of dictionary */
        QString _name;             /** the name of the dictionary */

        QStringList _words;        /** list of words */
        QList<QChar> _pos;          /** list of parts of speech for words */
        QStringList _definitions;  /** list of word definitions */
};

#endif
