/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzaboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 04:41:39 by mzaboub           #+#    #+#             */
/*   Updated: 2019/12/12 07:50:31 by mzaboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
void	printbits(void *p, int bytes)
{
	char	bb;
	int		j;

	j = bytes;
	while (j-- > 1)
		p++;
	while (bytes-- > 0)
	{
		j = 7;
		bb = *(char *)p;
		while (j >= 0)
		{
			printf("%u", ((bb >> j) & 1));
			j--;
		}
		p--;
		printf(" ");
	}
	printf("\n");
}
*/
int			power(int n, int i)
{
	int j;
	int res;

	j = 0;
	res = 1;
	while (j < i)
	{
		res *= n;
		j++;
	}
	printf("%d^%d == %d;\n", n, i, res);
	return (res);
}


/*
** ****************************************************************************
*/

t_uint32	is_special_case(t_bigint_compound *compound, t_buffer *node)
{
	if (compound->bigbit == -1337 && compound->v_num.length == 0)
	{
		if (compound->sign & 1)
			ft_strcpy(node->buff, "-inf");
		else
			ft_strcpy(node->buff, "inf");
		return (TRUE);
	}
	else if (compound->bigbit == -1337 && compound->v_num.length != 0)
	{
		ft_strcpy(node->buff, "nan");
		return (TRUE);
	}
	return (FALSE);
}

/*
** *************************
*/

void		ft_special_case(t_buffer *node)
{
	SET_FLAG_ON(node->flags, STRING);
	SET_FLAG_OFF(node->flags, XFLOAT);
	SET_FLAG_OFF(node->flags, ZERO);
	node->buff = \
		build_result(node->flags, node->buff, node->precision, node->width);
}

/*
** ***************************************************************************
*/

t_uint32	ft_add_sign(t_bigint_compound *compound, t_buffer node)
{
	if (compound->sign & 1)
	{
		node.buff[0] = '-';
		return (1);
	}
	else if (IS_ON(node.flags, PLUS))
	{
		node.buff[0] = '+';
		return (1);
	}
	else if (IS_ON(node.flags, SPACE))
	{
		node.buff[0] = ' ';
		return (1);
	}
	else
		return (0);
}
s