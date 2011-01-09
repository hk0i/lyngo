#ifndef __IMP_DRILLBIT_H
#define __IMP_DRILLBIT_H

#include <iostream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTime>
#include <QVector>
#include "ui_drillbit.h"

class Imp_drillbit: public QMainWindow, Ui::MainWindow
{

	Q_OBJECT

	public:
		Imp_drillbit() : QMainWindow(),
			myCompleted (0)
			//myWords(255), myDefs(255), myPOS(255)	//init vectors to 255 len.
		{
			 setupUi(this);

			 // connect signals and slots
			 connect (mnuOpen, SIGNAL(triggered()), this,
					 SLOT(mnuOpen_clicked()));
			 connect (mnuExit, SIGNAL(triggered()), this,
					 SLOT(mnuExit_clicked()));

			 //buttons
			 connect (tbChoice1, SIGNAL(clicked()), this,
					 SLOT(tbChoice1_clicked()));
			 connect (tbChoice2, SIGNAL(clicked()), this,
					 SLOT(tbChoice2_clicked()));
			 connect (tbChoice3, SIGNAL(clicked()), this,
					 SLOT(tbChoice3_clicked()));
			 connect (tbChoice4, SIGNAL(clicked()), this,
					 SLOT(tbChoice4_clicked()));

		}

	private slots:

		// Menus
		// File menu
		void mnuOpen_clicked(void);
		void mnuExit_clicked(void);

		//buttons
		void tbChoice1_clicked(void);
		void tbChoice2_clicked(void);
		void tbChoice3_clicked(void);
		void tbChoice4_clicked(void);

	private:

		//functions
		void loadFile (const QString &fileName);// load the .ldb file, populate
												// vectors

		void parseLine (const QString line);	// parses lines from  ldb file
												// and adds

		int nextRand (void);					// gets next random number as a
												// helper function to nextWord.

		void nextWord (void);					// prompts user for the next
												// word. and sets up variables
												// accordingly
		bool cAnswerPresent (void);				// returns true when the correct
												// answer is available in the
												// list of choices.
		bool isAChoice (QString);				// returns true if QString is
												// already listed as a possible
												// answer.
		void updateTitle (void);				// udpates titledbar with
												// (currentWord/TotalWords)

		void restart (void);					// restarts the driller (reloads
												// the current drill file).

		void enableButtons(void);				// enables all buttons (used at
												// the start of the next
												// question).

		// storage for lyngo drill bit data:
		QVector<QString> myWords;	// word list
		QVector<QString> myDefs;	// definitions
		QString *myQuestions; 		// points to the array currently being used
	   								//	for questions
		QString *myAnswers;			// points to the array currently being used
									// for answers.
		QVector<QChar>   myPOS;  	// parts of speech
		QVector<bool>	 myDone;	// determines which problems are finished
	   								// by placing a true or false value in the
									// appropriate column.	
		int				 myCurrent;	// current word being tested
		int				 myCorrect;	// the current correct answer (values 1-4)
		int				 myCompleted;// stores the number of questions completed
									 // to avoid the infinite loop caused by the
									 // last question searching the myDone list.
		//*/


};

#endif


// extra notes go here.
// TODO: Add a text input option. Make them type it for better practice! Don't
// be lazy! Also perhaps add something to let them type in symbols if they don't
// have them already on their keyboards.
