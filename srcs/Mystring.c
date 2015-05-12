/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 04:07:02 by achazal           #+#    #+#             */
/*   Updated: 2015/05/03 04:07:04 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Mystring.h>

t_string			newString(char *str)
{
	t_string		string;

	string.safe = 0;
	if (!(string.str = strdup(str)))
		string.len = 0;
	else
		string.len = strlen(str);
	return (string);
}

t_string			initString(char c, ssize_t len)
{
	t_string		string;

	string.safe = 0;
	if (!(string.str = (char *)malloc(sizeof(char) * len + 1)))
		string.len = 0;
	else
	{
		memset(string.str, c, len);
		string.str[len] = '\0';
		string.len = len;
	}
	return (string);
}

void				destroyString(t_string *string)
{
	free(string->str);
}

t_string			dupString(t_string string)
{
	t_string		newstring;

	newstring.len = lenString(string);
	if (newstring.len == -1)
	{
		if (string.safe >= 2)
		{
			write (2, "String error : Can't dup, unclosed string\n", 42);
			exit (0);
		}
		newstring.len = string.len;
	}
	newstring.str = strndup(string.str, newstring.len);
	return (newstring);
}

ssize_t				lenString(t_string string)
{
	ssize_t			len;

	if (!string.safe)
		return (string.len);
	len = 0;
	while (string.str[len] && len < string.len)
		len++;
	if (len == string.len && string.str[len])
		return (-1);
	return (len);
}

ssize_t				getlenString(t_string string)
{
	return (string.len);
}

int					reduceString(t_string *string, ssize_t len)
{
	char			*newstr;
	ssize_t			stringlen;

	if (!string->safe)
	{
		newstr = strndup(string->str, len);
		destroyString(string);
		string->str = newstr;
		string->len = len;
		if (!newstr)
			return (-1);
		return (1);
	}
	if ((stringlen = lenString(*string) == -1))
	{
		if (string->safe == 2)
		{
			destroyString(string);
			*string = initString('\0', len);
		}
		else if (string->safe == 3)
		{
			write (2, "String error : Can't reduce string, unclosed string\n", 45);
			exit (0);
		}
	}
	if (len >= stringlen)
		return (0);
	if (!(newstr = strndup(string->str, len)))
		return (-1);
	destroyString(string);
	string->str = newstr;
	string->len = len;
	return (1);
}

int					increaseString(t_string *string, ssize_t len)
{
	char			*newstr;
	ssize_t			stringlen;

	if (!string->safe)
	{
		newstr = strndup(string->str, len);
		destroyString(string);
		string->str = newstr;
		string->len = len;
		if (!newstr)
			return (-1);
		return (1);
	}
	if ((stringlen = lenString(*string) == -1))
	{
		if (string->safe == 2)
		{
			destroyString(string);
			*string = initString('\0', len);
		}
		else if (string->safe == 3)
		{
			write (2, "String error : Can't reduce string, unclosed string\n", 45);
			exit (0);
		}
	}
	if (len <= stringlen)
		return (0);
	if (!(newstr = strndup(string->str, len)))
		return (-1);
	destroyString(string);
	string->str = newstr;
	string->len = len;
	return (1);
}

int					newlenString(t_string *string, ssize_t len)
{
	char			*newstring;
	ssize_t			detected_len;
	int				ret;
	char			safety;	

	if (!string->safe)
	{
		newstring = strndup(string->str, len);
		destroyString(string);
		string->str = newstring;
		string->len = len;
	}
	detected_len = lenString(*string);
	if (string->safe >= 2 && len == -1)
	{
		write (2, "String error : Can't reset len, unclosed string\n", 45);
		exit (0);
	}
	safety = string->safe;
	string->safe = 0;
	if (detected_len >= len)
		ret = reduceString(string, len);
	else
		ret = increaseString(string, len);
	string->safe = safety;
	return (1);
}

int					modifyString(t_string *string, ssize_t pos, char c)
{
	ssize_t			len;

	if (!string->safe)
	{
		string->str[pos] = c;
		return (1);
	}
	len = lenString(*string);
	if (string->safe >= 2 && len == -1)
	{
		write (2, "String error : Can't modify, unclosed string\n", 45);
		exit (0);
	}
	if (len >= pos)
		return (0);
	string->str[pos] = c;
	return (1);
}

int					replaceString(t_string *string, char *str)
{
	if (!string->safe)
	{
		destroyString(string);
		if (!(string->str = strdup(str)))
			return (0);
		return (1);
	}
	destroyString(string);
	if (string->safe == 3 && !str)
	{
		write (2, "String error : Can't replace, replacing by NULL\n", 48);
		exit (0);
	}
	if (str)
	{
		if (!(string->str = strdup(str)))
			return (0);
		return (1);
	}
	string->str = NULL;
	return (0);
}

int					putString(t_string string)
{
	ssize_t			len;

	if (string.safe == 0)
		return (write(1, string.str, string.len));
	if ((len = lenString(string)) == -1)
	{
		if (string.safe == 2)
			write(2, "String warning : Can't put, unclosed string\n", 44);
		if (string.safe == 3)
		{
			write (2, "String error : Can't put, unclosed string\n", 42);
			exit (0);
		}
		return (-1);
	}
	return (write (1, string.str, len));
}

int					superdebugString(t_string *string)
{
	if (string->safe == 3)
		return (0);
	string->safe = 3;
	return (1);
}

int					debugString(t_string *string)
{
	if (string->safe == 2)
		return (0);
	string->safe = 2;
	return (1);
}

int					safeString(t_string *string)
{
	if (string->safe == 1)
		return (0);
	string->safe = 1;
	return (1);
}

int					unsafeString(t_string *string)
{
	if (string->safe == 0)
		return (0);
	string->safe = 0;
	return (1);
}
// t_string			catString(t_string *dst, t_string src)
// {
// 	t_string		string;

// 	if (!string->safe)
// 	{
// 		strcat(dst->string, src);
// 		return (*dst);
// 	}
	
// }

// t_string			joinString(t_string s1, t_string s2);
