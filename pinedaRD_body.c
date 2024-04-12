#include "pinedaRD_header.h"
//#include "PINEDA_MP_translation.c"

/* initializeStruct sets the values of the variables in struct Doctor and struct Patient to 0 (for numbers) and NULL (for string/char)
@param struct Doctor *doc
@param struct Patient pat
*/
void initializeStruct(struct Doctor *doc, struct Patient *pat)//Initialize struct variables in the beginning of the program
{
    int i;

    strcpy(pat->cSymptoms, "");
    strcpy(pat->sName, "");
    strcpy(pat->sGender,"");
    strcpy(pat->sPronouns,"");
    pat->nPatientNum=FALSE;
    pat->nAge=FALSE;
    doc->nImpression =FALSE;
    doc->nSymptom =FALSE;
    for(i=0;i<MAX;i++)
    {
        doc->numSympofImp[i] =FALSE;
        pat->fImpPercent[i]= 0;
        strcpy(doc->sSymptom[i], "");
        strcpy(doc->sImpression[i], "");
        strcpy(doc->sAskSymptom[i], "");
        strcpy(pat->sResultImp[i],"");
    }
}
/*cutLine will remove the newline at the end of a string
(this is because using fgets() adds a newline on the input)

@param string sLine- the string to be modified
*/
void cutLine(string sLine)
{
    sLine[strcspn(sLine,"\n")] = '\0'; //strcspn searches for the first instance of the character in the second parameter
}

/*fixLettercase will capitalize the first letter of each word in a string,
while setting the rest to lowercase letters. This will be used to make the
symptoms/impressions more uniform in their appearance

@paramm string sInputs - the string to be modified */
void fixLetterCase(string sInputs)
{
    int i;
    for(i=0;i<(int)strlen(sInputs);i++)
    {
        if( i==0||sInputs[i-1]==' ')
        {
            if(sInputs[i]>='a'&&sInputs[i]<='z')
                sInputs[i] = sInputs[i]-32;
        }else
        if(sInputs[i]>='A'&&sInputs[i]<='Z')
            sInputs[i] = sInputs[i] +32;
    }
}
/*formatString combines cutLine() and fixLetterCase()
since they will be used together in most cases except
int the list of questions because the questions should not use
fixletterCase()

@param string sLine - the string to be modified */
void formatString(string sLine)
{
    cutLine(sLine);
    fixLetterCase(sLine);
}
// ********************* DISPLAY FUNCTIONS ***********************
/*these three display functions : displayMainMenu(), displayMenuDoctor(),
and displaySympList() are only used to display information for the user. */
void displayMainMenu(int nLang)
{
	if(nLang ==0)
	{
		printf("MENU #1 User Type");
	    printf("\n\n");
	    printf("D for Doctor\n");
	    printf("P for Patient\n");
	    printf("E for Exit\n");
	}else{
		printf("MENU #1 Kamusta!");
	    printf("\n\n");
	    printf("D - Doktor\n");
	    printf("P - Pasyente\n");
	    printf("E - Paalam\n");
	}

}
void displayMenuDoctor(int nLang)
{
    printf("\n\n");
    if(nLang ==0)
    {
    	printf("C to Create a new list of symptoms and impressions.\n");
	    printf("U to Use the existing list of symptoms and expressions.\n");
	    printf("D to Display Symptoms\n");
	    printf("M to Modify Symptoms\n");
	    printf("E for Exit\n");
	}else{
		printf("C para lumikha ng bagong listahan ng mga symtomas at imppresyon.\n");
	    printf("U para gamitin ang nakaraan na listahan ng mga symtomas at impresyon.\n");
	    printf("D para ipakita ang mga sintomas\n");
	    printf("M para palitan ang mga sintomas\n");
	    printf("E para bumalik\n");
	}

}
void displaySympList(int nLimit, string sSymptoms[], int nLang)
{
    int i;
    if(nLang ==0)
 	   printf("Below is a list of symptoms.\n\n");
 	else
 		printf("Nasa ilalim ang listahan ng mga symtomas.\n\n");
    for(i=0;i<nLimit;i++)
        printf("%d. %s\n", i+1, sSymptoms[i]);
}

// *****************END OF DISPLAY FUNCTIONS ********************
// ********************IS VALID FUNCTIONS ***********************
/*isValid Limit will determine wether the entered limit for number of symptoms,
number of impressions, and number of symptoms in an expression is valid

@param int nInput - is the user input for (number of symptoms, number of impressions,
                    and number of symptoms in each impression)  which will be checked if valid,
@param int nLimit - will be the upperbound limit (20) for nSymptoms and nImpressions,
                    while (nSymptoms) for number of symptoms in an impression. */
int isValidLimit(int nInput, int nLimit, int nLang)
{
    if(nInput>0 && nInput <=nLimit)
        return TRUE;
    else
    {
    	if(nLang ==0)
        	printf("%s", INVALID);
        else
        	printf("%s",INVALID1);
        return FALSE;
    }
}

/*isValidNumSymp will be called when entering the symptoms to be associated with the impression.
It will check if it is within the number of symptoms and if it is unique from the previously
entereed symptoms

@param int nIndex - is the index of the current impression that is being updated.
@param int nInput - is the number which corresponds to what symptom was chosen.
@param struct doctor doc - will be required to access the current list of symptoms, and impressions */

