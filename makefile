all:
	gcc touchpad-config.c -o touchpad-config

add_autostart:
	echo -e '[Desktop Entry]\n	Type=Application\n  Exec=~/etc/touchpad-config\n	Comment=Autostart touchpad daemon' > ~/.config/autostart/touchpad-config.desktop

install: all add_autostart
	mkdir -p /etc/touchpad-config
	mv ./touchpad-config /etc/touchpad-config/
