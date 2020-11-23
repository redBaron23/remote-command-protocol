#!/bin/zsh
#
#

gcc ./client/udpClient.c -o client.out
gcc ./server/udpServer.c -o server.out

./server.out