int isValidNumSymp(int nIndex, int nInput, int nLang, struct Doctor doc)//if the chosen symptom exists in the list
{
    if(nInput >0 && nInput <=doc.nSymptom)//If Input is within the range of existing symptoms
    {
        if(searchString(doc.sSymptom[nInput-1],doc.sSympofImp[nIndex],doc.numSympofImp[nIndex]) == -1) //search if the symptom is already associated with the impression
            return TRUE;
        else
        {
        	if(nLang==0)
        		printf("%s is already included in a %s case.\n", doc.sSymptom[nInput-1],doc.sImpression[nIndex]);
        	else
        		printf("Ang %s ay naulit at kasama na sa %s case.\n", doc.sSymptom[nInput-1],doc.sImpression[nIndex]);
		}
        return FALSE;
    }
    else
    {
    	if(nLang ==0)
        	printf("%s", INVALID);
        else
        	printf("%s",INVALID1);
        return FALSE;
    }
    return FALSE;
}
/* isValidGender  will check if the patient's input on his gender is correct

@param cGender is the user input (m/f)
@param struct Patient *pat - patient.sGender will be modified
                            according to the stateddd gender
@return - either (1/0), returns 1 if the input is validd, 0 otherwise. */
int isValidGender(char cGender, string sGender, string sPronouns, int nLang)
{
	string m[]={"male","lalaki"};
	string f[]={"female","babae"};
	switch(nLang)
	{
		case 0: switch(cGender)
				    {
				        case 'm': case 'M': strcpy(sGender,m[nLang]);
				                            strcpy(sPronouns,"He");break;
				        case 'f':case 'F': strcpy(sGender,f[nLang]);
				                            strcpy(sPronouns,"She");break;
				        default: printf("%s",INVALID);
				                return 0;
				    }break;
		case 1:  switch(cGender)
			    {
			        case 'l': case 'L':strcpy(sGender,m[nLang]); break;
       			    case 'b': case 'B':strcpy(sGender,f[nLang]); break;
			        default: printf("%s",INVALID1);
			                 return 0;
			    }break;
	}

    return 1;
}
/* isValidAnswer will check if the patient's answer on the symptoms questions are valid

@param cAnswer - is the patient's input which should be (y/n)
@param *pSympPresent - is the number of symptoms present in the patient
@return - returns 1 if valid , 0 otherwise */
int isValidAnswer(char cAnswer,int *pSympPresent, int nLang)
{
    switch(cAnswer)
    {
        case 'y': case 'Y': *pSympPresent += 1; break;
        case 'n': case 'N': break;
        default:if(!nLang)
                    printf("%s",INVALID);
                else
                    printf("%s",INVALID1);
                return 0;
    }
    return 1;
}
// ********************END OF VALID FUNCTIONS *******************

//******************DOCTOR FUNCTIONS*****************************
/* absValue will give the absolute value of a given number, this is used to avoid math.h library
 @param - int nNum - the given number which will be changed to its absolute value
 @return - int nNum - will be returned as an absolute value */
int absValue(int nNum)//returns positive nNum
{
    if(nNum<0)
        nNum *= -1;
    return nNum;
}
/*compareString will compare two strings with each other just like strcmp. But, this returns the
exact distance between the ascii of two strings unlike strcmp which returns random positive, negative, or 0.
It will always compare until the length of the shorter string. I used this function so in option modify, or
option display, if you input the wrong spelling of an impression, it will guess your intended imptession.

@param string sString1, sString2 - these are the strings that will be compared, it doesnt matter wether the shorter
                                string is on the first parameter or second, this function will find the shorter one.
@return - returns int diff which is an absolute value or the distance between the two strings */
int compareString(string sString1, string sString2)//just like strcmp but it returns the exact difference of the ascii of two strings (strcmp returns randomly positive, randomly negative, or 0)
{
    int length, diff=0, i;
    // find the length of the shorter string
    if(strlen(sString1)>=strlen(sString2))
        length = strlen(sString2);
    else
        length = strlen(sString1);
    //get the difference of every character up to the end of the short string
    for(i=0;i<length;i++)
    {
        diff += absValue((int)sString1[i]-(int)sString2[i]);
    }
    return diff;
}
/*stringChoice is a version of the linear search algorithm but instead of using the condition
strcmp() ==0, it will find the shortest distance between the input string and the string from the
list of impressions, then assume that that is the intended impression of the user.

@param - string sInput - the string impression input of the user
@param - string sOptionBank[MAX] - the list of impressions created by the doctor
@param - int nLimit - number of elements present in sOptionBank

@return - int nImpIndex - returns the index of the element closest to the string input
Assumption: this function will not tell you if the string input exists in the list of strings or not,
            it will always give you an element in the list of strings that is closest to the input
*/
int stringChoice(string sInput, string sOptionBank[MAX], int nLimit)//given a string, it will search for its closest match in an array of strings
{
    int i, nDiff, nMin, nImpIndex =0;
    //base case, set the first element of the list of impressions as the closest distance with the input
    nMin = compareString(sInput, sOptionBank[0]);
    for(i=1;i<nLimit;i++)
    {
    //succeeding elements
        nDiff= compareString(sInput, sOptionBank[i]);
        if(nMin > nDiff)
        {
        //if current element is closer than the previous closest element to the input, update the current as the closest element
            nMin = nDiff;
            nImpIndex=i;
        }
    }
    return nImpIndex;
}


/*createSympImp is the option 1 of the MP specs and it will get the list of symptoms, questions, impressions
from the doctor's input

@param struct Doctor *doc - this will be a pointer type because its values will be updated */

