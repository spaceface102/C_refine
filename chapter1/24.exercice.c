#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

#define SIZE 1000
#define ALLGOOD 1
#define HEX	   -1
#define OCTAL  -2
#define BAD    -3

typedef struct multi_line{
	/*need signed bit since for track since closing 
	char subtract: if too many closing 'track' should be negative */
	int64_t track;
	uint64_t start_linenum;
	uint64_t end_linenum;
	uint8_t start_line[SIZE+1];
	uint8_t end_line[SIZE+1];
} multline;

//Func Declerations
char *getline(uint8_t currline[]);
int check_octal(char escape_char);
char escape_sequence_check(char escape_char);
int binsearch(const char array[], int find, int n);
void error(uint64_t linenum, char *message, uint8_t currline[]);
//SINGLE FUNC
void init_escape(uint8_t curr_char, uint8_t currline[], uint64_t linenum, 
uint8_t *repeat_timer, uint8_t *check_escape, uint8_t *hex_check, uint8_t *octal_check);
//EOF SINGLE FUNC DECLERATION
void set_multline_chars(multline *character, uint8_t currline[], uint64_t linenum, int8_t modifier);


int main(int argc, char *argv[])
{	//SIZE+1 to make sure that '\0' fits
	uint8_t squote, len_squote, dquote, comment, check_escape,
	repeat_timer, octal_check, hex_check,
	currline[SIZE+1]; 

	uint64_t linenum = 1, i, check_comment[2] = {0, 0};
	/*check_comment[0] == activate check for '/', check_comment[1] == 
	char_num (need to make sure * is right after /) */
	
	multline brack, braces, paren;
	brack.track = 0; brack.start_linenum = 0, brack.end_linenum = 0;
	braces.track = 0; braces.start_linenum = 0, braces.end_linenum = 0;
	paren.track = 0; paren.start_linenum = 0, paren.end_linenum = 0;

	squote =
	len_squote = dquote = comment = 
	check_escape = repeat_timer = 
	octal_check = hex_check = 0x0;
	
	FILE *fh;
	char *(*choose_func)() = (argc >= 2) ? fgets : getline;

	if (argc >= 2)
		if ((fh = fopen(argv[1], "r")) == NULL)
		{
			printf("\"%s\" does not exist!\nBye!\n", argv[1]);
			exit(42); //error, can't read file
		}

	do{
		if(choose_func(currline, SIZE+1, fh) == NULL)
			break;

		for(i = 0; currline[i] != '\0'; i++) //i == current char num 
		{
			if(comment)
			{
				if(currline[i] == '*')
				{
					check_comment[0] = 1;
					check_comment[1] = i;
					continue;
				}
				if(check_comment[0])
				{
					if((check_comment[1] + 1 == i) && (currline[i] == '/'))
						comment = 0;
					else
						check_comment[0] = 0;
				}
				continue;
			}
			else if(check_comment[0])
			{
				if((check_comment[1] + 1 == i) && (currline[i] == '*'))
				{
					comment = 1;
					continue;
				}
				//C99 Comments
				else if((check_comment[1] + 1 == i) && (currline[i] == '/'))
				{
					check_comment[0] = 0;
					break; //don't need to set comment == 1, need to move to the next line
				}
				else
					check_comment[0] = 0;
			}

			if(!(dquote==1 || squote==1) && currline[i] != '\'' && currline[i] != '\"') //have started quote
			{
				switch(currline[i])
				{
					case '[':
						set_multline_chars(&brack, currline, linenum, 1);
						break;
					case ']':
						set_multline_chars(&brack, currline, linenum, -1);
						break;
					case '(':
						set_multline_chars(&paren, currline, linenum, 1);
						break;
					case ')':
						set_multline_chars(&paren, currline, linenum, -1);
						break;
					case '{':
						set_multline_chars(&braces, currline, linenum, 1);
						break;
					case '}':
						set_multline_chars(&braces, currline, linenum, -1);
						break;
					case '/':
						check_comment[0] = 1; //indicate to check for comment
						check_comment[1] = i; //char num of '/', looking for next char '*'
						break;
				}
			}
			else if(currline[i] == '\"' || dquote == 1)
			{
				if (currline[i] == '\"' && i > 0 && currline[i-1] != '\\')
					dquote += 1;
				else if (currline[i] == '\"' && i == 0)
					dquote += 1;
				else if (currline[i] == '\"' && i >= 2 && currline[i-1] == '\\' && currline[i-2] == '\\')
					dquote += 1;

				//does the handeling of escape sequence checking	
				init_escape(currline[i], currline, linenum, 
				&repeat_timer, &check_escape, &hex_check, &octal_check);
			}
			else if(currline[i] == '\'' || squote == 1)
			{
				if(currline[i] != '\'' && !repeat_timer && !check_escape)
					//still not done with '' need to make sure only one char
					len_squote += 1;

				if (currline[i] == '\'' && i > 0 && currline[i-1] != '\\')
					squote += 1;
				else if (currline[i] == '\'' && i == 0)
					squote += 1;
				else if (currline[i] == '\'' && i >= 2 && currline[i-1] == '\\' && currline[i-2] == '\\')
					squote += 1;

				//does the handeling of escape sequence checking	
				init_escape(currline[i], currline, linenum, 
				&repeat_timer, &check_escape, &hex_check, &octal_check);
			}

			if(squote == 2)
			{
				if (len_squote > 1)
					error(linenum, "Too many chars in \' \'", currline);
				else if(len_squote == 0)
					error(linenum, "NO char between \' \'", currline);
				len_squote = 0;
				squote = 0;
			}
			if(dquote == 2)
				dquote = 0;
		}

		if (dquote == 1)
			error(linenum, "Missing \"", currline);

		if (squote == 1)
			error(linenum, "Missing \'", currline);

		linenum++;
		dquote = squote = len_squote = 0;
	} while(i > 0);

	if (brack.track)
	{
		error(brack.start_linenum, "Missing ]", brack.start_line);
		if(strlen((char *)brack.end_line) && !(isspace(brack.end_line[0]))) 
			error(brack.end_linenum, "Last ]", brack.end_line);
	}

	if (braces.track)
	{
		error(braces.start_linenum, "Missing }", braces.start_line);
		if(strlen((char *)braces.end_line) && !(isspace(braces.end_line[0]))) 
			error(braces.end_linenum, "Last }", braces.end_line);
	}

	if (paren.track)
	{
		error(paren.start_linenum, "Missing )", paren.start_line);
		if(strlen((char *)paren.end_line) && !(isspace(paren.end_line[0])))
			error(paren.end_linenum, "Last )", paren.end_line);
	}
	return 0;
}


