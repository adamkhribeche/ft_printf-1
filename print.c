/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhribec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 14:47:25 by nkhribec          #+#    #+#             */
/*   Updated: 2019/10/06 21:58:38 by nkhribec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		get_prefix_len(int flag, char *s)
{
	return (is_on(flag, PLUS) && (is_on(flag, d) || is_on(flag, i))) +\
	(is_on(flag, HASH) && is_on(flag, OCTAL)) +\
	((is_on(flag, HASH) && (is_on(flag, X) || is_on(flag, x))) * 2) +\
	((s[0] == '-' || s[0] == '^') && !(is_on(flag, PLUS)));
}

char	*ft_realloc(char **s, size_t size)
{
	char	*tmp;

	tmp = *s;
	*s = ft_memalloc(sizeof(char) * size);
	ft_strcpy(*s, tmp);
	ft_strdel(&tmp);
	return (*s);
}

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
	while (--i >= 0)
		s[i + shift_value] = s[i];
	while (--shift_value >= 0)
		s[shift_value] = '^';
}

void	fprecision(char **s, int flag, int precision, int shift_value)
{
	int		p_len;// 0x 0X 0
	
	p_len = get_prefix_len(flag, *s);
	*s = ft_realloc(s, precision + p_len + 1);
	*s += p_len;
	shift(*s, shift_value);
	blacktozero(*s, shift_value);
	*s -= p_len;
}

void	ft_get_precision(char **s, int precision, int p_len, int len)
{
	int	shift_value;
	
	shift_value = precision - len;
	*s += p_len;
	shift(*s, shift_value);
	blacktozero(*s, shift_value);
	*s -= p_len;
}

void	fwidth(char **s, int flag, int precision, int width)
{
	int		len;
	int		shift_value;
	int		p_len;// +0x +0X +0
	int		take_space;
	
	*s = ft_realloc(s, width + 1);
	p_len = get_prefix_len(flag, *s);
	take_space = !(is_on(flag, PLUS)) && (is_on(flag, SPACE)) && *s[0] == '^';
	len = (int)ft_strlen(*s) - p_len;
	if (precision > len)
		ft_get_precision(s, precision, p_len, len);//complete with 0000 after prefix
	len = (int)ft_strlen(*s);
	*s = *s + take_space;
	if (!(is_on(flag, MINUS)))
	{
		shift(*s, width - len);
		if (is_on(flag, ZERO) && !(is_on(flag, PRECISION)))
			blacktozero(*s, width - len);
	}
	else
		nulltoblack(*s, width);
	*s = *s - take_space;
}

int		ft_print(char **s, int flag, int precision, int width)
{
	int		len;
	int		p_len;

	p_len = get_prefix_len(flag, *s);
	len = (int)ft_strlen(*s);
	if (precision >= (len - p_len) && precision >= width)
		fprecision(s, flag, precision, precision - (len - p_len));
	else if (width >= len && width >= precision)
		fwidth(s, flag, precision, width);
	ft_putstr(*s);
	len = ft_strlen(*s);
	ft_strdel(s);
	return (len);
}
