/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_remove_client.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 19:22:39 by pribault          #+#    #+#             */
/*   Updated: 2018/01/19 21:49:11 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_remove_client(t_server *server, t_client *client)
{
	t_vector	*vector;

	if (!server || !(vector = server->clients) || !client)
		return ;
	if (server->client_del)
		server->client_del(server, client);
	if ((void*)client >= vector->ptr &&
		(void*)client < vector->ptr + vector->size)
		ft_vector_del_one(vector, ((void*)client - vector->ptr) /
		vector->type);
}
