
#include "pinedaRD_body.c"


int getInt(int *nNum)
{
    scanf(" %d", nNum);
    return *nNum;
}
float getFloat(float * fNum)
{
    scanf(" %f", fNum);
    return *fNum;
}
char getCharInput(char* cNum)
{
    scanf(" %c", cNum);
    return *cNum;
}
void getString(string sWord)
{
    scanf(" %[^\n]", sWord);
    getchar();
}
void getDoctorInput(struct Doctor *doc)
{
    int i, j;
    string sWord;
    scanf(" %d %d",&doc->nSymptom,&doc->nImpression);
    getchar();
    for(i=0;i<doc->nSymptom;i++)
    {
        scanf(" %[^\n]",doc->sSymptom[i]);
        getchar();
    }
    for(i=0;i<doc->nImpression;i++)
    {
        scanf(" %[^\n]",doc->sImpression[i]);
        getchar();
        scanf(" %d",&doc->numSympofImp[i]);
        getchar();
        for(j=0;j<doc->numSympofImp[i];j++)
        {
            getString(sWord);
            strcpy(doc->sSympofImp[i][j],sWord);
        }
    }
}
void printSeparatorsTest(int nWords, int *nIteration, int nLang)//modified to not use FILE function
{
		string connector[2]={"and","at"};
        if(nWords>2)
        {
            if(*nIteration<nWords-2)
                printf(", ");
            else if(*nIteration==nWords-2)
                printf(", %s ",connector[nLang]);
            else
                printf(". ");
        }else if(nWords==2)
        {
            if(*nIteration ==0)
                printf(" %s ",connector[nLang]);
            else
                printf(". ");
        }else
            printf(". ");

        *nIteration +=1;
}
void testFunc(int nLang)
{
    struct Patient pat;
    int i, j, nNum1, nNum2, nNum3;
    float fNum[20];
    string sWord1, sWord2;
    string starline= "*************";
    char cLetter;
    struct Doctor doc;
    string sWordList[30];
    for(i=0;i<30;i++)
        getString(sWordList[i]);

    getDoctorInput(&doc);

    printf("%s\n",starline);
    printf("isValidLimit\n");
    printf("%s\n",starline);
    for(i=0;i<3;i++)
    {
        scanf(" %d", &nNum1);
        scanf("%d", &nNum2);
        nNum3 = isValidLimit(nNum1, nNum2,nLang);
        if(nNum3)
            printf("%d   %d\n", nNum1, nNum2);
    }

    printf("%s\n",starline);
    printf("isValidGender\n");
    printf("%s\n",starline);
    for(i=0;i<3;i++)
    {
        nNum1 = isValidGender(getCharInput(&cLetter),pat.sGender,pat.sPronouns,nLang);
        if(nNum1)
            printf("%d  %s  %s\n",nNum1,pat.sGender,pat.sPronouns);
    }


    printf("%s\n",starline);
    printf("isValidAnswer\n");
    printf("%s\n",starline);
    for(i=0;i<3;i++)
    {
        nNum1 =0;
        nNum2 = isValidAnswer(getCharInput(&cLetter),&nNum1,nLang);
        printf("Returns :%d, nWords: %d \n",nNum2,nNum1); //nWords
    }

    printf("%s \n",starline);
    printf("absValue\n");
    printf("%s \n",starline);
    for(i=0;i<3;i++)
    {
        printf("%d\n",absValue(getInt(&nNum1)));
    }

    printf("%s \n",starline);
    printf("compareString \n");
    printf("%s \n",starline);
    strcpy(sWord1,"\0");
    getString(sWord2);
    printf("%d\n",compareString(sWord1,sWord2));
    for(i=1;i<3;i++)
    {
        getString(sWord1);
        getString(sWord2);
        printf("%d \n",compareString(sWord1,sWord2));
    }

    printf("%s \n",starline);
    printf("stringChoice \n");
    printf("%s \n",starline);
    for(i=0;i<3;i++)
    {
        getString(sWord1);
        formatString(sWord1);
        printf("%s \n",doc.sImpression[stringChoice(sWord1,doc.sImpression,doc.nImpression)]);
    }

    printf("%s\n",starline);
    printf("searchString\n");
    printf("%s\n",starline);
    for(i=0;i<3;i++)
    {
        getString(sWord1);
        printf("%d\n",searchString(sWord1,sWordList,30));
    }

    printf("%s \n",starline);
    printf("sortImpRank\n");
    printf("%s \n",starline);
    for(j=0;j<3;j++)
    {
        for(i=0;i<doc.nImpression;i++)
        {
            getFloat(&fNum[i]);
        }
        for(i=0;i<doc.nImpression;i++)
            strcpy(sWordList[i],doc.sImpression[i]);
        printf("Returned Value: %d\n", SortImpRank(fNum, sWordList,doc.sImpression,doc.nImpression));
        for(i=0;i<doc.nImpression;i++)
            printf("%0.2f  ",fNum[i]);
        printf("\n");
    }

    printf("%s\n",starline);
    printf("lastName\n");
    printf("%s\n",starline);
    for(i=0;i<3;i++)
    {
        strcpy(sWord2,"\0");
        getString(sWord1);
        lastName(sWord1,sWord2);
        printf("%s\n",sWord2);
    }


    printf("%s\n",starline);
    printf("printSeparators\n");
    printf("%s\n",starline);
    for(i=0;i<3;i++)
    {
        getInt(&nNum1);
        nNum2=0;
        for(j=0;j<nNum1;j++)
        {
            getString(sWordList[j]);
        }
        for(j=0;j<nNum1;j++)
        {
            printf("%s",sWordList[j]);
            printSeparatorsTest(nNum1,&nNum2,nLang);
        }
        printf("\n");
    }

}
