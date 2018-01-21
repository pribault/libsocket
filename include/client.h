/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:51:55 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 12:31:03 by pribault         ###   ########.fr       */
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
# include <netdb.h>
# include "libft.h"

/*
***************
**	defines  **
***************
*/

# define READ_BUFFER_SIZE		65536

/*
**	default client values
*/

# define CLIENT_DEFAULT_QUEUE_MAX	10
# define CLIENT_DEFAULT_TIMEOUT_S	1
# define CLIENT_DEFAULT_TIMEOUT_US	0

/*
**	client opt's masks
*/

# define CLIENT_RUNNING		0x1

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

typedef struct		s_msg
{
	void			*ptr;
	size_t			size;
}					t_msg;

typedef struct		s_towrite
{
	int				fd;
	t_msg			data;
}					t_towrite;

typedef struct		s_client
{
	t_protocol		protocol;
	int				sockfd;
	struct sockaddr	addr;
	socklen_t		addr_len;
	struct timeval	timeout;
	t_vector		*write_queue;
	uint8_t			opt;
}					t_client;

/*
*****************
**	functions  **
*****************
*/

t_client			*client_new(void);

#endif
