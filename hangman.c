#include<stdio.h>	
#include<stdlib.h>	
#include<string.h>	
#include<time.h>
	
void diagone(int i); 
void diagtwo(int i); 
void diagthree(int i); 
void diagfour(int i); 
void diagfive(int i); 
void diagsix(int i); 
void diagseven(int i); 
void diageight(int i,char word[20],FILE *);	
int game(char *,char *,int,FILE *,int ispresent[26],int word_count);	

typedef struct mine
{
	char str[20];
}mine;

mine obj[96000];


typedef struct dup
{
	char st[20];
}dup;

dup ob[96000];

char guess[20]="";
int v = 0;

void main()		
{	
	FILE *fp;
	int i=0,j=0,word_count=0,length=0,index=0,ispresent[26]={0} ;
	char a[20];

	char cipher[20],word[20],*pch;
	fp=fopen("6.txt","r");		
	while((fgets(a,20,fp)))
	{
		a[6] = '\0';
		sprintf(obj[i].str,"%s",a);
		i++;
	}					
	word_count = i-1;
	srand(time(NULL));
	index=rand()%(word_count-1);
	sprintf(word,"%s",obj[index].str);
	length=strlen(word);	
	printf(" #Word : %d\n",word_count);
	switch(length)
	{	
		case 6:
			sprintf(cipher,"%s","______");
			break;
	}
	printf("\t\t\t\t Welcome to Hangman Game\n");			
	game(cipher,word,length,fp,ispresent,word_count);		
}	

int game(char cipher[20],char word[20],int length,FILE *fp,int ispresent[26],int word_count)	
{		
	int i=0,j=0,k=0,r=0,g=0,w=0,flag=0,asc=0,c1=0,c2=0,u=1,y=0,z=0;
	static	int g_i[6] = {-1,-1,-1,-1,-1,-1} ,p = 0,q=0, mistakecount=0 , remaining_count=8; 
	static char g_c[6] = "______";
	char guessed_letter;				

	while(1)	
	{	
	flag=0;		
	k = 0;
	c1 = 0;
	c2 = 0;
	int count1[26] = {0} , count2[26] = {0};
	//printf(" Original Word : %s\n",word);
	printf("\t\t\t\t The word to be guessed is   :   %s(%d)\n",cipher,length);			
	printf(" Enter the guessed letter :\n\n ");			
	scanf("%s",&guessed_letter);	
	asc=guessed_letter;	
	
	if(!((asc>=97&&asc<=122)))
	{
		printf(" The given input is Invalid.\n Please be careful while entering input\n");
		printf(" #Wrong attempts left : %d\n",remaining_count);		
		continue;
	}
	else
	{
		asc = asc - 97;
	}
	if(ispresent[asc]==1)
	{	
		printf(" You have already entered this letter.\n Please try with other letters\n");
		printf(" #Wrong attempts left : %d\n",remaining_count);		
		continue;
	}
	ispresent[asc]=1;
	u = 1;
	for(i=0;i<length;i++)	
	{			
		if(word[i]==guessed_letter)		
		{		
			cipher[i]=guessed_letter;						
			g_i[p] = i;
			g_c[p]= guessed_letter;
			p++;
			c1++;
			flag=1;			
			u = 0;
			v = 1;
		}		
	}	
	if(u)
	{
		guess[q] = guessed_letter;
		printf(" Failed Letters : %s\n",guess);
		q++;
	}	
	for(j=0;j<word_count;j++)
	{
		for(i=0;i<length;i++)	
		{			
			if((obj[j].str[i])==guessed_letter)		
			{		
				c2++;		
			}		
		}		
		for(g=0;g<p;g++)
		{
				if(((obj[j].str[g_i[g]]) == g_c[g]))
				{		
					w++;
				}
		}
		if((w==p && c1 == c2))
		{			
			u = 1;			
			for(y=0;y<6;y++)
			{
				for(z=0;z<q;z++)
				{
					if(obj[j].str[y] == guess[z])
					{
						u = 0;
						break;
					}
				}
			}	
			
			if(v == 1)
			{		
				for(i=0;i<6;i++)
				{	
					if(cipher[i]!='_')
					{
					asc = cipher[i];
					asc = asc - 97;
					count1[asc]++;
				}
			}
		}	
			for(i=0;i<6;i++)
			{			
				asc = obj[j].str[i];
				asc = asc - 97;
				count2[asc]++;
			}	
	
			for(i=0;i<26;i++)
			{			
				if(count1[i]!=0)
				{
					if(count1[i]!=count2[i])
					{
						u = 0;
					}
				}
			}		
			
			for(i=0;i<26;i++)
			{
				count1[i] = count2[i] = 0;
			}
			if(u)
			{		
				sprintf(ob[k].st,"%s",obj[j].str);
				//printf(" %d %s\n",k,ob[k].st);
				k++;
			}
		}
		w = 0;
		c2 = 0;
	}	
	
	int t = 0;
	t = rand()%k;
	sprintf(word,"%s",ob[t].st);

	//printf(" Number of Possible Selections : %d\n",k);
	//printf(" Selected Index : %d\t%s\n",t,word);
	if(flag==1)		
	{		
		printf(" Your Guess is correct!\n");						
		printf(" #Wrong attempts left : %d\n",remaining_count);		
		if(strcmp(cipher,word)==0)	
		{	
			printf("\t\t\t\t Congratulations!!!!\n\t\t\t\t The correct word is\t \"%s\"\n\t\t\t\t You have won the game!!!!!!\n",cipher);	
			fclose(fp);
			exit(EXIT_SUCCESS);	
		}	
	}
	if(flag==0)
	{
		mistakecount++;
		remaining_count--;

		printf(" Oops. You have made a mistake!!!\n");
		printf(" #Wrong Attempts left: %d\n",remaining_count);		
		
		switch(mistakecount)
		{
			case 1:
				diagone(i);
				break;
			case 2:
				diagtwo(i);
				break;
			case 3:
				diagthree(i);
				break;
			case 4:
				diagfour(i);
				break;
			case 5:
				diagfive(i);
				break;
			case 6:
				diagsix(i);
				break;
			case 7:
				diagseven(i);
				break;
			case 8:
				diageight(i,word,fp);
				break;
		}
	game(cipher,word,length,fp,ispresent,word_count);		
	}
	}
	return 0;		
}	


