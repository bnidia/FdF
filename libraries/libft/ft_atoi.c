/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnidia <bnidia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 02:51:47 by bnidia            #+#    #+#             */
/*   Updated: 2021/11/03 10:17:11 by bnidia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_atoi
** Convert a string to a integer
** Return Value
** The converted value. Pointer *nptr not moved and not corrupted
*/

int	ft_atoi(const char *nptr)
{
	int		num;
	int		sign;
	char	*num_ptr;

	num = 0;
	sign = 1;
	num_ptr = (char *)nptr;
	while (*num_ptr == '\t' || *num_ptr == '\n' || *num_ptr == '\v' \
		|| *num_ptr == '\f' || *num_ptr == '\r' || *num_ptr == ' ')
		num_ptr++;
	if (*num_ptr == '-')
		sign = -1;
	if (*num_ptr == '-' || *num_ptr == '+')
		num_ptr++;
	while (*num_ptr >= '0' && *num_ptr <= '9')
		num = num * 10 + *num_ptr++ - '0';
	return (num * sign);
}
