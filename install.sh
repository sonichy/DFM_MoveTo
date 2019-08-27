s="[Desktop Entry]\nType=Application\nExec=`pwd`/MoveTo %u\nIcon=edit-cut\nName=移动到\nX-DFM-MenuTypes=SingleFile;SingleDir;MultiFileDirs;"
echo -e $s > MoveTo.desktop
sudo cp `pwd`/MoveTo.desktop /usr/share/deepin/dde-file-manager/oem-menuextensions/MoveTo.desktop
killall dde-file-manager dde-desktop dde-file-manager-daemon