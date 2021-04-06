char *escape(char str[], char out[])
{
	//if you feed in a str, the output must be 
	//big enough to fit all the new shit
	int i, j;
	for(i = 0, j = 0; str[i] != '\0'; i++, j++)
	{
		switch(str[i])
		{	
		case '\n': 
			out[j++] = '\\'; out[j] = 'n';
			break;
		case '\t':
			out[j++] = '\\'; out[j] = 't';
			break;
		default:
			out[j] = str[i];
			break;
		}
	}
	out[j] = '\0';
	return out;
}
