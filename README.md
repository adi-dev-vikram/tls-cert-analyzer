# tls-cert-analyzer
client side and server side scripts to analyse the tls connection parameters and certs
*.) The python script helps in extracting useful info from a pem format ssl certificate 
For example: CN Name, Subject Alt Name, cipher suite used in TLS Handshake etc.
To get cert info from cmdline:
openssl s_client -showcerts -connect url:443
