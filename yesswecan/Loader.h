class Loader
{
   private:
      bool loaded;        //set to true if a file is successfully loaded into memory
      std::ifstream inf;  //input file handle
   public:
      void loadline(char line[]);

      int32_t convert(char line[], int32_t beg, int32_t end);
      bool canLoad(char inFile[]);
      Loader(int argc, char * argv[]);
      bool isLoaded();
      bool hasErrors(char line[]);
      bool addrCheck(char line[]);
      bool dataCheck(char line[]);
      bool spaceCheck(char line[]);
      bool colonCheck(char line[]);
      bool pipeCheck(char line[]);
      bool isHex(char ch);

};
