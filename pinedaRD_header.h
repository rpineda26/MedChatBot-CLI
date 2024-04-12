#include <stdio.h>
#include <string.h>
#define MAX 20
#define SMAX 200
#define FALSE 0
#define TRUE 1
#define INVALID "Invalid Input. Try Again.\n"
#define INVALID1 "Maling Sagot. Subukan Muli.\n"
#define E2319 "ERROR 2319 - Doctor's List is yet to be created.\n"
#define T2319 "ERROR 2319 - Hindi pa nalilikha ang listahan ng doktor.\n"

typedef char string[SMAX];
typedef int BOOL;

struct Doctor{
    int nSymptom;
    int nImpression;
    int numSympofImp[MAX];
    string sSymptom[MAX];
    string sImpression[MAX] ;
    string sAskSymptom[MAX];
    string sSympofImp[MAX][MAX];
    BOOL listcreated;
};

struct Patient{
    int nPatientNum;
    int nAge;
    float fImpPercent[MAX];
    char cSymptoms[MAX+1];
    string sGender;
    string sPronouns;
    string sName;
    string sResultImp[MAX];
};

    // main source: https://www.mayoclinic.org/symptoms/index
void initializeStruct(struct Doctor *doc, struct Patient *pat);
//format functions
void cutLine(string sLine);//cuts the newline from the strings initialized with fgets()
void fixLetterCase(string sInputs);//first letter of every word should be capitalized, the rest are small letters
void formatString(string sLine);
void printSeparators(int nWords, int *nIteration, int nLang,FILE* fFile);//takes care of printing ',' 'and' '.' which follows the english grammar
void lastName(string FullName, string famName);
void displayMainMenu(int nLang);
void displayMenuDoctor(int nLang);
void displaySympList(int nLimit, string sSymptoms[], int nLang);

//Validator functions
int isValidLimit(int nLimit, int nMax, int nLang); //if the limit of symptoms/impressions to consider is valid
int isValidNumSymp(int nIndex, int nInput, int nLang, struct Doctor doc);//if the entered symptom to be associated in an impression is valid
int isValidGender(char cGender, string sGender, string sPronouns, int nLang);
int isValidAnswer(char cAnswer, int *pSympPresent, int nLang);
//File Functions
void saveSympFile(FILE* fFile, struct Doctor doc);
void saveImpFile(FILE* fFile, struct Doctor doc);

//Major Functions
void createSympImp(struct Doctor *doc, int nLang);
int displaySymp(struct Doctor doc, int nLang);//return the index of the choice impression
void modifySymp(struct Doctor *doc, int nLang);
void useExisting(struct Doctor *doc, FILE* fFile[3],int nLang);
void menuDoctor(struct Doctor *doc, FILE* fFile[3], int nLang);
int menuPatient(struct Patient *anon, struct Doctor doc, int nLang);
int diagnosis(struct Patient *pat, struct Doctor doc); //returns number of applicable impressions to patient and updates patient->nDiagnosisImp[i] accordingly
int SortImpRank(float fPercent[],string patImp[], string docImp[], int nLimit);
//Algorithm Functions
int absValue(int nNum);//returns positive nNum;
int compareString(string sString1, string sString2);//just like strcmp but it returns the exact difference of the ascii of two strings (strcmp returns randomly positive, randomly negative, or 0)
int stringChoice(string sInput, string sOptionBank[MAX], int nLimit);//given a string, it will search for its closest match in an array of strings
int searchString(string key, string Array[], int nElem);//returns the index if string key is found in Array, returns -1 if not found
int checkPossibleImp(struct Patient *pat, struct Doctor doc, int nImpIndex);// returns TRUE if given impression applies to patient

