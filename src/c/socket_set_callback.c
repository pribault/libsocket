/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_set_callback.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:15:33 by pribault          #+#    #+#             */
/*   Updated: 2018/04/16 16:18:42 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

void	socket_set_callback(t_socket *socket, t_callback cb, void *ptr)
{
	if (cb >= SOCKET_CALLBACK_MAX)
		return ;
	((void**)&socket->client_add)[cb] = ptr;
}
