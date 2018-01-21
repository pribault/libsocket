/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 11:15:22 by pribault          #+#    #+#             */
/*   Updated: 2018/01/21 11:54:13 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_H
# define LIBSOCKET_H

/*
****************
**	includes  **
****************
*/

# include <sys/socket.h>
# include <unistd.h>

/*
*************
**	types  **
*************
*/

/*
**	enums
*/

typedef enum	e_protocol
{
	TCP = SOCK_STREAM,
	UDP = SOCK_DGRAM
}				t_protocol;

typedef enum	e_callback
{
	CLIENT_ADD_CB,
	CLIENT_DEL_CB,
	MSG_RECV_CB,
	MSG_SEND_CB,
	CLIENT_EXCEPTION_CB,
	SERVER_EXCEPTION_CB,
	CALLBACK_MAX
}				t_callback;

/*
**	structures
*/

typedef struct	s_msg
{
	void		*ptr;
	size_t		size;
}				t_msg;

/*
**	others
*/

/*
**	warning, t_client is different
**	between client and server functions
*/

typedef void	*t_client;
typedef void	*t_server;

/*
************************
**	client functions  **
************************
*/

t_client		*client_new(t_protocol protocol,
				char *address, char *port);

/*
************************
**	server functions  **
************************
*/

t_server		*server_new(void);
void			server_delete(t_server **server);
int				server_start(t_server *server, t_protocol protocol,
				char *port);
void			server_stop(t_server *server);
void			server_attach_data(t_server *server, void *data);
void			*server_get_data(t_server *server);
void			server_set_callback(t_server *server, t_callback cb,
				void *ptr);
int				server_poll_events(t_server *server);
void			server_remove_client(t_server *server, t_client *client);
int				server_get_client_fd(t_client *client);
void			server_enqueue_write(t_server *server, t_client *client,
				t_msg *msg);
void			server_enqueue_write_by_fd(t_server *server, int fd,
				t_msg *msg);
void			server_add_client_by_fd(t_server *server, int fd);
char			*server_get_client_address(t_client *client);
void			server_client_attach_data(t_client *client, void *data);
void			*server_client_get_data(t_client *client);
int				server_set_queue_max(t_server *server, int max);
int				server_get_queue_max(t_server *server);
void			server_set_clients_max(t_server *server, size_t max);
size_t			server_get_clients_max(t_server *server);
int				server_connect(t_server *server, char *address,
				char *port);;

#endif
