/*
 * This file is part of the trojan project.
 * Trojan is an unidentifiable mechanism to bypass GFW.
 * Copyright (C) 2017  GreaterFire
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CLIENTSESSION_H_
#define _CLIENTSESSION_H_

#include "session.h"
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

class ClientSession : public Session {
private:
    enum Status {
        HANDSHAKE,
        REQUEST,
        CONNECTING_REMOTE,
        FORWARD
    } status;
    boost::asio::ip::tcp::socket in_socket;
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket>out_socket;
    void destroy();
    void in_async_read();
    void in_async_write();
    void in_recv(const std::string &data);
    void in_send(const std::string &data);
    void out_async_read();
    void out_async_write();
    void out_recv(const std::string &data);
    void out_send(const std::string &data);
public:
    ClientSession(const Config &config, boost::asio::io_service &io_service, boost::asio::ssl::context &ssl_context);
    boost::asio::basic_socket<boost::asio::ip::tcp, boost::asio::stream_socket_service<boost::asio::ip::tcp> >& accept_socket();
    void start();
};

#endif // _CLIENTSESSION_H_