void createSympImp(struct Doctor *doc, int nLang)
{
    int i,j, nInput;
    doc->listcreated = TRUE; // you can now use the other  doctor options, the patient menu, and the exit program
    switch(nLang)
    {
	    	case 0: do{
				        printf("How many symptoms do you want to consider? ");
				        scanf(" %d", &doc->nSymptom);
				    }while(!isValidLimit(doc->nSymptom,MAX,nLang)); //loop until valid input
				        getchar(); // getchar() is here so fgets() will work properly after a scanf was called
				    for(i= 0; i<doc->nSymptom;i++)
				    {
				        printf("Symptom #%d:\n", i+1);
				        printf("What is the symptom? ");
				        fgets(doc->sSymptom[i], SMAX, stdin);
				        formatString(doc->sSymptom[i]);     //format after string input
				        printf("How do you want to ask the symptom? ");
				        fgets(doc->sAskSymptom[i], SMAX,stdin);
				        cutLine(doc->sAskSymptom[i]); //format after string input, dont use fixlettercase() here
				    }
				    printf("How many impressions do you want to enter? ");
				    do{
				        scanf(" %d", &doc->nImpression);
				    }while(!isValidLimit(doc->nImpression,MAX,nLang)); //loop until valid input
				        getchar();
				    for(i= 0; i<doc->nImpression;i++)
				    {
				        printf("Impression #%d:\n", i+1);
				        printf("What is the illness? ");
				        fgets(doc->sImpression[i], SMAX, stdin);
				        formatString(doc->sImpression[i]); //format after string input
				        displaySympList(doc->nSymptom,doc->sSymptom,nLang); //display the list of symptoms (check display functions lines 69-97)

				       do{
				            printf("How many of the symptoms above are present in a %s case? ", doc->sImpression[i]);
				            scanf(" %d", &doc->numSympofImp[i]);
				        }while(!isValidLimit(doc->numSympofImp[i],doc->nSymptom,nLang));//loop until valid input

				        printf("Enter the corresponding number of each symptom:\n");
				        for(j=0;j<doc->numSympofImp[i];j++)
				        {
				            do{
				                scanf("%d", &nInput);
				            }while(!isValidNumSymp(i, nInput,nLang,*doc)); //loop until valid input
				            getchar();
				            strcpy(doc->sSympofImp[i][j],doc->sSymptom[nInput-1]);
				        }
	  				 } break;
    	case 1: do{
			        printf("Gaanong karaming Sintomas ang gusto mong ilista? ");
			        scanf(" %d", &doc->nSymptom);
			    }while(!isValidLimit(doc->nSymptom,MAX,nLang)); //loop until valid input
			        getchar(); // getchar() is here so fgets() will work properly after a scanf was called
			    for(i= 0; i<doc->nSymptom;i++)
			    {
			        printf("Sintomas #%d:\n", i+1);
			        printf("Ano ang Sintomas? ");
			        fgets(doc->sSymptom[i], SMAX, stdin);
			        formatString(doc->sSymptom[i]);     //format after string input
			        printf("Pano mo itatanong ang sintomas? ");
			        fgets(doc->sAskSymptom[i], SMAX,stdin);
			        cutLine(doc->sAskSymptom[i]); //format after string input, dont use fixlettercase() here
			    }
			    printf("Gaanong karaming impresyon ang ililista? ");
			    do{
			        scanf(" %d", &doc->nImpression);
			    }while(!isValidLimit(doc->nImpression,MAX,nLang)); //loop until valid input
			        getchar();
			    for(i= 0; i<doc->nImpression;i++)
			    {
			        printf("Impresyon #%d:\n", i+1);
			        printf("Ano ang sakit? ");
			        fgets(doc->sImpression[i], SMAX, stdin);
			        formatString(doc->sImpression[i]); //format after string input
			        displaySympList(doc->nSymptom,doc->sSymptom,nLang); //display the list of symptoms (check display functions lines 69-97)

			       do{
			            printf("Gaanong karami sa mga sintomas ang kasama sa kaso ng %s? ", doc->sImpression[i]);
			            scanf(" %d", &doc->numSympofImp[i]);
			            }while(!isValidLimit(doc->numSympofImp[i],doc->nSymptom,nLang));//loop until valid input

			        printf("Ilagay ang numero ng bawat sintomas:\n");
			        for(j=0;j<doc->numSympofImp[i];j++)
			        {
			            do{
			                scanf("%d", &nInput);
			            }while(!isValidNumSymp(i, nInput,nLang,*doc)); //loop until valid input
			            getchar();
			            strcpy(doc->sSympofImp[i][j],doc->sSymptom[nInput-1]);
			        }
			    }break;
	}
}
/* displaySymp is option D in the MP spec (this is not like the display functions declared above in lines 69-97).
    This will ask for a string input (impression) then display the symptoms associated with that impression.

    @param struct Doctor doc - the list of symptoms and impressions will be accessed but not updated so no pointers
    @return int nImpIndex - the index of the input impression from the existing list of symptoms

    @assumptions - this function will not tell you if the string input exists in the list of strings or not,
            it will always give you an element in the list of strings that is closest to the input, as it assumes that
            the closest element is the impression you entended to choose. this is a feature
            not a bug because it can read wrong spellings*/

