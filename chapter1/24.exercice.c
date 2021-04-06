#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

#define SIZE 1000 //max number of chars per line
/*return values for escape_sequence_check()*/
#define ALLGOOD 1
#define HEX	   -1
#define OCTAL  -2
#define BAD    -3

/*STRUCTS*/
typedef struct multi_line{
	/*need signed bit since for track since closing 
	char subtract: if too many closing 'track' should be negative */
	int64_t track; //related to arithmetic of opening and closing chars
	uint64_t start_linenum;
	uint64_t end_linenum;
	uint8_t start_line[SIZE+1];
	uint8_t end_line[SIZE+1];
} multline;

typedef struct escape_chars{
	uint8_t check_escape;
	uint8_t repeat_timer;
	uint8_t octal_check;
	uint8_t hex_check;
} escape_chars;

typedef struct comment{
	uint8_t comment; //for c89 style comments '*/'
	uint8_t check_comment; //activate check
	uint64_t num_char; //make sure right character rigth after
} comment;

typedef struct quote{
	char type; //' or "
	uint64_t len; //numb of chars inside of quotes
	uint8_t track; //tracks number of ' or ", when 2 done
} quote;

typedef struct essential{
	uint8_t currline[SIZE];
	uint64_t linenum;
	uint8_t curr_char;
	uint64_t i; //in currline, can be thought about as curr_char num
} essential //often passed to other functions
/*EOF STRUCTS*/


/*Func Declerations */
int check_octal(char escape_char);
void init_multline(int num_structs, ...);
char escape_sequence_check(char escape_char);
int binsearch(const char array[], int find, int n);
char *getline(uint8_t currline[], uint64_t n, FILE *fh);
void error_multline(multline *ml_chr, char specified_char);
void error(uint64_t linenum, char *message, uint8_t currline[]);
void quote_check(quote *qchar, escape_chars *esc, essential *info);  
void set_multline_chars(multline *character, essential *info, int8_t modifier);
/*EOF Func Declerations*/


int main(int argc, char *argv[])
{	
	essential info = {.linenum = 1, .i = 0}
	quote squote = {.type = '\'', .len = 0, .track = 0};
	quote dquote = {.type = '\"', .len = 0, .track = 0};
	comment comnt = {.comment = 0, .check_comment = 0, .num_char = 0}; 
	escape_chars esc = {.check_escape = 0, repeat_timer = 0, .octal_check = 0, .hex_check = 0};
	multline brack, braces, paren;
	/*old way to do it brack.track = 0; brack.start_linenum = 0, brack.end_linenum = 0;*/
	/*memset(&braces, 0, (void *)(braces.start_line) - (void *)&(braces.track));
	just a cool way to set zeros between track & start_line, BUT, it is not safe
	It is confusing, and with padding, there can be unintential affects. The reason
	it works is because track is pushed to the stack at a earlier memory address and
	the elements below it follow it in order.*/
	init_multline(3, &brack, &braces, &paren); //curious of variadic functions, just think its cool

	FILE *fh = NULL;
	if (argc >= 2 && ((fh = fopen(argv[1], "r")) == NULL))
	{
			printf("\"%s\" does not exist!\nBye!\n", argv[1]);
			exit(42); //error, can't read file
	}
	char *(*choose_func)() = (agrc > 2) ? fgets : getline;

	do{
		if(choose_func(info.currline, SIZE, fh) == NULL)
			break;

		for(info.i = 0; info.currline[info.i] != '\0'; info.i++) //info.i == current char num 
		{
			info.curr_char = info.currline[info.i];
			if(comnt.comment)
			{
				if(info.curr_char == '*')
				{
					comnt.check_comment = 1;
					comnt.num_char = i + 1; //check next char
					continue;
				}
				if(comnt.check_comment && comnt.num_char == i) 
				{
					if (info.curr_char == '/')
						comnt.comment = 0;
					else
						comnt.check_comment = 0;
				}
				continue;
			}
			else if(comnt.check_comment && comnt.num_char == i) 
			{
				if(info.curr_char == '*')
				{
					comnt.comment = 1;
					continue;
				}
				//C99 Comments
				else if(info.curr_char == '/')
				{
					comnt.check_comment = 0;
					break; //get the next line break out of for loop
				}
				else
					comnt.check_comment = 0;
			}

			//check if have started quote
			if(!(dquote.track==1 || squote.track==1) &&
			info.curr_char != '\'' && info.curr_char != '\"') 
			{
				switch(info.curr_char)
				{
					case '[':
						set_multline_chars(&brack, &info, 1);
						break;
					case ']':
						set_multline_chars(&brack, &info, -1);
						break;
					case '(':
						set_multline_chars(&paren, &info, 1);
						break;
					case ')':
						set_multline_chars(&paren, &info, -1);
						break;
					case '{':
						set_multline_chars(&braces, &info, 1);
						break;
					case '}':
						set_multline_chars(&braces, &info, -1);
						break;
					case '/':
						comnt.check_comment = 1;
						comnt.num_char = i + 1; //check value of next char
						break;
				}
			}
			/* WILL REMOVE THIS SOON 
			else if(info.curr_char == '\'' || squote == 1)
			{

				if (info.curr_char == '\'' && i > 0 && currline[i-1] != '\\')
					squote += 1;
				else if (info.curr_char == '\'' && i == 0)
					squote += 1;
				else if (info.curr_char == '\'' && i >= 2 && currline[i-1] == '\\' && currline[i-2] == '\\')
					squote += 1;

				//does the handeling of escape sequence checking	
				init_escape(info.curr_char, currline, linenum, 
				&repeat_timer, &check_escape, &hex_check, &octal_check);
			}
			*/

			if(squote.track == 2)
			{
				if (squote.len > 1)
					error(info.linenum, "Too many chars in \' \'", info.currline);
				else if(squote.len == 0)
					error(info.linenum, "NO char between \' \'", info.currline);
				squote = {.len = 0, .track = 0};
			}
			if(dquote.track == 2)
				dquote = {.len = 0, .track = 0};
			//EOF char i
		}

		//EOF Line linenum
		if (dquote.track == 1)
		{
			error(info.linenum, "Missing \"", info.currline);
			dquote = {.len = 0, .track = 0};
		}
		
		if (squote.track == 1)
		{
			error(info.linenum, "Missing \'", info.currline);
			squote = {.len = 0, .track = 0};
		}

		info.linenum++;
	} while(info.i > 0); 

	//EOF File
	error_multline(3, &brack, &braces, &paren);
	return 0;
}

