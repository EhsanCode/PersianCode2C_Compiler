
/*
	 Ehsan Amini
	 1381/4/23
*/

#define BRABAR1  100     //  =  (brabr)
#define STAR     101     //  *
#define DIV      102     //  /
#define MINES    103     //  -
#define PLUS     104     //  +
#define PEN      105
#define COLOR    106
#define BKGRAND  107
#define CLS      108
#define POINT    109
#define CIRCL    110
#define ARC      111
#define LIN      112
#define RECT     113
#define VA       114
#define AZ       115
#define TA       116
#define BE       117
#define DER      118
#define MARKAZ   119
#define SHOA     120
#define AGAR     121
#define BORO     122
#define LESS     123     //  <
#define GREAT    124     //  >
#define EQUAL1   125     // == (mosave)
#define LESEQ    126     // <=   ( => )
#define GREEQ    127     // >=   ( =< )
#define MOKHALF  128     //  #
#define VAR      129
#define BEGIN    130
#define ENDPROG  131
#define EEST     132

#define BRABAR2  151     //  =
#define EQUAL2   152     // ==

#define DOT      201     //  .
#define COLN     202     //  :
#define CAMA     204     //  ,
#define LP       205     //  (
#define RP       206     //  )

#define BLACK0   320
#define BLUE0    321
#define GREEN0   322
#define CYAN0    323
#define RED0     324
#define MAGENTA0 325
#define BROWN0   326
#define GRAY0    327
#define YELLOW0  328
#define WHITE0   329
#define DARK     330
#define LIGHT    331

#define BLACK1   300     // ³  0
#define BLUE1    301     // ³  1
#define GREEN1   302     // ³  2
#define CYAN1    303     // ³  3
#define RED1     304     // ³  4
#define MAGENTA1 305     // ³  5
#define BROWN1   306     // ³  6
#define LGRAY1   307     // ³  7
#define DGRAY1   308     // ³  8
#define LBLUE1   309     // ³  9
#define LGREEN1  310     // ³ 10
#define LCYAN1   311     // ³ 11
#define LRED1    312     // ³ 12
#define LMAGENT1 313     // ³ 13
#define YELLOW1  314     // ³ 14
#define WHITE1   315     // ³ 15


#define ID       500
#define NUMBER   600
#define LABEL    700

#define ERROR    800
#define ERRORLEX 801
#define ERRORPT  802

#define ENDFILE  900

#define LEN_LINE 255
#define NUMTOKEN 33

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <time.h>
#include <string.h>



struct word
	{
	 char w[30];
	}st[100],label_t[100],goto_label_t[100];
int stc,ltc,gltc;

FILE *list_file;
int line_num;
char curr_token_org[40];

char strstakcpy(char* str1,char* str2)
	{
	 int len,j;
	 char end_ch;
	 int intbuffer,len_num=0;
	 strcat(str2,"\0");
	 len=strlen(str2)-1;
	 end_ch=str2[len];
	 str2[len]='\0';

	 for (int i=0;i<len;i++)
		{
		 intbuffer=256+str2[i];
		 while ((str2[i]>='0' && str2[i]<='9')||
		       (intbuffer>=128 && intbuffer<=137))
			{
			 if (intbuffer>=128 && intbuffer<=137)
				str2[i]=intbuffer-80;
			 len_num++;i++;
			 intbuffer=256+str2[i];
			}
		 for (j=0; j<len_num;j++)
			str1[len-i-1+len_num-j]=str2[i-j-1];
		 len_num=0;
		 switch (str2[i])
			{
			 case '(' :
				str1[len-i-1]=')';
			 break;
			 case ')' :
				str1[len-i-1]='(';
			 break;
			 case '>' :
				str1[len-i-1]='<';
			 break;
			 case '<' :
				str1[len-i-1]='>';
			 break;
			 case '{' :
				str1[len-i-1]='}';
			 break;
			 case '}' :
				str1[len-i-1]='{';
			 break;
			 default:
				str1[len-i-1]=str2[i];
			}
		}
	 str1[len]='\0';
	 return end_ch;
	}

class Precompiler
	{
		FILE *in,*tempfile;
	 public:
		void Precompile(char*);
	};
void Precompiler::Precompile(char* file_in)
	{
	 char file_temp_name[12];
	 // Open input file.
	 strcpy(file_temp_name,file_in);
	 strcat(file_temp_name,".fg\0");
	 if ((in = fopen(file_temp_name, "r+"))== NULL)
		{
		 printf("\nCannot open input file.");
		 exit(0);
		}
	 // Open temp file.
	 strcpy(file_temp_name,file_in);
	 strcat(file_temp_name,".tmp\0");
	 if ((tempfile = fopen(file_temp_name,"w+"))== NULL)
		{
		 printf("\nCannot macke temp file.");
		 exit(0);
		}

	 char temp_buff[LEN_LINE];
	 char end_ch[2],temp_buff0[LEN_LINE];
	 end_ch[1]='\0';
	 int i;
	 fgets(temp_buff,LEN_LINE,in);
	 while (!feof(in))
		{
		 end_ch[0]=strstakcpy(temp_buff0,temp_buff);
		 strcat(temp_buff0,end_ch);
		 fputs(temp_buff0,tempfile);
		 fgets(temp_buff,LEN_LINE,in);
		}
	 //fprintf(tempfile,"$\0");  // <----------------
	 fclose(tempfile);
	 fclose(in);

	}


//    Lexical Analyzer

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
	    int curr;
	    char buffer[LEN_LINE];
	    char token_list[100][20];
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

class LexicalAnalyzer
	{
		FILE *tempfile;
		int out_list_felag;
		//char buffer[LEN_LINE];
		//char token_list[100][20];
		//int curr;
		void set_buffer(void);
		int id_keyword(void);
		int number(void);
		int label(void);
	 public:
		void init(char*);
		int lex(void);
		LexicalAnalyzer(void);
		LexicalAnalyzer(int);
		~LexicalAnalyzer(void);

	};

