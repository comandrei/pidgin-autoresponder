# pidgin-autoresponder
A Pidgin plugin that will autorespond with a custom message when you are idle.
Faculty Project, 1st year


# how to build

1. apt-get build-dep pidgin
2. download pidgin sources
3. tar xvzf pidgin_2.6.2.orig.tar.gz && cd pidgin-2.6.2
4. ./configure (pass in options from the About dialog in Pidgin on your platform)
5. cd libpurple/plugins
6. cp auto_responder.c
7. make auto_responder.so
8. mkdir -p ~/.purple/plugins && cp auto_responder.so ~/.purple/plugins


[official build instructions](https://developer.pidgin.im/wiki/CHowTo/BasicPluginHowto)
