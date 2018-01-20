/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_connect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 15:17:30 by pribault          #+#    #+#             */
/*   Updated: 2018/01/20 15:33:40 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		client_connect(t_client *client, t_protocol protocol,
		char *address, char *port)
{
	struct addrinfo	*result;
	struct addrinfo	*addr;
	struct addrinfo	hints;

	if (!client || !address || !port)
		return (0);
	ft_bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = protocol;
	if (getaddrinfo(address, port, &hints, &result) != 0 ||
		(client->sockfd = socket(AF_INET, protocol, 0)) < 0)
		return (0);
	addr = result;
	while (addr)
		if (connect(client->sockfd, addr->ai_addr, addr->ai_addrlen) >= 0)
		{
			freeaddrinfo(result);
			return (1);
		}
	freeaddrinfo(result);
	return (0);
}
