/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 04:07:02 by achazal           #+#    #+#             */
/*   Updated: 2015/05/03 04:07:04 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSTRING
# define MYSTRING
# include <sys/types.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# include <stdio.h>

typedef struct		s_string
{
	char			*str;
	ssize_t			len;
	char			safe;
}					t_string;


t_string			newString(char *str);
t_string			initString(char c, ssize_t len);
void				destroyString(t_string *string);
int					putString(t_string string);
t_string			dupString(t_string string);
ssize_t				lenString(t_string string);
ssize_t				getlenString(t_string string);
int					reduceString(t_string *string, ssize_t len);
int					increaseString(t_string *string, ssize_t len);
int					newlenString(t_string *string, ssize_t len);
int					modifyString(t_string *string, ssize_t pos, char c);
int					replaceString(t_string *string, char *str);
int					superdebugString(t_string *string);
int					debugString(t_string *string);
int					safeString(t_string *string);
int					unsafeString(t_string *string);

#endif
