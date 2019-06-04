#pre-requisites for installing genmake
*apt install devscripts 

#Dependencies
*apt-get install -y build-essential autoconf libtool libssl-dev gawk debhelper dh-systemd init-system-helpers pkg-config

#generate genmake file 
sudo ./create-deb-pkg.sh

#install deb package

sudo dpkg -i genmake_2.0_amd64.deb

#Uninstall deb package

sudo dpkg -r genmake
