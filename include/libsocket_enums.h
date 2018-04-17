/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket_enums.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 13:35:56 by pribault          #+#    #+#             */
/*   Updated: 2018/04/16 15:05:37 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_ENUMS_H
# define LIBSOCKET_ENUMS_H

# ifndef __cplusplus

# include "libsocket_defines.h"

typedef enum	e_protocol
{
	TCP = SOCK_STREAM,
	UDP = SOCK_DGRAM
}				t_protocol;

typedef enum	e_domain
{
	IPV4 = AF_INET,
	IPV6 = AF_INET6
}				t_domain;

typedef enum	e_write_type
{
	WRITE_BY_FD,
	WRITE_BY_ADDR
}				t_write_type;

typedef enum	e_callback
{
	SOCKET_CLIENT_ADD_CB = 0,
	SOCKET_CLIENT_DEL_CB,
	SOCKET_MSG_RECV_CB,
	SOCKET_MSG_SEND_CB,
	SOCKET_MSG_TRASH_CB,
	SOCKET_CLIENT_EXCEPTION_CB,
	SOCKET_BIND_CB,
	SOCKET_UNBIND_CB,
	SOCKET_EXCEPTION_CB,
	SOCKET_BUFFER_FULL_CB,
	SOCKET_CALLBACK_MAX
}				t_callback;

# else

#  pragma message __FILE__ "C only header"

# endif

#else

# pragma message __FILE__ "already included"

#endif
