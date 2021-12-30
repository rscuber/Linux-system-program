#!/bin/bash
echo "This script will install and configure vim and zsh automatic."
echo "The time this takes is related to the network conditions, please wait patiently."
if [[ `whoami` == "root" ]];then
    echo -e "\033[31mYou are  running this script with Root\033[0m"
    echo -e "\033[31mGenerally, we do not recommend using root for programming or directly controlling your Linux OS, especially when you are a beginner \033[0m"
    echo -e "\033[31mSo, There is no necessary for you to configure with root."
    read -p "Do you really want to do this?[N/y]" choice
    if [[ ${choice} != y ]];then
    	echo "Bye."
    	exit 1
    fi
fi
if which apt-get >/dev/null; then
	sudo apt-get install -y vim vim-gnome ctags xclip astyle python-setuptools python-dev git wget
elif which yum >/dev/null; then
	sudo yum install -y gcc vim git ctags xclip astyle python-setuptools python-devel wget	
fi

##Add HomeBrew support on  Mac OS
if which brew >/dev/null;then
    echo "You are using HomeBrew tool"
    brew install vim ctags git astyle
fi

sudo easy_install -ZU autopep8 
sudo ln -s /usr/bin/ctags /usr/local/bin/ctags
rm -rf ~/vim* 2>&1 >/dev/null
rm -rf ~/.vim* 2>&1 >/dev/null
mv -f ~/vim ~/vim_old
cd ~/ && git clone https://gitee.com/suyelu/vim.git
mv -f ~/.vim ~/.vim_old 2>&1 >/dev/null
mv -f ~/vim ~/.vim 2>&1 >/dev/null
mv -f ~/.vimrc ~/.vimrc_old 2>&1 >/dev/null
mv -f ~/.vim/.vimrc ~/ 
git clone https://gitee.com/suyelu/vundle.git ~/.vim/bundle/vundle
echo "程序正在自动安装相应插件" > kaikeba
echo "command-t插件需要等待时间较长，不要担心" >> kaikeba
echo "建议你掏出手机拍下以下内容：" >> kaikeba
echo "  经过多次测试，command-t插件最后可能会报错，但是实际上却安装上了；" >> kaikeba
echo "你可以在安装完成后，执行\`vim\`命令，并直接输入:BundleInstall,回车，来重新开始安装。" >> kaikeba
echo "你会发现，所有任务会瞬间完成。当然，如果真的没有安装成功，上面的命令也会重新安装未完成的插件。" >> kaikeba
echo "安装完毕将自动退出" >> kaikeba
echo "请耐心等待" >> kaikeba
vim kaikeba -c "BundleInstall" -c "q" -c "q"
rm kaikeba
echo "安装完成"

