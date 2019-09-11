s="[Desktop Entry]\nType=Application\nExec=`pwd`/MoveTo cut %U\nIcon=edit-cut\nName=移动到\nX-DFM-MenuTypes=SingleFile;SingleDir;MultiFileDirs;"
echo -e $s > MoveTo.desktop
sudo cp `pwd`/MoveTo.desktop /usr/share/deepin/dde-file-manager/oem-menuextensions/MoveTo.desktop
s="[Desktop Entry]\nType=Application\nExec=`pwd`/MoveTo copy %U\nIcon=edit-copy\nName=复制到\nX-DFM-MenuTypes=SingleFile;SingleDir;MultiFileDirs;"
echo -e $s > CopyTo.desktop
sudo cp `pwd`/CopyTo.desktop /usr/share/deepin/dde-file-manager/oem-menuextensions/CopyTo.desktop
killall dde-file-manager dde-desktop dde-file-manager-daemon