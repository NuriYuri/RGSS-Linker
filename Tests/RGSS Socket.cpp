#include "stdafx.h"
// http://social.msdn.microsoft.com/Forums/expression/en-US/f1a5d251-44a7-461e-83a4-275b53d0c815/trouble-with-getstaticportmappingcollection-when-port-forwarding-port-mapping?forum=windowsgeneraldevelopmentissues

//---
//Definition Block
//---
//Constantes
VALUE cSocket=NULL;
VALUE eSocketError=NULL;
VALUE eSocketNETDOWN=NULL;
VALUE cTCPServer=NULL;
VALUE cTCPSocket=NULL;
int SocketTMPFlag=0;
int SocketWaitTimer=50;

//Structures
struct RGSSsocketData {
	SOCKET dsocket;
	struct sockaddr_in dservice;
	int closed;
};
struct RGSSSOCKET {
    struct RBasic basic;
    void (*dmark)(void*);
    void (*dfree)(void*);
    RGSSsocketData *data;
};
#define RSOCKET(obj)   (R_CAST(RGSSSOCKET)(obj))
//Fonctions
VALUE RB_Socket_alloc(VALUE klass);
void RB_Socket_free(RGSSsocketData* ptr);

//---
//Function Block
//---

void Init_Socket()
{
	cSocket=rb_define_class("Socket",RGSSLinker_GetObject(_id_rb_cObject));
	eSocketError=rb_define_class("SocketError",RGSSLinker_GetObject(_id_rb_eStandardError));
	eSocketNETDOWN=rb_define_class("SocketNETDOWN",RGSSLinker_GetObject(_id_rb_eStandardError));
	rb_define_alloc_func(cSocket,_rbf RB_Socket_alloc);
	rb_define_private_method(cSocket,"initialize",_rbf RB_Socket_Init,3);
	rb_define_private_method(cSocket,"initialize_copy",_rbf RB_Socket_Init,3);
	rb_define_method(cSocket,"connect",_rbf RB_Socket_connect,2);
	rb_define_method(cSocket,"bind",_rbf RB_Socket_bind,2);
	rb_define_method(cSocket,"send",_rbf RB_Socket_send,1);
	rb_define_method(cSocket,"recv",_rbf RB_Socket_recv,1);
	rb_define_method(cSocket,"recv_peek",_rbf RB_Socket_recv_peek,1);
	rb_define_method(cSocket,"close",_rbf RB_Socket_close,0);
	rb_define_method(cSocket,"closed?",_rbf RB_Socket_closed,0);
	rb_define_method(cSocket,"listen",_rbf RB_Socket_listen,1);
	rb_define_method(cSocket,"accept",_rbf RB_Socket_accept,0);
	rb_define_method(cSocket,"shutdown",_rbf RB_Socket_shutdown,1);
	rb_define_method(cSocket,"select_readable?",_rbf RB_TCPSocket_readable,0);
	rb_define_sigleton_method(cSocket,"setWaitTimer",_rbf RB_Socket_SetWaitTimer,1);

	//Definition des constantes de socket
	rb_define_const(cSocket,"AF_UNSPEC",LONG2FIX(AF_UNSPEC));
	rb_define_const(cSocket,"AF_INET",LONG2FIX(AF_INET));
	rb_define_const(cSocket,"AF_IPX",LONG2FIX(AF_IPX));
	rb_define_const(cSocket,"AF_APPLETALK",LONG2FIX(AF_APPLETALK));
	rb_define_const(cSocket,"AF_NETBIOS",LONG2FIX(AF_NETBIOS));
	rb_define_const(cSocket,"AF_INET6",LONG2FIX(AF_INET6));
	rb_define_const(cSocket,"AF_IRDA",LONG2FIX(AF_IRDA));
	rb_define_const(cSocket,"AF_BTH",LONG2FIX(AF_BTH));
	
	rb_define_const(cSocket,"SOCK_STREAM",LONG2FIX(SOCK_STREAM));
	rb_define_const(cSocket,"SOCK_DGRAM",LONG2FIX(SOCK_DGRAM));
	rb_define_const(cSocket,"SOCK_RAW",LONG2FIX(SOCK_RAW));
	rb_define_const(cSocket,"SOCK_RDM",LONG2FIX(SOCK_RDM));
	rb_define_const(cSocket,"SOCK_SEQPACKET",LONG2FIX(SOCK_SEQPACKET));
	
	rb_define_const(cSocket,"IPPROTO_ICMP",LONG2FIX(IPPROTO_ICMP));
	rb_define_const(cSocket,"IPPROTO_IGMP",LONG2FIX(IPPROTO_IGMP));
	rb_define_const(cSocket,"BTHPROTO_RFCOMM",LONG2FIX(3));//BTHPROTO_RFCOMM
	rb_define_const(cSocket,"IPPROTO_TCP",LONG2FIX(IPPROTO_TCP));
	rb_define_const(cSocket,"IPPROTO_UDP",LONG2FIX(IPPROTO_UDP));
	rb_define_const(cSocket,"IPPROTO_ICMPV6",LONG2FIX(IPPROTO_ICMPV6));
	rb_define_const(cSocket,"IPPROTO_RM",LONG2FIX(113));//IPPROTO_RM = 113

	rb_define_const(cSocket,"SOMAXCONN",LONG2FIX(SOMAXCONN));
	rb_define_const(cSocket,"SD_RECEIVE",LONG2FIX(SD_RECEIVE));
	rb_define_const(cSocket,"SD_SEND",LONG2FIX(SD_SEND));
	rb_define_const(cSocket,"SD_BOTH",LONG2FIX(SD_BOTH));

	cTCPSocket=rb_define_class("TCPSocket",cSocket);
	rb_define_private_method(cTCPSocket,"initialize",_rbf RB_TCPSocket_Init,2);
	rb_define_private_method(cTCPSocket,"initialize_copy",_rbf RB_TCPSocket_Init,2);
	rb_define_method(cTCPSocket,"readable?",_rbf RB_TCPSocket_readable,0);
	rb_undef_method(cTCPSocket,"connect");
	rb_undef_method(cTCPSocket,"bind");
	rb_undef_method(cTCPSocket,"accept");
	rb_undef_method(cTCPSocket,"listen");

	cTCPServer=rb_define_class("TCPServer",cSocket);
	rb_undef_method(cTCPServer,"connect");
	rb_undef_method(cTCPServer,"bind");
	rb_define_private_method(cTCPServer,"initialize",_rbf RB_TCPServer_Init,2);
	rb_define_private_method(cTCPServer,"initialize_copy",_rbf RB_TCPServer_Init,2);
	rb_define_method(cTCPServer,"accepting?",_rbf RB_TCPSocket_readable,0);
}

