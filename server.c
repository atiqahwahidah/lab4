#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>

#define PORT 8008

int main(int argc, char *argv[])
{
int socket_desc, new_socket, c;
long valread;
struct sockaddr_in address;
int addrlen=sizeof(address);

char *me="HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 53\n\n Hi assalamualaikum.Nama saya Nur Atiqah Wahidah.#UiTMdiHatiku";

if ((socket_desc = socket(AF_INET, SOCK_STREAM,0))==0)
{
puts("In the socket!");
return 1;
}

if (socket_desc == -1)
{
printf("Socket cannot be created!");
}

address.sin_family =AF_INET;
address.sin_addr.s_addr=INADDR_ANY;
address.sin_port=htons (8008);

memset (address.sin_zero, '\0', sizeof address.sin_zero);

if(bind(socket_desc,(struct sockaddr *)&address, sizeof(address))<0)
{
puts("Bind FAILED!");
return 1;
}
puts("Bind done :)");

listen(socket_desc,3);

puts("Listening...");

while (1)
{
printf("\n***Waiting for connection***\n");
if ((new_socket=accept(socket_desc,(struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
{
puts("Connection accepted <3");
}

char buffer[30000] = {0};
valread = read(new_socket, buffer, 30000);
printf("%s\n",buffer);
write(new_socket,me,strlen(me));
printf("***Message has been sent***");
close(new_socket);
}
return 0;
}
