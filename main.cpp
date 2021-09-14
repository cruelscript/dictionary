#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include "BinaryTreeSearch.hpp"

typedef BinaryTreeSearch<std::string> Dictionary;
enum    State
{
  START,
  ACTION_SELECTION,
  INSERT_WORD,
  SEARCH_WORD,
  DELETE_WORD,
  RETURN,
  SAVE,
  EXIT
};

int chooseDictionary();
int chooseAction();
int chooseToReturn();

int printMenu(State programState);
State processInput(Dictionary* dictionary, State programState, int userChoice, std::istream& in, std::ostream& out);

int main()
{
  try
  {
    std::cout << "Enter the input file: ";
    std::string fileName;
    std::cin >> fileName;

    std::ifstream in(fileName);
    if(!in.is_open())
    {
      std::string e = "main: Error. " + fileName + "was not found";
      throw std::exception(e.c_str());
    }
    std::ofstream out("newDictionary.txt");

    State programState = START;

    size_t dictionarySize = 0;
    in >> dictionarySize;
    if(!in)
    {
      std::string e = fileName + ": Error. Invalid size of the dictionary.";
      throw std::exception(e.c_str());
    }
    if(dictionarySize == 0)
    {
      std::string e = fileName + ": Error. Size cannot be zero.";
      throw std::exception(e.c_str());
    }
    if(dictionarySize > 100000)
    {
      std::string e = fileName + ": Error. Size cannot be more than 100000.";
      throw std::exception(e.c_str());
    }

    auto dictionary = new BinaryTreeSearch<std::string>(dictionarySize);
    if(!dictionary)
    {
      throw std::bad_alloc();
    }

    while(programState != EXIT)
    {
      int userChoice = printMenu(programState);
      programState = processInput(dictionary, programState, userChoice, in, out);
    }
    delete dictionary;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return -1;
  }
  return 0;
}

int printMenu(State programState)
{
  switch(programState)
  {
  case ACTION_SELECTION:
    return chooseAction();
  case RETURN:
    return chooseToReturn();
  }
}

State processInput(Dictionary* dictionary, State programState, int userChoice, std::istream& in, std::ostream& out)
{
  std::string userString;
  std::string word, translations;

  switch(programState)
  {
  case START:
    dictionary->insert(in);
    std::cout << "Dictionary has been successfully generated.\n";
    system("pause");
    return ACTION_SELECTION;


  case ACTION_SELECTION:
    switch(userChoice)
    {
    case 0:
      return INSERT_WORD;
    case 1:
      return SEARCH_WORD;
    case 2:
      return DELETE_WORD;
    default:
      return SAVE;
    }

  case INSERT_WORD:
    std::cout << "Print a word you want to add: ";
    std::cin >> word;
    std::cout << "\nGreat. Print a translation to it. Use ';' to add more than one.\n";
    std::cin >> translations;
    std::cout << (dictionary->insert(word, translations)
                  ? "The word has been successfully inserted.\n"
                  : "Word was not added.\n");
    system("pause");
    return RETURN;

  case SEARCH_WORD:
    std::cout << "Print a word you want to find: ";
    std::cin >> userString;
    dictionary->print(std::cout, userString);
    system("pause");
    return RETURN;

  case DELETE_WORD:
    std::cout << "Print a word you want to delete: ";
    std::cin >> userString;
    std::cout << (dictionary->deleteWord(userString) ? "The word has been successfully deleted.\n" : "");
    system("pause");
    return RETURN;

  case RETURN:
    return userChoice ? SAVE : ACTION_SELECTION;

  case SAVE:
    std::cout << "Do you want to save changes? (y/n)\n";
    std::cin >> userString;

    if(userString == "y" || userString == "Y" || userString == "yes" || userString == "Yes")
    {
      dictionary->print(out);
      std::cout << "\nDictionary was saved to newDictionary.txt";
    }
    std::cout << "\nEnglish-Russian dictionary.\ncruelscript 2020\n";

  default:
    return EXIT;
  }
}

int chooseAction()
{
  int N_OPTIONS = 4;
  int key = 0;
  int code = 0;
  do
  {
    system("cls");
    key = (key + N_OPTIONS) % N_OPTIONS;
    std::cout << "Choose an action to do:  \n";
    std::cout << (key == 0 ? "->" : "   ");
    std::cout << "Insert new word.\n";
    std::cout << (key == 1 ? "->" : "   ");
    std::cout << "Search for a word.\n";
    std::cout << (key == 2 ? "->" : "   ");
    std::cout << "Delete word.\n";
    std::cout << (key == 3 ? "->" : "   ");
    std::cout << "Quit.\n";

    code = _getch();

    if(code == 224)
    {
      code = _getch();
      if(code == 72)
      {
        key--;
      }
      if(code == 80)
      {
        key++;
      }
    }
  }
  while(code != 13);
  system("cls");
  return key;
}

int chooseToReturn()
{
  int N_OPTIONS = 2;
  int key = 0;
  int code = 0;
  do
  {
    system("cls");
    key = (key + N_OPTIONS) % N_OPTIONS;
    std::cout << "Choose an action to do:  \n";
    std::cout << (key == 0 ? "->" : "   ");
    std::cout << "Return to action selection.\n";
    std::cout << (key == 1 ? "->" : "   ");
    std::cout << "Quit.\n";

    code = _getch();

    if(code == 224)
    {
      code = _getch();
      if(code == 72)
      {
        key--;
      }
      if(code == 80)
      {
        key++;
      }
    }
  }
  while(code != 13);
  system("cls");
  return key;
}