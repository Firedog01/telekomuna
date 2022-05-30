#include "sender.h"

using namespace std;

bool sender::send_file(std::string filename) {
	while(true) {
		uint8_t mode = receiveOne(port);
		cout << "begin connection: " << +mode << '\n';
		if(mode == NAK) {
			cout << "CRC disabled\n";
			CRC_enabled = false;
			break;
		} else if (mode == 'C') {
			cout << "CRC enabled\n";
			CRC_enabled = true;
			break;
		}
	}
	uint8_t packetLength = CRC_enabled ? PACKET_LENGTH_CRC : PACKET_LENGTH;

	FILE* file = fopen(filename.c_str(), "rb");
	fseek(file, 0, SEEK_END);
	int32_t fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	cout << "sending file of length: " << fileSize << " in " << fileSize / 128 + 1 << " packets\n";

	int seq = 1;
	uint8_t sendStatus;
	while(ftell(file) < fileSize) {
		vector<uint8_t> packet(packetLength + 1, 0);
		vector<uint8_t> payload(DATA_LENGTH, 0);

		// header
		packet.insert(packet.begin(), SOH);
		packet.insert(packet.begin() + 1, seq);
		packet.insert(packet.begin() + 2, 255 - seq);

		// payload
		auto readSize = (int32_t) fread(payload.data(), 1, DATA_LENGTH, file);
		packet.insert(packet.begin() + 3, payload.begin(), payload.end());
		if(packet.size() > packetLength) {
			packet.erase(packet.begin() + packetLength, packet.end());
		}

		for(int i = 0; i < payload.size(); i++) {
			cout << +payload[i] << ' ';
		}
		cout << "\npayload size: " << payload.size() << '\n';


		// checksum
		uint32_t checksum = getChecksum(payload, CRC_enabled);
		if(CRC_enabled)
			for(uint8_t i = 0; i < 4; i++)
				packet[3 + DATA_LENGTH + i] = (uint8_t) (checksum >> ((3 - i) * 8));
		else
			packet[3 + DATA_LENGTH] = (uint8_t) checksum;

		for(int i = 0; i < packet.size(); i++) {
			cout << +packet[i] << ' ';
		}
		cout << "\npacket size: " << packet.size() << '\n';

		cout << "sending packet " << seq << '\n';
		send(port, packet);
		sendStatus = receiveOne(port);

		if(sendStatus == ACK) { // move to next block
			cout << "sent successfully\n";
			seq++;
		} else if(sendStatus == NAK) { // resend
			cout << "needs to be resent\n";
			fseek(file, -readSize, SEEK_CUR);
		}
	}

	send(port, {EOT});
	uint8_t ret = receiveOne(port);

	fclose(file);
	if(ret == ACK) {
		return true;
	}
	cout << "did not get confirmation of end of communication\n";
	return false;
}