LexicalAnalyzer::LexicalAnalyzer(void)
	{
	 out_list_felag=1;
	 curr=-1;
	}

LexicalAnalyzer::LexicalAnalyzer(int out_felag)
	{
	 out_list_felag=out_felag;
	 curr=-1;
	}

LexicalAnalyzer::~LexicalAnalyzer(void)
	{
	 fclose(tempfile);
	}

void LexicalAnalyzer::set_buffer(void)
	{
	 char temp_buffer1[LEN_LINE],temp_buffer2[LEN_LINE];
	 char end_ch[2];
	 end_ch[1]='\0';
	 curr=0;
	 fgets(buffer,LEN_LINE,tempfile);
	 strcpy(temp_buffer2,buffer);
	 end_ch[0]=strstakcpy(temp_buffer1,temp_buffer2);
	 strcat(temp_buffer1,end_ch);
	 if (!feof(tempfile))
		{
		 line_num++;
		 if (out_list_felag)
			{
			 fprintf(list_file," %d ) ",line_num);
			 fputs(temp_buffer1,list_file);
			}
		}
	}

void LexicalAnalyzer::init(char* file_in)
	{
	 line_num=0;
	 FILE *dbfin;
	 char file_temp_name[12];
	 char temp_buff[LEN_LINE];
	 // Open data base file.
	 if ((dbfin = fopen("database.dbf", "r+"))== NULL)
		{
		 printf("\nCannot found data base file.");
		 exit(0);
		}
	 //    init token list foram tata base file.
	 int i=0,j;
	 fgets(temp_buff,LEN_LINE,dbfin);
	 while (!feof(dbfin))
		{
		 strstakcpy(token_list[i++],temp_buff);
		 fgets(temp_buff,LEN_LINE,dbfin);
		}
	 fclose(dbfin);
	 // Open temp file for compile.
	 strcpy(file_temp_name,file_in);
	 strcat(file_temp_name,".tmp\0");
	 if ((tempfile = fopen(file_temp_name,"r+"))== NULL)
		{
		 printf("\nCannot open temp file.");
		 exit(0);
		}
	 // Open list file for Error message.
	 if (out_list_felag)
		{
		 strcpy(file_temp_name,file_in);
		 strcat(file_temp_name,".lis\0");
		 if ((list_file = fopen(file_temp_name,"w+"))== NULL)
			{
			 printf("\nCannot macke list file.");
			 exit(0);
			}
		}

	 set_buffer();
	 curr=-1;
	}

int LexicalAnalyzer::id_keyword(void)
	{
	 char temp[30];
	 int i=0,cunt;
	 int intbuffer;
	 intbuffer=256+buffer[curr];
	 while ((intbuffer>=141 && intbuffer<=175)
		|| (intbuffer>=224 && intbuffer<=254)
		|| (buffer[curr]>='0' && buffer[curr]<='9')
		|| (intbuffer>=128 && intbuffer<=137)
		|| (buffer[curr]=='_'))
			{
			 temp[i++]=buffer[curr++];
			 intbuffer=256+buffer[curr];
			}
	 temp[i]=NULL;
	 strcpy(curr_token_org,temp);
	 curr--;
	 for (cunt=0;cunt<NUMTOKEN;cunt++)
		if (!strcmp(temp,token_list[cunt]))
			return cunt+100;
	 if (!strcmp(temp,token_list[NUMTOKEN]))
			return PLUS;
	 for (cunt=NUMTOKEN+1;cunt<=NUMTOKEN+12;cunt++)
		if (!strcmp(temp,token_list[cunt]))
			return cunt+320-NUMTOKEN-1;
	 return ID;
	}

int LexicalAnalyzer::number(void)
	{
	 int intbuffer,i=0;
	 intbuffer=256+buffer[curr];
	 while ((buffer[curr]>='0' && buffer[curr]<='9')||
	       (intbuffer>=128 && intbuffer<=137))
		 {
		  curr_token_org[i++]=buffer[curr];
		  intbuffer=256+buffer[++curr];
		 }
	 curr--;
	 curr_token_org[i]=NULL;
	 return NUMBER;
	}

int LexicalAnalyzer::label(void)
	{
	 char temp[30];
	 int i=0;
	 int intbuffer;
	 curr++;
	 intbuffer=256+buffer[curr];
	 while ((intbuffer>=141 && intbuffer<=175)
		|| (intbuffer>=224 && intbuffer<=254)
		|| (buffer[curr]>='0' && buffer[curr]<='9')
		|| (intbuffer>=128 && intbuffer<=137)
		|| (buffer[curr]=='_'))
			{
			 temp[i++]=buffer[curr++];
			 intbuffer=256+buffer[curr];
			}
	 if (i==0)
		return ERRORLEX;
	 temp[i]=NULL;
	 strcpy(curr_token_org,temp);
	 curr--;
	 return LABEL;
	}

