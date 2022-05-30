#include "receiver.h"

using namespace std;

bool receiver::receive_file(std::string filename) {
	vector<uint8_t> packet;
	uint8_t c = CRC_enabled ? 'C' : NAK;
	uint8_t packetLength = CRC_enabled ? PACKET_LENGTH_CRC : PACKET_LENGTH;
	uint8_t i = 0;

	do {
		cout << "initializing connection " << +i << '\n';
		send(port, {c});
		packet = receive(port, packetLength);
		Sleep(10000); // 10s
	} while(i++ < 6 && packet[0] == 0);

	if(packet[0] == 0)
		return false; // could not establish connection

	FILE *file = fopen(filename.c_str(), "wb");
	while(packet[0] != EOT) {
		vector<uint8_t> outBuffer(DATA_LENGTH + 1);
		cout << "packet " << +packet[1] << " received\n";

		for(int i = 0; i < packetLength; i++) {
			cout << +packet[i] << ' ';
		}
		cout << "\n";

		// read payload
		outBuffer.insert(outBuffer.begin(), packet.begin() + 3, packet.begin() + 3 + DATA_LENGTH);
		outBuffer.erase(outBuffer.begin() + 128, outBuffer.end());

		// check checksum
		uint32_t checksum = getChecksum(outBuffer, CRC_enabled);
		cout << "calculated checksum: " << checksum << '\n';
		bool correct = true;
		if(CRC_enabled) {
			for(i = 0; i < 4; i++) {
				if (packet[3 + DATA_LENGTH + i] != (uint8_t) (checksum >> ((3 - i) * 8))) {
					correct = false;
				}
			}
		} else {
			correct = (packet[3 + DATA_LENGTH] == (uint8_t) checksum);
		}

		// send confirmation
		if(correct) {
			cout << "checksum correct\n";
			send(port, {ACK});
			auto zeros = find(outBuffer.begin(), outBuffer.end(), 0);
			if(zeros != outBuffer.end()) {
				outBuffer.erase(zeros, outBuffer.end());
			}
			fwrite(outBuffer.data(), 1, outBuffer.size(), file);
		} else {
			cout << "checksum error!\n";
			send(port, {NAK});
		}
		packet = receive(port, packetLength);
	}
	send(port, {ACK});
	cout << "end transmission\n";
	fclose(file);
	return true;
}
