######################################################################
# Automatically generated by qmake (2.01a) Sat Jan 15 11:21:50 2011
######################################################################

TEMPLATE = app
TARGET = quiz
DEPENDPATH += .
INCLUDEPATH += . ../
CONFIG += debug

mac {
    CONFIG -= app_bundle
    CONFIG -= debug
}

# Input
SOURCES += quiz.cpp \
           ../LyQuestion.h \
           ../LyQuestion.cpp \
           ../LyDict.h \
           ../LyDict.cpp \
           ../LyWord.h \
           ../LyWord.cpp \
           ../LyQuiz.h \
           ../LyQuiz.cpp
