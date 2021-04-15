/***********************************************************************
* Author:
*    Jared Denning
* Summary: 
*    Simple program that allows user to play sodoku
************************************************************************/

using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>


const char letters[10] = "ABCDEFGHI";
const char numbers[10] = "123456789";

/**********************************************************************
 * Main function that gets fileName and initially displays options 
 * board. Enters a do while loop to continue playing the game.
 ***********************************************************************/
char checkCell(char board[9][9], int row, int column,char pValues[10],
               int &count)
{
   //same count to keep track of length of pValues
   count = 0;
   
   
   //Going through the constant numbers
   for (int i = 0; i < 9; i++)
   {
      //this counter checks to see how many times numbers[i] is in
      //the row or column. If its more than 0 then we know we dont
      //need it.
      int counter = 0;
      
      //checks if the numbers are in the row
      for (int j = 0; j < 9; j++) 
      {
         //if it finds the number in row, counter goes up
         if (numbers[i] == board[row][j])
         {
            counter++;
         }
      }
      //checks if the numbers are in the column
      for (int j = 0; j < 9; j++) 
      {
         //now checks both the column and the numbers in pValues
         if (numbers[i] == board[j][column])
         {
            counter++;
         }
      }

      //this for loop checks the square
      for (int j = 0; j <= 2; j++)//j is for row
      {
         for (int k = 0; k <= 2; k++)//k is for column
         {
         //uses integer division to get the start of the 
         //row and column for square
            if (board[row / 3 * 3 + j][column / 3 * 3 + k] 
               == numbers[i])          
               counter++;
         }
      }
      //if counter wasnt incremented, then the number was not in 
      //the row, column or square and can be added to pValues
      if (counter == 0)
      {
         //increment count to keep track of pvalues after every
         //addition
         pValues[count] = numbers[i];
         count++;
      }
      
   }
   //sets the last position in pvalues to null so we can traverse
   //through it easier.
   pValues[count] = '\0';

}

/**********************************************************************
 * Main function that gets fileName and initially displays options 
 * board. Enters a do while loop to continue playing the game.
 ***********************************************************************/
bool isSolvable(char board[9][9], int row, int column, char pValues[10]
                , int count)
{
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         if (board[i][j] == '0')
         {
            row = i;
            column = j;
            checkCell(board, row, column, pValues, count);
            if (count == 0)
            {
               return false;
            }
         }
      }
   }
   return true;
}
 
/**********************************************************************
 * simple read file functions. Takes the txt file and creates a 9x9
 * array.
 ***********************************************************************/
bool isComplete(char board[9][9])
{
   for (int i = 0; i <= 8; i++)
   {
      for (int j = 0; j <= 8; j++)
      {
         if (board[i][j] == '0')
         {
            return false;
         }
      }
   }
   return true;
}

/**********************************************************************
 * Simple function to display the array as a sodoku board
 ***********************************************************************/
void displayBoard(char board[9][9])
{
   cout << "   A B C D E F G H I\n";  
   
   //nested for loops to get to single elmements in array
   //conditional then helps decide where to put spaces
   for (int i = 0; i <= 8; i++)
   {
      cout << i + 1 << "  ";
      for (int j = 0; j <= 8; j++)
      {
         cout << (board[i][j] == '0' ? ' ' : board[i][j])
              << ((j + 1) % 3 != 0 || j == 8 ? "" : "|")
              << ((j + 1) % 3 != 0 ? " " : "")
              << (j == 8 ? "\n" : "");
      }
      
      if (i == 2 || i == 5)
         cout << "   -----+-----+-----\n";
   }
   cout << endl;
}

/**********************************************************************
 * simple read file functions. Takes the txt file and creates a 9x9
 * array.
 ***********************************************************************/
void chooseCell(char board[9][9], int &row, int &column, 
                char pValues[10], int &count)
{

   //goes through rows
   for (int i = 0; i <=8; i++)
   {
      //cout << "I: " << i << endl;
      //goes through columns
      for (int j = 0; j <=8; j++)
      {
         //cerr << "J: " << j << endl;
         //checks for an empty square
         if (board[i][j] == '0')
         {
            row = i;
            column = j;
            checkCell(board, row, column, pValues, count);
         }
      }
   } 
   return;
}

/**********************************************************************
 * simple read file functions. Takes the txt file and creates a 9x9
 * array.
 ***********************************************************************/