int LexicalAnalyzer::lex(void)
	{
	 int f1;
	 curr++;
	 l1:
	 f1=0;
	 //if (buffer[curr]=='$' || buffer[curr]=='\x0')
	 if (feof(tempfile))
		return ENDFILE;
	 if (curr==LEN_LINE || buffer[curr]=='\n')
		{
		 set_buffer();
		 goto l1;
		}
	 while (buffer[curr]==' '||buffer[curr]=='\t')
		{
		 curr++;
		 f1=1;
		 //if (buffer[curr]=='$'|| buffer[curr]=='\x0')
		 if (feof(tempfile))
			return ENDFILE;
		 else if (buffer[curr]=='\n')//|| buffer[curr]==LEN_LINE
			set_buffer();
		}
	 if (f1)
		goto l1;
	 if (buffer[curr]=='!')
		{
		 set_buffer();
		 f1=1;
		}
	 if (f1)
		goto l1;
	 curr_token_org[0]=buffer[curr];
	 curr_token_org[1]=NULL;
	 curr_token_org[2]=NULL;
	 switch (buffer[curr])
		{
		 case '(' : return LP;
		 case ')' : return RP;
		 case ',' : return CAMA;
		 case '.' : return DOT;
		 case ':' : return COLN;
		 case '#' : return MOKHALF;
		 case '=' :
			if (buffer[curr+1]=='=')
				{
				 curr++;
				 curr_token_org[1]=buffer[curr];
				 return EQUAL2;
				}
			return	BRABAR2;
		 case '<' :
			if (buffer[curr+1]=='=')
				{
				 curr++;
				 curr_token_org[1]=buffer[curr];
				 return LESEQ;
				}
			return	LESS;
		 case '>' :
			if (buffer[curr+1]=='=')
				{
				 curr++;
				 curr_token_org[1]=buffer[curr];
				 return GREEQ;
				}
			return	GREAT;
		 case '+' : return PLUS;
		 case '-' : return MINES;
		 case '*' :
		 case 'x' : return STAR;
		 case '/' : return DIV;
		}
	 int intbuffer;
	 intbuffer=256+buffer[curr];
	 if ((intbuffer>=141 && intbuffer<=175)
		|| (intbuffer>=224 && intbuffer<=254))
			return id_keyword();
	 if ((buffer[curr]>='0' && buffer[curr]<='9')||
	    (intbuffer>=128 && intbuffer<=137))
		return number();
	 if (buffer[curr]>='@')
		return label();
	 return ERRORLEX;
	}


//               Sentex & Semantic Analysis.

//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\
	int curr_token;
	char gramer[13][5];
	int pt[6][8];

	char stak[300];
	int id_f;
	int top;
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\

class SentexSemanticAnalysis
	{

		LexicalAnalyzer lexanalyz;
		//int curr_token;
		//char gramer[13][5];
		//char stak[300];
		//int top;
		//int pt[6][8];
		int last_error;
		//int stc;

		//int id_f;
		int error_flag;

		void init_geramer(void);
		void init_pars_table(void);
		int match(int);
		int advance(void);
		void error_analysis(void);
		void error_analysis(char*);
		int g_ID(void);
		void g_DCLS(void);
		void g_DCLS_pr(void);
		void g_DCL(void);
		void g_DCL_pr(void);
		void g_PEXPS(int num);
		void g_EXPS(int num);
		void g_EXPS_pr(int num);
		void g_EXP(void);
		int pars_table(char);

		void g_PRODOC(void);
		void g_PRODOC_pr(void);
		void g_BRABAR(void);
		void g_PEN(void);
		void g_BKGRAND(void);
		void g_CIRCL(void);
		void g_ARC(void);
		void g_CARG(void);
		void g_LIN(void);
		void g_RECT(void);
		void g_LARG(void);
		void g_POINT(void);
		void g_COLOR(void);
		void g_BORO(void);
		void g_LABEL(int);
		void g_AGAR(void);
		void g_COMP(void);

		int g_DFC(void);

	 public:
		int g_PROGRAM(void);
		SentexSemanticAnalysis(char* file_in);
		~SentexSemanticAnalysis(void);
	};

SentexSemanticAnalysis::SentexSemanticAnalysis(char* file_in)
	{
	 //line_num=0;
	 stc=0;
	 ltc=0;
	 gltc=0;
	 last_error=0;
	 error_flag=0;
	 lexanalyz.init(file_in);
	 init_geramer();
	 init_pars_table();
	 curr_token=lexanalyz.lex();
	}

SentexSemanticAnalysis::~SentexSemanticAnalysis(void)
	{
	 int i,j;
	 for (i=0;i<ltc;i++)
		{
		 for (j=0;j<gltc-1 && strcmp(label_t[i].w,goto_label_t[j].w);j++);
		 if (strcmp(label_t[i].w,goto_label_t[j].w))
			{
			 char tempstr1[30],tempstr2[30];
			 strcpy(tempstr2,label_t[i].w);
			 tempstr2[strlen(tempstr2)+1]=NULL;
			 tempstr2[strlen(tempstr2)]=' ';
			 strstakcpy(tempstr1,tempstr2);
			 fprintf(list_file,"\n\t.¢ª÷ –ê‘þ  ü `ù“ø¤“ ' œþû `%s@ ' ’¨¤“ ü¤“ : ¤¢ªû",tempstr1);
			}
		}
	 fprintf(list_file,"\n");
	 for (i=0;i<gltc;i++)
		{
		 for (j=0;j<ltc-1 && strcmp(label_t[j].w,goto_label_t[i].w);j++);
		 if (strcmp(label_t[j].w,goto_label_t[i].w))
			{
			 char tempstr1[30],tempstr2[30];
			 strcpy(tempstr2,goto_label_t[i].w);
			 tempstr2[strlen(tempstr2)+1]=NULL;
			 tempstr2[strlen(tempstr2)]=' ';
			 strstakcpy(tempstr1,tempstr2);
			 fprintf(list_file,"\n\t.¢ª÷ –ê‘þ `%s@ ' ’¨¤“ `%s@ ù“ø¤“ '  ü¤“ : ‘¯¡",tempstr1,tempstr1);
			 error_flag=1;
			}
		}
	 fprintf(list_file,"\n");
	 if (error_flag==0)
		fputs("\n\t  Not found error.\n\t\t\t\t .¢ª÷ –ê‘þ ü‘¯¡ œþû",list_file);
	 fclose(list_file);
	}

int SentexSemanticAnalysis::match(int this_token)
	{
	 if (this_token==curr_token)
		return 1;
	 return 0;
	}

int SentexSemanticAnalysis::advance(void)
	{
	 curr_token=lexanalyz.lex();
	 if (curr_token==ERRORLEX)
		{
		 error_analysis(".ù—¡‘÷ª‘÷ öîø—");//	curr_token
		 return 0;
		}
	 return 1;
	}

void SentexSemanticAnalysis::error_analysis(void)
	{
	 if (last_error==line_num)
		return;
	 fprintf(list_file,"\n\tError in line: %d \n\n",line_num);
	 last_error=line_num;
	 error_flag=1;
	 while (!( match(DOT) || match(ENDFILE)))
		advance();
	}

