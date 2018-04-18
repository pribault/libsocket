/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_find_client_by_address.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 11:17:20 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 15:00:52 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

t_client	*socket_find_client_by_address(t_socket *socket,
			struct sockaddr_storage *addr)
{
	t_client	*client;
	t_vector	*vector;
	size_t		i;

	i = (size_t)-1;
	vector = &socket->clients;
	while (++i < vector->n)
		if (!(client = ft_vector_get(vector, i)))
			return (NULL);
		else if (!memcmp(&client->addr, addr, sizeof(struct sockaddr)))
			return (client);
	return (NULL);
}
