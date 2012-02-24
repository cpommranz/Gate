/*----------------------
   GATE version name: gate_v...

   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See GATE/LICENSE.txt for further details
----------------------*/


#ifndef GateMacfileParser_h
#define GateMacfileParser_h 1
#include "globals.hh"
#include <vector>
#include <iostream> 
#include <sys/types.h>
#include <sys/stat.h>
#include <sstream> 
#include <fstream> 
#include <math.h>

using namespace std;

/*use this class to generate fully resolved macfiles and a splitfile*/

enum {ROOT=0,ASCII=1,ARF=2,PROJ=3,ECAT=4,SINO=5,ACCEL=6,LMF=7,CT=8,DAQ=9,MDB=10,SIZE=11};

class GateMacfileParser
{
public:

  GateMacfileParser(G4String macfileName,G4int numberOfSplits,G4int numberOfAliases,G4String* aliasesPtr);
  ~GateMacfileParser();
  void SetVerboseLevel(G4int value) { m_verboseLevel = value; };
  G4int GenerateResolvedMacros(G4String directory);
  G4String GetOutputMacDir();
  G4String GetoutputDir(){return outputDir;}; 
  void CleanAbort(ofstream& output, ofstream& splitfile);
  
 protected:
  
  // Misc variables   
  G4int m_verboseLevel;
  G4String macName;
  G4int nSplits; 
  G4int nAliases;
  G4String* aliases;
  char buffer[256];
  G4String macline;
  G4String localDir;
  G4String outputDir;
  G4String PWD;
  G4String outputMacDir;
  G4int oldSplitNumber;
  // Concerning time management
  G4double timeStop;
  G4double timeStart;
  G4double timeSlice;
  G4double addSlice;
  G4double virtualStartTime;
  G4double virtualStopTime;
  G4double lambda;
  G4String timeUnit;
  G4bool addSliceBool;
  G4bool readSliceBool;
  // Concerning output module
  G4String originalRootFileName;
  G4String originalProjFileName;
  G4String originalEcat7FileName;
  G4String originalAccelFileName;
  G4String originalSinoFileName;
  G4String originalLmfFileName;
  G4String originalAsciiFileName;
  G4String originalCTFileName;
  G4String originalARFFileName;
  // Conerning actor
  vector<G4String> listOfActorType;
  vector<G4String> listOfActorName;
  vector<G4String> listOfEnabledActorType;
  vector<G4String> listOfEnabledActorName;
  // Member functions
  void InsertAliases();
  void InsertSubMacros(ofstream& output,G4int splitNumber,ofstream& splitfile);
  void DealWithTimeCommands(ofstream& output,G4int splitNumber,ofstream& splitfile);
  void IgnoreRandomEngineCommand();
  void ExtractLocalDirectory(G4String macfileName);
  G4int GenerateResolvedMacro(G4String outputName,G4int splitNumber,ofstream& splitfile);
  void InsertOutputFileNames(G4int splitNumber,ofstream& splitfile);
  void SearchForActors(G4int splitNumber,ofstream& output, ofstream& splitfile);
  void AddSplitNumberWithExtension(G4int splitNumber);
  bool IsComment(G4String line);
  void FormatMacline();
  void LookForEnableOutput();
  void CheckOutputPrint();
  void CheckOutput(ofstream&,ofstream&,G4int);
  int enable[SIZE];
  int filenames[SIZE];
  bool* usedAliases;
  bool Braced(G4String origFile);
  void BraceReplace(G4String def, G4String origFile, char* SplitNumberAsString);
  const G4String ExtractFileName(G4String key);
  bool TreatOutputStream(G4String key, G4String def, G4String& origFile, char* SplitNumberAsString);
  void AddPWD(G4String key);
  void CalculateTimeSplit(G4int splitNumber);
  void skipComment(std::istream & is);
  bool ReadColNameAndUnit(std::istream & is, std::string name, string & unit);

};
#endif


