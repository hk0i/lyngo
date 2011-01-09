#include "imp_drillbit.h"

#define UniqueAnswer while (isAChoice(myAnswers[rAns])) \
	                       rAns = qrand() % (myWords.size()-1);

//slots
void Imp_drillbit::mnuOpen_clicked(void)
{
	QString fName = QFileDialog::getOpenFileName(this,
								tr("Select a word list to review"),
								"",
								"Lyngo Drillbit File (*.ldb)");
	if (!fName.isEmpty())
	{
		//open the file!
		loadFile(fName);
	}

}

void Imp_drillbit::mnuExit_clicked(void)
{
	exit(0);
}


// button slots 
void Imp_drillbit::tbChoice1_clicked(void)
{
	// if it's the correct answer, advance to the next one.
	// TODO: Add a count for number of answers right/wrong and maybe a prompt
	// telling the users if they were right or wrong.
	if (myCorrect == 1)
	{
		nextWord();
		// increment myCurrent to avoid infinite loop.
	}
	else
	{
		// don't let them make the same mistake twice ;)
		// aww, we're such nice guys =)
		tbChoice1->setEnabled(false);
	}
}

void Imp_drillbit::tbChoice2_clicked(void)
{
	if (myCorrect == 2)
	{
		nextWord();
	}
	else
	{
		tbChoice2->setEnabled(false);
	}
}

void Imp_drillbit::tbChoice3_clicked(void)
{

	if (myCorrect == 3)
	{
		nextWord();
	}
	else
	{
		tbChoice3->setEnabled(false);
	}

}

void Imp_drillbit::tbChoice4_clicked(void)
{

	if (myCorrect == 4)
	{
		nextWord();
	}
	else
	{
		tbChoice4->setEnabled(false);
	}

}

//private functions
void Imp_drillbit::loadFile(const QString &fileName)
{
	QFile fFile(fileName);

	if (!fFile.exists())
	{
		std::cerr << "error: file does not exist ("
				  << fileName.toStdString().c_str()
				  << ")." << std::endl;
		return;
	}
	if (!fFile.open( QIODevice::ReadOnly ))
	{
		std::cerr << "error: could not open file ("
				  << fileName.toStdString().c_str()
				  << ")." << std::endl;
	}

	QTextStream ts(&fFile);
	ts.setCodec("UTF8");

	myWords.clear();
	myDefs.clear();
	myPOS.clear();
	myDone.clear();

	while (!ts.atEnd())
	{
		QString line = ts.readLine();
		parseLine(line);
	}

	std::cout << "Done loading file." << std::endl;
	nextWord();

	
}

void Imp_drillbit::parseLine(QString line)
{
	//TODO: Make this more robust -- it needs to be able to eat empty lines
	//without causing a ruckus!
	//TODO: Add another rule to ! -- make it more general so we can pass
	//arguments for language, and title, etc.. that way for japanese we can
	//provide full JP and then a hiragana version (then from hiragana somehow
	//create a romanization automatically-- or vice versa)
	//first rule, ignore comments.
	if (line.at(0) == '#')
		return;
	else if (line.at(0) == '!')
	{
		// second rule, ! prefixes the unit name.
		// so grab the name, and set our title accordingly.
		lblUnit->setText(line.right(line.size()-1));
		return;
	}

	// quick cheap way to get this function done fast. Should consider revising
	// for performance later
	QStringList word;
	word = line.split('\t');
	myWords.append(word[0]);
	myPOS.append(word[1][0]);
	myDefs.append(word[2]);
	myDone.append(false);

	std::cout << "myWords[" << myWords.count()-1 << "] = '"
			  << myWords.at(myWords.count()-1).toStdString().c_str() << "'"
			  << std::endl;
		
}

int Imp_drillbit::nextRand(void)
{
	return 0;
}

