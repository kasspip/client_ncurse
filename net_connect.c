#include "net.h"

static SSL_CTX	*InitCTX(t_net *net)
{   
	const SSL_METHOD *method;
	SSL_CTX *ctx;
 
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	method = SSLv3_client_method();
	ctx = SSL_CTX_new(method);
	if ( ctx == NULL )
	{
		net->alert = (char**)malloc(sizeof(char*) * 2);
		net->alert[0] = strdup("Error: SSL_CTX_new() failed");
		net->alert[1] = 0;
	}
	return ctx;
}

static int 		OpenConnection(t_net *net)
{   
	int sd;
	struct hostent *host;
	struct sockaddr_in addr;

	if ( (host = gethostbyname(net->addr)) == NULL )
	{
		net->alert = (char**)malloc(sizeof(char*) * 2);
		net->alert[0] = strdup("Error: gethostbyname() failed");
		net->alert[1] = 0;
	}
	sd = socket(PF_INET, SOCK_STREAM, 0);
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(net->port);
	addr.sin_addr.s_addr = *(long*)(host->h_addr);
	if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
	{
		close(sd);
		net->alert = (char**)malloc(sizeof(char*) * 2);
		net->alert[0] = strdup("Error: connect() failed");
		net->alert[1] = 0;
	}
	return sd;
}

static void		show_certificate(t_net *net)
{   
	X509		*certif;
	const char	*encrypt;
	const char	*issuer;
 
	certif = NULL;
	certif = SSL_get_peer_certificate(net->ssl.ssl);
	encrypt = SSL_get_cipher(net->ssl.ssl);
	if ( certif )
	{
		issuer = X509_NAME_oneline(X509_get_issuer_name(certif), 0, 0);
		net->alert = (char**)malloc(sizeof(char*) * 3);
		net->alert[0] = stringf("# SSL encryption: %s", encrypt);
		net->alert[1] = stringf("# SSL Certifificate Issuer : %s", issuer);
		net->alert[2] = 0;
		X509_free(certif);
		free((void*)issuer);
	}
	else
	{
		net->alert = (char**)malloc(sizeof(char*) * 2);
		net->alert[0] = stringf("# SSL encryption: %s", encrypt);
		net->alert[1] = 0;
	}
}

int 			net_connect(t_net *net)
{
	SSL_library_init();
	net->ssl.ctx = InitCTX(net);
	net->sock = OpenConnection(net);
	net->ssl.ssl = SSL_new(net->ssl.ctx);
	SSL_set_fd(net->ssl.ssl, net->sock);
	if (SSL_connect(net->ssl.ssl) == -1)
	{
		net->alert = (char**)malloc(sizeof(char*) * 2);
		net->alert[0] = strdup("Error: connection with host failed.");
		net->alert[1] = 0;
		return (0);
	}
	show_certificate(net);
	net->is_connected = 1;
	return (1);
}