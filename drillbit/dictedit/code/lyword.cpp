#include "lyword.h"

LyWord::LyWord(void)
{

}

LyWord::LyWord(const QString &word,
               const QChar   &pos,
               const QString &definition)
{
    this->_word = word;
    this->_pos  = pos;
    this->_definition = definition;
}

QString LyWord::word(void) const       { return _word; }
QString LyWord::definition(void) const { return _definition; }
QChar   LyWord::pos(void) const        { return _pos; }

/**
 * @brief
 *  Returns a human-readable word representing the part of speech.
 */
QString LyWord::partOfSpeech(void) const
{
    switch (_pos.toAscii()) {

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
 *  Returns a QStringList of all the word's data linked together
 * @param fileOutput
 *  When set to true (the default value) this will output the part of speech a
 *  a single character instead of a human-understandable word. Set this value
 *  to false when using data() for a human display.
 */
QStringList LyWord::data(bool fileOutput) const
{
    QStringList ret;
    ret << _word;
    if (fileOutput)
        ret << _pos;
    else
        ret << partOfSpeech();
    ret << _definition;
    return ret;
}

void LyWord::setWord(const QString &newWord)
{
    _word = newWord;
}

void LyWord::setDefinition(const QString &newDef)
{
    _definition = newDef;
}

void LyWord::setPos(const QChar &newPos)
{
    _pos = newPos;
}