//---
//Allocatin d'une socket
//---
VALUE RB_Socket_alloc(VALUE klass)
{
	return Data_Wrap_Struct(klass,NULL,(void(*) (MULTIPLE_ARG)) RB_Socket_free,ruby_xmalloc(sizeof(RGSSsocketData)));
}

//---
//Check des erreurs
//---
VALUE CheckSocketError(VALUE self,char* msg,int Error)
{
	if(Error==WSAENETDOWN)
	{
		rb_raise2(eSocketNETDOWN,msg,Error);
		return self;
	}
	else if(Error==WSAENETRESET || Error==WSAECONNABORTED || Error==WSAETIMEDOUT || Error==WSAECONNRESET)
	{
		RB_Socket_close(self);
	}
	rb_raise2(eSocketError,msg,Error);
	return self;
}

//---
//Initialisation d'un object RGSS Socket
//---
VALUE RB_Socket_Init(VALUE self,VALUE af,VALUE type,VALUE protocol)
{
	rb_check_type(self,T_DATA);
	RGSSsocketData* socket_data=RSOCKET(self)->data;
	socket_data->dsocket=INVALID_SOCKET;
	socket_data->dservice=sockaddr_in();
	rb_check_type(af,T_FIXNUM);
	rb_check_type(type,T_FIXNUM);
	rb_check_type(protocol,T_FIXNUM);
	socket_data->dsocket=socket(rb_num2long(af),rb_num2long(type),rb_num2long(protocol));
	if(socket_data->dsocket==INVALID_SOCKET)
		return CheckSocketError(self,"Error, can't create socket : %ld\n",WSAGetLastError());
	socket_data->dservice.sin_family=(ADDRESS_FAMILY)rb_num2long(af);
	socket_data->closed=2;
	return self;
}

