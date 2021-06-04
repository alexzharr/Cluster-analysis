//Zharikov Alexey 211

#include "Proxi.h"

int main()
{
	Proxi p;
	p.open_log();

	int     i, err, opt = 1;
	int     sock, new_sock;
	fd_set  active_set, read_set;
	struct  sockaddr_in  addr;
	struct  sockaddr_in  client;
	char    buf[BUFLEN];
	socklen_t  size;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup failed\n");
		return 1;
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("Server: cannot create socket");
		exit(EXIT_FAILURE);
	}
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	err = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
	if (err < 0)
	{
		perror("Server: cannot bind socket");
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	err = listen(sock, 3);
	if (err < 0)
	{
		perror("Server: listen queue failure");
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	FD_ZERO(&active_set);
	FD_SET(sock, &active_set);

	while (1) {
		read_set = active_set;
		if (select(FD_SETSIZE, &read_set, NULL, NULL, NULL) < 0)
		{
			perror("Server: select  failure");
			WSACleanup();
			exit(EXIT_FAILURE);
		}
		for (unsigned int j = 0; j < read_set.fd_count; j++) {
			i = read_set.fd_array[j];
			if (FD_ISSET(i, &read_set)) {
				if (i == sock) {
					size = sizeof(client);
					new_sock = accept(sock, (struct sockaddr*)&client, &size);
					if (new_sock < 0) {
						perror("accept");
						WSACleanup();
						exit(EXIT_FAILURE);
					}
					fprintf(stdout, "Server: connect from host %s, port %hu.\n",
						inet_ntoa(client.sin_addr),
						ntohs(client.sin_port));
					FD_SET(new_sock, &active_set);
				}
				else {
					err = p.read_from_client(i, buf);
					if (err < 0) {
						closesocket(i);
						FD_CLR(i, &active_set);
					}
					else {
						if (strstr(buf, "stop")) {
							closesocket(i);
							FD_CLR(i, &active_set);
						}
						else {
							p.write_to_client(i, buf);
						}
					}
				}
			}
		}
	}
	WSACleanup();
	return 0;
}