int displaySymp(struct Doctor doc, int nLang)//return the index of the choice impression
{
    string sInput;
    int i, nImpIndex;
	if(nLang ==0)
   		 printf("What is the Impression? ");
   	else
   		printf("Ano ang Impresyon? ");
    getchar();
    fgets(sInput, SMAX, stdin);
    formatString(sInput);
    nImpIndex = stringChoice(sInput, doc.sImpression, doc.nImpression);// find the input from the list of impressions and get the index
    if(nLang==0)
   		 printf("Symptoms of a %s are:\n", doc.sImpression[nImpIndex]);
   	else
   		printf("Ang mga Sintomas ng %s ay:\n", doc.sImpression[nImpIndex]);

    for(i=0;i<doc.numSympofImp[nImpIndex];i++) //list its associated symptoms
    {
        printf("   %s\n", doc.sSympofImp[nImpIndex][i]);

    }
    return nImpIndex;
}
/* modifySymp is option M in MP specs. It will get an input impression,
    display its symptoms, then modify its associated symptoms.

    @param struct Doctor *doc - pointer variable because the list of
    associated symptoms in an impression will be updated */
void modifySymp(struct Doctor *doc, int nLang)
{
    int nImpIndex, nInput, i ;
    nImpIndex = displaySymp(*doc,nLang); // the first part of this is exactly the same as the displaySymp so just call displaySymp here
    if(nLang ==0)
    	printf("You can modify the symptoms of %s\n", doc->sImpression[nImpIndex]);
    else
    	printf("Pwedeng baguhin ang mga sintomas ng %s\n", doc->sImpression[nImpIndex]);
    //reinitialize the symptoms (reset the values)
    for(i=0;i<doc->nSymptom;i++)
    {
        strcpy(doc->sSympofImp[nImpIndex][i],"\0");
    }
    displaySympList(doc->nSymptom,doc->sSymptom,nLang);//ddisplay the list of all existing symptoms in the list
    if(nLang ==0)
   		 printf("\nHow many of the symptoms above are present in a %s case?", doc->sImpression[nImpIndex]);
   	else
   		printf("\nGaanong karami sa mga sintomas na nakalista sa taas ang kabilang sa kaso ng %s?", doc->sImpression[nImpIndex]);
    do{
        scanf(" %d", &doc->numSympofImp[nImpIndex]);
    }while(!isValidLimit(doc->numSympofImp[nImpIndex],doc->nSymptom,nLang));//loop until valid input
    for(i=0;i<doc->numSympofImp[nImpIndex];i++)
    {
        if(nLang ==0)
			printf("Enter the corressponding number of each symptom:\n");
		else
			printf("Ilagay ang numero ng bawat sintomas:\n");
        do{
            scanf(" %d", &nInput);
        }while(!isValidNumSymp(nImpIndex, nInput,nLang,*doc));//loop until valid input
        strcpy(doc->sSympofImp[nImpIndex][i],doc->sSymptom[nInput-1]);
    }
    if(nLang==0)
		printf("Here are the NEW SYMPTOMS of %s:\n", doc->sImpression[nImpIndex]);//list the new symptoms
	else
		printf("Narito ang mga BAGONG SINTOMAS ng %s:\n", doc->sImpression[nImpIndex]);
    for(i=0;i<doc->numSympofImp[nImpIndex];i++)
    {
       printf("   %s\n", doc->sSympofImp[nImpIndex][i]);
    }
}
/*saveSympFile will save the information about the symptoms contained in struct Doctor.
                This includes the number of symptoms, actual list of symptoms, and the list of questions

    @param FILE* fFile is the file variable for the symptom file
    @param struct Doctor doc will only be accessed not updated, so no pointers */
void saveSympFile(FILE* fFile, struct Doctor doc)
{
    int i;
    fFile = fopen("symplist.txt","w");
    //symptoms
    fprintf(fFile,"%d\n", doc.nSymptom);
    for(i=0; i<doc.nSymptom;i++)
        fprintf(fFile,"%s\n", doc.sSymptom[i]);
    //ask symptoms
    for(i=0;i<doc.nSymptom;i++)
        fprintf(fFile,"%s\n",doc.sAskSymptom[i]);
    fclose(fFile);
}
/*saveImpFile will save the information about impressions. This includes,  number of impressions, actual
            list of impressions, number of symptoms in each impression, list of symptoms in each impression
*/
void saveImpFile(FILE* fFile, struct Doctor doc)
{
    int i,j;
    fFile = fopen("implist.txt","w");
    fprintf(fFile,"%d\n",doc.nImpression);
    for(i=0;i<doc.nImpression;i++)
    {
        fprintf(fFile, "%d ", doc.numSympofImp[i]);
    }
    fprintf(fFile,"\n");
    for(i=0;i<doc.nImpression;i++)
    {
         fprintf(fFile,"%s\n",doc.sImpression[i]);
         for(j=0;j<doc.numSympofImp[i];j++)
         {
            fprintf(fFile,"%s\n",doc.sSympofImp[i][j]);
         }
    }
    fclose(fFile);
}
/* this is option U in MP specs, it will read the details of a symptom text file and impression textfile
    and save it on struct Doctor. This is an alternative way of providing a list of symptoms/impressions
    aside from createSympImp()

    @param struct Doctor *doc - will be updated so it will be a pointer
    @param FILE* fFile[3] - file variables for the files to read
    @string sFileName[] - the variable that contains the name of the textfile to be opened */

