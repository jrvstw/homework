wget https://www.kernel.org/pub/linux/kernel/v2.6/linux-2.6.38.tar.bz2

sudo apt-get install fakeroot build-essential kernel-package libncurses5 libncurses5-dev

make mrproper
make menuconfig
make localmodconfig
make bzImage
make modules
sudo make modules_install
sudo make install

sudo vim /etc/default/grub
# GRUB_HIDDEN_TIMEOUT=10
# GRUB_HIDDEN_TIMEOUT_QUIET=true

sudo update-grub2
sudo shutdown -r now

uname -a