void diagone(int i) 
{ 
	printf("\n\n\t\t\t\t\tGoing to jail\t\t.\t..\t...\n\n\n"); 
} 

void diagtwo(int i) 
{ 	 
	printf("\n\n\t\t\t\t\t|---------------|\n\t\t\t\t\t|\t\t|\n"); 
	   for(i=0;i<25;i++)	
		{ 
				printf("\t\t\t\t\t\t\t"); 
				printf("|\n"); 
		} 
	printf("\t\t\t"); 
	   for(i=0;i<70;i++) 
		{ 
			printf("-"); 
		} 
	printf("\n"); 
} 

void diagthree(int i) 
{ 	 
	printf("\n\n\t\t\t\t\t|---------------|\n\t\t\t\t\t|\t\t|\n\t\t\t\t|-------------|\t\t|\n\t\t\t\t|             |\t\t|\n\t\t\t\t|             |\t\t|\n\t\t\t\t|             |\t\t|\n\t\t\t\t|-------------|\t\t|\n"); 
	   for(i=0;i<25;i++) 
		{ 
				printf("\t\t\t\t\t\t\t"); 
				printf("|\n"); 
		} 
	printf("\t\t\t"); 
	   for(i=0;i<70;i++) 
		{ 
			printf("-"); 
		} 
	printf("\n"); 
} 

void diagfour(int i) 
{
	printf("\n\n\t\t\t\t\t|---------------|\n\t\t\t\t\t|\t\t|\n\t\t\t\t|-------------|\t\t|\n\t\t\t\t|   __    __  |\t\t|\n\t\t\t\t|             |\t\t|\n\t\t\t\t|             |\t\t|\n\t\t\t\t|-------------|\t\t|\n"); 
	   for(i=0;i<25;i++) 
		{ 
				printf("\t\t\t\t\t\t\t"); 
				printf("|\n"); 
		} 
	printf("\t\t\t"); 
	   for(i=0;i<70;i++) 
		{ 
			printf("-"); 
		} 
	printf("\n"); 
} 

