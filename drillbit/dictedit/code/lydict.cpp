#include "lydict.h"

#ifdef DEBUG
#include <iostream>
#endif

LyDict::LyDict(void)
{

}

void LyDict::load(const QString &fileName) { this->load_file(fileName); }
void LyDict::setName(const QString &newName) { this->_name = newName; }

void LyDict::load_file(const QString &fileName)
{
    QFile fp(fileName);

    if (!fp.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&fp);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line[0] != '#')
            parse_line(line);
    }

    fp.close();
}

void LyDict::parse_line(QString line)
{
    QStringList tokens = line.split('\t');
    if (line[0] == '!') {
        this->setName(line.remove(0,1));
        return;
    }

    if (tokens.count() > 2)
        this->add(tokens[0], tokens[1][0], tokens[2]);
}

/**
 * @brief Retrieve the number of words in dictionary
 */
const int LyDict::count(void) const { return _words.size(); }

/**
 * @brief convenience function for adding a word
 */
void LyDict::add(const QString &word,
                 const char &pos,
                 const QString &definition)
{
    this->add(word, QChar(pos), definition);
}

/**
 * @brief
 *  Adds a LyWord directly to the list.
 */
void LyDict::add(const LyWord &word)
{
    _words.append(word);
}

void LyDict::add(const QString &word,
                    const QChar &pos,
                    const QString &definition)
{
    LyWord newWord(word, pos, definition);
    _words.append(newWord);

    DEBUG_PRINT("Word added: "
            << newWord.data().join(QString(", "))
               .mid(2).toStdString().c_str());

}

/**
 * @brief Removes a word at position i
 */
void LyDict::removeAt(const int &i)
{
    _words.removeAt(i);
}

void LyDict::save(const QString &fileName)
{
    QFile fp(fileName);

    if (!fp.open(QIODevice::WriteOnly | QIODevice::Text)) {
        DEBUG_PRINT("Could not write to file " << fileName.toStdString().c_str());
        return;
    }

    QTextStream out(&fp);
    out << "!" << this->_name << endl;
    for (int i = 0; i < _words.size(); ++i)
        out << _words[i].data().join(QString("\t")).trimmed() << endl;
}

/**
 * @brief
 *  Creates a QStringList of the information of word at position i and returns
 *  it.
 */
LyWord *LyDict::itemAt(const int &i)
{
    return &_words[i];
}

QChar LyDict::posFromName(QString name)
{
    name = name.toLower();
    if (name == "expression")
        return 'e';
    else if (name == "verb")
        return 'v';
    else if (name == "noun")
        return 'n';
    else if (name == "pronoun")
        return 'p';
    else if (name == "adjective")
        return 'a';
    else if (name == "adverb")
        return 'd';
    else if (name == "preposition")
        return 'r';
    else if (name == "conjunction")
        return 'c';
    else if (name == "interjection")
        return 'i';
}

QString LyDict::posFromAbbr(QChar letter)
{
    letter = letter.toLower();
    switch (letter.toAscii()) {

        case 'e':
            return QString("expression");
            break;

        case 'v':
            return QString("verb");
            break;

        case 'n':
            return QString("noun");
            break;

        case 'p':
            return QString("pronoun");
            break;

        case 'a':
            return QString("adjective");
            break;

        case 'd':
            return QString("adverb");
            break;

        case 'r':
            return QString("preposition");
            break;

        case 'c':
            return QString("conjunction");
            break;

        case 'i':
            return QString("interjection");
            break;

        default:
            return QString("");
    }
}

/**
 * @brief
 *  Returns the name of the dictionary (the "Unit Title")
 */
QString LyDict::name(void)
{
    return this->_name;
}
