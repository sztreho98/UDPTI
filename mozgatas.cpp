#include <iostream>
#include <fstream>
#include "BT.h"

int main(int argc, const char *argv[])
{
  /
  if (argc != 3)
  {
 
    if (argv[1] && !argv[2])
    {
   
      std::cerr << "Nincs kimeneti file!" << std::endl \
        << "Hasznalat: " << argv[0] << " bemeneti_file kimeneti_file" \
        << std::endl;

     
      return -1;
    }

   
    std::cerr << "Hasznalat: " << argv[0] << " bemeneti_file kimeneti_file" \
      << std::endl;

    return -2;
  }

  
  std::ifstream input(argv[1]);

 
  if (!input)
  {
    std::cerr << "Bemeneti file nem olvashato!" << std::endl;
    return -3;
  }

  
  if (input.peek() == EOF)
  {
    std::cerr << "Bemeneti file ures!" << std::endl;
    return -4;
  }

  // Létrehozzuk a kimeneti file-t kezelő objektumot is
  std::ofstream output(argv[2]);

  
  char* currentChar = new char;

  
  BT BinTree;

  bool isComment = false;

 
  while(input.read(currentChar, sizeof(char)))
  {
    switch (*currentChar)
    {
      
      case '>':
      
        isComment = true;

       
        continue;

     
      case '\n':

      
        isComment = false;

        
        continue;

      
      case 'N':
        continue;
    }

   
    if(isComment)
    {
      continue;
    }

    
    for (int i = 0; i < 8; i++)
    {
      
      if(*currentChar & 0x80)
      {
        
        BinTree << '1';
      }
      else
      {
        
        BinTree << '0';
      }
     
      *currentChar <<= 1;
    }
  }


  input.close();

 
  BinTree.printAllNodes(BinTree.getRoot(), output);

 
  BinTree.printHeight(BinTree.getRoot(), output);

  
  BinTree.printAverage(BinTree.getRoot(), output);

 
  BinTree.printVariance(BinTree.getRoot(), output);

 
  BT BinTree2;

 
  BinTree2 = BinTree;

  
  output << std::endl << "******* MÁSOLAT *******" << std::endl << std::endl;
  BinTree2.printAllNodes(BinTree2.getRoot(), output);
  BinTree2.printHeight(BinTree2.getRoot(), output);
  BinTree2.printAverage(BinTree2.getRoot(), output);
  BinTree2.printVariance(BinTree2.getRoot(), output);

  
  BT BinTree3;

  
  BinTree3 = std::move(BinTree);

  output << std::endl << "******* MOZGATOTT *******" << std::endl << std::endl;
  BinTree3.printAllNodes(BinTree3.getRoot(), output);
  BinTree3.printHeight(BinTree3.getRoot(), output);
  BinTree3.printAverage(BinTree3.getRoot(), output);
  BinTree3.printVariance(BinTree3.getRoot(), output);

  
  output.close();

  delete currentChar;
  currentChar = nullptr;

  return 0;
}
