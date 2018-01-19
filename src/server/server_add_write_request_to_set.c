/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_add_write_request_to_set.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 12:50:09 by pribault          #+#    #+#             */
/*   Updated: 2018/01/19 22:20:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_add_write_request_to_set(fd_set *set, t_vector *write_queue,
		int *fd_max)
{
	t_towrite	*towrite;
	size_t		i;

	i = write_queue->n;
	if (!set || !write_queue)
		return ;
	while (--i < (size_t)-1)
	{
		if ((towrite = ft_vector_get(write_queue, i)))
		{
			if (towrite->client.fd > *fd_max)
				*fd_max = towrite->client.fd;
			FD_SET(towrite->client.fd, set);
		}
	}
}