void error_multline(multline *ml_chr, char specified_char) //specified char should be closing char
{
	char last[7] = {'L', 'a', 's', 't', ' '};
	char missing[10] = {'M', 'i', 's', 's', 'i', 'n', 'g', ' '};
	//hacky way to get specific char for each different struct
	missing[8] = last[5] = specified_char; missing[9] = last[6] = '\0';

	if (ml_chr->track) //should be == 0 if for every opening char there is a closing char
	{
		error(ml_chr->start_linenum, missing, ml_char->start_line);
		if( strlen((char *)ml_char->end_line) && ml_char->end_line[0] != '\n' ) 
			error(ml_char->end_linenum, last, ml_char->end_line);
	}
}


void init_multline(int num_structs, ...)
{
	va_list args;
	va_start(args, num_structs);
	for(int i = 0; i < num_structs; i++)
	{
		multline *temp = va_arg(args, multline *);
		temp->track = 0;
		temp->start_linenum = 0;
		temp->end_linenum = 0;
	}
	va_end(args);
}


char *getline(uint8_t currline[], uint64_t n, FILE *fh)
{
	int i; uint8_t c;
	for(i = 0; i < n - 1 && (c = getchar()) != '\n';i++)
		currline[i] = c;
	currline[i] = '\0'; //this is why we do < n - 1
	if (!i) //no data in currline, end of program
		return NULL;
}


int binsearch(const char array[], int find, int n)
//type meaning feed me the sizeof the type of the array
{
	uint64_t low = 0, high = n - 1, mid;
	if(high == (uint64_t)(-1)) //n == 0 high == n - 1 therefore -1 therefore 0xff..ff
		return -1;
	while(low <= high)
	{
		mid = (high+low)/2;
		if (find > array[mid])
			low = mid + 1;
		else if( find < array[mid])
			high = mid - 1;
		else
			return mid;
	}
	return -1; //didn't find it :(
}


