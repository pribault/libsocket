/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_poll_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 10:31:22 by pribault          #+#    #+#             */
/*   Updated: 2018/01/19 13:10:52 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		server_poll_events(t_server *server)
{
	fd_set	input;
	fd_set	output;
	int		fd_max;
	int		ret;

	if (!server)
		return (0);
	FD_ZERO(&input);
	FD_ZERO(&output);
	fd_max = -1;
	server_add_clients_to_set(&input, server->clients, &fd_max);
	server_add_write_request_to_set(&output, server->write_queue, &fd_max);
	if ((ret = select(fd_max, &input, &output, NULL, &server->timeout)) < 0)
		return (0);
	if (!ret)
		return (1);
	return (1);
}
