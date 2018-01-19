/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:51:48 by pribault          #+#    #+#             */
/*   Updated: 2018/01/19 12:58:31 by pribault         ###   ########.fr       */
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

typedef enum		e_callback
{
	CLIENT_ADD_CB,
	CLIENT_DEL_CB,
	MSG_RECV_CB,
	MSG_SEND_CB,
	CLIENT_EXCEPTION_CB,
	SERVER_EXCEPTION_CB,
	CALLBACK_MAX
}					t_callback;

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
	void			*data;
	void			(*client_add)(struct s_server*, t_client*);
	void			(*client_del)(struct s_server*, t_client*);
	void			(*msg_recv)(struct s_server*, t_client*, t_msg*);
	void			(*msg_send)(struct s_server*, t_client*, t_msg*);
	void			(*client_excpt)(struct s_server*, t_client*);
	void			(*server_excpt)(struct s_server*);
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
void				server_attach_data(t_server *server, void *data);
void				*server_get_data(t_server *server);
void				server_set_callback(t_server *server, t_callback cb,
					void *ptr);
int					server_poll_events(t_server *server);
void				server_add_clients_to_set(fd_set *set,
					t_vector *clients, int *fd_max);
void				server_add_write_request_to_set(fd_set *set,
					t_vector *write_queue, int *fd_max);

#endif