void SentexSemanticAnalysis::error_analysis(char* message)
	{
	 if (last_error==line_num)
		return;
	 fprintf(list_file,"\n\t%s :‘¯¡\n\n",message,line_num);
	 last_error=line_num;
	 error_flag=1;
	 while (!(match(DOT) || match(ENDFILE)))
		advance();
	 //advance();
	}

int SentexSemanticAnalysis::g_ID(void)
	{
	 int i=0,f=1;
	 if (!match(ID))
		{
		 error_analysis(".¢ª÷ ù¢¢ «þ¡ª— ¤þç—õ");
		 return 0;
		}
	 while (i<stc)
		if (!strcmp(st[i++].w,curr_token_org))
			f=0;
	 if (id_f==0 && f==0)
		{
		 error_analysis(".¤þç—õ ¢¢›õ éþ¤ã—");
		 return 0;
		}
	 if (id_f==1 && f==1)
		{
		 error_analysis(".ù¢ª÷ éþ¤ã— ¤þç—õ");
		 return 0;
		}
	 if (id_f==0)
		strcpy(st[stc++].w,curr_token_org);
	 advance();
	 return 1;
	}

int SentexSemanticAnalysis::g_PROGRAM(void)
	{
	 if (match(VAR))
		{
		 advance();
		 id_f=0;
		 g_DCLS();
		 id_f=1;
		}
	 if (match(BEGIN))
		advance();
	 else
		error_analysis(".¢ª‘“ üõ÷ «¡ªõ ùõ‘÷¤“ ü¢—“");
	 if (match(COLN))
		advance();
	 else
		error_analysis(".¢ª÷ –ê‘þ ':' –õòä");
	 g_PRODOC();
	 if (match(ENDPROG))
		advance();
	 else
		error_analysis(".¢ª‘“ üõ÷ «¡ªõ ùõ‘÷¤“ ö‘þ‘•");
	 if (match(DOT))
		advance();
	 else
		error_analysis(".¤“—ãõ‘÷ ü¤£ð ù¯ì÷");

	 if (error_flag==0)
		return 1;
	 return 0;
	}

void SentexSemanticAnalysis::g_DCLS(void)
	{
	 // DCLS -> DCL DCLS'
	 g_DCL();
	 g_DCLS_pr();
	}

void SentexSemanticAnalysis::g_DCLS_pr(void)
	{
	 // DCLS' -> DCL DCLS' | epsilon
	 if (match(ID))
		{
		 g_DCL();
		 g_DCLS_pr();
		}
	}

void SentexSemanticAnalysis::g_DCL(void)
	{
	 // DCL -> ID DCL' .
	 g_ID();
	 g_DCL_pr();
	 if (match(DOT))
		advance();
	 else
		error_analysis(".¤“—ãõ‘÷ ü¤£ð ù¯ì÷");
	}

void SentexSemanticAnalysis::g_DCL_pr(void)
	{
	 // DCL' -> , ID DCL' | ø ID DCL' | epsilon
	 if (match(CAMA) || match(VA))
		{
		 advance();
		 g_ID();
		 g_DCL_pr();
		}
	}

void SentexSemanticAnalysis::g_PRODOC(void)
	{
	 while (!(match(ENDPROG) || match(ENDFILE)))
		{
		 g_PRODOC_pr();
		 if (match(DOT))
			advance();
		 else
			error_analysis(".¤“—ãõ‘÷ ü¤£ð ù¯ì÷");
		}
	}

void SentexSemanticAnalysis::g_PRODOC_pr(void)
	{
	 if (match(CLS))
		advance();
	 else if (match(EEST))
		advance();
	 else if (match(ID))
		g_BRABAR();
	 else if (match(PEN))
		g_PEN();
	 else if (match(BKGRAND))
		g_BKGRAND();
	 else if (match(CIRCL))
		g_CIRCL();
	 else if (match(ARC))
		g_ARC();
	 else if (match(LIN))
		g_LIN();
	 else if (match(RECT))
		g_RECT();
	 else if (match(POINT))
		g_POINT();
	 else if (match(COLOR))
		g_COLOR();
	 else if (match(BORO))
		g_BORO();
	 else if (match(LABEL))
		g_LABEL(0);
	 else if (match(AGAR))
		g_AGAR();
	 else
		error_analysis(".¤“—ãõ‘÷ ùóõ›");
	}

void SentexSemanticAnalysis::g_BRABAR(void)
	{
	 g_ID();
	 if (match(BRABAR1) || match(BRABAR2))
		advance();
	 else
		error_analysis();
	 g_EXP();
	}

void SentexSemanticAnalysis::g_PEN(void)
	{
	 advance();
	 if (curr_token>=BLACK0 && curr_token<=LIGHT)
		g_DFC();
	 else
		g_EXP();
	}

void SentexSemanticAnalysis::g_BKGRAND(void)
	{
	 advance();
	 if (curr_token>=BLACK0 && curr_token<=LIGHT)
		g_DFC();
	 else
		g_EXP();
	}

