void Init_Socket();
VALUE RB_Socket_Init(VALUE self,VALUE af,VALUE type,VALUE protocol);
VALUE RB_Socket_connect(VALUE self,VALUE hostname,VALUE port);
VALUE RB_Socket_send(VALUE self,VALUE str);
VALUE RB_Socket_recv(VALUE self,VALUE obj);
VALUE RB_Socket_recv_peek(VALUE self,VALUE obj);
VALUE RB_Socket_close(VALUE self);
VALUE RB_Socket_closed(VALUE self);
VALUE RB_Socket_listen(VALUE self,VALUE obj);
VALUE RB_Socket_accept(VALUE self);
VALUE RB_Socket_bind(VALUE self,VALUE hostname,VALUE port);
VALUE RB_Socket_shutdown(VALUE self,VALUE how);
VALUE RB_TCPSocket_Init(VALUE self, VALUE hostname, VALUE port);
VALUE RB_TCPSocket_readable(VALUE self);
VALUE RB_TCPServer_Init(VALUE self, VALUE hostname, VALUE port);
VALUE RB_Socket_SetWaitTimer(VALUE self, VALUE timer);