/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 11:15:22 by pribault          #+#    #+#             */
/*   Updated: 2018/01/19 22:33:12 by pribault         ###   ########.fr       */
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

t_client				*client_new(t_protocol protocol,
						char *address, char *port);

/*
************************
**	server functions  **
************************
*/

t_server				*server_new(void);
void					server_delete(t_server **server);
int						server_start(t_server *server, t_protocol protocol,
						char *port);
void					server_stop(t_server *server);
void					server_attach_data(t_server *server, void *data);
void					*server_get_data(t_server *server);
void					server_set_callback(t_server *server, t_callback cb,
						void *ptr);
int						server_poll_events(t_server *server);
int						server_get_client_fd(t_client *client);

#endif
