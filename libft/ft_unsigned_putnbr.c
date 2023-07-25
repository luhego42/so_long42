/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_putnbr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:03:36 by luhego            #+#    #+#             */
/*   Updated: 2023/07/25 17:35:38 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_unsigned_putnbr(size_t nbr, char *base, int *count)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (nbr >= 0 && nbr < base_len)
		ft_putchar_count(base[nbr], count);
	else
	{
		ft_unsigned_putnbr(nbr / base_len, base, count);
		ft_unsigned_putnbr(nbr % base_len, base, count);
	}
}
