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

#ifndef MYFLOATS
# define MYFLOATS
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# include <stdio.h>

typedef struct		s_floats
{
	float			*values;
	ssize_t			len;
}					t_floats;

t_floats	newFloats(int n, ...);
void		putFloats(t_floats floats);
void		destroyFloats(t_floats *floats);

#endif
