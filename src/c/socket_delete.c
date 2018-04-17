/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 14:09:39 by pribault          #+#    #+#             */
/*   Updated: 2018/04/16 14:10:53 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

void	socket_delete(t_socket **socket)
{
	ft_vector_del(&(*socket)->clients);
	ft_circ_buffer_del(&(*socket)->write_queue);
	free(*socket);
}
