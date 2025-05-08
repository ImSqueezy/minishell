#include "../Includes/parsing.h"
#include "../Libraries/Libft/libft.h"

int	isred(char c)
{
	return (c == '>' || c == '<');
}

int	isop(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

// string additional length
//	> returns additional length of strings if a space will be added to it (might check quoting syntax errors here)
//	> example: "ls>a", if the string would be "ls > a" 2 chars will be added then
//    the additional length will return 6 as the new length of the string to be returned

size_t	straddlen(const char *p, size_t old_len);

char	*space_it(const char *p)
{
	size_t	i;
	char	quote;
	char	*res;
	char	prev;

	res = malloc(straddlen(p, ft_strlen(p)) * sizeof(char) + 1);
	if (!res)
		return (NULL);
	(1) && (i = 0, quote = 0, prev = 0);
	while (*p)
	{
		// quoting_traffic();
		if (!quote && (*p == '\'' || *p == '"'))
			quote = *p;
		else if (quote && *p == quote)
			quote = 0;
		if (isop(*p) && !quote)
		{
			if (prev && prev != ' ' && !isop(prev))
				res[i++] = ' ';
			res[i++] = *p; // fill current
			prev = *p++; // sat what ever operator
			if (!*p)
				break ;
			if (isop(*p) && prev == *p && *p != '|') // setting it to red if it's red, and also set his next to space if it's not
			{
				res[i++] = *p;
				if (*(p + 1) && *(p + 1) != 32)
					res[i++] = ' ';
			}
			else if (isop(*p) && *p == '|') // setting curr to pipe 
			{
				res[i++] = ' ';
				res[i++] = *p;
				if (*(p + 1) && *(p + 1) != 32)
					res[i++] = ' ';
			}
			else if (!isop(*p) && *p != ' ') // setting the next to space if it's not space
			{
				res[i++] = ' ';
				res[i++] = *p;	
			}
			if (*p == ' ')
				res[i++] = *p;
		}
		else
			res[i++] = *p;
		(1) && (prev = *p, p++);
	}
	res[i] = '\0';
	return (res);
}


size_t	straddlen(const char *p, size_t old_len)
{
	size_t	new_len;
	size_t	i;
	char	quote;
	char	prev;

	quote = 0;
	new_len = 0;
	prev = 0;
	while (*p)
	{
		if (!quote && (*p == '\'' || *p == '"'))
			quote = *p;
		else if (quote && *p == quote)
			quote = 0;
		if (isop(*p) && !quote)
		{
			if (prev && prev != ' ' && !isop(prev)) // if previous char is not OPERATOR and it is not SPACE increment and move to next char
				new_len++;
			prev = *p++; // in all cases prev is derefrenced since we need to check coming character
			if (!*p)
				break ;
			if (!isop(*p) && *p && *p != ' ') // if then the next char is not OPERATOR, neither a '\0' or SPACE > increment
				new_len++;
			else if (prev == *p && isop(*p) && *p == '|') // else it's going to an OPERATOR, a PIPE has the advantage over redirections, the length and the address is incremented
														// and the next is checked if it's not a space, if so increment
			{
				(1) && (new_len++, p++);
				if (*p && *p != 32)
					new_len++;
			}
			else if (prev == *p && isop(*p) && *(p + 1) != ' ') // else it's going to be at the same type and next is not SPACE (ignore if not at the same type) 
				new_len++;
		}
		(1) && (prev = *p, p++);
	}
	return (old_len + new_len);
}

int main(int ac, char **av)
{
	// char *p = "ls| cat<< e|cat>file1| cat file1";
	// char *p = "\'ls>>a\' || > | && &&cat>>a || \"cat>a\"";
	// char *p = "ls>ls>"; //><<>>|||";
	// char *p = ">><<>>|||";
	char *p = " ls| cat<< e";

	printf("%zu becomes %zu\n", ft_strlen(p), straddlen(p, ft_strlen(p)));
	char *new = space_it(p);
	printf("%s.\n- len = %zu", new, ft_strlen(new));
	free(new);
	return (0);
}