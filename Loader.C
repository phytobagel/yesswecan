/**
 * Names: Joe Sawin Jerome Glenn
 * Team:24
*/
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <ctype.h>
#include <string>
#include "Loader.h"
#include "Memory.h"

//first column in file is assumed to be 0
#define ADDRBEGIN 2   //starting column of 3 digit hex address 
#define ADDREND 4     //ending column of 3 digit hext address
#define DATABEGIN 7   //starting column of data bytes
#define COMMENT 28    //location of the '|' character 



/**
 * Loader constructor
 * Opens the .yo file named in the command line arguments, reads the contents of the file
 * line by line and loads the program into memory.  If no file is given or the file doesn't
 * exist or the file doesn't end with a .yo extension or the .yo file contains errors then
 * loaded is set to false.  Otherwise loaded is set to true.
 *
 * @param argc is the number of command line arguments passed to the main; should
 *        be 2
 * @param argv[0] is the name of the executable
 *        argv[1] is the name of the .yo file
 */
Loader::Loader(int argc, char * argv[])
{
   loaded = false;

   //Start by writing a method that opens the file (checks whether it ends 
   //with a .yo and whether the file successfully opens; if not, return without 
   //loading)
    
   if (!Loader::canLoad(argv[1]))
   {
       return;
   }

    

   //The file handle is declared in Loader.h.  You should use that and
   //not declare another one in this file.
   
   //Next write a simple loop that reads the file line by line and prints it out
   
    char arr[250];
    int lineNumber = 1;
    while (inf.peek() != EOF)
    {
        inf.getline(arr, 250);

        if (arr[0] == '0' && arr[DATABEGIN] != ' ')
        {
            Loader::loadline(arr);
        }
        
        if (hasErrors(arr)) 
            {
              std::cout << "Error on line " << std::dec << lineNumber
                        << ": " << arr << std::endl;
              return;
            }
        lineNumber++;
    
    }

   //Next, add a method that will write the data in the line to memory 
   //(call that from within your loop)
   
    

   //Finally, add code to check for errors in the input line.
   //When your code finds an error, you need to print an error message and return.
   //Since your output has to be identical to your instructor's, use this cout to print the
   //error message.  Change the variable names if you use different ones.
   //  std::cout << "Error on line " << std::dec << lineNumber
   //       << ": " << line << std::endl;
    
    
    if (hasErrors(arr)) 
        {
            std::cout << "Error on line " << std::dec << lineNumber
                      << ": " << arr << std::endl;
            return;
        }


   //If control reaches here then no error was found and the program
   //was loaded into memory.
   loaded = true;  
  
}

/**
 * isLoaded
 * returns the value of the loaded data member; loaded is set by the constructor
 *
 * @return value of loaded (true or false)
 */
bool Loader::isLoaded()
{
   return loaded;
}


//You'll need to add more helper methods to this file.  Don't put all of your code in the
//Loader constructor.  When you add a method here, add the prototype to Loader.h in the private
//section.

//takes as input the name of the input file, returns true if the name of the file ends
//with a .yo extension and the file can be opened (it opens the file using the 
//c++ ifstream open method).  If the file can't be opened (doesn't exist or the filename 
//is incorrect), the function returns false. Note that the file handle you'll use is 
//declared as a private data member (an ifstream) in the Loader class
bool Loader::canLoad(char inFile[])
{
    int size = strlen(inFile);
    
    if (!(inFile[size - 3] == '.' 
        && inFile[size - 2] == 'y'
        && inFile[size - 1] == 'o' ))
    {
        return false;
    }        

    inf.open(inFile, std::ifstream::in);

    if (!(inf.good()))
    {
        return false;
    }
    
    return true;
}   
   
   
//Parameter = char line[].  This should be the current line that the constructor
//is loading into memory.  It can be assumed here that line has an address and
//has data.  Loadline should put the data into memory at the given address.
//It should not return any data.
    
void Loader::loadline(char line[])
{   
    Memory * mem = Memory::getInstance();              //This will either create a new memory object
                                                       //or return an existing one.
    
    uint32_t addr = convert(line, ADDRBEGIN, ADDREND); //starting address for loading
    
    bool error = false;                                //for error checking
    
    //loops through the data segement, and loads it into memory
    //byte by byte.
     
    for (int i = DATABEGIN; line[i] != ' '; i += 2)              //This for loop should loop through the data
    {                                                            //to be stored and store it byte by byte.
        int8_t data = Loader::convert(line, i, (i + 1));        //numeric data to store
        
        mem->putByte(data, addr, error);                         //this method stores the data at the specified address
                                                                 //in data.
        addr++;                                                  //address needs to be incremented
    }
}    
    
//takes as input the full line, the start of the address to store in,
//and the end of the address to store in, and returns the numeric
//value of the address in mem where it should be stored in
//if you give it 0x00a return 10.
    
int32_t Loader::convert(char line[], int32_t beg, int32_t end)
{        
    int32_t j = 0;
    char chrArray[4] = {0};
    
    for (int i = beg; i <= end; i++, j++)
    {
        chrArray[j  ] = line[i];      
    }
    
    
    return std::stoul(chrArray, NULL, 16);
}

//takes as input an individual line.  Method goes through several checks
//on the given line, returning true at any point where an error is 
//detected.  If every check passes, the method returns false. Each check
//is self contained in a helper method.

bool Loader::hasErrors(char line[])
{ 
//    if (addrCheck(line) && dataCheck(line) &&
  //      spaceCheck(line) && colonCheck(line) &&
//        pipeCheck(line))
//    {
//        return false;
//    }
    return false;
}


//checking for correct address formatting?
bool Loader::addrCheck(char line[])
{
    if (line[0] != '0' || line[1] != 'x')
    {
      return false; 
    }

     for (int i = 2; i < 5; i++)
        {
            if(!isHex(line[i]))
            {
            return false;
            }
        }

    return true;
}

//checking for correct data formatting!
//characters must be valid hex, databegin must
//be starting point, no spaces throughout until the
//end.  Length must be an even number in between 2 and 20.
bool Loader::dataCheck(char line[])
{
    int count = 0;
    for(int i = DATABEGIN; line[i] != ' ';i++)
    {
        if(isHex(line[i]))
        {
            count++;
        }
    }

    for(int i = count; line[i] != '|'; i++)
    {
        if(line[i] != ' ')
        {
            return false;
        }
    }

    if (count % 2 == 0 && count >=2 && count <= 20)
    {
        return true;
    }
    return false;
}

bool Loader::spaceCheck(char line[])
{
    if (line[6] != ' ' && line[27] != ' ')
    {
    return false;
    }
    return true;
}

bool Loader::colonCheck(char line[])
{
    if (line[5] != ':')
    {
        return false;
        }
        return true;
}

bool Loader::pipeCheck(char line[])
{
    if (line[28] != '|')
    {
        return false;
    }
    return true;
}

bool Loader::isHex(char ch)
{
     if(!((ch >= 48 && ch <= 57) || 
          (ch >= 65 && ch <= 70) ||
          (ch >= 97 && ch <= 102)))
     return true;
     else
     return false;    
}
