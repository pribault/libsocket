/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circ_buffer_get_size.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 15:53:46 by pribault          #+#    #+#             */
/*   Updated: 2018/03/27 15:54:42 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint64_t	ft_circ_buffer_get_size(t_circ_buffer *buffer)
{
	return ((buffer->write_idx < buffer->read_idx) ?
		buffer->elems + buffer->write_idx - buffer->read_idx :
		buffer->write_idx - buffer->read_idx);
}
