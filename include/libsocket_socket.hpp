/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket_socket.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:58:47 by pribault          #+#    #+#             */
/*   Updated: 2018/04/20 14:51:42 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_SOCKET_HPP
# define LIBSOCKET_SOCKET_HPP

# ifdef __cplusplus

#  include "libsocket_callbacks.hpp"
#  include <boost/circular_buffer.hpp>

namespace libsocket
{
	class	Socket
	{
		public:

			Socket(Callbacks callbacks);

		private:

			std::vector<Client>				clients;
			boost::circular_buffer<Message>	write_queue;
			Callbacks						callbacks;
	};
}

# else

#  error "c++ only header"

# endif

#endif
