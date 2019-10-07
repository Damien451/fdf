/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:14:10 by rle-ru            #+#    #+#             */
/*   Updated: 2019/06/01 16:34:03 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *s)
{
	int i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
			|| s[i] == '\r' || s[i] == '\v' || s[i] == '\f')
		i++;
	if (s[i] == '-')
		sign = -sign;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && s[i] > 47 && s[i] < 58)
	{
		res *= 10;
		res += s[i] - 48;
		i++;
	}
	return (res * sign);
}
