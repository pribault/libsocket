/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_set_callback.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 10:22:09 by pribault          #+#    #+#             */
/*   Updated: 2018/03/28 11:57:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	server_set_callback(t_server *server, t_callback cb, void *ptr)
{
	if (cb >= CALLBACK_MAX)
		return ;
	((void**)&server->client_add)[cb] = ptr;
}