VALUE RB_Socket_connect(VALUE self,VALUE hostname,VALUE port)
{
	int hr;
	rb_check_type(self,T_DATA);
	RGSSsocketData* socket_data=RSOCKET(self)->data;
	if(!socket_data->closed)
		return 0;
	struct hostent *remoteHost;
	rb_check_type(hostname,T_STRING);
	rb_check_type(port,T_FIXNUM);
	remoteHost=gethostbyname(RSTRING_PTR(hostname));//remoteHost=gethostbyname(RSTRING(hostname)->ptr);
	if(!remoteHost)
		rb_raise2(eSocketError,"Error, can't find host %s : %ld\n",RSTRING_PTR(hostname),WSAGetLastError());//rb_raise2(eSocketError,"Error, can't find host %s : %ld\n",RSTRING(hostname)->ptr,WSAGetLastError());
	socket_data->dservice.sin_addr.S_un.S_addr=*(ULONG*)remoteHost->h_addr_list[0];
	socket_data->dservice.sin_port=htons((USHORT)rb_num2long(port));
	hr=connect(socket_data->dsocket,(SOCKADDR*)&socket_data->dservice,sizeof(SOCKADDR_IN));
	if(hr==SOCKET_ERROR)
		return CheckSocketError(self,"Error, can't connect to server : %ld", WSAGetLastError());
	socket_data->closed=0;
	return self;
}

VALUE RB_Socket_send(VALUE self,VALUE str)
{
	int hr;
	rb_check_type(self,T_DATA);
	RGSSsocketData* socket_data=RSOCKET(self)->data;
	rb_check_type(str,T_STRING);
	if(socket_data->closed)
	{
		rb_warning("Socket %ld closed.",self);
		return 0;
	}
	hr=send(socket_data->dsocket,RSTRING_PTR(str),RSTRING_LEN(str),0);//hr=send(socket_data->dsocket,RSTRING(str)->ptr,RSTRING(str)->len,0);
	if(hr==SOCKET_ERROR)
	{
		CheckSocketError(self,"Can't send data %ld",WSAGetLastError());
		return 0;
	}
	return LONG2FIX(hr);
}

VALUE RB_Socket_recv(VALUE self,VALUE obj)
{
	int hr;
	rb_check_type(self,T_DATA);
	RGSSsocketData* socket_data=RSOCKET(self)->data;
	if(socket_data->closed)
	{
		rb_warning("Socket %ld closed.",self);
		return 0;
	}
	if(obj&0x01)
	{
		int length=rb_num2long(obj);
		char* buffer=(char*)calloc(1,length);
		if(!buffer)
			rb_raise2(eSocketError,"Can't alloc memory %d",length);
		hr=recv(socket_data->dsocket,buffer,length,SocketTMPFlag);
		if(hr==SOCKET_ERROR)
		{
			CheckSocketError(self,"Can't receive data %ld",WSAGetLastError());
	  	free(buffer);
			return rb_str_new2("\x00");
		}
		else if(hr==0)
		{
			RB_Socket_close(self);
			rb_warning("Can't receive data %ld (closed)",WSAGetLastError());
	  	free(buffer);
			return rb_str_new2("\x00");
		}
		obj=rb_str_new(buffer,hr);
		free(buffer);
		return obj;
	}
	else
	{
		rb_check_type(obj,T_STRING);
		hr=recv(socket_data->dsocket,RSTRING_PTR(obj),RSTRING_LEN(obj),SocketTMPFlag);//hr=recv(socket_data->dsocket,RSTRING(obj)->ptr,RSTRING(obj)->len,SocketTMPFlag);
		if(hr==SOCKET_ERROR)
		{
			rb_warning("Can't receive data %ld",WSAGetLastError());
			return 1;
		}
		else if(hr==0)
		{
			RB_Socket_close(self);
			rb_warning("Can't receive data %ld (closed)",WSAGetLastError());
			return 1;
		}
		return LONG2FIX(hr);
	}
}

VALUE RB_Socket_recv_peek(VALUE self,VALUE obj)
{
	SocketTMPFlag=MSG_PEEK;
	obj=RB_Socket_recv(self,obj);
	SocketTMPFlag=0;
	return obj;
}

