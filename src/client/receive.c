/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 13:59:40 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 17:22:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

t_pack	*receive_client(t_client *client)
{
	t_pack	*ret;
	size_t	size;

	ret = NULL;
	if (client && (size = client->waiting->n))
	{
		pthread_mutex_lock(&client->receiver_mutex);
		ret = ft_vector_get(client->waiting, size - 1);
		ft_vector_resize(client->waiting, size - 1);
		pthread_mutex_unlock(&client->receiver_mutex);
	}
	return (ret);
}
