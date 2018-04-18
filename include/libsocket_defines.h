/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket_defines.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 13:38:02 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 15:31:02 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_DEFINES_H
# define LIBSOCKET_DEFINES_H

# ifndef __cplusplus

#  define METHOD(prot, dom)	(t_method){prot, dom}

/*
**	possible methods
*/

# ifdef LIBSOCKET_STRUCTURES_H

#  define TCP_IPV4	(t_method){TCP, IPV4}
#  define TCP_IPV6	(t_method){TCP, IPV6}
#  define UDP_IPV4	(t_method){UDP, IPV4}
#  define UDP_IPV6	(t_method){UDP, IPV6}

# else

#  pragma message "libsocket.h not included, partial defines"

# endif

/*
**	redefine BYTE macro if necessary
*/

# ifndef BYTE

#  define BYTE(shift)	(1 << shift)

# endif

# ifndef TIMEVAL

#  define TIMEVAL(s, us)	(struct timeval){s, us}

# endif

/*
**	macros used in socket_poll_events to define
**	the type of events to handle
*/

# define ACCEPT_CONNECTIONS		BYTE(0)
# define ALLOW_READ				BYTE(1)
# define ALLOW_WRITE			BYTE(2)

/*
**	number of messages that can be enqueued to write in a socket
*/

#  ifdef LIBSOCKET_INTERNAL

#   define CIRCULAR_BUFFER_SIZE	128

/*
**	default values
*/

#   define DEFAULT_READ_BUFFER_SIZE	512
#   define DEFAULT_QUEUE_MAX			2
#   define DEFAULT_TIMEOUT_S			1
#   define DEFAULT_TIMEOUT_US		0

/*
**	option masks
*/

#   define SERVER_RUNNING		0x1

#  endif

# else

#  pragma message __FILE__ "C only header"

# endif

#else

# pragma message __FILE__ "already included"

#endif