char *getline(uint8_t currline[])
{
	/*In reality you should doing file IO here, but this is what I think KR
	expect out of you prev. to getting to file IO chapeter*/
	int i; uint8_t c;
	for(i = 0; i < SIZE && (c = getchar()) != '\n';i++)
		currline[i] = c;
	currline[i] = '\0'; //currline is SIZE+1: look at main()
	return "done";
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


void init_escape(uint8_t curr_char, uint8_t currline[], uint64_t linenum,
uint8_t *repeat_timer, uint8_t *check_escape, uint8_t *hex_check,
uint8_t *octal_check)
{
	if (*repeat_timer)
	{
		*repeat_timer -= 1;
		if (curr_char == '\'' || curr_char == '\"')
		{
			if(*hex_check && *repeat_timer == 1) 
				/*==1 since og value ==2 and after -=1 == 1
				& if here curr_char == ' or " therefore then end*/
				error(linenum, "No hex number present!", currline);
			*hex_check = *octal_check = *repeat_timer = 0;
		}
		if(*hex_check)
		{
			if(!isxdigit(curr_char))
			{
				error(linenum, "Hex Not a valid char number", currline);
				*repeat_timer = 0;
				*hex_check = 0;
			}
		}
		if(*octal_check)
		{
			if(!check_octal(curr_char))
			{
				error(linenum, "Octal Not a valid char number", currline);
				*repeat_timer = 0;
				*octal_check = 0;
			}
		}
	}

	//allow '\\' for cases like '\n'
	if(*check_escape)
	{
		switch (escape_sequence_check(curr_char))
		{	
			case ALLGOOD:
				break;
			case HEX: 
				*hex_check = 1;
				*repeat_timer = 2;
				break;
			case OCTAL:
				*octal_check = 1;
				/*even though max three numbers, since what denotes if it will be
				an octal is the '\n' number n; n itself is part of the number, unlike
				with hex where the first char == 'x' and is therefore not part of the 
				number.*/
				*repeat_timer = 2;
				break;
			case BAD:
				error(linenum, "Not a valid escape char", currline);
				break;
		}
		*check_escape = 0;
	}
	else if (curr_char == '\\')
		*check_escape = 1;
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
