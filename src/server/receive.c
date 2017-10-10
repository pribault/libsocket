/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 13:59:45 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 14:17:27 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

t_pack		*receive_server(t_server *server)
{
	t_pack	*ret;
	size_t	size;

	ret = NULL;
	if (server && (size = server->waiting->n))
	{
		pthread_mutex_lock(&server->receiver_mutex);
		ret = ft_vector_get(server->waiting, 0);
		ft_vector_del_one(server->waiting, 0);
		pthread_mutex_unlock(&server->receiver_mutex);
	}
	return (ret);
}