char escape_sequence_check(char escape_char)
{
	const static char escape[12] = {
	'\"', '\'', '?', '\\', 'a', 'b', 'e', 'f', 'n', 'r', 't', 'v'
	}; //all escape chars ordered by min ascii to max ascii 

	
	if (binsearch(escape, escape_char, 12) >= 0)
		return ALLGOOD; //True, char is a escape_sequence
	else if (escape_char == 'x')
		return HEX; //'\xhh' or '\nnn' (hex or octal)
		//now have to make sure that if /x that there are only two hex digits
	else if (check_octal(escape_char))
		return OCTAL;
		//similar story for this one, have to make sure that only 3 octal digits
	else
		return BAD; 	
}


void quote_check(uint8_t currline[], uint8_t i, quote *qchar, uint64_t linenum, escape_chars *esc)  
{
	if (info.curr_char == qchar->type)
	{
		//handle '\'' or '\"'
		if (i > 0 && currline[i-1] != '\\')
			qchar->track += 1;
		//handle when first char is " or ' in line
		else if (i == 0)
			qchar->track += 1;
		//handle '\\'
		else if (i >= 2 && currline[i-1] == '\\' && currline[i-2] == '\\')
			qchar->track += 1;
	}
	else //therefore != qchar->type
	{
		//really only useful for '' aka single quotes
		if(!repeat_timer && !check_escape)
			//still not done with '' need to make sure only one char
			qchar->len += 1;
	}

	//does the handeling of escape sequence checking	
	if (esc->repeat_timer)
	{
		esc->repeat_timer -= 1;
		if (info.curr_char == qchar->type)
		{
			if(esc->hex_check && esc->repeat_timer == 1) 
				/*==1 since og value ==2 and after -=1 == 1
				& if here curr_char == ' or " therefore then end*/
				error(linenum, "No hex number present!", currline);
			esc->hex_check = esc->octal_check = 
			esc->repeat_timer = 0;
		}
		if(esc->hex_check)
		{
			if(!isxdigit(info.curr_char))
			{
				error(linenum, "Hex Not a valid char number", currline);
				esc->repeat_timer = 0;
				esc->hex_check = 0;
			}
		}
		if(esc->octal_check)
		{
			if(!check_octal(info.curr_char))
			{
				error(linenum, "Octal Not a valid char number", currline);
				esc->repeat_timer = 0;
				esc->octal_check = 0;
			}
		}
	}

	//allow '\\' for cases like '\n'
	if(esc->check_escape)
	{
		switch (escape_sequence_check(info.curr_char))
		{	
			case ALLGOOD:
				break;
			case HEX: 
				esc->hex_check = 1;
				esc->repeat_timer = 2;
				break;
			case OCTAL:
				esc->octal_check = 1;
				/*even though max three numbers, since what denotes if it will be
				an octal is the '\n' number n; n itself is part of the number, unlike
				with hex where the first char == 'x' and is therefore not part of the 
				number.*/
				esc->repeat_timer = 2;
				break;
			case BAD:
				error(linenum, "Not a valid escape char", currline);
				break;
		}
		esc->check_escape = 0;
	}
	else if (info.curr_char == '\\')
		esc->check_escape = 1;
}


void set_multline_chars(multline *character, uint8_t currline[], uint64_t linenum, int8_t modifier)
{
	int active_error = 0;
	char message_error[53] = "Missing opening bracket/brace/paren\tOr extra closing";

	character->track += modifier;
	if (character->track < 0)
	{	
		if(strlen((char *)character->start_line))
			error(linenum, message_error, character->start_line);
		else
			error(linenum, message_error, currline);
		character->start_linenum = 0;
		character->end_linenum = 0;
		character->track = 0;
		active_error = 1;
	}
	else if (character->track == 1)
	{	//want to avoid setting this more than once
		character->start_linenum = linenum; //do sizeof for clarity: sizeof(uint8_t) == 1 byte
		memcpy(character->start_line, currline, sizeof(uint8_t)*(SIZE+1));
	}

	if (character->track == 0)
	{
		//done with the character pair, have opening and closing char
		character->start_linenum = 0;
		character->end_linenum = 0;
	}
	else if (!active_error && modifier == -1)
	{
		character->end_linenum = linenum; 
		if (character->start_linenum < character->end_linenum)
			memcpy(character->end_line, currline, sizeof(uint8_t)*(SIZE+1));
	}
}


int check_octal(char escape_char)
	{return isdigit(escape_char) && escape_char >= '0' && escape_char < '8';}


void error(uint64_t linenum, char *message, uint8_t currline[]) 
	{printf("Line %lu: %s error!\n\t%s\n", linenum, message, currline);}