void Imp_drillbit::nextWord(void)
{

	int nextNum = -1;	// random number for next word.
	int rAns = 0;		// used for finding a unique random answer.
	QTime midnight(0, 0, 0);
	qsrand(midnight.secsTo(QTime::currentTime()));

	// if we've done all the words, don't try to do another one. you will end up
	// in an infinite loop ;p
	// TODO: Add a message asking user to start over.
	// TODO: move this to another function so we can say "YAY YOU WON. START
	// OVER?" and stuff. And make this function a little smaller
	if (myCompleted >= myWords.size()-1)
	{
		// StandardButton QMessageBox::question ( QWidget * parent,
		// const QString & title, const QString & text,
		// StandardButtons buttons = Ok,
		// StandardButton defaultButton = NoButton )   [static]
		int iReset = QMessageBox::question(this, tr("Lyngo Drillbit"),
									tr("Hey, looks like you've finished "
									"your drilling.\n"
									"Would you like to start back at the "
									"beginning?"),
									QMessageBox::Retry | QMessageBox::No,
									QMessageBox::Retry);

		if (iReset == QMessageBox::Retry)
		{
			std::cerr << "Restarting ..." << std::endl;
			restart();
		}


		return;
	}

	// I don't know why I do this, really...
	tbChoice1->setText("...");
	tbChoice2->setText("...");
	tbChoice3->setText("...");
	tbChoice4->setText("...");

	// enable all the buttons so we can click 'em.
	enableButtons();

	// randomly pick a word that hasn't been done yet.
	std::cerr << "Picking a word . . ." << std::endl;
	while (nextNum == -1)
	{
		nextNum = qrand() % (myWords.size() - 1);
		/*std::cerr << "nextNum \t" << nextNum << "\tmyWords.size()" << myWords.size()
				  << std::endl;*/
		if (myDone[nextNum])
			nextNum = -1;
	}

	// set that we have picked this word before, so it won't repeat
	myDone[nextNum] = true;

	// pick which set of words to use as questions, and which to use as answers.
	// To do this we'll use some pointers.
	myQuestions = 0;
	myAnswers = 0;

	int tails = 0; //heads or tails.
	tails = (qrand() % 2);
	if (tails)
	{
		myQuestions = myWords.data();
		myAnswers = myDefs.data();
	}
	else
	{
		myQuestions = myDefs.data();
		myAnswers = myWords.data();
	}

	// now that we picked the next word, display it.
	lblWord->setText(myQuestions[nextNum]);

	std::cerr << "Word selected ["
			  << myQuestions[nextNum].toStdString().c_str()
			  << "], picking myAnswers . . ." << std::endl;
	
	// insert the correct answer into a random slot
	myCorrect = (qrand() % 4) +1;
	switch (myCorrect)
	{
		case 1:
			tbChoice1->setText(myAnswers[nextNum]);
			break;

		case 2:
			tbChoice2->setText(myAnswers[nextNum]);
			break;

		case 3:
			tbChoice3->setText(myAnswers[nextNum]);
			break;

		case 4:
		default:
			tbChoice4->setText(myAnswers[nextNum]);
			break;
	}

	// randomly select the rest of the myAnswers, but make sure none are in use.

	rAns = nextNum;	// without this the loop won't start and all myAnswers except
					// the real answer will print out as myAnswers[0]
	if (myCorrect != 1)
	{
		UniqueAnswer
		tbChoice1->setText(myAnswers[rAns]);
	}
	if (myCorrect != 2)
	{
		UniqueAnswer
		tbChoice2->setText(myAnswers[rAns]);
	}
	if (myCorrect != 3)
	{
		UniqueAnswer
		tbChoice3->setText(myAnswers[rAns]);
	}
	if (myCorrect != 4)
	{
		UniqueAnswer
		tbChoice4->setText(myAnswers[rAns]);
	}

	myCompleted ++;
	updateTitle();

}

bool Imp_drillbit::cAnswerPresent(void)
{
	if (tbChoice1->text() == myAnswers[myCurrent])
		return true;
	if (tbChoice2->text() == myAnswers[myCurrent])
		return true;
	if (tbChoice3->text() == myAnswers[myCurrent])
		return true;
	if (tbChoice4->text() == myAnswers[myCurrent])
		return true;
	return false;
}

bool Imp_drillbit::isAChoice(QString test)
{
	//std::cout << "Testing word: " << test.toStdString().c_str() << std::endl;
	if (tbChoice1->text() == test)
		return true;
	if (tbChoice2->text() == test)
		return true;
	if (tbChoice3->text() == test)
		return true;
	if (tbChoice4->text() == test)
		return true;
	return false;
}

void Imp_drillbit::updateTitle(void)
{
	QString title;
	QTextStream ts (&title);
	ts << "Lyngo Drillbit (" << myCompleted << "/" << myWords.size() << ")";
	this->setWindowTitle(title);
}

void Imp_drillbit::restart(void)
{
	// blank out the completed array
	for (int i = 0; i < myDone.size(); i++)
		myDone[i]=false;
	myCompleted = 0;

	nextWord();
}

void Imp_drillbit::enableButtons(void)
{
	tbChoice1->setEnabled(true);
	tbChoice2->setEnabled(true);
	tbChoice3->setEnabled(true);
	tbChoice4->setEnabled(true);
}