void useExisting(struct Doctor *doc, FILE* fFile[], int nLang)
{
    int i, j;
    string both[2]={"PINEDA_MP.exe: Fatal error, symplist.txt and implist.txt NOT FOUND. Returning to main menu...\n\n",
						"PINEDA_MP.exe: Mabigat na Mali, ang symplist.txt at implist.txt ay HINDI MAKITA. Balik sa Main Menu...\n\n"};
	string symp[2]={"PINEDA_MP.exe: Fatal error, symplist.txt NOT FOUND. Returning to main menu...\n\n",
						"PINEDA_MP.exe: Mabigat na Mali, ang implist.txt ay HINDI MAKITA. Balik sa Main Menu...\n\n"};
	string imp[2]={"PINEDA_MP.exe: Fatal error, implist.txt NOT FOUND. Returning to main menu...\n\n",
						"PINEDA_MP.exe: Mabigat na Mali, ang implist.txt ay HINDI MAKITA. Balik sa Main Menu...\n\n"};
    //open files
    fFile[0] = fopen("symplist.txt","r");
    fFile[1] = fopen("implist.txt","r");
    if (fFile[0] == NULL) //Print error when unsuccessful
	{
        printf("\n");
		if(fFile[1]==NULL)
            fprintf(stderr, "%s",both[nLang]);
		else
            fprintf(stderr, "%s",symp[nLang]);
	}else if(fFile[1] == NULL){
    	printf("\n");
        fprintf(stderr, "%s",imp[nLang]);
	}else{//if successful
		doc->listcreated = TRUE; // you can access the other options in the program
	//symptoms
        fscanf(fFile[0], " %d ", &doc->nSymptom);
        for(i=0;i<doc->nSymptom;i++){
            fgets(doc->sSymptom[i],SMAX, fFile[0]);
            formatString(doc->sSymptom[i]);
        }
        for(i=0;i<doc->nSymptom;i++){
            fgets(doc->sAskSymptom[i],SMAX,fFile[0]);
            cutLine(doc->sAskSymptom[i]);
        }
    //Impressions
        fscanf(fFile[1]," %d ",&doc->nImpression);
        for(i=0;i<doc->nImpression;i++)
            fscanf(fFile[1]," %d ",&doc->numSympofImp[i]);
        for(i=0;i<doc->nImpression;i++)
        {
            fgets(doc->sImpression[i],SMAX,fFile[1]);
            formatString(doc->sImpression[i]);
            for(j=0;j<doc->numSympofImp[i];j++){
                fgets(doc->sSympofImp[i][j],SMAX,fFile[1]);
                formatString(doc->sSympofImp[i][j]);
            }
        }
    //close if successfully opened
        for(i=0;i<2;i++)
            fclose(fFile[i]);
	}
}
/*menuDoctor handles the doctor menu which will give the user 5 options to choose: C,U,D,M will their respective functions  above
                while E will exit back to the main menu
    @param struct Doctor *doc - will be updated in case c (createSympImp), case U (updateExissting), and case M(modifySymp)
    @param FILE* fFile - are the file variables for writing data into a file and reading data
    @param sFileName - variable that will hold the name of the textfile*/
void menuDoctor(struct Doctor *doc, FILE* fFile[3],int nLang)
{
    char cInput;
    BOOL isLoop = TRUE;
    if(nLang==0)
		printf("\n\nMENU #2 Doctor");
	else
		printf("\n\nMENU #2 Doktor");
    do{
        displayMenuDoctor(nLang); // display information on the choices for the user
        scanf(" %c", &cInput);
        switch(cInput)
        {
            case 'c': case 'C': createSympImp(doc,nLang);
                                saveSympFile(fFile[0], *doc);
                                saveImpFile(fFile[1], *doc);
                                break;
            case 'u': case 'U': useExisting(doc,fFile,nLang);
                                isLoop= FALSE;
                                break;
            case 'd': case 'D': if(doc->listcreated)
                                    displaySymp(*doc,nLang);
                                else //cant choose display when there's no list created
                                {
                                	if(nLang ==0)
                                		printf("%s",E2319);
									else
										printf("%s",T2319);
								}
                                break;
            case 'm': case 'M':if(doc->listcreated){
                                    modifySymp(doc,nLang);
                                    saveImpFile(fFile[1], *doc); //overwrite the impression text file to update the modified impression
                                }else  //cant choose display when there's no list created
                                {
                                	if(nLang ==0)
                                		printf("%s",E2319);
									else
										printf("%s",T2319);
								}
                                break;
            case 'e': case 'E': isLoop = FALSE;
                               break;
            default: if(nLang==0)
						printf("%s", INVALID);
					else
						printf("%s",INVALID1);//dont exit back to main menu when input is invalid
        }
    }while(isLoop);
}
//******************END OF DOCTOR FUNCTIONS**********************

//*******************PATIENT FUNCTIONS***************************

/*searchString is a linear search function which finds the index of key string
    if it  exists in an array of strings. This is the normal version of stringChoice()
    and it is still necessary to have this version when it is needed to find out if
    a key exists or not.

    @param string key - the string that will be searching for
    @param- string Array[] - the list of strings where we will be searching through
    @param -int nElem - is the number of elements present in string Array[]

    @return - int - returns the index in the list of strings if the key exists in the list.
                    otherwisee, it returns -1 to signify there is no string in the list similar to the key. */
int searchString(string key, string Array[], int nElem)
{
    int i;
    for(i=0;i<nElem;i++)
    {
        if(strcmp(key,Array[i])==0)
            return i;
    }
    return -1;
}

