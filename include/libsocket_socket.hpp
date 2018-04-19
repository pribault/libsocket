/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket_socket.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:58:47 by pribault          #+#    #+#             */
/*   Updated: 2018/04/19 14:00:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_SOCKET_HPP
# define LIBSOCKET_SOCKET_HPP

#  include "libsocket_callbacks.hpp"

namespace libsocket
{
	template	<class CB>
	class	Socket
	{
		public:

			Socket(void)
			{
				callbacks.buffer_full(*this);
			}

		private:

			CB	callbacks;
	};
}

#endif
