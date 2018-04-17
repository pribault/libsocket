/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 11:15:22 by pribault          #+#    #+#             */
/*   Updated: 2018/04/16 16:18:06 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_H
# define LIBSOCKET_H

# define LIBSOCKET_VERSION_MAJOR	2
# define LIBSOCKET_VERSION_MINOR	0

# ifdef __cplusplus

namespace libsocket
{
}

# else

/*
****************
**	includes  **
****************
*/

#  include <sys/socket.h>
#  include <inttypes.h>
#  include <unistd.h>
#  include <netdb.h>

#  include "libft.h"

#  include "libsocket_structures.h"

/*
************************
**	socket functions  **
************************
*/

/*
**	allocate a new socket, return null on error
*/

t_socket	*socket_new(void);

/*
**	delete a socket created with socket_new
*/

void		socket_delete(t_socket **socket);

/*
**	bind a socket to a port.
**	return 1 on succes, 0 on error.
**
**	errors leading to failure:
**	 - socket already bind
**	 - cannot create socket
**	 - cannot set options to socket
**	 - cannot bind socket
**	 - cannot listen on port (tcp only)
**
**	you can register a callback with socket_set_callback
**	to be notified of of bind and unbind events.
*/

int			socket_bind(t_socket *socket, t_method method, char *port);

/*
**	unbind a socket and clear all queues and buffers.
**	this function will silently fail if the socket is not binded.
**	you can register a callback with socket_set_callback
**	to be notified of of bind and unbind events.
*/

void		socket_unbind(t_socket *socket);

/*
**	set a callback to call when an event is generated.
**	available callbacks:
**	 - SOCKET_CLIENT_ADD_CB, will be called with (t_socket *, t_client *)
**	 - SOCKET_CLIENT_DEL_CB, will be called with (t_socket *, t_client *)
**	 - SOCKET_MSG_RECV_CB, will be called with (struct s_socket *, t_client *,
**		t_msg *)
**	 - SOCKET_MSG_SEND_CB, will be called with (struct s_socket *, t_client *,
		t_msg *)
**	 - SOCKET_MSG_TRASH_CB, will be called with (struct s_socket *, t_client *,
		t_msg *)
**	 - SOCKET_CLIENT_EXCEPTION_CB, will be called with (struct s_socket *,
		t_client *)
**	 - SOCKET_BIND_CB, will be called with (struct s_socket *)
**	 - SOCKET_UNBIND_CB, will be called with (struct s_socket *)
**	 - SOCKET_EXCEPTION_CB, will be called with (struct s_socket *)
**	 - SOCKET_BUFFER_FULL_CB, will be called with (struct s_socket *)
*/

void		socket_set_callback(t_socket *socket, t_callback cb, void *ptr);

# endif

#else

# pragma message __FILE__ "already included"

#endif
