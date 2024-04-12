
#include "pinedaRD_testFunctions.c"
//./PINEDA_MPmain<mp.txt

//@param nLang refers to the language being used by the system. It was not included in the comments due to repition


int main()
{   //Declarations, Initializations
    char cMenu;
    struct Doctor doctor;
    struct Patient pat;
    BOOL isLoop = TRUE;
    FILE* fFile[3];
    int nLang = FALSE;//English mode
    doctor.listcreated = FALSE;
   initializeStruct(&doctor, &pat);
    do{
        displayMainMenu(nLang);
        scanf(" %c", &cMenu);
        switch(cMenu)
        {
            case 'd': case 'D': menuDoctor(&doctor, fFile,nLang);break;
            case 'p': case 'P': if(doctor.listcreated)
                                {
                                	if(nLang==0)
                                		HPI(&pat,doctor, menuPatient(&pat, doctor, nLang), nLang, fFile[2]);
                                	else
                                		tagalogHPI(&pat,doctor, menuPatient(&pat, doctor, nLang), nLang, fFile[2]);
								}
                                else
                                {
                                	if(nLang ==0)
                                		printf("%s",E2319);
									else
										printf("%s",T2319);
								}
                                break;
            case 'e': case 'E': if(doctor.listcreated)
            					{
                                    isLoop=FALSE;
                                    if(nLang==0)
                                   		 printf("\n\nProgram Shutting Down.....\n");
                                   	else
                                   		printf("\n\nPaalam!........\n");
                            	}
                                else
                                {
                                	if(nLang ==0)
                                		printf("%s",E2319);
									else
										printf("%s",T2319);
								}
                                break;
            case 't': case 'T':  do{
                                        if(nLang==0)
                                            printf("Translate to Tagalog? (y/n)");
                                        else
                                            printf("Isalin sa Ingles? (y/n");
                                        scanf(" %c",&cMenu);
                                        switch(cMenu)
                                        {
                                            case'y': case'Y': nLang = !nLang;
                                                              if(doctor.listcreated)
                                                                    Translate(doctor.sSymptom,nLang,doctor.nSymptom);
                                                              break;
                                            case'n':case'N': break;
                                            default:if(nLang ==0)
                                                        printf("%s",INVALID);
                                                     else
                                                        printf("%s", INVALID1);
                                        }
                                }while(cMenu!='y'&& cMenu!='Y'&&cMenu!='n'&&cMenu!='N'); break;
            case 'z': case 'Z': testFunc(nLang); break;
            default: if(nLang==0)
						printf("%s",INVALID);
					else
						printf("%s",INVALID1);
        }
    }while(isLoop == TRUE);
    return 0;
}
