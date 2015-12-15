# pidgin-autoresponder
A Pidgin plugin that will autorespond with a custom message when you are idle.
Faculty Project, 1st year

# how to build

apt-get build-dep pidgin
download pidgin sources
tar xvzf pidgin_2.6.2.orig.tar.gz && cd pidgin-2.6.2
./configure (pass in options from the About dialog in Pidgin on your platform)
cd libpurple/plugins
cp auto_responder.c
make auto_responder.so
mkdir -p ~/.purple/plugins && cp auto_responder.so ~/.purple/plugins
