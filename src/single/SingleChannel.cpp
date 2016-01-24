/* Copyright (C) 2015-2016 Alexander Shishenko <GamePad64@gmail.com>
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
#include "SingleChannel.h"
#include <QCoreApplication>

SingleChannel::SingleChannel() :
		QUdpSocket() {
	bool bound = bind(QHostAddress::LocalHost, 61346);
	if(bound) {
		connect(this, &SingleChannel::readyRead, this, &SingleChannel::datagramReceived);
	}else{
		writeDatagram("show", QHostAddress::LocalHost, 61346);
		exit(1);
	}
}

SingleChannel::~SingleChannel() {}

void SingleChannel::datagramReceived() {
	while(hasPendingDatagrams()) {
		QByteArray datagram(pendingDatagramSize(), 0);
		QHostAddress sender;
		uint16_t port;

		readDatagram(datagram.data(), datagram.size(), &sender, &port);

		if(datagram == "show")
			emit showMainWindow();
	}
}