int SentexSemanticAnalysis::g_DFC(void)
	{
	 if (match(BLACK0))
		 {
		  advance();
		  if (match(LIGHT))  // Seyah Roshan !
			{
			 advance();
			 return DGRAY1;
			}
		  return BLACK1;
		 }
	 if (match(BLUE0))
		 {
		  advance();
		  if (match(LIGHT))
			{
			 advance();
			 return LBLUE1;
			}
		  return BLUE1;
		 }
	 if (match(GREEN0))
		 {
		  advance();
		  if (match(LIGHT))
			{
			 advance();
			 return LGREEN1;
			}
		  return GREEN1;
		 }
	 if (match(CYAN0))
		 {
		  advance();
		  if (match(LIGHT))
			{
			 advance();
			 return LCYAN1;
			}
		  return CYAN1;
		 }
	 if (match(RED0))
		 {
		  advance();
		  if (match(LIGHT))
			{
			 advance();
			 return LRED1;
			}
		  return RED1;
		 }
	 if (match(MAGENTA0))
		 {
		  advance();
		  if (match(LIGHT))
			{
			 advance();
			 return LMAGENT1;
			}
		  return MAGENTA1;
		 }
	 if (match(BROWN0))
		 {
		  advance();
		  return BROWN1;
		 }
	 if (match(GRAY0))
		 {
		  advance();
		  if (match(LIGHT))
			{
			 advance();
			 return LGRAY1;
			}
		  if (match(DARK))
			{
			 advance();
			 return DGRAY1;
			}
		  error_analysis(" .¢ª‘“üõ ¤“—ãõ‘÷ ’þî¤— öþ ‘“ ‘þø ü‘ú÷—“ ü¤—¨î‘¡ ï÷¤ ");  // KHAKESTARY KHALY NDARIM.
		 }
	 if (match(YELLOW0))
		{
		 advance();
		 return YELLOW1;
		}
	 if (match(WHITE0))
		 {
		  advance();
		  if (match(DARK)) // Sefit Tirah !
			{
			 advance();
			 return LGRAY1;
			}
		  return WHITE1;
		 }
	 error_analysis(" .¢ª‘“üõ ¤“—ãõ‘÷ ï÷¤" ); // Rangh dar kar nabodeh!
	 return -1;
	}

void SentexSemanticAnalysis::g_CIRCL(void)
	{
	 advance();
	 if (match(LP))
		g_PEXPS(3);
	 else
		g_CARG();
	}

void SentexSemanticAnalysis::g_ARC(void)
	{
	 advance();
	 if (match(LP))
		g_PEXPS(5);
	 else
		{
		 g_CARG();
		 if (match(AZ))
			advance();
		 else
			error_analysis();
		 g_EXP();
		 if (match(TA))
			advance();
		 else
			error_analysis();
		 g_EXP();
		}
	}

void SentexSemanticAnalysis::g_CARG(void)
	{
	 if (match(BE))
		 advance();
	 else
		 error_analysis();
	 if (match(MARKAZ))
		 advance();
	 else
		 error_analysis();
	 g_EXPS(2);
	 if (match(SHOA))
		 advance();
	 else
		 error_analysis();
	 g_EXP();
	}

void SentexSemanticAnalysis::g_LIN(void)
	{
	 advance();
	 if (match(LP))
		g_PEXPS(4);
	 else
		g_LARG();
	}

void SentexSemanticAnalysis::g_RECT(void)
	{
	 g_LIN();
	}
 /*
	{
	 advance();
	 if (match(LP))
		g_PEXPS(4);
	 else
		g_LARG();
	}
 */

void SentexSemanticAnalysis::g_LARG(void)
	{
	 if (match(AZ))
		 advance();
	 else
		 error_analysis();
	 g_EXPS(2);
	 if (match(BE))
		 advance();
	 else
		 error_analysis();
	 g_EXPS(2);
	}

void SentexSemanticAnalysis::g_POINT(void)
	{
	 advance();
	 if (match(LP))
		g_PEXPS(2);
	 else
		{
		 if (match(DER))
			advance();
		 else
			error_analysis();
		 g_EXPS(2);
		}
	}

void SentexSemanticAnalysis::g_COLOR(void)
	{
	 advance();
	 if (match(LP))
		g_PEXPS(3);
	 else
		{
		 if (match(DER))
			advance();
		 else
			error_analysis();
		 g_EXPS(2);
		 if (match(TA))
			advance();
		 else
			error_analysis();
		 if (curr_token>=BLACK0 && curr_token<=LIGHT)
			g_DFC();
		 else
			g_EXP();
		}
	}

void SentexSemanticAnalysis::g_BORO(void)
	{
	 if (match(BORO))
		advance();
	 g_LABEL(1);
	}

void SentexSemanticAnalysis::g_LABEL(int flag)
	{
	 int i=0,f=0;
	 if (!match(LABEL))
		{
		 error_analysis();
		 return;
		}
	 if (flag==0)
		{
		 while (i<ltc)
			 if (!strcmp(label_t[i++].w,curr_token_org))
				 f=1;
		 if (f==1)
			{
			 error_analysis(".ü¤¤î— ’¨¤“");
			 return;
			}
		 else
			strcpy(label_t[ltc++].w,curr_token_org);
		}
	 else
		{
		 while (i<gltc)
			 if (!strcmp(goto_label_t[i++].w,curr_token_org))
				 f=1;
		 if (f==0)
			strcpy(goto_label_t[gltc++].w,curr_token_org);
		}
	 advance();
	}

void SentexSemanticAnalysis::g_AGAR(void)
	{
	 advance();
	 g_EXP();
	 g_COMP();
	 g_EXP();
	 g_BORO();
	}

void SentexSemanticAnalysis::g_COMP(void)
	{
	 if (match(LESS) || match(GREAT))
		{
		 advance();
		 if (match(BRABAR2) || match(EQUAL1))
			advance();
		}
	 else if(match(LESEQ) || match(GREEQ))
		advance();
	 else if(match(EQUAL1) || match(EQUAL2) || match(MOKHALF))
		advance();
	 else if(match(BRABAR2))
		{
		 advance();
		 if(match(BRABAR2))
			advance();
		 else
			error_analysis(".–¨ öîõõ ¤þè ¯¤ª ¤¢ ’‘¨—÷ ñõä");
		}
	 else
		error_analysis();
	}

void SentexSemanticAnalysis::g_PEXPS(int num)
	{
	 if (match(LP))
		advance();
	 else
		error_analysis();
	 g_EXPS(num);
	 if (match(RP))
		advance();
	 else
		error_analysis(".¤“—ãõ‘÷ ü¤£ð ¥—÷¤•");
	}

void SentexSemanticAnalysis::g_EXPS(int num)
	{
	 g_EXP();
	 g_EXPS_pr(num-1);
	}

