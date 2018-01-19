/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:51:48 by pribault          #+#    #+#             */
/*   Updated: 2018/01/19 09:00:20 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

/*
****************
**	includes  **
****************
*/

# include <sys/socket.h>
# include <arpa/inet.h>
# include "libft.h"

/*
***************
**	defines  **
***************
*/

/*
**	default server values
*/

# define SERVER_DEFAULT_QUEUE_MAX	10
# define SERVER_DEFAULT_TIMEOUT_S	1
# define SERVER_DEFAULT_TIMEOUT_US	0

/*
**	server opt's masks
*/

# define SERVER_RUNNING		0x1

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

typedef struct		s_towrite
{
	int				fd;
	void			*data;
	size_t			size;
}					t_towrite;

typedef struct		s_client
{
	int				fd;
	struct sockaddr	addr;
	socklen_t		addr_len;
	struct timeval	last;
}					t_client;

typedef struct		s_server
{
	t_protocol		protocol;
	int				sockfd;
	int				queue_max;
	struct timeval	timeout;
	t_vector		*clients;
	t_vector		*write_queue;
	uint16_t		port;
	uint8_t			opt;
}					t_server;

/*
*****************
**	functions  **
*****************
*/

t_server			*server_new(void);
void				server_delete(t_server **server);
int					server_start(t_server *server, t_protocol protocol,
					char *port);
void				server_stop(t_server *server);

#endif
