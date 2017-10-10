/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 12:12:42 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 17:27:23 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

int		destroy_server(t_server *server)
{
	if (!server || close(server->sockfd) == -1)
		return (0);
	stop_server_autocleaner(server);
	stop_server(server);
	ft_vector_del(&server->waiting);
	ft_vector_del(&server->clients);
	pthread_mutex_destroy(&server->receiver_mutex);
	pthread_mutex_destroy(&server->autocleaner_mutex);
	free(server);
	return (1);
}
