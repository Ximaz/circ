# CIRC Server

- The PASS commands allows a client (or server) to send a password in order to
  upgrade their connection to some privileged one. The given password must be
  matched with a locally known password by the server. The best way is to hash
  the password server-side and never store it in clear. Then, apply the same
  hash function to the given password from the command and compare it to the
  locally known password. If it matches: upgrade the connection with appropriate
  permissions.