void SentexSemanticAnalysis::g_EXPS_pr(int num)
	{
	 if (num <= 0 )
		return;
	 if (match(VA) || match(CAMA))
		advance();
	 else
		error_analysis(".–¨¤“—ãõ‘÷ ('ø'‘þ ',')‘ûù¢÷÷î¢› ‘þ ø ‘û¤—õ¤‘• ¢¢ã—");
	 g_EXP();
	 g_EXPS_pr(num-1);
	}

void SentexSemanticAnalysis::init_geramer(void)
	{
	 strcpy(gramer[0] ,"bc\0");
	 strcpy(gramer[1] ,"bc+\0");
	 strcpy(gramer[2] ,"bc-\0");
	 strcpy(gramer[3] ,"\0");
	 strcpy(gramer[4] ,"de\0");
	 strcpy(gramer[5] ,"de*\0");
	 strcpy(gramer[6] ,"de/\0");
	 strcpy(gramer[7] ,"\0");
	 strcpy(gramer[8] ,"f\0");
	 strcpy(gramer[9] ,"f-\0");
	 strcpy(gramer[10],"i\0");
	 strcpy(gramer[11],")a(\0");
	}

int SentexSemanticAnalysis::pars_table(char tps)
	{
	 int temp;
	 if (match(NUMBER) || match(ID))
		temp=0;
	 else if (match(PLUS))
		temp=1;
	 else if (match(MINES))
		temp=2;
	 else if (match(STAR))
		temp=3;
	 else if (match(DIV))
		temp=4;
	 else if (match(LP))
		temp=5;
	 else if (match(RP))
		temp=6;
	 else
		temp=7;
	 return (pt[tps-'a'][temp]);
	}

void SentexSemanticAnalysis::init_pars_table(void)
	{
	 for (int i=0;i<6;i++)
		for (int j=0;j<8;j++)
			pt[i][j]=ERRORPT;
	 pt[0][0]=0; pt[0][2]=0; pt[0][5]=0; pt[1][1]=1;
	 pt[1][2]=2; pt[1][6]=3; pt[1][7]=3; pt[2][0]=4;
	 pt[2][2]=4; pt[2][5]=4; pt[3][1]=7; pt[3][2]=7;
	 pt[3][3]=5; pt[3][4]=6; pt[3][6]=7; pt[3][7]=7;
	 pt[4][0]=8; pt[4][2]=9; pt[4][5]=8; pt[5][0]=10;
	 pt[5][5]=11;
	 }

void SentexSemanticAnalysis::g_EXP(void)
	{
	 int next_pro;
	 strcpy(stak,gramer[0]);
	 top=strlen(gramer[0])-1;
	 while(top>=0)
		if ((stak[top]=='+' && match(PLUS)) ||
		     (stak[top]=='-' && match(MINES)) ||
		     (stak[top]=='*' && match(STAR)) ||
		     (stak[top]=='/' && match(DIV)) ||
		     (stak[top]=='(' && match(LP)) ||
		     (stak[top]==')' && match(RP)) ||
		     (stak[top]=='i' && (match(ID) || match(NUMBER))) )
			{
			 if (match(ID))
				g_ID();
			 else
				advance();
			 stak[top--]='\0';
			}
		 else
			{
			 next_pro=pars_table(stak[top]);
			 if (next_pro==ERRORPT)
				{
				 error_analysis(".¤“—ãõ‘÷ ü®‘þ¤ –¤‘“ä");
				 return;
				}
			 stak[top]='\0';
			 strcat(stak,gramer[next_pro]);
			 top+=strlen(gramer[next_pro])-1;
			}
	}

//        ---------------- Generating Code ------------------

//     Generating Maden Code

/////////////////////////////////////////////////
	 LexicalAnalyzer le1(0);
////////////////////////////////////////////////

class GeneratingMadenCode
	{
		FILE *output;
		//LexicalAnalyzer le1;
		void standard_token(int,char*,int);
		void standard_color(int,char*,int);
		void id_cod(char*);
		void ins_id(void);
		void ins_pp_comp(void);
		void ins_pp_comp(char*);
		void ins_pp(int);
		void mc_LABEL(void);
		void mc_ID(void);
	 public:
		GeneratingMadenCode(void);
		~GeneratingMadenCode(void);
		void MadenCode(char*);

	 };

GeneratingMadenCode::GeneratingMadenCode(void)
	{
	}

GeneratingMadenCode::~GeneratingMadenCode(void)
	{
	 //delete lee;
	 fclose(output);
	}

void GeneratingMadenCode::MadenCode(char* file_in)
	{
	 int t1=stc,t2=ltc,t3=gltc;
	 le1.init(file_in);
	 stc=t1;ltc=t2;gltc=t3;
	 int this_token;
	 //line_num=0;
	 char file_temp_name[13];
	 strcpy(file_temp_name,file_in);
	 strcat(file_temp_name,".ob\0");
	 if ((output = fopen(file_temp_name,"w+"))== NULL)
		{
		 printf("\nCannot macke objecte file.");
		 exit(0);
		}
	 ins_id();
	 fprintf(output,"$");
	 while(le1.lex() != COLN);
	 this_token=le1.lex();
	 while(this_token != ENDPROG)
		{
		 switch(this_token)
			{
			 case ID:
				mc_ID();
			 break;
			 case CLS:
				fprintf(output,"\ncleardevice() ;");
			 break;
			 case EEST:
				fprintf(output,"\ngetche() ;");
			 break;
			 case LABEL:
				fprintf(output,"\n");
				mc_LABEL();
				fprintf(output," :");
			 break;
			 case CIRCL:
				fprintf(output,"\ncircle");
				ins_pp_comp();
			 break;
			 case ARC:
				fprintf(output,"\narc");
				ins_pp_comp();
			 break;
			 case LIN:
				fprintf(output,"\nline");
				ins_pp_comp();
			 break;
			 case RECT:
				fprintf(output,"\nrectangle");
				ins_pp_comp();
			 break;
			 case POINT:
				fprintf(output,"\nputpixel");
				ins_pp_comp(", getcolor() ");
			 break;
			 case AGAR:
				fprintf(output,"\nif");
				ins_pp(2);
				fprintf(output," ;");
			 break;
			 case BORO:
				fprintf(output,"\ngoto ");
				le1.lex();
				mc_LABEL();
				fprintf(output," ;");
			 break;
			 case PEN:
				fprintf(output,"\nsetcolor");
				ins_pp(0);
				fprintf(output," ) ;");
			 break;
			 case BKGRAND:
				fprintf(output,"\nsetbkcolor");
				ins_pp(0);
				fprintf(output," ) ;");
			 break;
			 case COLOR:
				fprintf(output,"\nsetfillstyle ( SOLID_FILL , getcolor() ) ;");
				fprintf(output,"\nfloodfill");
				ins_pp_comp();
			 break;

			}
		 this_token=le1.lex();
		}
	 fprintf(output,"\n$\0");
	 fclose(output);
	}

