#include "LyWord.h"

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

/** Returns the word */
QString LyWord::word(void) const       { return _word; }
/** Returns the definition */
QString LyWord::definition(void) const { return _definition; }
/** Returns the QChar representing the part of speech.
 * @see partOfSpeech
 */
QChar   LyWord::pos(void) const        { return _pos; }

/**
 * @brief
 *  Returns a human-readable word representing the part of speech.
 *  The conversion table is as follows:
 *
 *  <table>
 *      <tr>
 *          <td>Symbol</td>
 *          <td>partOfSpeech Return Value</td>
 *      </tr>
 *      <tr>
 *          <td>e</td>
 *          <td>expression</td>
 *      </tr>
 *      <tr>
 *          <td>v</td>
 *          <td>verb</td>
 *      </tr>
 *      <tr>
 *          <td>n</td>
 *          <td>noun</td>
 *      </tr>
 *      <tr>
 *          <td>p</td>
 *          <td>pronoun</td>
 *      </tr>
 *      <tr>
 *          <td>a</td>
 *          <td>adjective</td>
 *      </tr>
 *      <tr>
 *          <td>d</td>
 *          <td>adverb</td>
 *      </tr>
 *      <tr>
 *          <td>r</td>
 *          <td>preposition</td>
 *      </tr>
 *      <tr>
 *          <td>c</td>
 *          <td>conjunction</td>
 *      </tr>
 *      <tr>
 *          <td>i</td>
 *          <td>interjection</td>
 *      </tr>
 *  </table>
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
 * @param[in] fileOutput
 *  When set to true (the default value) this will output the part of speech as
 *  a single character instead of a human-understandable word. Set this value
 *  to false when using data() for a human display.
 * @see partOfSpeech
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

/**
 * @brief
 *  Assigns the word attribute of the LyWord to newWord
 * @param[in] newWord
 *  The word to be assigned.
 */
void LyWord::setWord(const QString &newWord)
{
    _word = newWord;
}

/**
 * @brief
 *  Assigns the definition of a LyWord.
 * @param[in] newDef
 *  The new definition to be assigned to the LyWord.
 */
void LyWord::setDefinition(const QString &newDef)
{
    _definition = newDef;
}

/**
 * @brief
 *  Assigns a part of speech to the word.
 * @param[in] newPos
 *  A QChar representing the part of speech to assign to the word.
 */
void LyWord::setPos(const QChar &newPos)
{
    _pos = newPos;
}