void diagfive(int i) 
{ 	 
	printf("\n\n\t\t\t\t\t|---------------|\n\t\t\t\t\t|\t\t|\n\t\t\t\t|-------------|\t\t|\n\t\t\t\t|   __    __  |\t\t|\n\t\t\t\t|      __     |\t\t|\n\t\t\t\t|             |\t\t|\n\t\t\t\t|-------------|\t\t|\n"); 
	   for(i=0;i<20;i++) 
		{ 
				printf("\t\t\t\t\t\t\t"); 
				printf("|\n"); 
		} 
	printf("\t\t\t"); 
	   for(i=0;i<70;i++) 
		{ 
			printf("-"); 
		} 
	printf("\n"); 
} 

void diagsix(int i) 
{
	printf("\n\n\t\t\t\t\t|---------------|\n\t\t\t\t\t|\t\t|\n\t\t\t\t|-------------|\t\t|\n\t\t\t\t|   __    __  |\t\t|\n\t\t\t\t|      __     |\t\t|\n\t\t\t\t|             |\t\t|\n\t\t\t\t|-------------|\t\t|\n\t\t\t\t     |   |\t\t|\n\t\t\t\t     |   |\t\t|\n\t\t\t    |---------------------|     |\n\t\t\t    |                     |     |\n\t\t\t    |                     |     |\n\t\t\t    |                     |     |\n\t\t\t    |---------------------|     |\n"); 
	   for(i=0;i<20;i++) 
		{ 
				printf("\t\t\t\t\t\t\t"); 
				printf("|\n"); 
		} 
	printf("\t\t\t"); 
	   for(i=0;i<70;i++) 
		{ 
			printf("-"); 
		} 
	printf("\n"); 
} 

void diagseven(int i) 
{
	printf("\n\n\t\t\t\t\t|---------------|\n\t\t\t\t\t|\t\t|\n\t\t\t\t|-------------|\t\t|\n\t\t\t\t|   __    __  |\t\t|\n\t\t\t\t|      __     |\t\t|\n\t\t\t\t|             |\t\t|\n\t\t\t\t|-------------|\t\t|\n\t\t\t\t     |   |\t\t|\n\t\t\t\t     |   |\t\t|\n\t\t\t    |---------------------|     |\n\t\t\t    |                     |     |\n\t\t\t    |                     |     |\n\t\t\t    |                     |     |\n\t\t\t    |---------------------|     |\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n"); 
	   for(i=0;i<20;i++) 
		{ 
				printf("\t\t\t\t\t\t\t"); 
				printf("|\n"); 
		} 
	printf("\t\t\t"); 
	   for(i=0;i<70;i++) 
		{ 
			printf("-"); 
		} 
	printf("\n"); 
} 

void diageight(int i,char word[20],FILE *fp) 
{
	printf("\n\n\t\t\t\t\t|---------------|\n\t\t\t\t\t|\t\t|\n\t\t\t\t|-------------|\t\t|\n\t\t\t\t|   __    __  |\t\t|\n\t\t\t\t|      __     |\t\t|\n\t\t\t\t|             |\t\t|\n\t\t\t\t|-------------|\t\t|\n\t\t\t\t     |   |\t\t|\n\t\t\t\t     |   |\t\t|\n\t\t\t    |---------------------|     |\n\t\t\t    |                     |     |\n\t\t\t    |                     |     |\n\t\t\t    |                     |     |\n\t\t\t    |---------------------|     |\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t   |\t   |\t\t|\n\t\t\t\t@@@|\t   |@@@\t\t|\n\t\t\t\t@@@ \t    @@@\t\t|\n"); 
	   for(i=0;i<20;i++) 
		{ 
				printf("\t\t\t\t\t\t\t"); 
				printf("|\n"); 
		} 
	printf("\t\t\t"); 
	   for(i=0;i<70;i++) 
		{ 
			printf("-"); 
		} 
	printf("\n"); 
	printf("\n\n\t\t\t\t\tSORRY!!\n\t\t\t\t\tYOU ARE HANGED TO DEAD!!!!\n\t\t\t\t\tTHE CORRECT WORD IS \"%s\"\n\t\t\t\t\tBYE!!BYE!!!!\n",word); 
	fclose(fp);	
	exit(EXIT_FAILURE);
} 
