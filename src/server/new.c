/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 11:20:11 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 17:23:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

static void	*free_and_return(t_server *server)
{
	if (server)
	{
		if (server->waiting)
			ft_vector_del(&server->waiting);
		if (server->clients)
			ft_vector_del(&server->clients);
		pthread_mutex_destroy(&server->receiver_mutex);
		pthread_mutex_destroy(&server->autocleaner_mutex);
		free(server);
	}
	return (NULL);
}

static int	server_init(t_server *new)
{
	ft_bzero(new, sizeof(t_server));
	new->sockfd = -1;
	new->running = 0;
	new->timeout = 10;
	new->refresh = 1000;
	if (pthread_mutex_init(&new->receiver_mutex, NULL) ||
	pthread_mutex_init(&new->autocleaner_mutex, NULL) ||
	!(new->waiting = ft_vector_new(sizeof(t_pack), 0)) ||
	!(new->clients = ft_vector_new(sizeof(t_id), 0)))
		return (0);
	return (1);
}

t_server	*new_server(char *port, int prot)
{
	struct sockaddr_in	addr;
	t_server			*new;

	if (!(new = (t_server*)malloc(sizeof(t_server))) || !server_init(new) ||
	!(new->protocol = prot))
		return (free_and_return(new));
	if ((new->sockfd = socket(AF_INET, prot, 0)) == -1)
		return (free_and_return(new));
	ft_bzero(&addr, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(ft_atoi(port));
	if (bind(new->sockfd, (struct sockaddr*)&addr,
	sizeof(struct sockaddr_in)))
		return (free_and_return(new));
	return (new);
}
