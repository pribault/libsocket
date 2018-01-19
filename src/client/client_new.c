/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 19:39:06 by pribault          #+#    #+#             */
/*   Updated: 2018/01/18 23:00:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_client	*client_new_tcp(t_client *client, char *address, char *port)
{
	(void)client;
	(void)address;
	(void)port;
	return (NULL);
}

t_client	*client_new_udp(t_client *client, char *address, char *port)
{
	(void)client;
	(void)address;
	(void)port;
	return (NULL);
}

t_client	*client_new(t_protocol protocol, char *address, char *port)
{
	t_client	*client;

	if (!(client = (t_client*)malloc(sizeof(t_client))))
		return (NULL);
	if (protocol == TCP)
		return (client_new_tcp(client, address, port));
	else if (protocol == UDP)
		return (client_new_udp(client, address, port));
	else
		free(client);
	return (NULL);
}