void GeneratingMadenCode::standard_token(int ttok,char* stoken,int ltokn=-1)
	{
	 switch(ttok)
		{
		 case BRABAR1:
		 case BRABAR2:
			if (ltokn==LESS||ltokn==GREAT||ltokn==BRABAR2)
				strcpy(stoken,"=\0");
			else
				strcpy(stoken," =\0");
		 break;
		 case STAR:
			strcpy(stoken," *\0");
		 break;
		 case DIV:
			strcpy(stoken," /\0");
		 break;
		 case MINES:
			strcpy(stoken," -\0");
		 break;
		 case PLUS:
			strcpy(stoken," +\0");
		 break;
		 case LESS:
			strcpy(stoken," <\0");
		 break;
		 case GREAT:
			strcpy(stoken," >\0");
		 break;
		 case EQUAL1:
		 case EQUAL2:
			if (ltokn==LESS||ltokn==GREAT||ltokn==BRABAR2)
				strcpy(stoken,"=\0");
			else
				strcpy(stoken," ==\0");
		 break;
		 case MOKHALF:
			strcpy(stoken," !=\0");
		 break;
		 case LESEQ:
			strcpy(stoken," <=\0");
		 break;
		 case GREEQ:
			strcpy(stoken," >=\0");
		 break;
		 case LP:
			strcpy(stoken," (\0");
		 break;
		 case RP:
			strcpy(stoken," )\0");
		 break;
		 case BORO:
			strcpy(stoken," ) goto \0");
		 break;
		 case LABEL:
			strcpy(stoken,"\0");
			mc_LABEL();
		 break;
		}
	}

void GeneratingMadenCode::standard_color(int ttok,char* stoken,int ltokn=-1)
	{
	 int temp;
	 switch (ttok)
		{
		 case LIGHT:
			if (ltokn==GRAY0)
				temp=7;
			else
				temp=ltokn-BLACK0+8;
		 break;
		 case DARK:
			if (ltokn==GRAY0)
				temp=8;
			else
				temp=7;
		 break;
		 case YELLOW0:
			temp=14;
		 break;
		 case WHITE0:
			temp=15;
		 break;
		 default :
			temp=ltokn-BLACK0;
		}
	 itoa(temp,stoken,10);
	}

void GeneratingMadenCode::ins_pp_comp(void)
	{
	 ins_pp_comp("\0");
	}

void GeneratingMadenCode::ins_pp_comp(char* mass)
	{
	 int this_token=le1.lex();
	 if (this_token==LP)
		ins_pp(1);
	 else
		{
		 if (this_token==BE)
			le1.lex();
		 ins_pp(0);
		}
	 fprintf(output," %s) ;",mass);
	}

void GeneratingMadenCode::ins_pp(int flag)
	{
	 int next_token,this_token=le1.lex(),ltoken;
	 char codtemp[12],temp_curr_token[30],last_curr_token[30];
	 fprintf(output," (");
	 ltoken=next_token=this_token;
	 strcpy(last_curr_token,curr_token_org);
	 while (this_token!=DOT)
		{
		 if (next_token!=DOT)
			{
			 next_token=le1.lex();
			 strcpy(temp_curr_token,curr_token_org);
			 strcpy(curr_token_org,last_curr_token);
			 strcpy(last_curr_token,temp_curr_token);
			}
		 if (flag==1 && next_token==DOT)
			return;
		 if (!(this_token==VA||this_token==CAMA||this_token==SHOA||
		      this_token==AZ||this_token==TA||this_token==BE))
			{
			 if (this_token==NUMBER)
				 fprintf(output," %s",curr_token_org);
			 else if (this_token==ID)
				{
				 id_cod(codtemp);
				 fprintf(output," %s",codtemp);
				}
			 else if (this_token>=BLACK0 && this_token<= LIGHT)
				{
				 if (!(next_token>=BLACK0 && next_token<= LIGHT))
					{
					 standard_color(this_token,codtemp,ltoken);
					 fprintf(output," %s",codtemp);
					}
				}
			 else
				{
				 standard_token(this_token,codtemp,ltoken);
				 fprintf(output,"%s",codtemp);
				}
			}
		 else
			fprintf(output," ,");
		 ltoken=this_token;
		 this_token=next_token;
		}
	}

void GeneratingMadenCode::mc_ID(void)
	{
	 char codtemp[12];
	 int this_token;
	 id_cod(codtemp);
	 fprintf(output,"\n%s =",codtemp);
	 le1.lex();
	 this_token=le1.lex();
	 while (this_token!=DOT)
		{
		 if (this_token==NUMBER)
			 fprintf(output," %s",curr_token_org);
		 else if (this_token==ID)
			{
			 id_cod(codtemp);
			 fprintf(output," %s",codtemp);
			}
		 else
			{
			 standard_token(this_token,codtemp);
			 fprintf(output," %s",codtemp);
			}
		 this_token=le1.lex();
		}
	 fprintf(output," ;");
	}

