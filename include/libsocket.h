/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 11:15:22 by pribault          #+#    #+#             */
/*   Updated: 2017/10/10 21:01:49 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_H
# define LIBSOCKET_H

/*
**	includes
**
**	waouh, includes, so awesome :o
*/

# include "libft.h"
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <pthread.h>
# include <errno.h>

/*
***************
**	defines  **
***************
*/

/*
*************
**	enums  **
*************
*/

typedef enum	e_protocol
{
	TCP = SOCK_STREAM,
	UDP = SOCK_DGRAM
}				t_protocol;

/*
******************
**	structures  **
******************
*/

typedef struct			s_client
{
	t_protocol			protocol;
	int					sockfd;
	t_vector			*write_queue;
}						t_client;

typedef struct			s_server
{
	t_protocol			protocol;
	int					sockfd;
	int					queue_max;
	struct timeval		timeout;
	t_vector			*clients;
	t_vector			*write_queue;
	uint16_t			port;
}						t_server;

/*
************************
**	client functions  **
************************
*/

t_client				*new_client(t_protocol protocol,
						char *address, char *port);

/*
************************
**	server functions  **
************************
*/

t_server				*new_server(t_protocol protocol, char *port);

#endif
