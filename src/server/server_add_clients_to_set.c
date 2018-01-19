/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_add_clients_to_set.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 11:46:21 by pribault          #+#    #+#             */
/*   Updated: 2018/01/19 21:42:34 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_add_clients_to_set(fd_set *set, t_vector *clients,
		int *fd_max)
{
	t_client	*client;
	size_t		i;

	if (!set || !clients || !fd_max)
		return ;
	i = (size_t)clients->n;
	while (--i != (size_t)-1)
	{
		if ((client = ft_vector_get(clients, i)))
		{
			if (client->fd > *fd_max)
				*fd_max = client->fd;
			FD_SET(client->fd, set);
		}
	}
}