VALUE RB_Socket_closed(VALUE self)
{
	rb_check_type(self,T_DATA);
	RGSSsocketData* socket_data=RSOCKET(self)->data;
	return socket_data->closed;
}

VALUE RB_Socket_close(VALUE self)
{
	int hr;
	rb_check_type(self,T_DATA);
	RGSSsocketData* socket_data=RSOCKET(self)->data;
	if(socket_data->closed)
		return 0;
	hr=closesocket(socket_data->dsocket);
	if(hr==SOCKET_ERROR)
		rb_raise2(eSocketError,"Error, close socket : %ld",WSAGetLastError());
	socket_data->closed=2;
	return 2;
}

VALUE RB_Socket_listen(VALUE self,VALUE obj)
{
	int hr;
	rb_check_type(self,T_DATA);
	RGSSsocketData* socket_data=RSOCKET(self)->data;
	rb_check_type(obj,T_FIXNUM);
	if(socket_data->closed)
	{
		rb_warning("Socket %ld closed.",self);
		return 0;
	}
	hr=listen(socket_data->dsocket,rb_num2long(obj));
	if(hr==SOCKET_ERROR)
		return CheckSocketError(self,"Error, listen socket : %ld",WSAGetLastError());
	return 2;
}

VALUE RB_Socket_accept(VALUE self)
{
	SOCKET dclient;
	VALUE clientSocket;
	struct sockaddr_in cservice;
	int size=sizeof(SOCKADDR_IN);
	rb_check_type(self,T_DATA);
	RGSSsocketData* socket_data=RSOCKET(self)->data;
	if(socket_data->closed)
	{
		rb_warning("Socket %ld closed.",self);
		return 0;
	}
	dclient=accept(socket_data->dsocket,(SOCKADDR*)&cservice,&size);
	if(dclient==SOCKET_ERROR)
		return CheckSocketError(self,"Error, accept socket : %ld",WSAGetLastError());
	if(RSOCKET(self)->basic.klass == cSocket)
		clientSocket=rb_obj_alloc(cSocket);
	else
		clientSocket=rb_obj_alloc(cTCPSocket);
	RGSSsocketData* client_data=RSOCKET(clientSocket)->data;
	client_data->dsocket=dclient;
	client_data->closed=0;
	memcpy(&client_data->dservice,&cservice,size);
	return clientSocket;
}

VALUE RB_Socket_bind(VALUE self,VALUE hostname,VALUE port)
{
	int hr;
	rb_check_type(self,T_DATA);
	RGSSsocketData* socket_data=RSOCKET(self)->data;
	if(!socket_data->closed)
		return 0;
	struct hostent *remoteHost;
	rb_check_type(hostname,T_STRING);
	rb_check_type(port,T_FIXNUM);
	remoteHost=gethostbyname(RSTRING_PTR(hostname));
	if(!remoteHost)
		rb_raise2(eSocketError,"Error, can't find host %s : %ld\n",RSTRING_PTR(hostname),WSAGetLastError());
	socket_data->dservice.sin_addr.S_un.S_addr=*(ULONG*)remoteHost->h_addr_list[0];
	socket_data->dservice.sin_port=htons((USHORT)rb_num2long(port));
	hr=bind(socket_data->dsocket,(SOCKADDR*)&socket_data->dservice,sizeof(SOCKADDR_IN));
	if(hr==SOCKET_ERROR)
		return CheckSocketError(self,"Error, can't bind the socket : %ld", WSAGetLastError());
	socket_data->closed=0;
	return self;
}

VALUE RB_Socket_shutdown(VALUE self,VALUE how)
{
	int hr;
	rb_check_type(self,T_DATA);
	RGSSsocketData* socket_data=RSOCKET(self)->data;
	rb_check_type(how,T_FIXNUM);
	hr=shutdown(socket_data->dsocket,rb_num2long(how));
	if(hr==SOCKET_ERROR)
		return CheckSocketError(self,"Error, can't shutdown : %ld", WSAGetLastError());
	return self;
}

