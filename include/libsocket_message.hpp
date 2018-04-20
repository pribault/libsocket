/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket_message.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:55:38 by pribault          #+#    #+#             */
/*   Updated: 2018/04/20 08:57:26 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_MESSAGE_HPP
# define LIBSOCKET_MESSAGE_HPP

# include <inttypes.h>

namespace	libsocket
{
	typedef struct	s_msg
	{
		void		*ptr;
		uint64_t	size;
	}				t_msg;
}

#endif