void GeneratingMadenCode::id_cod(char* codid)
	{
	 int i=0;
	 char id_num[8];
	 while ((i<stc && strcmp(st[i].w,curr_token_org)))i++;
	 itoa(i,id_num,10);
	 strcpy(codid,"id");
	 strcat(codid,id_num);
	}

void GeneratingMadenCode::ins_id(void)
	{
	 int i=0;
	 char id_num[6],id_name[10];
	 for (i=0;i<stc;i++)
		{
		 itoa(i,id_num,10);
		 strcpy(id_name,"id");
		 strcat(id_name,id_num);
		 fprintf(output,"%s\n",id_name);
		}
	}

void GeneratingMadenCode::mc_LABEL(void)
	{
	 int i=0;
	 char laebl_num[6],laebl_name[10];
	 while ((i<ltc && strcmp(label_t[i].w,curr_token_org)))i++;
	 itoa(i,laebl_num,10);
	 strcpy(laebl_name,"lb");
	 strcat(laebl_name,laebl_num);
	 fprintf(output,"%s",laebl_name);
	}


//          Generating  C  Code

class GeneratingCode
	{
		FILE *output,*input,*mainfile;
	 public:
		void mackcod(char*);
	};

void GeneratingCode::mackcod(char* file_in)
	{
	 char file_temp_name[13],inputbuff[LEN_LINE];
	 strcpy(file_temp_name,file_in);
	 strcat(file_temp_name,".cpp\0");
	 if ((output = fopen(file_temp_name,"w+"))== NULL)
		{
		 printf("\nCannot macke output file.");
		 exit(0);
		}
	 strcpy(file_temp_name,file_in);
	 strcat(file_temp_name,".ob\0");
	 if ((input = fopen(file_temp_name,"r+"))== NULL)
		{
		 printf("\nCannot open objecte file.");
		 exit(0);
		}
	 if ((mainfile = fopen("main.man","r+"))== NULL)
		{
		 printf("\nCannot open main file.");
		 exit(0);
		}
	 {
	  struct tm *ptr;
	  time_t lt;
	  lt=time(NULL);
	  ptr=localtime(&lt);
	  fprintf(output,"\n /*\n\t%s */\n\n",asctime(ptr));
	 }
	 fgets(inputbuff,LEN_LINE,mainfile);
	 while (strcmp(inputbuff,"$\n"))
		{
		 fputs(inputbuff,output);
		 fgets(inputbuff,LEN_LINE,mainfile);
		}
	 fgets(inputbuff,LEN_LINE,input);
	 if (strcmp(inputbuff,"$\n"))
		{
		 fprintf(output,"	 int ");
		 while (strcmp(inputbuff,"$\n"))
			{
			 inputbuff[strlen(inputbuff)-1]='\0';
			 fputs(inputbuff,output);
			 fgets(inputbuff,LEN_LINE,input);
			 if (strcmp(inputbuff,"$\n"))
				fprintf(output," , ");
			}
		 fprintf(output," ;\n");
		}
	 fgets(inputbuff,LEN_LINE,mainfile);
	 while (strcmp(inputbuff,"$\n"))
		{
		 fputs(inputbuff,output);
		 fgets(inputbuff,LEN_LINE,mainfile);
		}
	 fgets(inputbuff,LEN_LINE,input);
	 while (strcmp(inputbuff,"$"))
		{
		 fprintf(output,"	 ");
		 fputs(inputbuff,output);
		 fgets(inputbuff,LEN_LINE,input);
		}
		 fgets(inputbuff,LEN_LINE,mainfile);
	 while (strcmp(inputbuff,"$\n"))
		{
		 fputs(inputbuff,output);
		 fgets(inputbuff,LEN_LINE,mainfile);
		}
	 fclose(output);
	 fclose(input);
	 fclose(mainfile);
	}

void mackEXEcod(char *file_in)
	{
	 char file[20],tempfilename[13];
	 const char *fil;
	 strcpy(tempfilename,file_in);
	 strcat(tempfilename,".cpp");
	 strcpy(file,"tcc ");
	 strcat(file,tempfilename);
	 fil=file;
	 system(fil);
	}

void ana_file(char *in)
	{
	 for (int i=0;i<8 && in[i] !='.' && in[i] !='\n' ;i++);
	 if (in[i]=='.')
		if (strcmp(in+i,".fg"))
			{
			 printf("\nError!\nThis file not a 'fg' file.");
			 exit(0);
			}
	 in[i]='\0';
	}

void view(char* file_in)
	{
	 char file[20];
	 const char *fil;
	 strcpy(file,"edit ");
	 strcat(file,file_in);
	 fil=file;
	 system(fil);
	}

void main(int num ,char* argom[])
	{
	 char file_in[40];
	 char tempfilename[40];
	 int felag=0;
	 if (num < 2)
		{
		 printf("\n Enter File name:");
		 gets(file_in);
		}
	 else
		{
		 strcpy(file_in,argom[1]);
		 if (!strcmp(file_in,"/?"))
			{
			 view("farger.hlp\0");
			 return;
			}
		}
	 ana_file(file_in);
	 {
	  Precompiler prc;
	  prc.Precompile(file_in);
	  SentexSemanticAnalysis  ssa(file_in);
	  felag=ssa.g_PROGRAM();
	 }
	 if (felag)
		{
		 strcpy(tempfilename,file_in);
		 strcat(tempfilename,".lis");
		 view(tempfilename);
		 GeneratingMadenCode gc1;
		 gc1.MadenCode(file_in);
		 GeneratingCode gc;
		 gc.mackcod(file_in);
		 strcpy(tempfilename,file_in);
		 strcat(tempfilename,".cpp");
		 view(tempfilename);
		 //mackEXEcod(file_in);
		}
	 else
		{
		 strcpy(tempfilename,file_in);
		 strcat(tempfilename,".lis");
		 view(tempfilename);
		 strcpy(tempfilename,file_in);
		 strcat(tempfilename,".fg");
		 view(tempfilename);
		}
	}
