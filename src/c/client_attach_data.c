/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_attach_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:14:58 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 15:15:54 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

void	client_attach_data(t_client *client, void *data)
{
	client->data = data;
}
