/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circ_buffer_get.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:36:53 by pribault          #+#    #+#             */
/*   Updated: 2018/03/27 14:38:59 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_circ_buffer_get(t_circ_buffer *buffer, uint32_t idx)
{
	if (buffer->write_idx != buffer->read_idx &&
	idx < (buffer->elems + buffer->write_idx - buffer->read_idx) %
	buffer->elems)
		return (buffer->ptr + ((buffer->read_idx + idx) % buffer->elems) *
		buffer->type);
	return (NULL);
}
