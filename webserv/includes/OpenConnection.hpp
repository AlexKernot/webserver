/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenConnection.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:36:15 by akernot           #+#    #+#             */
/*   Updated: 2024/03/18 18:00:30 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdStream.hpp"
#include "Ahttp.hpp"
#include "AHttpRequest.hpp"

class OpenConnection : public FdStream {
public:
	OpenConnection(int fd);
	void sendResponse(Ahttp* response);
	AHttpRequest* receiveRequest();
	void reject();
	~OpenConnection();

private:
	int fd;

	OpenConnection();
	OpenConnection(const OpenConnection&);
	OpenConnection& operator=(const OpenConnection&);
}