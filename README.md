# NFS-Server
Implementation of NFS-like file server with lib and testing program

# Build and run
You can build whole project with a script:

`./build_all.sh`

The script will compile dynamic libraries (socket, message, client), so it will need sudo privileges to put it in /usr/lib directory.

To run the server you can use a script:

`./run_server.sh address_ip port_number`

If you don't pass any parameters it will use localhost as address IP and 6941 as a port number. To make the server visible to other computers (outside of localhost) you can pass either 0.0.0.0 or your inner IP address.

To run testing program you can use a script:

`./run_client_test.sh address_ip port_number`

If you don't pass any parameters it will once again use localhost as address IP and 6941 as a port number.