/*checkPossibleImp will find how many of the patients symptoms matches an impression's associated symptoms.
    It will strore the ratio of the (patients existing symptom associated with the impression) to the
    (total number of symptoms associated with the impression)

@param struct Patient *pat - it will update pat->nImpPercent[] so it needs the struct to be a pointer
@param struct Doctor doc - it only needs to access some variables in struct Doctor but no need to update
@int nImpIndex - this will tell the function which impression is going to be checked
@return - returns the ratio of (patient:total sympinimp) which is = 1 if all symptoms associated with the impression
            are present in the patient while it rounds off to 0 if there is 1 or more symptoms missing int the patient.
            This will serve as a TRUE/FALSE condition in the next function
*/
int checkPossibleImp(struct Patient *pat, struct Doctor doc, int nImpIndex)// returns TRUE if given impression applies to patient
{
    int i,nCount =0;
    for(i=0;i<doc.nSymptom;i++)
        {
            if(pat->cSymptoms[i] == 'y' || pat->cSymptoms[i] =='Y')
            {
               if(searchString(doc.sSymptom[i],doc.sSympofImp[nImpIndex],doc.nSymptom)!=-1)
                    nCount++;
            }
        }

    pat->fImpPercent[nImpIndex]= nCount*1.0 / doc.numSympofImp[nImpIndex];
    return (int)pat->fImpPercent[nImpIndex];//if all symptoms are present then the return value = 1, if not, then it will be 0 (integer cuts off the decimal)

}
/*diagnosis() will check if the patient is to be diagnosed with a certain impression.

@param struct Patient *pat - it will update patient.sResultIMP to hold the diagnosed impressions
@param struct Doctor doc - some doctor variables data are required in the code

@return - nCount- returns the number of impressions diagnosed to the patient. */
int diagnosis(struct Patient *pat, struct Doctor doc) //returns number of applicable impressions to patient and updates patient->nDiagnosisImp[i] accordingly
{
    int i, nCount =0;

    for(i=0;i<doc.nImpression;i++)
    {
        if(checkPossibleImp(pat, doc, i))
        {
            strcpy(pat->sResultImp[nCount],doc.sImpression[i]);
            nCount++;
        }
    }
    return nCount;
}
/*sortImpRank ranks the impressions on the patient according the number of symptoms present
that match the impressions symptoms to those reported by the patient. This function will only
be called when there is no 100% impression that is diagnosed to the patient.

@param struct Patient *pat- patient.sResultImp will be updated to store all impressions but in
    ranked order (highest percentage to lowest). patient.nImpPercent already contains the float
    ratio and it will be updated to be sorted in descending order
@param struct doctor doc - needs to be accessed but not changed

@return nCount which counts the number of impressions higher than 0% chance of manifesting */
int SortImpRank(float fPercent[],string patImp[], string docImp[], int nLimit)
{
    int i, j, nHigh, nCount =0;
    float fTemp;
    string sTemp;
    // the sorting will be based on the float percentages
    for(i=0;i<=nLimit;i++)
    {
        //copy actual list of impressions onto patient array of impressions
        strcpy(patImp[i],docImp[i]);
    }
    //sort the temp array into ascending order
    for(i=0;i<nLimit-1;i++)
    {
        nHigh =i;
        for(j=i+1;j<nLimit;j++)
        {
            if(fPercent[j]>fPercent[nHigh])
                nHigh =j;
        }
        //swap
        fTemp = fPercent[i];
        fPercent[i] = fPercent[nHigh];
        fPercent[nHigh] = fTemp;
        //also swap the actual list of impressions in the struct patient's array
        strcpy(sTemp,patImp[i]);
        strcpy(patImp[i],patImp[nHigh]);
        strcpy(patImp[nHigh],sTemp);
    }
    //count the number of impressions that have more than 0% chance
    for(i=0;i<nLimit;i++)
    {
        if(fPercent[i]>0.0)
            nCount++;
    }
    return nCount;
}

/*printSeparators will print english separators :{"," "." "and"}.
@param nWords - the number of words left to be listed
@param *nIteration - this function requires a different index variable from the for-loop it will be called in.
                        this parameter represents that index
@param FILE*fFile - this function will print directly to the save file

Assumption: The MP Specs does not follow the Oxford Comma but this function will follow the oxford comma */
void printSeparators(int nWords, int *nIteration, int nLang, FILE* fFile)//takes care of printing ',' 'and' '.' which follows the english grammar
{
		string connector[2]={"and","at"};
        if(nWords>2)
        {
            if(*nIteration<nWords-2)
                fprintf(fFile,", ");
            else if(*nIteration==nWords-2)
                fprintf(fFile,", %s ",connector[nLang]);
            else
                fprintf(fFile,". ");
        }else if(nWords==2)
        {
            if(*nIteration ==0)
                fprintf(fFile," %s ",connector[nLang]);
            else
                fprintf(fFile,". ");
        }else
            fprintf(fFile,". ");

        *nIteration +=1;
}

