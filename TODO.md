#For Lyngo Drillbit

* Make drillbit source conform to new conventions

* Make drillbit use LyDict model code from dictedit.

* Change ldb format to be more flexible, use lines prefixed with an '!' to
  execute commands to specify variables, instead of just using it for the
  language. I.E., !lang1=EN,lang2=JP -- also possibly add the functionality of
  specifying the format of the columns, in this way (i.e., !LANG1 POS LANG2)
  this way the file format is more flexible.

* Add options dialog (and/or menus) to control:
    * # of times a question can be wrong before skipping to the next question
    * Which language should be presented in the question, and which should be
       available in the answer (if not using both and randomly picking just one).
       i.e., asking a word in english with presented words in spanish, vice versa,
       or mixed

* Add generate HTML quiz option to allow creation of HTML forms quizes (i.e.,
* forms with a submit button) or hand written quizes that can be printed out.
  Allow users to select # of questions, and a choice of random words, or let
  users pick words from a list with check boxes.

* Add a button to allow users to make corrections to any mispelled words in
  questions or answers.

* Add game show mode to allow "players" to get points, and with points they
* can buy prizes and stuff. (i.e., an "ability" to eliminate half of the wrnog
* choices).

#MISC

* Flash card program using drillbit files to produce flash cards for use on
  screen with option of producing html output for printing cut-out flash cards.

* Agenda application which can automatically download and synchronize
  assignments from the internet.
