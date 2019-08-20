#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>

void cut(QString source, QString Dir)
{
    QString dest = Dir + "/" + QFileInfo(source).fileName();
    if(QFileInfo(source).isSymLink()){
        QString symLinkTarget = QFileInfo(source).symLinkTarget();
        QFile file(symLinkTarget);
        if(!file.link(dest)){
            QMessageBox::critical(NULL, "错误", symLinkTarget + "\n创建链接\n" + dest + "\n失败！");
            return;
        }
        if(!QFile::remove(source)){
            QMessageBox::critical(NULL, "错误", "无法删除剪切的源文件 " + source, QMessageBox::Ok);
            return;
        }
    }else{
        if(!QFile::copy(source, dest)){
            QMessageBox::StandardButton SB = QMessageBox::warning(NULL, "覆盖", "是否覆盖 " + dest + " ?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
            if(SB == QMessageBox::Yes){
                if(!QFile::remove(dest)){
                    QMessageBox::critical(NULL, "错误", "无法覆盖新文件 " + dest);
                }
                if(QFile::copy(source, dest)){
                    QFile::remove(source);
                }else{
                    QMessageBox::critical(NULL, "错误", "粘贴失败！");
                }
            }else if(SB == QMessageBox::No){
                dest =  Dir + "/副本-" + QFileInfo(dest).fileName();
                //qDebug() << "副本" << source << dest;
                if(!QFile::copy(source, dest)){
                    QMessageBox::critical(NULL, "错误", "粘贴失败！");
                }
            }
        }else{
            // 修改文件时间
            QFile file(dest);
            //qDebug() << "修改粘贴文件时间为原文件时间" <<
            file.setFileTime(QFileInfo(source).lastModified(), QFileDevice::FileModificationTime);

            if(!QFile::remove(source)){
                QMessageBox::critical(NULL, "错误", "无法删除剪切的源文件 " + source, QMessageBox::Ok);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString dir = QFileDialog::getExistingDirectory(NULL, "移动到", ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    QStringList args = QApplication::arguments();
    if(args.length() > 1 && dir != ""){
        for(int i=1; i<args.length(); i++){
            if(args.at(i).startsWith("file://")){
                QUrl url(args.at(i));
                cut(url.toLocalFile(), dir);
            }else{
                cut(args.at(i), dir);
            }
        }
        //args.removeFirst();
        //QMessageBox MB(QMessageBox::Information, "移动到", args.join("\n") + "\n移动到\n" + dir);
        //MB.exec();
    }
    //qApp->quit();
    //return a.exec();
    return 0;
}