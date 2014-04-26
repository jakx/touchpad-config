all:
	gcc touchpad-config.c -o touchpad-config

add_autostart:
	echo '[Desktop Entry]\nType=Application\nExec=~/etc/touchpad-config\nComment=Autostart touchpad daemon' > ~/.config/autostart/touchpad-config.desktop

install: all add_autostart
	mkdir -p /etc/touchpad-config
	mv ./touchpad-config /etc/touchpad-config/