/*lastName will get the last name of the patient which will be used as the filename for that patient's HPI
@param FullName - the full name of the patient
@param famName - this will be modified to store the patient's last name */
void lastName(string FullName, string famName) // gets the lastname,assumes that the full name is in the form (first + last)
{
    string surName[25];
    string suffixes[]={"II", "III","IV","Jr.","Sr.","jr.","sr.","jr","sr","Jr","Sr","JR","SR"};
    string unique[] = {"dela","del","de","delos","da","Dela", "Del","De","Delos","Da","la","La"};
    int i, j=0,k=0;

    for(i=0;i<=(int)strlen(FullName);i++) //separate full name word by word
    {
        if(FullName[i]==' '|| FullName[i]=='\0')
        {
            surName[k][j] = '\0';
            k++;// move to next row/word
            j=0;//reset column to zero
        }else
        {
            surName[k][j]=FullName[i];
            j++;//move to next column
        }
    }

    //get the last name
    if(searchString(surName[k-1],suffixes,13)!=-1)//name has suffixes: Jr.,Sr.,III,IV
        k--;
    if((strcmp(surName[k-3],"de")==0||strcmp(surName[k-3],"De")==0)&& (strcmp(surName[k-2],"la")==0||strcmp(surName[k-2],"La")==0) )// "de La +name"
    {
        strcat(strcpy(famName,surName[k-3])," ");
       strcat(strcat(famName,surName[k-2])," ");
    }else if(searchString(surName[k-2],unique,12)!=-1)// "dela/del/de/delos/la + name"
        strcat(strcpy(famName,surName[k-2])," ");
    strcat(famName,surName[k-1]);
}
/*menuPatient is the part II of the MP specs which will ask the patients' details to generate the HPI
@param - struct Patient *anon - its values will be updated
@struct Doctor doc - will only be accessed but not updated
@param FILE* fFile - the HPI will be saved here

Assumption - if there are no exact impressions on the patient, the HPI will display the impressions
from highest chance to lowest. Impressions with 0% chance will not be listed. Morover, if all impressions
have 0% chance (patient answered no to all questions), then HPI will display the patient is healthy
*/
int menuPatient(struct Patient *anon, struct Doctor doc, int nLang)
{
    int i, nWords=0;
    char cInput;

    //patient information

    switch(nLang)
    {
    	case 0: printf("\n\nMENU #3 Patient\n\n");
				 printf("What is your name? ");
			    getchar();
			    fgets(anon->sName,SMAX,stdin);
			    cutLine(anon->sName);
			    printf("What is your patient number? ");
			    scanf(" %d", &anon->nPatientNum);
			    printf("Enter your age: ");
			    scanf(" %d", &anon->nAge);
			    do{
			        printf("Gender (M/F): ");
			        scanf(" %c", &cInput);
			    }while(!isValidGender(cInput,anon->sGender,anon->sPronouns,nLang));
				break;
    	case 1: printf("\n\nMENU #3 Pasyente\n\n");
				 printf("Ano ang iyong pangalan? ");
			    getchar();
			    fgets(anon->sName,SMAX,stdin);
			    cutLine(anon->sName);
			    printf("Ano ang iyong numero bilang pasyente? ");
			    scanf(" %d", &anon->nPatientNum);
			    printf("Ano ang iyong edad: ");
			    scanf(" %d", &anon->nAge);
			    do{
			        printf("Kasarian (L/B): ");
			        scanf(" %c", &cInput);
			    }while(!isValidGender(cInput,anon->sGender,anon->sPronouns,nLang));
			    break;
	}

    //Ask for symptoms
    for(i=0;i<doc.nSymptom;i++)
    {
        printf("%s ", doc.sAskSymptom[i]);
        do{
            scanf(" %c", &anon->cSymptoms[i]);
        }while(!isValidAnswer(anon->cSymptoms[i],&nWords, nLang)); //nWords counts the number of symptoms that are present
    }

	return nWords;
}

void Translate(string sChange[], int nLang, int nLimit)
{
    int i, index;
    string sEngSymptoms[41]={"High Fever", "Nausea", "Chills","Runny Nose","Body Pain", "Headache","Loss Of Smell",
                        "Body Rashes", "Irritability","Dizziness","Fatigue","Trembling","Sore Muscles",
                        "Cough", "Sore Throat", "Loss Of Taste", "Back Pain", "Diarrhea","Elbow Pain", "Eye Pain",
                        "Eye Swelling", "Excessive Sweating", "Foot Pain", "Frequent Urination", "Green Stool", "Groin Pain", "Heel Pain","Hip Pain",
                        "Numbness","Joint Pain","Knee Pain","Leg Pain", "Leg Swelling","Neck Pain", "Nosebleeds","Sore Eyes",
                        "Shortness Of Breath", "Shoulder Pain", "White Tounge", "Yellow Tounge"};

    string sTagSymptoms[41]={"Mataas Na Lagnat", "Pagduduwal", "Panggiginaw","Sipon","Sakit Ng Katawan","Sakit Ng Ulo",
                        "Pagkawala Ng Pangamoy", "Pantal","Pagkayamutin","Pagkahilo","Pagod","Panginginig","Masakit Na Kalamnan",
                         "Ubo","Pamamaga Ng Lalamunan", "Kawalan Ng Pang Amoy", "Masakit Na Likod","Pagtatae","Sakit Ng Balikat",
                         "Sakit Ng Mata", "Namamagang Mata","Labis Na Pagpapawis", "Sakit Ng Paa", "Madalas na Pagihi","Kakaibang Kulay ng Dumi",
                         "Sakit Ng Singit", "Sakit Ng Sakong", "Sakit Ng Balakang", "Kawalan Ng Hininga", "Sakit Ng Braso",
                         "Namumuting Dila", "Naninilaw Na Dila"};

  //  string sEngImpressions[];
  //  string sTagImpressions[];
     for(i=0;i<nLimit;i++)//42 is the total number of translatable symptoms
    {
        switch(nLang)
        {
            case 0: index = searchString(sChange[i],sTagSymptoms,42);
                    if(index != -1)
                        strcpy(sChange[i],sEngSymptoms[index]);
                    else
                        printf("There are no direct English translations found for the symptom %s.\n",sChange[i]);
                    break;
            case 1: index = searchString(sChange[i],sEngSymptoms,42);
                    if(index != -1)
                        strcpy(sChange[i],sTagSymptoms[index]);
                    else
                        printf("Walang mahanap na katumbas sa Tagalog ang sintomas na %s.\n",sChange[i]);
                    break;
        }
    }
}

