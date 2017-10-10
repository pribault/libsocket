/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 11:20:04 by pribault          #+#    #+#             */
/*   Updated: 2017/10/10 19:15:12 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

static int	client_init(t_client *new)
{
	ft_bzero(new, sizeof(t_client));
	new->sockfd = -1;
	new->running = 0;
	new->timeout = 10;
	new->refresh = 1000;
	if (pthread_mutex_init(&new->receiver_mutex, NULL) ||
	pthread_mutex_init(&new->autocleaner_mutex, NULL) ||
	!(new->waiting = ft_vector_new(sizeof(t_pack), 0)))
		return (0);
	return (1);
}

static int	tcp_connect(t_client *new)
{
	(void)new;
	return (0);
}

static int	udp_connect(t_client *new)
{
	if ((new->sockfd = socket(new->addr->ai_family, new->addr->ai_socktype,
	new->addr->ai_protocol)) != -1)
	{
		time(&new->last);
		return (1);
	}
	return (0);
}

static void	*free_and_return(t_client *client)
{
	if (client)
	{
		if (client->waiting)
			ft_vector_del(&client->waiting);
		pthread_mutex_destroy(&client->receiver_mutex);
		pthread_mutex_destroy(&client->autocleaner_mutex);
		free(client);
	}
	return (NULL);
}

t_client	*new_client(char *ip, char *port, int prot)
{
	t_addrinfo	hints;
	t_client	*new;

	if (!(new = (t_client*)malloc(sizeof(t_client))) || !client_init(new) ||
	!(new->protocol = prot))
		return (free_and_return(new));
	ft_bzero(&hints, sizeof(t_addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = prot;
	if ((getaddrinfo(ip, port, &hints, &new->addresses)))
		return (free_and_return(new));
	new->addr = new->addresses;
	while (new->addr)
	{
		// if (prot == TCP && tcp_connect(new))
		// 	return (new);
		// else if (prot == UDP && udp_connect(new))
		// 	return (new);
		ft_memdump((void*)new->addr->ai_addr + 4, new->addr->ai_addrlen);
		new->addr = new->addr->ai_next;
	}
	return (free_and_return(new));
}
