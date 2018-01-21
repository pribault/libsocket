/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_disconnect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 15:17:37 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 12:29:27 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	client_disconnect(t_client *client)
{
	if (!client || !(client->opt & CLIENT_RUNNING))
		return ;
	close(client->sockfd);
}
