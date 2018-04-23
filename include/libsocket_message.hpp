/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket_message.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 08:55:38 by pribault          #+#    #+#             */
/*   Updated: 2018/04/20 14:49:38 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_MESSAGE_HPP
# define LIBSOCKET_MESSAGE_HPP

# ifdef __cplusplus

#  include "libsocket_client.hpp"

#  include <inttypes.h>
#  include <string.h>
#  include <stdio.h>
#  include <string>
#  include <vector>

namespace	libsocket
{
	class	Message
	{
		public:

			//	constructors
			Message(void);
			Message(std::string& string);
			Message(void *ptr, uint64_t size);

			//	destructor
			~Message(void);

			//	operators
			Message&	operator=(Message& message);
			Message&	operator=(std::string string);
			Message&	operator=(std::string& string);
			Message&	operator+=(Message& message);
			Message&	operator+=(std::string string);
			Message&	operator+=(std::string& string);

			Message&	append(Message& message);
			Message&	append(std::string string);
			Message&	append(std::string& string);
			Message&	append(void *ptr, uint64_t size);

			//	debug
			void	debug(void);
			void	print(void);

		protected:

			std::vector<uint8_t>	vector;

		private:

			Client	client;
			bool	null_terminated;
	};
}

# else

#  error "c++ only header"

# endif

#endif
