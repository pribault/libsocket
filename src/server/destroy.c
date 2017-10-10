/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 12:12:42 by pribault          #+#    #+#             */
/*   Updated: 2017/10/10 21:39:22 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

int		destroy_server(t_server *server)
{
	if (!server || close(server->sockfd) == -1)
		return (0);
	stop_server(server);
	ft_vector_del(&server->waiting);
	ft_vector_del(&server->clients);
	pthread_mutex_destroy(&server->receiver_mutex);
	pthread_mutex_destroy(&server->autocleaner_mutex);
	free(server);
	return (1);
}
