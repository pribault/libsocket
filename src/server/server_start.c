/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 21:06:13 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 11:01:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			server_start(t_server *server, t_protocol protocol)
{
	if (!server || (server->opt & SERVER_RUNNING))
		return (0);
	server->opt |= SERVER_RUNNING;
	server->protocol = protocol;
	return (1);
}