int chooseNextValue(char board[9][9], char pValues[10], int &count, int needed[4][75], int step)
{
   checkCell(board, needed[1][step], needed[2][step], pValues, count);
   //board[needed[1][step]][needed[2][step]] = pValues[needed[3][step]];
   
   cout << "step: " << step << " count: " << count << " index: " << needed[3][step] << endl;
   for (int i = 0; pValues[i]; i++)
   {
      cout << pValues[i] << ", ";
   }
   cout << endl;
   if (isSolvable(board, needed[1][step], needed[2][step], pValues, count) == false)
   {  
   
      if (count == 0)
      {
         return 0;
      }
      needed[3][step] += 1;
      return 0;
   }
   if (needed[3][step] < count - 1)
   {
      board[needed[1][step]][needed[2][step]] = pValues[needed[3][step]];
      needed[3][step] += 1;
   }
   
      
   return 1;
}

/**********************************************************************
 * simple read file functions. Takes the txt file and creates a 9x9
 * array.
 ***********************************************************************/
int changeLastValue(char board[9][9], char pValues[10], int &count,int needed[4][75], int &step)
{

   board[needed[1][step]][needed[2][step]] = pValues[needed[3][step]];
   checkCell(board, needed[1][step], needed[2][step], pValues, count);
   cout << "step: " << step << " count: " << count << " index: " << needed[3][step] << endl;
   for (int i = 0; pValues[i]; i++)
   {
      cout << pValues[i] << ", ";
   }
   if (needed[3][step] == 0)
   {
      //this means that there was only one option so make that zero and go back one more
      if (count == 1)
      {
         board[needed[1][step]][needed[2][step]] = '0';
         //board[needed[1][step - 1]][needed[2][step - 1]] = '0';
         step -= 2;
         checkCell(board, needed[1][step], needed[2][step], pValues, count);
         return 0;
      }
      
      board[needed[1][step]][needed[2][step]] = '0';
      return -1;
   }
   if (needed[3][step] < count - 1)
   {
      board[needed[1][step]][needed[2][step]] = pValues[needed[3][step]];
      needed[3][step] += 1;
      return 1;
   }
   if (needed[3][step] == count - 1)
   {
      //board[needed[1][step]][needed[2][step]] = pValues[needed[3][step]];
      //checkCell(board, needed[1][step - 1], needed[2][step - 1], pValues, count);
      needed[3][step] = 0;
      return 1;
   }
}

/**********************************************************************
 * simple read file functions. Takes the txt file and creates a 9x9
 * array.
 ***********************************************************************/
void solveBoard(char board[9][9], int &count, char pValues[10], int needed[4][75], int &step)
{
   int row;
   int column;
   
   if (isComplete(board) == true)
   {
      displayBoard(board);
      cout << "SUCCESS!\n";
      return;
   }
   if (isSolvable(board, row, column, pValues, count) == true)
   {
      cout << "True\n";
      step += chooseNextValue(board, pValues, count, needed, step); 
      return;  
   }
   
   if (isSolvable(board, row, column, pValues, count) == false)
   {
      cout << "False\n";
      //if (count > 1)
      board[needed[1][step]][needed[2][step]] = '0';
      step += changeLastValue(board, pValues, count, needed, step);
      return;
   }
   
   //solveBoard(board, count, pValues, needed, step);
   
}

/**********************************************************************
 * simple read file functions. Takes the txt file and creates a 9x9
 * array.
 ***********************************************************************/
int readFile(char fileName[256], char board[9][9], int needed[4][75])
{
   ifstream fin(fileName);
   
   if (fin.fail())
   {
      return -1;
   }

   for (int i = 0; i <= 8; i++)
   {
      for (int j = 0; j <= 8; j++)
      {
         fin >> board[i][j];
      }
   }
   fin.close();
   
   //needed is 4 dimensional array for spots on board[][] 
   //that need to be filled
   //first spot is position in array
   //second is row number of that position
   //third is column number
   //fourth is number of pValues it tried last
   int count = 0;
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         if (board[i][j] == '0')
         {
           needed[0][count] = count;
           needed[1][count] = i;
           needed[2][count] = j;
           needed[3][count] = 0;
           count++;
           
         }
      }
   }
   needed[0][count] = '\0';
   needed[1][count] = '\0';
   needed[2][count] = '\0';
   
   return 1;
}

/**********************************************************************
 * simple function meant to just display options.
 ***********************************************************************/
void displayOptions()
{
   cout << "Options:\n"
        << "   ?  Show these instructions\n"
        << "   D  Display the board\n"
        << "   E  Edit one square\n"
        << "   S  Show the possible values for a square\n"
        << "   Q  Save and Quit\n"
        << "   X  Solve Board\n\n";
}

/**********************************************************************
 * This asks for coordinates from user. Finds the coordinates relative
 * to the array, and then asks for users input on what to change it to.
 * Returns error if the coordinate already has a value.
 ***********************************************************************/
