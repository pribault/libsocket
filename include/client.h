/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:51:55 by pribault          #+#    #+#             */
/*   Updated: 2018/01/18 23:46:23 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

/*
****************
**	includes  **
****************
*/

# include <sys/socket.h>
# include "libft.h"

/*
*************
**	enums  **
*************
*/

typedef enum		e_protocol
{
	TCP = SOCK_STREAM,
	UDP = SOCK_DGRAM
}					t_protocol;

/*
******************
**	structures  **
******************
*/

typedef struct		s_client
{
	t_protocol		protocol;
	int				sockfd;
	struct timeval	timeout;
	t_vector		*write_queue;
	uint8_t			opt;
}					t_client;

/*
*****************
**	functions  **
*****************
*/

t_client			*client_new(t_protocol protocol, char *address,
					char *port);

#endif