void HPI(struct Patient *anon, struct Doctor doc, int nWords, int nLang, FILE *fFile)
{
	string surName="";
	string sNum;
	sprintf(sNum,"%d",anon->nPatientNum);
	int i,j=0;
	char cReadFile;
	lastName(anon->sName,surName);
	strcat(surName,sNum);
    strcat(surName,".txt");
    fFile = fopen(surName, "w");
    //Display HPI
    fprintf(fFile,"\n\n--------History of Present Illness Report---------\n\n");
    fprintf(fFile,"%s, patient # %d is a %d-year old %s. %s has ", anon->sName, anon->nPatientNum, anon->nAge, anon->sGender, anon->sPronouns);
    for(i=0;i<doc.nSymptom&&j<nWords;i++)
    {
        if(anon->cSymptoms[i]=='y'||anon->cSymptoms[i]=='Y')
        {
        	fprintf(fFile,"%s", doc.sSymptom[i]);
            printSeparators(nWords,&j,0,fFile);
		}
    }
    if(nWords ==0)
        fprintf(fFile,"no symptoms reported. This patient is very healthy.");
    else
    {
        nWords = diagnosis(anon, doc); //nWords now counts the number of direct impressions
        j=0;
        if(nWords>0)// if there is a 100% matching impression, no need to show the percentages of other impressions
        {
            fprintf(fFile,"Impressions are ");
            for(i=0;i<nWords ;i++)
            {
                fprintf(fFile,"%s", anon->sResultImp[i]);
                printSeparators(nWords,&j,0,fFile);
            }
        }else
        {
        //if there is no 100% matching impression, then show the percentage results from highest to lowest
            nWords = SortImpRank(anon->fImpPercent,anon->sResultImp,doc.sImpression,doc.nImpression); //nWords now counts the impressions with higher than 0% chance
            fprintf(fFile,"The are no direct impressions found. Here are the results: ");
            for(i=0;i<nWords;i++)
            {
                fprintf(fFile,"%s : %%%0.2f", anon->sResultImp[i],anon->fImpPercent[i]*100);
                printSeparators(nWords,&j,0,fFile);
            }
        }
    }
    fprintf(fFile,"\n\n--------------------END OF REPORT-----------------\n\n");
    fclose(fFile);
    fFile = fopen(surName, "r");
    cReadFile = fgetc(fFile);
    while(cReadFile!=EOF)
    {
        printf("%c",cReadFile);
        cReadFile = fgetc(fFile);
    }
    fclose(fFile);
    printf("\n\n");
}

void tagalogHPI(struct Patient *anon, struct Doctor doc, int nWords,int nLang, FILE *fFile)
{
	string surName="";
	string sNum;
	sprintf(sNum,"%d",anon->nPatientNum);
	int i,j=0;
	char cReadFile;
	lastName(anon->sName,surName);
	strcat(surName,sNum);
    strcat(surName,".txt");
    fFile = fopen(surName, "w");
    //Display HPI
    fprintf(fFile,"\n\n-------- Kasaysayan ng Kasalukuyang Karamdaman ---------\n\n");
    fprintf(fFile,"Si %s, pasyente # %d ay %d-taong gulang na %s. ", anon->sName, anon->nPatientNum, anon->nAge, anon->sGender);

    if(nWords ==0)
        fprintf(fFile,"Walang sintomas na nararamdaman ang pasyente. Si %s ay malusog.", anon->sName);
    else
    {
         fprintf(fFile,"Siya ay nakararanas ng ");
        for(i=0;i<doc.nSymptom&&j<nWords;i++)
        {
            if(anon->cSymptoms[i]=='y'||anon->cSymptoms[i]=='Y')
            {
                fprintf(fFile,"%s", doc.sSymptom[i]);
                printSeparators(nWords,&j,1,fFile);
            }
        }
    	j=0;
        nWords = diagnosis(anon, doc); //nWords now counts the number of direct impressions
        if(nWords>0)// if there is a 100% matching impression, no need to show the percentages of other impressions
        {
            fprintf(fFile,"Ang mga impresyon ay ");
            for(i=0;i<nWords ;i++)
            {
                fprintf(fFile,"%s", anon->sResultImp[i]);
                printSeparators(nWords,&j,1,fFile);
            }
        }else
        {
        //if there is no 100% matching impression, then show the percentage results from highest to lowest
            nWords = SortImpRank(anon->fImpPercent,anon->sResultImp,doc.sImpression,doc.nImpression); //nWords now counts the impressions with higher than 0% chance
            fprintf(fFile,"Walang direktang impresyon ang nakita. Narito ang  mga resulta: ");
            for(i=0;i<nWords;i++)
            {
                fprintf(fFile,"%s : %%%0.2f", anon->sResultImp[i],anon->fImpPercent[i]*100);
                printSeparators(nWords,&j,1,fFile);
            }
        }
    }
    fprintf(fFile,"\n\n--------------------END OF REPORT-----------------\n\n");
    fclose(fFile);
    fFile = fopen(surName, "r");
    cReadFile = fgetc(fFile);
    while(cReadFile!=EOF)
    {
        printf("%c",cReadFile);
        cReadFile = fgetc(fFile);
    }
    fclose(fFile);
    printf("\n\n");
}


//*******************END OF PATIENT FUNCTIONS********************