void editBoard(char board[9][9], int &count, char pValues[10])
{
   
   char coord[3];
   int column;
   int row;
   char value;
   
   cout << "What are the coordinates of the square: ";
   cin >> coord;
   
   //Uses ASCII table to go to an integer
   row = coord[1] - 49;
   
   //Uses ASCII table to turn any lowercase into uppercase
   if (coord[0] >= 97 && coord[0] <= 122)
      coord[0] -= 32;
   
   //loops through the letters in the constant Letters to find the
   //element place through the incremention of i
   for (int i = 0; i < 9; i++)
   {
      if (coord[0] == letters[i])
         column = i;
   }
   //checks to see if cell is filled
   if (board[row][column] != '0')
   {
      cout << "ERROR: Square '" << coord << "' is filled\n";
      return;
   }
    //after verifying that square is not filled, checks for
    //possible values
   checkCell(board, row, column, pValues, count);
      
   cout << "What is the value at '" << coord[0] << coord[1] << "': ";
   cin >> value;
   
   //another counter and loop to keep track of number of times number is in
   //pValues. If it is not in there, then it cant be put into the cell
   int counter = 0;
   for (int i = 0; i < count; i++)
   {
      if (value == pValues[i])
      {
         counter++;
      }
   }
   
   //if the counter stayed 0 then the users input was not in the list
   //of legal inputs and returns error.
   if (counter == 0)
   {
      cout << "ERROR: Value '" << value << "' in square '" << coord 
           << "' is invalid\n";
      return;
   }
   
   board[row][column] = value;
   
   return;
}

/**********************************************************************
 * Simple write function that writes the sodoku array into a file. 
 ***********************************************************************/
int saveBoard(char board[9][9])
{
   char dfileName[256];
   
   cout << "What file would you like to write your board to: ";
   cin >> dfileName;
   ofstream fout(dfileName);
   
   if (fout.fail())
   {
      return -1;
   }
   
   for (int i = 0; i <= 8; i++)
   {
      for (int j = 0; j <= 8; j++)
      {
         fout << (board[i][j] == ' ' ? '0' : board[i][j]) 
              << (j == 8 ? '\n' : ' ');     
      }
   }
   
   fout.close();
   
   cout << "Board written successfully\n";
   return 1;
}

/**********************************************************************
 * Function for users input of 'S' that calls the checkCell function
 * to check for possible values in the cell user gives us.
 ***********************************************************************/
void possibleValues(char board[9][9], int &count, char pValues[10])
{
   char coord[3];
   int column;
   int row;
   
   cout << "What are the coordinates of the square: ";
   cin >> coord;
   
   //Uses ASCII table to go to an integer
   row = coord[1] - 49;
   
   //Uses ASCII table to turn any lowercase into uppercase
   if (coord[0] >= 97 && coord[0] <= 122)
      coord[0] -= 32;
   
   //loops through the letters in the constant Letters to find the
   //element place through the incremention of i
   for (int i = 0; i < 9; i++)
   {
      if (coord[0] == letters[i])
         column = i;
   }
   
   //Makes sure that it is an empty cell
   if (board[row][column] != '0')
   {
      cout << "ERROR: Square '" << coord << "' is filled\n\n";
      return;
   }

   //this changes the pValues array so we can use it.
   checkCell(board, row, column, pValues, count);
   
   cout << "The possible values for '" << coord << "' are: ";
   
   //loops through for commas and spaces for UI
   for (int i = 0; pValues[i]; i++)
   {
      cout << pValues[i];
      if (i < count - 1)
         cout << ", "; 
   }
   cout << endl;
}

/**********************************************************************
 * Main function that gets fileName and initially displays options 
 * board. Enters a do while loop to continue playing the game.
 ***********************************************************************/
int main()
{
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   //These three statements make it so we can see the integers
   
   char pValues[10];
   char fileName[256];
   char board[9][9];
   int needed[4][75];
   char option;
   int count = 0;
   int step = 0;
   cout << "Where is your board located? ";
   cin >> fileName;
   cin.ignore();
   readFile(fileName, board, needed);
   
   displayOptions();
   displayBoard(board);
   //loops through the game unless the user quits with q or Q
   do
   {
      cout << "> ";
      cin >> option;
      if (option >= 97 && option <= 122)
         option -= 32;
         
      //calls function based on users input
      switch (option)
      {
         case '?':
            displayOptions();
            cout << endl;
            break;
         case 'D':
            displayBoard(board);
            break;
         case 'E':
            editBoard(board, count, pValues);
            cout << endl;
            break;
         case 'Q':
            saveBoard(board);
            break;
         case 'S':
            possibleValues(board, count, pValues);
            cout << endl;
            break;
         case 'X':
            solveBoard(board, count, pValues, needed, step);
            cout << endl;
            break;
         case 'C':
            isSolvable(board, 1, 2, pValues, count);
            cout << endl;
            break;
         
      }
   }
   while (option != 'Q');
   
   return 0;
}
