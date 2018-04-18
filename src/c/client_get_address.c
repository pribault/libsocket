/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_get_address.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:18:06 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 15:18:59 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

t_addr	*client_get_address(t_client *client)
{
	return (&client->addr);
}
