# DooR-API-Server

# File organization

```
DooR-API-Server
│
├ door_api/ ------------------------------ Shared library: Recieve request from Door Bridge and request Door with unix domain socket.
├ door_ipc/ ------------------------------ Shared library: Define inter process communication, this library is used by Application and DooR.
├ unix_domain_socket_client/ ------------- Shared library: Offer unix domain socket client.
├ src/ ----------------------------------- Door API Server files
│  ├ door_api_manager--------------------- Management worker
│  ├ door_api_worker---------------------- Receive re uest 
│  ├ i_observer--------------------------- Use for object pattern. observer is door_api_manager
│  ├ i_subject---------------------------- Use for object pattern. Subject is unix_domain_socket_server
│  ├ key_generator------------------------ Generate Key for IPC between application and DooR
│  ├ unix_domain_socket_server------------ Wait for container registration.
│  ├ worker_unix_domain_socket_server----- Wait for shared key request.
│  └ main
└ CMakeLists.txt- ------------------------ for cmake
```