void RB_Socket_free(RGSSsocketData* ptr)
{
	if(!ptr->closed)
	{
		int hr=closesocket(ptr->dsocket);
		if(hr==SOCKET_ERROR)
			rb_raise2(eSocketError,"Error, close socket : %ld",WSAGetLastError());
		rb_warning("FATAL Error, socket not closed !");
	}
	ruby_xfree(ptr);
}

VALUE RB_TCPSocket_Init(VALUE self, VALUE hostname, VALUE port)
{
	int hr;
	rb_check_type(self,T_DATA);
	RGSSsocketData* socket_data=RSOCKET(self)->data;
	rb_check_type(hostname,T_STRING);
	rb_check_type(port,T_FIXNUM);
	socket_data->dsocket=INVALID_SOCKET;
	socket_data->dservice=sockaddr_in();
	socket_data->dsocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(socket_data->dsocket==INVALID_SOCKET)
		return CheckSocketError(self,"Error, can't create socket : %ld\n",WSAGetLastError());
	socket_data->dservice.sin_family=AF_INET;
	struct hostent *remoteHost;
	remoteHost=gethostbyname(RSTRING_PTR(hostname));
	if(!remoteHost)
		rb_raise2(eSocketError,"Error, can't find host %s : %ld\n",RSTRING_PTR(hostname),WSAGetLastError());
	socket_data->dservice.sin_addr.S_un.S_addr=*(ULONG*)remoteHost->h_addr_list[0];
	socket_data->dservice.sin_port=htons((USHORT)rb_num2long(port));
	hr=connect(socket_data->dsocket,(SOCKADDR*)&socket_data->dservice,sizeof(SOCKADDR_IN));
	if(hr==SOCKET_ERROR)
		return CheckSocketError(self,"Error, can't connect to server : %ld", WSAGetLastError());
	socket_data->closed=0;
	return self;
}

VALUE RB_TCPSocket_readable(VALUE self)
{
	int hr;
	fd_set set;
	struct timeval timeout;
	rb_check_type(self,T_DATA);
	RGSSsocketData* socket_data=RSOCKET(self)->data;
	FD_ZERO(&set);
	FD_SET(socket_data->dsocket,&set);
	timeout.tv_sec=0;
	timeout.tv_usec=SocketWaitTimer;
	hr=select(socket_data->dsocket+1,&set,NULL,NULL,&timeout);
	if(hr==SOCKET_ERROR)
		return CheckSocketError(self,"Select error (TCPSocket#readable?/TCPServer#accepting?) : %ld", WSAGetLastError());
	if(FD_ISSET(socket_data->dsocket,&set))
		return 2;
	return 0;
}

VALUE RB_Socket_SetWaitTimer(VALUE self, VALUE timer)
{
	rb_check_type(timer,T_FIXNUM);
	SocketWaitTimer=rb_num2long(timer);
	return 2;
}

VALUE RB_TCPServer_Init(VALUE self, VALUE hostname, VALUE port)
{
	int hr;
	rb_check_type(self,T_DATA);
	RGSSsocketData* socket_data=RSOCKET(self)->data;
	rb_check_type(hostname,T_STRING);
	rb_check_type(port,T_FIXNUM);
	socket_data->dsocket=INVALID_SOCKET;
	socket_data->dservice=sockaddr_in();
	socket_data->dsocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(socket_data->dsocket==INVALID_SOCKET)
		return CheckSocketError(self,"Error, can't create socket : %ld\n",WSAGetLastError());
	socket_data->dservice.sin_family=AF_INET;
	struct hostent *remoteHost;
	remoteHost=gethostbyname(RSTRING_PTR(hostname));
	if(!remoteHost)
		rb_raise2(eSocketError,"Error, can't find host %s : %ld\n",RSTRING_PTR(hostname),WSAGetLastError());
	socket_data->dservice.sin_addr.S_un.S_addr=*(ULONG*)remoteHost->h_addr_list[0];
	socket_data->dservice.sin_port=htons((USHORT)rb_num2long(port));
	hr=bind(socket_data->dsocket,(SOCKADDR*)&socket_data->dservice,sizeof(SOCKADDR_IN));
	if(hr==SOCKET_ERROR)
		return CheckSocketError(self,"Error, can't bind the socket : %ld", WSAGetLastError());
	socket_data->closed=0;
	return self;
}
//http://www.gnu.org/software/libc/manual/html_node/Server-Example.html
