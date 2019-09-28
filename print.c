/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhribec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 14:47:25 by nkhribec          #+#    #+#             */
/*   Updated: 2019/09/28 18:48:44 by nkhribec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	nulltoblack(char *s, int until)
{
	while (until)
	{
		if (!*s)
			*s = '^';
		s++;
		until--;
	}
}

void	blacktozero(char *s, int until)
{
	while (until)
	{
		if (*s == '^')
			*s = '0';
		s++;
		until--;
	}
}

void	shift(char *s, int shift_value)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	//printf("i = %d\n", i);
	while (--i >= 0)
		s[i + shift_value] = s[i];
	while (--shift_value >= 0)
		s[shift_value] = '^';
}

void	fprecision(char **s, int flag, int precision, int shift_value)
{
	char	*tmp;
	int		avoid_prefix;// 0x 0X 0
	
	//avoid_prefix =  is_on(flag, PLUS) + (is_on(flag, HASH) && is_on(flag, OCTAL)) +\
					(is_on(flag, HASH) && (is_on(flag, X) || is_on(flag, x)) * 2) + (*s[0] == '-')\
					+ ((is_on(flag, DEC1) || is_on(flag, DEC2)) && (*s[0] != '-'));
	avoid_prefix =  (is_on(flag, PLUS)) + ((is_on(flag, HASH)) && (is_on(flag, OCTAL))) +\
					((is_on(flag, HASH) && ((is_on(flag, X)) || (is_on(flag, x)))) * 2) +\
					(*s[0] == '-' && !(is_on(flag, PLUS)));
	//printf("5$$$$$$$$%d\n", avoid_prefix);
	tmp = *s;
	*s = ft_memalloc(sizeof(char) * (precision + avoid_prefix + 1));
	ft_strcpy(*s, tmp);
	ft_strdel(&tmp);
	*s += avoid_prefix;
	shift(*s, shift_value);
	blacktozero(*s, shift_value);
	*s -= avoid_prefix;
}

void	fwidth(char **s, int flag, int precision, int width)
{
	char	*tmp;
	int		len;
	int		shift_value;
	int		avoid_prefix;// +0x +0X +0
	
	avoid_prefix =  (is_on(flag, PLUS)) + ((is_on(flag, HASH)) && (is_on(flag, OCTAL))) +\
					((is_on(flag, HASH) && ((is_on(flag, X)) || (is_on(flag, x)))) * 2) +\
					((*s[0] == '-') && !(is_on(flag, PLUS)));
	printf("5$$$$$$$$%d\n", avoid_prefix);
	len = (int)ft_strlen(*s) - avoid_prefix;
	tmp = *s;
	*s = ft_memalloc(sizeof(char) * (width + 1));
	ft_strcpy(*s, tmp);
	ft_strdel(&tmp);
	shift_value = len > precision ? 0 : precision - len;
	*s += avoid_prefix;
	shift(*s, shift_value);
	blacktozero(*s, shift_value);
	*s -= avoid_prefix;
	//printf("s = %s\n", *s);
	//printf("shift value = %d\n", shift_value);
	len = (int)ft_strlen(*s);
	if (!(is_on(flag, MINUS)))
	{
		shift(*s, width - len);
		if (is_on(flag, ZERO))
			blacktozero(*s, width - len);
	}
	else
		nulltoblack(*s, width);
}

int		ft_print(char **s, int flag, int precision, int width)
{
	int		len;
	int		prefix_len;
	int		space;

	//prefix_len =  is_on(flag, PLUS) + (is_on(flag, HASH) && is_on(flag, OCTAL)) +\
					(is_on(flag, HASH) && (is_on(flag, X) || is_on(flag, x)) * 2) + (*s[0] == '-')\
					+ ((is_on(flag, DEC1) || is_on(flag, DEC2)) && (*s[0] != '-'));
	prefix_len =  (is_on(flag, PLUS)) + ((is_on(flag, HASH)) && (is_on(flag, OCTAL))) +\
				  ((is_on(flag, HASH) && ((is_on(flag, X)) || (is_on(flag, x)))) * 2) +\
				  (*s[0] == '-' && !(is_on(flag, PLUS)));
	//printf("----------///%s\n", *s);
	printf("5$$$$$$$$%d\n", prefix_len);
	len = (int)ft_strlen(*s);
	if (precision >= (len - prefix_len) && precision >= width)
	{
		printf("-----pppp----    %s------\n", *s);
		fprecision(s, flag, precision, precision - (len - prefix_len));
		ft_putendl(*s);
		return (precision);
	}
	if (width >= len && width >= precision)
	{
		printf("------www--     %s--------\n", *s);
		fwidth(s, flag, precision, width);
		ft_putendl(*s);
		return (width);
	}
	ft_putendl(*s);
	return (len);
}

